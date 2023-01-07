#pragma once

#include "overload/misc.hpp"

#include <sstream>

namespace over {

    namespace sys {

        std::string Platform(std::string args);
        std::string Version(std::string args);

    }; // namespace sys

}; // namespace over

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#elif __linux__ || (__APPLE__ && __MACH__)

#include <sys/utsname.h>

#endif
