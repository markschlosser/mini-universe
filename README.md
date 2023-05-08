# mini-universe

Simulate interesting emergent 2D particle interactions with this simple-but-complex software written in C. Specify infinitely configurable seed states using configuration files. Render using symbols in a text-based command line or using actual pixels in OpenGL.

# Prerequisites

- CMake 3.25 or later
- a C99 compatible C compiler such as gcc or clang
- GLUT library (only needed if you want to build an OpenGL version)

# Build

## Set up build directory structure and clone the repository

```
mkdir mini-universe-project
cd mini-universe-project
git clone https://github.com/markschlosser/mini-universe.git
```

## Build command line version

From within the `mini-universe-project` directory:

```
mkdir build-cli
cd build-cli
cmake ../mini-universe/src/cli
make
```

You can then run the `./mini-universe-cli` application.


## Build OpenGL version

From within the `mini-universe-project` directory:

```
mkdir build-gl
cd build-gl
cmake ../mini-universe/src/gl
make
```

You can then run the `./mini-universe-gl` application.

# Demo

https://user-images.githubusercontent.com/21339323/236710199-c8cec661-d30d-4820-930d-ad4806f4570e.mov
