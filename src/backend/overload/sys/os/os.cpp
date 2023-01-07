#include "os.hpp"

namespace over {

    namespace sys {

        std::string Platform(std::string args) {

#ifdef _WIN32
            return over::Quotes("windows");
#elif __APPLE__ || __MACH__
            return over::Quotes("darwin");
#elif __linux__
            return over::Quotes("linux");
#elif __FreeBSD__
            return over::Quotes("freebsd");
#else
            return over::Quotes("other");
#endif
        }

    }; // namespace sys


}; // namespace over

#ifdef _WIN32

namespace over {

    namespace sys {

        std::string Version(std::string args) {

            DWORD dwVersion = 0;
            DWORD dwMajorVersion = 0;
            DWORD dwMinorVersion = 0;
            DWORD dwBuild = 0;

            std::ostringstream stream;

            dwVersion = GetVersion();

            // Get the Windows version.

            dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));


            dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

            // Get the build number.

            if (dwVersion < 0x80000000) dwBuild = (DWORD)(HIWORD(dwVersion));

            stream << dwMajorVersion << "." << dwMinorVersion << " (" << dwBuild
                   << ")";

            return over::Quotes("Windows " + stream.str());
        }

    }; // namespace sys

}; // namespace over

#elif __linux__ || (__APPLE__ && __MACH__)

namespace over {

    namespace sys {

        std::string Version(std::string args) {

            struct utsname buffer;

            if (uname(&buffer) != 0) {
                perror("uname");
                exit(EXIT_FAILURE);
            }

            return over::Quotes(std::string(buffer.sysname) + " (" +
                                std::string(buffer.release) + ")");
        }

    }; // namespace sys

}; // namespace over

#endif
