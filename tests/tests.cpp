#include <stdlib.h>
#include <iostream>
#include <os_name/os_name.hpp>

auto main() -> int
{
    auto const& str = Cool::os_name();
    std::cout << str << '\n';

    if (str.find("Unknown") != std::string::npos)
        return EXIT_FAILURE; // Error if we failed to get the exact version.
    return EXIT_SUCCESS;
}