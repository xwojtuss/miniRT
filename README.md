# MINIRT

miniRT - a raytracer written in C that simulates the light path using the full Phong reflection model. It is able to render textures and normal maps on three different shapes - plane, sphere and cylinder.
This project uses minilibx, which is an X11 library designed for 42 students. The library is automatically cloned from github, configured and compiled.
The scene is loaded via a file with the extention .rt, the configuration is as follows (parameters like color, position and orientation are made up of three numbers delimited by a comma):
Only one ambient light:
```
A [brightness 0-1] [color in rgb]
```
Only one camera:
```
C [position] [orientation] [FOV]
```
At least one diffuse light:
```
L [position] [brightness 0-1] [color in rgb]
```
Optional:
Plane:
```
pl [position] [orientation] [color in rgb] [texture path (optional)] [normal map path (optional)] [ambient const 0-1 (optional)] [diffuse const 0-1 (optional)] [specular const 0-1 (optional)] [shininess const (optional)]
```
Sphere:
```
sp [position] [diameter] [color in rgb] [texture path (optional)] [normal map path (optional)] [ambient const 0-1 (optional)] [diffuse const 0-1 (optional)] [specular const 0-1 (optional)] [shininess const (optional)]
```
Cylinder:
```
cy [position] [orientation] [diameter] [height] [color in rgb] [texture path (optional)] [normal map path (optional)] [ambient const 0-1 (optional)] [diffuse const 0-1 (optional)] [specular const 0-1 (optional)] [shininess const (optional)]
```

## Getting Started

These instructions will help you get a copy of the project up and running.

### Dependencies

- gcc
- cc
- make
- X11 include files (package xorg)
- XShm extension must be present (package libxext-dev)
- Utility functions from BSD systems - development files (package libbsd-dev)

### Installing

1. Clone the repository:
```
git clone https://github.com/xwojtuss/miniRT.git
```

2. Navigate to the project directory:
```
cd miniRT
```

3. Run the make command to build the project:
```
make
```

## Running the project

You can pass different scenes to the program, the directory 'scenes' has some example scenes:
```
./miniRT [scene to run]
```

## Authors

* **Wojtek Kornatowski** - [xwojtuss](https://github.com/xwojtuss)
* **Uladzimir Kireyeu** - [neulad](https://github.com/neulad)
