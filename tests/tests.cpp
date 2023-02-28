#include <iostream>
#include <os_name/os_name.hpp>

auto main() -> int
{
    std::cout << Cool::os_name() << '\n';
}