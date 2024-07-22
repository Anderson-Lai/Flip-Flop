## Flip-Flop is an open-source hypixel skyblock auction flipping mod
As of now, it is windows only

### How to build (run all commands in command prompt):
Ensure you already have cmake and a C++ compiler installed <br />
These steps use the MSVC C++ compiler <br />
Download cmake here: https://cmake.org/download/ <br />
<br />
Link to the library used to find profitable items to buy: https://github.com/Anderson-Lai/Pricing-Library <br />

#### First, install vcpkg
```
git clone https://github.com/microsoft/vcpkg.git
cd path/to/vcpkg
.\bootstrap-vcpkg.bat
```
#### Add vcpkg as an environment variable
```
setx VCPKG_ROOT_DIRECTORY path/to/vcpkg (ensure you use '/' and not '\\' even on windows)
```
#### Install depdencies with vcpkg
```
cd path/to/vcpkg
vcpkg install wxwidgets
vcpkg install curl
vcpkg integrate install
```
#### Build the project
Run the following commands at the project's root directory:
```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
