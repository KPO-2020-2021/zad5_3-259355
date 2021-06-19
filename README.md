![Class Diagram](/Diagram3.png)
## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `make` to build the desired target.

Requirements: cmake, gnuplot, doxygen + dot

Example:

``` bash
> mkdir build && cd build
> cmake .. # options: -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release], Debug is default
> make
> ./main
> make test      # Makes and runs the tests.
> make coverage  # Generate a coverage report.
> make doc       # Generate html documentation.
```

Things to remember:
* changes to zad5_3/CMakeLists.txt with new files added, i.e.:

```cpp
# --------------------------------------------------------------------------------
#                         Locate files (change as needed).
# --------------------------------------------------------------------------------
set(SOURCES          # All .cpp files in src/
    src/example.cpp
    src/lacze_do_gnuplota
    src/matrix3.cpp
    src/vector3.cpp
    src/Prostopadl.cpp
    src/Drone.cpp
    src/GranBlock.cpp
    src/Block.cpp
    src/scena.cpp
    src/Cuboid_obstacle.cpp
    src/Piramid.cpp
    src/Mount_with_ridge.cpp
)
set(TESTFILES        # All .cpp files in tests/
    tests/test1.cpp
    TestMat3.cpp
    TestVec3.cpp
    TestVec2.cpp
    drones_tests.cpp
)
set(LIBRARY_NAME zad3)  # Default name for the library built from src/*.cpp (change if you wish)
```
* changes to zad5_2/tests/CMakeLists.txt with new files added, i.e.:
```cpp
# List all files containing tests. (Change as needed)
set(TESTFILES        # All .cpp files in tests/
    tests/test1.cpp
    TestMat3.cpp
    TestVec3.cpp
    TestVec2.cpp
    drones_tests.cpp
)
```
The `main.cpp` in the folder `tests` is needed. Only there we define `#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN`.

The main loop of the program is in the `app` folder.

