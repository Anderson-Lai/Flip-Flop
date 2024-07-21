## Flip-Flop is an open-source hypixel skyblock auction flipping mod
As of now, it is windows only

### How to build:

#### First, install vcpkg
- git clone https://github.com/microsoft/vcpkg.git
- cd vcpkg
- .\bootstrap-vcpkg.bat
#### Add vcpkg as an environment variable
- open command prompt
- type in "setx VCPKG_ROOT_DIRECTORY path/to/vcpkg" (ensure you use '/' and not '\\' even on windows)
#### Install depdencies with vcpkg
- open command prompt
- cd path/to/vcpkg
- vcpkg install wxwidgets
- vcpkg install curl
- vcpkg integrate install
#### Build the project
- Run the following commands at the projects root directory
- mkdir build
- cd build
- cmake ..
- use visual studio to open the .sln file and press Ctrl + F5 to build