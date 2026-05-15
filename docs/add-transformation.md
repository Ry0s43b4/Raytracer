# How to add a new transformation

Transformations move primitives in the world without changing their geometry. The system uses a **Decorator** pattern: `TransformedPrimitive` wraps any `IPrimitive` and applies a `TransformationComposer` (translation + rotation) to map rays from world space into the primitive's local space.

---

## How transformations work

Instead of moving the primitive, we move the **ray** in the opposite direction before calling `intersect`, then move the resulting hit point and normal back into world space.

```
World ray
   │
   ▼  TransformationComposer::worldToLocalRay()
Local ray  ──►  primitive->intersect()  ──►  local Intersection
   │
   ▼  localToWorldPoint() / localToWorldNormal()
World Intersection  ──►  Renderer
```

The `ITransformation` interface defines these three operations:

```cpp
// Bring a world-space ray into this transform's local space
virtual Ray transformRayWorldToLocal(const Ray &worldRay) const = 0;

// Bring a local point back into world space
virtual Math::Vector3D transformPointLocalToWorld(const Math::Vector3D &p) const = 0;

// Bring a local normal back into world space (rotation only, no translation)
virtual Math::Vector3D transformNormalLocalToWorld(const Math::Vector3D &n) const = 0;
```

---

## Step 1 — Create the header

Create `include/Transformation/MyTransform.hpp`:

```cpp
#pragma once
#include "Transformation/ITransformation.hpp"

namespace RayTracer {

class MyTransform : public ITransformation {
public:
    explicit MyTransform(/* parameters */);

    Ray transformRayWorldToLocal(const Ray &worldRay) const override;
    Math::Vector3D transformPointLocalToWorld(const Math::Vector3D &p) const override;
    Math::Vector3D transformNormalLocalToWorld(const Math::Vector3D &n) const override;

private:
    // your transform data
};

}
```

---

## Step 2 — Implement the three methods

Create `src/Transformation/MyTransform.cpp`.

The key contract:
- `transformRayWorldToLocal` applies the **inverse** of your transform to the ray.
- `transformPointLocalToWorld` applies the **forward** transform to a point.
- `transformNormalLocalToWorld` applies the **forward** rotation (normals are not affected by translation).

### Translation (reference implementation)

```cpp
// Inverse: subtract the offset from the ray origin
Ray Translation::transformRayWorldToLocal(const Ray &worldRay) const
{
    return Ray(worldRay.origin() - _offset, worldRay.direction());
}

// Forward: add the offset to the point
Vector3D Translation::transformPointLocalToWorld(const Vector3D &p) const
{
    return p + _offset;
}

// Normals are direction-only — translation has no effect
Vector3D Translation::transformNormalLocalToWorld(const Vector3D &n) const
{
    return n;
}
```

### Rotation (summary)

- `transformRayWorldToLocal` — rotate origin and direction by the **inverse** (transposed) rotation matrix.
- `transformPointLocalToWorld` — rotate the point by the **forward** rotation matrix.
- `transformNormalLocalToWorld` — same as point, using the forward rotation.

See `src/Transformation/Rotation.cpp` for the full Euler-angles (XYZ) implementation.

---

## Step 3 — Add it to `TransformationComposer`

`TransformationComposer` currently composes `Translation` then `Rotation`. If your new transform is independent (like Scale or Shear), you can add it as a third member:

In `include/Transformation/TransformationComposer.hpp`:

```cpp
#include "Transformation/MyTransform.hpp"

class TransformationComposer {
    // ...
private:
    Translation    _translation;
    Rotation       _rotation;
    MyTransform    _myTransform;   // add this
};
```

In `TransformationComposer::worldToLocalRay`, apply it in the right order:

```cpp
Ray TransformationComposer::worldToLocalRay(const Ray &worldRay) const
{
    Ray r = _translation.transformRayWorldToLocal(worldRay);
    r     = _rotation.transformRayWorldToLocal(r);
    r     = _myTransform.transformRayWorldToLocal(r);   // add this
    return r;
}
```

Do the same for `localToWorldPoint` and `localToWorldNormal` (in reverse order for point/normal).

---

## Step 4 — Expose it in the scene file

In `include/Scene/SceneData.hpp`, add fields to `TransformData`:

```cpp
struct TransformData {
    bool enabled = false;
    // existing
    double tx = 0.0, ty = 0.0, tz = 0.0;
    double rx = 0.0, ry = 0.0, rz = 0.0;
    // new
    double sx = 1.0, sy = 1.0, sz = 1.0;   // example: scale
};
```

In `SceneParser::parseTransformIfAny`, read the new block:

```cpp
if (tf.exists("scale")) {
    const libconfig::Setting &sc = tf.lookup("scale");
    out.sx = sc.lookup("x");
    out.sy = sc.lookup("y");
    out.sz = sc.lookup("z");
}
```

In `SceneBuilder` (e.g. `addSpheres`), pass the new data to `TransformationComposer`:

```cpp
// Before:
TransformationComposer pose(translation, euler);

// After (if TransformationComposer now takes a third arg):
TransformationComposer pose(translation, euler, scale);
```

---

## Scene file usage

```
primitives:
{
    spheres = (
        {
            x = 0.0; y = 0.0; z = 5.0; r = 1.0;
            color = { r = 200; g = 100; b = 50; };
            transform = {
                translation = { x = 1.0; y = 0.0; z = 0.0; };
                rotation    = { x = 0.0; y = 45.0; z = 0.0; };
                scale       = { x = 2.0; y = 1.0; z = 1.0; };  # new
            };
        }
    );
};
```

---

## Existing transforms for reference

| Class | What it does | Normal affected? |
|---|---|---|
| `Translation` | Shifts the primitive by an offset vector | No |
| `Rotation` | Rotates around X, Y, Z axes (Euler degrees) | Yes |
| `TransformationComposer` | Combines Translation + Rotation in one pose | — |

---

## Checklist

- [ ] `include/Transformation/MyTransform.hpp`
- [ ] `src/Transformation/MyTransform.cpp` — all three interface methods implemented correctly
- [ ] `TransformationComposer` updated to include the new transform
- [ ] `TransformData` struct updated in `SceneData.hpp`
- [ ] `parseTransformIfAny()` reads the new fields
- [ ] `SceneBuilder` passes the new data to `TransformationComposer`
