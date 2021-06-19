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

## ATTENTION
Niestety z powodu blednego zapisania diagramy nie bylem w stanie dodawac do niego niektorych funkcji 
dlatego wprowadzam je tu. Odpowiadaja one za przelot drona oraz zwiad 

Klasa Drone

void Scouting(double angle, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[])

void GoForward(double angletemp, double lenght_of_path,PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[]);

void Orientation(double angle, double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[], const char *NamesFilesProper[];

void GoDownAndUp(double up_down,double angletemp, PzG::LaczeDoGNUPlota &Lacze, const char *NamesFilesLocal[],const char *NamesFilesProper[];

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
set(LIBRARY_NAME zad5_3)  # Default name for the library built from src/*.cpp (change if you wish)
```
* changes to zad5_3/tests/CMakeLists.txt with new files added, i.e.:
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

