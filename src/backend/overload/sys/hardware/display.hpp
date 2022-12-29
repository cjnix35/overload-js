#pragma once

#ifdef _WIN32

#include <wtypes.h>

#elif __linux__

#include <gtk/gtk.h>

#elif (__APPLE__ && __MACH__)

#include <CoreGraphics/CGDisplayConfiguration.h>

#endif

#include "../../misc.hpp"

namespace over {


    std::string GetDisplaySize(std::string args);


}; // namespace over