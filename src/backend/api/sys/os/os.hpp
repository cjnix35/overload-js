#pragma once

#include "../../json.hpp"
#include "../../constants.hpp"

#include <sstream>

using json = nlohmann::json;

namespace api {


    std::string Platform(std::string args);
    std::string Version(std::string args);


}; // namespace api

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#elif __linux__ || (__APPLE__ && __MACH__)

#include <sys/utsname.h>

#endif
