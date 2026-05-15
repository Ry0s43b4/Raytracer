# How to add a new light

A light computes the color contribution at a hit point, including optional shadow testing. Adding one requires touching four places.

---

## How lights work

For every rendered pixel that hits a surface, `Renderer::computeColor` iterates over all lights and calls:

```cpp
Color c = light->computeLight(intersection, viewDir, primitives);
```

The results are summed and clamped to `[0, 255]`. Each light is fully responsible for its own shadow logic — the renderer does not intervene.

The three arguments:

| Argument | Type | What it is |
|---|---|---|
| `intersection` | `const Intersection &` | Hit point, surface normal, base color |
| `viewDir` | `const Math::Vector3D &` | Unit vector from hit point toward the camera |
| `primitives` | `const vector<unique_ptr<IPrimitive>> &` | All scene primitives — used to cast shadow rays |

---

## Step 1 — Create the header

Create `include/Lights/MyLight.hpp`:

```cpp
#pragma once
#include "Lights/ILight.hpp"

namespace RayTracer {

class MyLight : public ILight {
public:
    MyLight(/* your parameters */);

    Color computeLight(
        const Intersection &intersection,
        const Math::Vector3D &viewDir,
        const std::vector<std::unique_ptr<IPrimitive>> &primitives
    ) const override;

private:
    // e.g. _position, _intensity, _color ...
};

}
```

---

## Step 2 — Implement `computeLight`

Create `src/Lights/MyLight.cpp`.

### Minimum — diffuse only (no shadows)

```cpp
Color MyLight::computeLight(
    const Intersection &intersection,
    const Math::Vector3D &/*viewDir*/,
    const std::vector<std::unique_ptr<IPrimitive>> &/*primitives*/
) const
{
    Math::Vector3D toLight = (_position - intersection.point()).normalized();
    double diff = std::max(0.0, intersection.normal().dot(toLight));

    const Color &c = intersection.color();
    return Color(
        static_cast<int>(c.r * diff * _intensity),
        static_cast<int>(c.g * diff * _intensity),
        static_cast<int>(c.b * diff * _intensity)
    );
}
```

### Adding shadow testing

Fire a shadow ray from the hit point toward the light. If any primitive lies in between, return black.

```cpp
static constexpr double SHADOW_EPSILON = 1e-4;

// Offset origin along the normal to avoid self-intersection
Math::Vector3D shadowOrigin = intersection.point()
                            + intersection.normal() * SHADOW_EPSILON;
Ray shadowRay(shadowOrigin, toLight);

for (const auto &primitive : primitives) {
    Intersection shadowHit = primitive->intersect(shadowRay);
    if (shadowHit.hasHit()
        && shadowHit.distance() > SHADOW_EPSILON
        && shadowHit.distance() < distToLight)   // stop at the light for point lights
        return Color(0, 0, 0);
}
```

For **directional lights** (infinitely far away), skip the `< distToLight` check — any occlusion casts a shadow.  
For **point lights**, always include it so objects behind the light do not block it.  
For **ambient light**, never do shadow testing — it represents indirect, omnidirectional light.

---

## Step 3 — Register it in `LightFactory`

In `include/Factory/LightFactory.hpp`, add the include:

```cpp
#include "Lights/MyLight.hpp"
```

In `src/Factory/LightFactory.cpp`, add a branch:

```cpp
if (type == "mylight")
    return std::make_unique<MyLight>(directionOrPosition, intensity);
```

---

## Step 4 — Wire it into `SceneBuilder`

### 4a — Add a data struct

In `include/Scene/SceneData.hpp`:

```cpp
struct MyLightData {
    double x, y, z;
    // any extra fields
};
```

Add a vector to `LightData`:

```cpp
struct LightData {
    // ...existing fields...
    std::vector<MyLightData> myLights;
};
```

### 4b — Parse from the scene file

In `SceneParser`, add a private method and call it from `parseLights()`:

```cpp
std::vector<MyLightData> SceneParser::parseMyLights() const
{
    std::vector<MyLightData> lights;
    if (!_config.exists("lights.mylight"))
        return lights;

    const libconfig::Setting &settings = _config.lookup("lights.mylight");
    for (int i = 0; i < settings.getLength(); ++i) {
        const libconfig::Setting &l = settings[i];
        MyLightData light;
        light.x = l.lookup("x");
        light.y = l.lookup("y");
        light.z = l.lookup("z");
        lights.push_back(light);
    }
    return lights;
}
```

### 4c — Instantiate in `SceneBuilder::addLights`

```cpp
#include "Lights/MyLight.hpp"

// inside addLights():
for (const auto &m : lights.myLights) {
    scene.addLight(std::make_unique<MyLight>(
        Math::Vector3D(m.x, m.y, m.z),
        lights.diffuse
    ));
}
```

---

## Scene file usage

```
lights:
{
    ambient = 0.2;
    diffuse = 0.8;

    mylight = (
        { x = 0.0; y = 10.0; z = 0.0; }
    );

    point       = ();
    directional = ();
};
```

---

## Existing lights for reference

| Class | Shadows | Direction |
|---|---|---|
| `AmbientLight` | No | N/A — uniform contribution |
| `DirectionalLight` | Yes (parallel rays) | Fixed world-space direction |
| `PointLight` | Yes (stops at light) | Computed per hit point from position |

---

## Checklist

- [ ] `include/Lights/MyLight.hpp`
- [ ] `src/Lights/MyLight.cpp` — `computeLight` with optional shadow ray
- [ ] `MyLightData` struct in `SceneData.hpp` + added to `LightData`
- [ ] `parseMyLights()` in `SceneParser` + called in `parseLights()`
- [ ] `addLights()` in `SceneBuilder` instantiates `MyLight`
- [ ] `LightFactory` handles `"mylight"` type string
