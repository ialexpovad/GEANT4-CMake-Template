# GEANT4-CMake-Template

A cross-platform C++ library template for simulation toolkit  GEANT4  in a regular CMake. [This](https://github.com/robotology/how-to-export-cpp-library) template was used as a basis for building a CMake project.

---

Here is an implementation of the [exampleB1](https://github.com/Geant4/geant4/tree/master/examples/basic/B1): this example demonstrates a very simple application where an energy deposit is accounted in user actions and their associated objects and a dose in a selected volume is calculated.


## Build the example
If your shell environment supports `mkdir`, you can just execute the following commands:

```shell
git clone https://github.com/ialexpovod/GEANT4-CMake-Template.git [your_name_project]
cd [your_name_project]
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```
Since GEANT4 can have only two types of configuration, you can specify either Release:
```
cmake ..-DCMAKE_BUILD_TYPE=Release /path/to/your/source 
```
or MinSizeRel:
```
cmake -DCMAKE_BUILD_TYPE=MinSizeRel /path/to/your/source
```
If you use the ROOT library in your project (Win32):
```
cmake .. -DWITH_ROOT=ON -DROOTSYS=C:/ROOT
```
If you use VS Code in the file `.vscode/settings.json` to build for example (Win32):
```
{
    "cmake.configureSettings": {
        "WITH_ROOT": "OFF",  // You can set it to "OFF" if you want to disable it
        "ROOTSYS": "C:/ROOT"
    }
}  
```