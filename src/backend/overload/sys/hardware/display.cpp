#include "display.hpp"

#ifdef _WIN32

namespace over {

    namespace sys {

        std::string GetDisplaySize(std::string args) {

            RECT desktop;
            // Get a handle to the desktop window
            const HWND hDesktop = GetDesktopWindow();
            // Get the size of screen to the variable desktop
            GetWindowRect(hDesktop, &desktop);
            // The top left corner will have coordinates (0,0)
            // and the bottom right corner will have coordinates
            // (horizontal, vertical)

            return "{\"width\":" + std::to_string(desktop.right) +
                   ",\"height\":" + std::to_string(desktop.bottom) + "}";
        }

    }; // namespace sys

}; // namespace over

#elif __linux__

namespace over {

    namespace sys {

        std::string GetDisplaySize(std::string args) {

            if (getenv("WAYLAND_DISPLAY") != nullptr) {


            } else {
                GdkRectangle workarea = {0};
                gdk_monitor_get_workarea(
                    gdk_display_get_primary_monitor(gdk_display_get_default()),
                    &workarea);

                return "{\"width\":" + std::to_string(workarea.width) +
                       ",\"height\":" + std::to_string(workarea.height) + "}";
            }
        }

    }; // namespace sys

}; // namespace over

#elif (__APPLE__ && __MACH__)

namespace over {

    namespace sys {

        std::string GetDisplaySize(std::string args) {

            auto mainDisplayId = CGMainDisplayID();
            return "{\"width\":" +
                   std::to_string(CGDisplayPixelsWide(mainDisplayId)) +
                   ",\"height\":" +
                   std::to_string(CGDisplayPixelsHigh(mainDisplayId)) + "}";
        }

    }; // namespace sys

}; // namespace over

#endif
