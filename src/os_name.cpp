#include <os_name/os_name.hpp>
#include <string>

#ifdef _WIN32

#include <Windows.h>
#include <vector>
#pragma comment(lib, "version.lib")

static auto os_name_impl() -> std::string
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

#endif // _WIN32

#ifdef __linux__

#include <fstream>

static auto os_name_impl() -> std::string
{
    std::ifstream os_release("/etc/os-release");

    std::string line;
    while (std::getline(os_release, line))
    {
        if (line.find("PRETTY_NAME=") != std::string::npos)
            return line.substr(line.find('=') + 1);
    }

    return "Linux (Unknown distribution)";
}

#endif // __linux__

#ifdef __APPLE__

#include <cstdlib>

static auto os_name_impl() -> std::string
{
    std::string os_version = "";
    std::string command    = "sw_vers -productVersion";
    FILE*       pipe       = popen(command.c_str(), "r");
    if (!pipe)
        return "MacOS (Unknown version)";
    char buffer[128];
    while (fgets(buffer, 128, pipe))
        os_version += buffer;
    pclose(pipe);
    os_version.erase(os_version.find_last_not_of('\n') + 1);
    return "MacOS " + os_version;
}

#endif // __APPLE__

#include <algorithm>
static auto remove_quotes(std::string str) -> std::string
{
    str.erase(std::remove(str.begin(), str.end(), '"'), str.end());
    return str;
}

namespace Cool {
auto os_name() -> std::string const&
{
    static std::string const name = remove_quotes(os_name_impl());
    return name;
}
} // namespace Cool