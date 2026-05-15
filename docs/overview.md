# Architecture Overview

## What the program does

The raytracer reads a scene description file, fires one ray per pixel through a virtual camera, finds the closest primitive each ray hits, evaluates every light source at that hit point (including shadow tests), and writes the result to `output.ppm`.

---

## End-to-end pipeline

```
main.cpp
  └─ SceneParser        → parses the .cfg file into plain data structs (SceneData)
       └─ SceneBuilder  → converts SceneData into live objects (Scene)
            └─ Renderer → fires rays, computes colors, fills an Image
                 └─ PPMWriter → writes the Image to disk
```

### 1. `SceneParser` (`src/Scene/SceneParser.cpp`)

Uses **libconfig++** to read the `.cfg` file.  
Produces a `SceneData` struct — plain POD structs, no polymorphism, no heap allocation.  
Nothing here knows about rendering; it is purely an I/O layer.

### 2. `SceneBuilder` (`src/Scene/SceneBuilder.cpp`)

Converts `SceneData` into a `Scene` by instantiating the real objects:
- Calls `scene.addPrimitive(...)` for each shape
- Calls `scene.addLight(...)` for ambient, directional, and point lights
- Wraps primitives in `TransformedPrimitive` when the scene file specifies a transform

The `Scene` object owns all primitives and lights via `std::unique_ptr`.

### 3. `Renderer` (`src/Core/Renderer.cpp`)

Loops over every pixel, calls `camera.generateRay(x, y)`, then:

1. **`castRay`** — tests the ray against every primitive, returns the closest `Intersection`.
2. **`computeColor`** — for each light, calls `light->computeLight(intersection, viewDir, primitives)` and sums the results.

Colors are clamped to `[0, 255]` before being stored.

### 4. `PPMWriter` (`src/Core/PPMWriter.cpp`)

Writes the `Image` pixel buffer to a plain-text PPM file (`output.ppm`).

---

## Key data types

| Type | File | Purpose |
|---|---|---|
| `Ray` | `include/Math/Ray.hpp` | Origin + direction; `at(t)` returns a point |
| `Intersection` | `include/Core/Intersection.hpp` | Hit flag, distance, world point, normal, color |
| `Color` | `include/Core/Color.hpp` | RGB integers 0–255 with `clamp()` |
| `Vector3D` | `include/Math/Vector3D.hpp` | 3-component double vector with dot, length, normalize |
| `Scene` | `include/Scene/Scene.hpp` | Owns all primitives and lights |
| `Image` | `include/Core/Image.hpp` | 2-D pixel buffer |

---

## Design patterns in use

| Pattern | Where |
|---|---|
| **Factory** | `LightFactory`, `PrimitiveFactory` — create objects by string type |
| **Decorator** | `TransformedPrimitive` wraps any `IPrimitive` and applies a rigid transform |
| **Builder** | `SceneBuilder` assembles a `Scene` from a `SceneData` description |
| **Interface / Strategy** | `IPrimitive` and `ILight` decouple the renderer from concrete implementations |

---

## Module map

```
include/
  Core/         — Intersection, Color, Image, Renderer, PPMWriter, RaytracerError
  Math/         — Vector3D, Point3D, Ray
  Primitives/   — IPrimitive, Sphere, Plane, Cylinder, Cone, TransformedPrimitive
  Lights/       — ILight, AmbientLight, DirectionalLight, PointLight
  Transformation/ — ITransformation, Translation, Rotation, TransformationComposer
  Scene/        — Camera, Scene, SceneData, SceneParser, SceneBuilder
  Factory/      — LightFactory, PrimitiveFactory

src/            — mirrors include/ with .cpp implementations
scenes/         — .cfg scene files
docs/           — this documentation
tests/          — Criterion unit tests
```
