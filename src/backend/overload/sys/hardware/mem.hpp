#pragma once

#include "overload/misc.hpp"

#include <cstring>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>


#elif __linux__

#include <sys/types.h>
#include <sys/sysinfo.h>
#include <cstdlib>
#include <string>

#elif (__APPLE__ && __MACH__)

#include <sys/sysctl.h>
#include <sys/types.h>

#endif

namespace over {

    namespace sys {

        std::string GetTotalPhysicalMemory(std::string args);

        std::string GetPhysicalMemoryUsage(std::string args);

        std::string GetProcPhysMemoryUsage(std::string args);

        std::string GetTotalVirtualMemory(std::string args);

        std::string GetVirtualMemoryUsage(std::string args);

        std::string GetProcVirtualMemoryUsage(std::string args);

    }; // namespace sys

}; // namespace over