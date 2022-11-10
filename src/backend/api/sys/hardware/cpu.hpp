#pragma once

#include "../../misc.hpp"

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#elif __linux__

#include <sys/utsname.h>
#include <fstream>
#include <string>

#elif (__APPLE__ && __MACH__)

#include "../os/darwin.hpp"

#endif


namespace api {

    std::string CPUFrequency(std::string args);

    template <std::uint32_t IdentLen>
    static std::string CentralProcessorSubkey(const char* key);

    std::string CPUVendor(std::string args);

    std::string CPUModel(std::string args);


}; // namespace api
