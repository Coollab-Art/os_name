#pragma once
#include <string>

namespace Cool {

/// Returns the OS name and version.
/// We cache the result so calling this function is extremely cheap after the first time.
auto os_name() -> std::string const&;

} // namespace Cool
