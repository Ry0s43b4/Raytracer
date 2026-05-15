# Writing a graphical plugin

This document explains how to add a new graphical backend (SDL, ncurses, OpenGL, an ASCII renderer, …) to the raytracer. The existing SFML plugin (`plugins/sfml/`) is the canonical example.

---

## How the plugin system works

The raytracer never links a graphical library directly. Instead, every backend is built as a **shared object** placed in `./plugin/`. At runtime:

1. `PluginManager` scans `./plugin/` for `*.so` (Linux) and `*.dylib` (macOS).
2. For each file, `DLLoader<IGraphical>` (which wraps `SharedLibrary`, our libdl encapsulation) opens the library and resolves two C entry points: `create` and `destroy`.
3. The launcher GUI shows each plugin in the right-hand column.
4. When the user picks one and clicks **Start**, the raytracer renders the scene and the chosen plugin displays it.

That means a new backend needs **three things**:

- a class deriving from `RayTracer::IGraphical`,
- a pair of `extern "C"` factory functions called `create` / `destroy`,
- a Makefile rule that produces a shared library in `./plugin/`.

---

## The `IGraphical` contract

Every plugin implements `include/Graphical/IGraphical.hpp`:

```cpp
namespace RayTracer {

class IGraphical {
public:
    virtual ~IGraphical() = default;

    virtual std::string name() const = 0;
    virtual void open(int width, int height, const std::string &title) = 0;
    virtual bool isOpen() const = 0;
    virtual bool pollEvents() = 0;
    virtual void display(const Image &image) = 0;
    virtual void close() = 0;
};

}
```

Method-by-method:

| Method | When it's called | Notes |
|---|---|---|
| `name()` | Once at discovery time, to label the entry in the launcher. | Cheap, must not open windows. |
| `open(w, h, title)` | Once, right before the first frame is shown. | Create the window/surface here. |
| `isOpen()` | Each iteration of the main loop. | Return `false` when the window is gone. |
| `pollEvents()` | Each iteration. | Pump events; return `false` if the user asked to quit (so the loop exits cleanly). |
| `display(image)` | Each iteration. | Copy `Image` pixels to the screen and flip the buffer. |
| `close()` | Once, when the loop exits. | Release every resource. The destructor will also call it as a safety net. |

The `Image` you receive is row-major `RayTracer::Color` (each channel `int 0–255`). Convert to whatever format your backend wants in `display()`.

---

## Step-by-step: a new plugin called `foo`

### 1. Create the plugin folder

```
plugins/foo/
├── FooDisplay.hpp
└── FooDisplay.cpp
```

### 2. Write the class

`plugins/foo/FooDisplay.hpp`:

```cpp
#pragma once

#include "Graphical/IGraphical.hpp"

namespace RayTracer {

class FooDisplay : public IGraphical {
public:
    FooDisplay();
    ~FooDisplay() override;

    std::string name() const override;
    void open(int width, int height, const std::string &title) override;
    bool isOpen() const override;
    bool pollEvents() override;
    void display(const Image &image) override;
    void close() override;

private:
    bool _running;
    int  _width;
    int  _height;
};

}
```

`plugins/foo/FooDisplay.cpp`:

```cpp
#include "FooDisplay.hpp"

#include <iostream>

namespace RayTracer {

FooDisplay::FooDisplay() : _running(false), _width(0), _height(0) {}
FooDisplay::~FooDisplay() { close(); }

std::string FooDisplay::name() const { return "Foo Display"; }

void FooDisplay::open(int w, int h, const std::string &title)
{
    _width = w;
    _height = h;
    _running = true;
    std::cout << "[foo] open " << title << " " << w << "x" << h << "\n";
    // ... allocate your backend's resources here.
}

bool FooDisplay::isOpen() const { return _running; }

bool FooDisplay::pollEvents()
{
    // Pump your event queue. Return false when the user requested to close.
    return _running;
}

void FooDisplay::display(const Image &image)
{
    // Push image pixels to your backend.
    (void)image;
}

void FooDisplay::close()
{
    if (_running) {
        std::cout << "[foo] close\n";
        _running = false;
    }
}

}

// ---- Plugin entry points: required, exact names ------------------------

extern "C" RayTracer::IGraphical *create()
{
    return new RayTracer::FooDisplay();
}

extern "C" void destroy(RayTracer::IGraphical *plugin)
{
    delete plugin;
}
```

The two `extern "C"` symbols **must** be named `create` and `destroy` — that's what `DLLoader<IGraphical>` looks up.

### 3. Add a Makefile rule

Copy the SFML recipe in `Makefile` and adjust the name and link flags:

```make
FOO_PLUGIN_SRC  = plugins/foo/FooDisplay.cpp
FOO_PLUGIN_NAME = $(PLUGIN_DIR)/libfoo_display.$(PLUGIN_EXT)

# add it to the list of plugins built by `make`
PLUGINS += $(FOO_PLUGIN_NAME)

$(FOO_PLUGIN_NAME): $(FOO_PLUGIN_SRC)
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -fPIC $(SHARED_FLAGS) \
		-Iinclude \
		-o $@ $(FOO_PLUGIN_SRC) \
		# add your backend's linker flags here, e.g. -lSDL2
```

Key flags:
- `-fPIC` — required for shared objects.
- `$(SHARED_FLAGS)` — expands to `-shared` (Linux) or `-dynamiclib` (macOS).
- The plugin must **not** link the raytracer's `.o` files; it only depends on the `IGraphical` header.

### 4. Build

```
make
```

That produces `./plugin/libfoo_display.so` (Linux) or `./plugin/libfoo_display.dylib` (macOS).

### 5. Launch

```
./raytracer            # or ./raytracer --gui
```

The launcher lists every plugin found under `./plugin/`. Pick a scene from the left column, your plugin from the right column, click **Start**.

---

## Lifecycle and ownership

- The plugin shared library stays mapped as long as **any instance returned by `create` is still alive**. `PluginManager` enforces this through a shared loader handle whose deleter calls `destroy`.
- Never `delete` an `IGraphical*` returned by another plugin's `create`. Always pair `create` and `destroy` from the same loader.
- A plugin's destructor will be called from the `destroy` C function, in the plugin's own translation unit — so virtual tables, statics and per-plugin globals are still valid there.

---

## Troubleshooting

| Symptom | Likely cause |
|---|---|
| Plugin doesn't appear in the launcher | Wrong extension (must be `.so` on Linux, `.dylib` on macOS), or file isn't in `./plugin/`. |
| `Skipping '…/libfoo.so': Failed to load symbol 'create'` | The factory symbols aren't named `create` / `destroy`, or you forgot `extern "C"`, or they're hidden by visibility flags. |
| Crash on exit / double free | Destroy function ran but the underlying library was already unmapped. Make sure you destroy every instance **before** the loader is closed (the framework handles this, but custom code that calls `loader.close()` manually must respect the order). |
| Plugin builds but crashes on `display()` | Most often a size mismatch — re-create your backend's pixel buffer/texture when `image.width()` or `image.height()` changes. |

---

## Reference

| File | What's in it |
|---|---|
| `include/Graphical/IGraphical.hpp` | Interface every plugin implements. |
| `include/Plugin/SharedLibrary.hpp` / `.cpp` | RAII libdl wrapper. |
| `include/Plugin/DLLoader.hpp` | Template that resolves `create` / `destroy` symbols. |
| `include/Plugin/PluginManager.hpp` / `.cpp` | Scans `./plugin/` and exposes the discovered backends. |
| `plugins/sfml/` | Reference implementation (SFML 3). |
