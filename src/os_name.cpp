#include <os_name/os_name.hpp>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <vector>
#pragma comment(lib, "version.lib")

namespace Cool {

auto os_name() -> std::string
{
    static std::string const default_string = "Windows (Unknown version)";

    std::vector<BYTE> buffer;
    DWORD             version_size = GetFileVersionInfoSizeW(L"kernel32.dll", nullptr);
    if (version_size == 0)
        return default_string;

    buffer.resize(version_size);
    if (!GetFileVersionInfoW(L"kernel32.dll", 0, version_size, buffer.data()))
        return default_string;

    VS_FIXEDFILEINFO* file_info      = nullptr;
    UINT              file_info_size = 0;
    if (!VerQueryValueW(buffer.data(), L"\\", (LPVOID*)&file_info, &file_info_size))
        return default_string;

    if (file_info_size != sizeof(VS_FIXEDFILEINFO))
        return default_string;

    return "Windows " + std::to_string(HIWORD(file_info->dwProductVersionMS)) + "." + std::to_string(LOWORD(file_info->dwProductVersionMS)) + "." + std::to_string(HIWORD(file_info->dwProductVersionLS)) + "." + std::to_string(LOWORD(file_info->dwProductVersionLS));
}

} // namespace Cool
#endif // _WIN32

#ifdef __linux__

namespace Cool {

auto os_name() -> std::string
{
    struct utsname uts;
    uname(&uts);
    return uts.sysname;
}

} // namespace Cool

#endif // __linux__

#ifdef __APPLE__

namespace Cool {

auto os_name() -> std::string
{
    struct utsname uts;
    uname(&uts);
    return uts.sysname;
}

} // namespace Cool

#endif // __APPLE__