# mini-universe

Simulate interesting emergent 2D particle interactions with this simple-but-complex software written in C. Specify infinitely configurable seed states using configuration files. Render using symbols in a text-based command line or using actual pixels in OpenGL.

```
.----------------------------------------------------------------.
|                                              1 2     1         |
|                                            11141 11 1          |
|           1                           1   121113 111           |
|                                         1122 1  1  11          |
|                1                       1  21                   |
|                  1                  1    1 1                   |
|                                              1                 |
|                       11          1  1                         |
|             1                               1       1          |
|                      3 2       1                               |
|                    1 11 1   11 1  11      1                    |
|                        1 3113  13311111                        |
|                       1 2  27544654411 1         1             |
|                       11  32286a5896 21                        |
|                        1121326bdg9c661              1          |
|                       11  1 266dcc611221                       |
|       1               11  142145287 6141     1                 |
|                     1  13111122114213211                       |
|                   1111232 32213 211312      1                  |
|                     1  12    2  12 1        1   1              |
|                  1111                1        2                |
|                                                                |
|                                        1                       |
|                                                   1 2  1       |
|           1   1                                    3           |
|                 1                                 1   1        |
|                                                                |
|                                                 1  1           |
|1                                                               |
|                                              1                 |
|                                                                |
|                                                               1|
`----------------------------------------------------------------'
```

# Prerequisites

- CMake 3.25 or later
- a C99 compatible C compiler such as gcc or clang
- GLUT library

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
