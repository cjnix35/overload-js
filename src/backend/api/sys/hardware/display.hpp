#pragma once

#include "../../json.hpp"

using json = nlohmann::json;


#ifdef _WIN32

#include <wtypes.h>

#elif __linux__

#include <gtk/gtk.h>

#elif (__APPLE__ && __MACH__)

#include <CoreGraphics/CGDisplayConfiguration.h>

#endif

namespace api {


    std::string GetDisplaySize(std::string args);


}; // namespace api