# How to add a new primitive

A primitive is any shape the renderer can intersect a ray with. Adding one requires touching five places.

---

## Step 1 — Create the header

Create `include/Primitives/MyShape.hpp`:

```cpp
#pragma once

#include "Primitives/IPrimitive.hpp"
#include "Math/Vector3D.hpp"
#include "Core/Color.hpp"

namespace RayTracer {

class MyShape : public IPrimitive {
public:
    MyShape(/* your parameters */, const Color &color);

    Intersection intersect(const Ray &ray) const override;

private:
    // your geometry fields
    Color _color;
};

}
```

The only method you **must** implement is `intersect`. Everything else is up to you.

---

## Step 2 — Implement `intersect`

Create `src/Primitives/MyShape.cpp`.

`intersect` receives a world-space `Ray` and must return an `Intersection`:

- **Miss** → return a default-constructed `Intersection()` (`hasHit() == false`).
- **Hit** → return `Intersection(true, distance, worldPoint, worldNormal, _color)`.

Rules for a valid hit:
- `distance` must be **positive** (in front of the ray origin). Discard negative or near-zero values.
- `worldPoint` is `ray.at(distance)` — i.e. `origin + direction * distance`.
- `worldNormal` must be a **unit vector** pointing outward from the surface.

Example (sphere) for reference:

```cpp
Intersection Sphere::intersect(const Ray &ray) const
{
    Math::Vector3D oc = ray.origin() - _center;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * oc.dot(ray.direction());
    double c = oc.dot(oc) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0)
        return Intersection();   // miss

    double t = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (t <= 0.001) {
        t = (-b + std::sqrt(discriminant)) / (2.0 * a);
        if (t <= 0.001)
            return Intersection();
    }

    Math::Vector3D point  = ray.at(t);
    Math::Vector3D normal = (point - _center).normalized();
    return Intersection(true, t, point, normal, _color);
}
```

---

## Step 3 — Add a data struct

In `include/Scene/SceneData.hpp`, add a struct for the raw config data:

```cpp
struct MyShapeData {
    double x, y, z;
    // any other fields your shape needs
    ColorData color;
    TransformData transform;   // include if your shape supports transforms
};
```

Then add a vector of it to `SceneData`:

```cpp
struct SceneData {
    // ...existing fields...
    std::vector<MyShapeData> myShapes;
};
```

---

## Step 4 — Parse it from the scene file

In `include/Scene/SceneParser.hpp`, declare a private parser method:

```cpp
std::vector<MyShapeData> parseMyShapes() const;
```

In `src/Scene/SceneParser.cpp`, implement it following the same pattern as `parseSpheres`:

```cpp
std::vector<MyShapeData> SceneParser::parseMyShapes() const
{
    std::vector<MyShapeData> result;

    if (!_config.exists("primitives.myshapes"))
        return result;

    const libconfig::Setting &settings = _config.lookup("primitives.myshapes");

    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &s = settings[i];
        MyShapeData shape;
        shape.x = s.lookup("x");
        shape.y = s.lookup("y");
        shape.z = s.lookup("z");
        shape.color = parseColor(s.lookup("color"));
        shape.transform = parseTransformIfAny(s);
        result.push_back(shape);
    }
    return result;
}
```

Then call it in `SceneParser::parse()`:

```cpp
data.myShapes = parseMyShapes();
```

---

## Step 5 — Instantiate it in SceneBuilder

In `src/Scene/SceneBuilder.cpp`, add an `#include` and a helper method:

```cpp
#include "Primitives/MyShape.hpp"

void SceneBuilder::addMyShapes(Scene &scene, const std::vector<MyShapeData> &shapes)
{
    for (const auto &s : shapes) {
        Color color(s.color.r, s.color.g, s.color.b);

        if (s.transform.enabled) {
            Math::Vector3D translation(s.x + s.transform.tx,
                                       s.y + s.transform.ty,
                                       s.z + s.transform.tz);
            Math::Vector3D euler(s.transform.rx, s.transform.ry, s.transform.rz);
            TransformationComposer pose(translation, euler);

            scene.addPrimitive(std::make_unique<TransformedPrimitive>(
                std::make_unique<MyShape>(/* local-space args */, color),
                pose
            ));
        } else {
            scene.addPrimitive(std::make_unique<MyShape>(
                Math::Vector3D(s.x, s.y, s.z),
                color
            ));
        }
    }
}
```

Call it from `SceneBuilder::build`:

```cpp
addMyShapes(scene, data.myShapes);
```

---

## Scene file usage

```
primitives:
{
    myshapes = (
        { x = 0.0; y = 0.0; z = 5.0;
          color = { r = 200; g = 100; b = 50; }; },
        { x = 2.0; y = 0.0; z = 5.0;
          color = { r = 50; g = 100; b = 200; };
          transform = {
              translation = { x = 0.0; y = 0.0; z = 0.0; };
              rotation    = { x = 0.0; y = 45.0; z = 0.0; };
          };
        }
    );
};
```

---

## Checklist

- [ ] `include/Primitives/MyShape.hpp`
- [ ] `src/Primitives/MyShape.cpp` — `intersect` returns valid distance, point, unit normal
- [ ] `MyShapeData` struct in `SceneData.hpp`
- [ ] `parseMyShapes()` in `SceneParser`
- [ ] `data.myShapes = parseMyShapes()` in `SceneParser::parse()`
- [ ] `addMyShapes()` in `SceneBuilder` + call in `build()`
