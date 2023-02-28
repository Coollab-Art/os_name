# os_name

## Usage

```cpp
std::string const name = Cool::os_name();
// Might return:
// "Windows 10.0.19041.2546"
// "Ubuntu 22.04.2 LTS"
// "MacOS 11.7.4"
```

Good to know: We cache the result so calling this function is extremely cheap after the first time.

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/os_name)
target_link_libraries(${PROJECT_NAME} PRIVATE os_name::os_name)
```

Then include it as:
```cpp
#include <os_name/os_name.hpp>
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
