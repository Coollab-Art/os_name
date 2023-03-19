cmake_minimum_required(VERSION 3.8)

set(WARNINGS_AS_ERRORS_FOR_OS_NAME OFF CACHE BOOL "ON iff you want to treat warnings as errors")

add_library(os_name)
add_library(os_name::os_name ALIAS os_name)
target_compile_features(os_name PUBLIC cxx_std_11)

# ---Add source files---
if(WARNINGS_AS_ERRORS_FOR_OS_NAME)
    target_include_directories(os_name PUBLIC include)
else()
    target_include_directories(os_name SYSTEM PUBLIC include)
endif()
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
target_sources(os_name PRIVATE ${SRC_FILES})

# ---Set warning level---
if(MSVC)
    target_compile_options(os_name PRIVATE /W4)
else()
    target_compile_options(os_name PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion)
endif()

# ---Maybe enable warnings as errors---
if(WARNINGS_AS_ERRORS_FOR_OS_NAME)
    if(MSVC)
        target_compile_options(os_name PRIVATE /WX)
    else()
        target_compile_options(os_name PRIVATE -Werror)
    endif()
endif()
