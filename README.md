# Raytracer

Raytracer is a project designed to recreate the 3D rendering technique called 'Raytracing'. It was developed in collaboration with André Frappier, Noah Heurtaut and Thomas Leboucq.

## 🚀 Features

* **3D Rendering:** Core implementation of the raytracing algorithm in C++.
* **Real-time Display:** Window management and pixel rendering powered by **SFML**.
* **Primitives:** Support for basic geometric shapes (spheres, planes, cylinders, cones).
* **Lighting:** Management of diffuse lights, specular highlights, shadows, and reflections.
* **Camera:** Custom camera positioning, direction, and Field of View (FOV) handling.

## 🛠️ Installation & Compilation

To build and run the project, you need a C++ compiler supporting **C++17** (like `g++` or `clang++`), `make`, and the **SFML** library.

### 1. Install SFML (Linux)
If you are on an Epitech environment or Ubuntu, install SFML using your package manager:
```bash
# Ubuntu / Debian / Epitech Dump
sudo apt-get install libsfml-dev

# Fedora
sudo dnf install SFML-devel
```

### 2. Clone & Compile
```bash
# Clone the repository
git clone https://github.com
cd Raytracer

# Compile the project
make
```

## 💻 Usage

Run the executable by passing your scene configuration file as an argument:

```bash
./raytracer [path_to_scene_file]
```

## 👥 Authors

* [**André Frappier**](https://github.com/AndreFRAPPIER)
* [**Noah Heurtaut**](https://github.com/noahhrt)
* [**Thomas Leboucq**](https://github.com/Zeusisss)
* [**Nicky Truong**](https://github.com/Ry0s43b4)
