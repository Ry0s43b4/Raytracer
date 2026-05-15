# Scene file format

Scene files use the **libconfig++** format (`.cfg`). Run the raytracer with:

```
./raytracer scenes/my_scene.cfg
```

Output is always written to `output.ppm` in the current directory.

---

## Camera

```
camera:
{
    resolution = { width = 800; height = 600; };
    position   = { x = 0.0; y = 0.0; z = 0.0; };
    rotation   = { x = 0.0; y = 0.0; z = 0.0; };  # Euler degrees
    fieldOfView = 72.0;                              # Horizontal FOV in degrees
};
```

`position` is the world-space origin of the camera.  
`rotation` tilts the camera (e.g. `x = 15.0` tilts it downward).  
`fieldOfView` controls the zoom level — lower values zoom in, higher zoom out.

---

## Primitives

All primitives support an optional `transform` block (see [Transforms](#transforms) below).

### Sphere

```
spheres = (
    { x = 0.0; y = 0.0; z = 5.0; r = 1.5;
      color = { r = 255; g = 64; b = 64; }; }
);
```

| Field | Type | Meaning |
|---|---|---|
| `x`, `y`, `z` | float | Center position |
| `r` | float | Radius |
| `color` | RGB | Surface color (0–255 per channel) |

### Plane

```
planes = (
    { axis = "Y"; position = -1.0;
      color = { r = 200; g = 200; b = 200; }; }
);
```

| Field | Type | Meaning |
|---|---|---|
| `axis` | `"X"`, `"Y"`, or `"Z"` | Normal direction of the plane |
| `position` | float | Offset along that axis |
| `color` | RGB | Surface color |

### Cylinder

```
cylinders = (
    { x = 0.0; y = 0.0; z = 5.0; axis = "Z"; r = 0.5;
      color = { r = 64; g = 200; b = 64; }; }
);
```

| Field | Type | Meaning |
|---|---|---|
| `x`, `y`, `z` | float | Position (or local origin when transformed) |
| `axis` | `"X"`, `"Y"`, or `"Z"` | Axis the cylinder runs along |
| `r` | float | Radius |
| `color` | RGB | Surface color |

### Cone

```
cones = (
    { x = 0.0; y = 0.0; z = 5.0; axis = "Y"; r = 1.0;
      min = -2.0; max = 0.0;
      color = { r = 64; g = 64; b = 220; }; }
);
```

| Field | Type | Meaning |
|---|---|---|
| `x`, `y`, `z` | float | Apex position |
| `axis` | `"X"`, `"Y"`, or `"Z"` | Axis the cone opens along |
| `r` | float | Half-angle scale |
| `min`, `max` | float | Clipping bounds along the axis |
| `color` | RGB | Surface color |

---

## Transforms

Any primitive (except `planes`) can carry an optional `transform` block:

```
{ x = 0.0; y = 0.0; z = 0.0; r = 1.0;
  color = { r = 200; g = 100; b = 50; };
  transform = {
      translation = { x = 2.0; y = 0.0; z = 0.0; };
      rotation    = { x = 0.0; y = 45.0; z = 0.0; };
  };
}
```

When `transform` is present, the `x`, `y`, `z` of the primitive become its **local** origin.  
The `translation` offsets it in world space; `rotation` angles are Euler degrees (XYZ order).

---

## Lights

```
lights:
{
    ambient = 0.2;   # Base brightness on all surfaces (0.0–1.0)
    diffuse = 0.8;   # Intensity multiplier for directional and point lights

    point = (
        { x = -3.0; y = 5.0; z = 1.0; }
    );

    directional = (
        { x = -1.0; y = -1.0; z = 1.0; }   # direction vector (not a position)
    );
};
```

### Ambient light

- Always present; controlled by the `ambient` scalar.
- Illuminates every surface uniformly — no shadows, no direction.
- `0.0` = pure black in shadow. `1.0` = full brightness everywhere.

### Directional light

- One entry per `{ x; y; z; }` in the `directional` array.
- `x`, `y`, `z` define the **direction** the light travels (not its position).
- Intensity is taken from the top-level `diffuse` value.
- Casts parallel shadows across the entire scene.

### Point light

- One entry per `{ x; y; z; }` in the `point` array.
- `x`, `y`, `z` define the **position** of the light source in world space.
- Intensity is taken from the top-level `diffuse` value.
- Casts shadows that diverge outward; objects behind the light are not shadowed.
- Multiple point lights are supported.

---

## Full example

```
camera:
{
    resolution  = { width = 800; height = 600; };
    position    = { x = 0.0; y = 2.0; z = -5.0; };
    rotation    = { x = 10.0; y = 0.0; z = 0.0; };
    fieldOfView = 72.0;
};

primitives:
{
    spheres = (
        { x = 0.0; y = 0.0; z = 6.0; r = 1.2;
          color = { r = 220; g = 60; b = 60; }; },
        { x = -2.5; y = 0.0; z = 7.0; r = 1.0;
          color = { r = 60; g = 200; b = 60; };
          transform = {
              rotation = { x = 0.0; y = 30.0; z = 0.0; };
          };
        }
    );

    planes = (
        { axis = "Y"; position = -1.2;
          color = { r = 180; g = 180; b = 180; }; }
    );
};

lights:
{
    ambient = 0.25;
    diffuse = 0.75;

    point = (
        { x = -4.0; y = 6.0; z = 1.0; }
    );

    directional = ();
};
```
