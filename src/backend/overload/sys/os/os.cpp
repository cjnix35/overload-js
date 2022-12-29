#include "os.hpp"

namespace api {


    std::string Platform(std::string args) {

#ifdef _WIN32
        return api::Quotes("windows");
#elif __APPLE__ || __MACH__
        return api::Quotes("darwin");
#elif __linux__
        return api::Quotes("linux");
#elif __FreeBSD__
        return api::Quotes("freebsd");
#else
        return api::Quotes("other");
#endif
    }


}; // namespace api

#ifdef _WIN32

namespace api {


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

        return api::Quotes("Windows " + stream.str());
    }


}; // namespace api

#elif __linux__ || (__APPLE__ && __MACH__)

namespace api {


    std::string Version(std::string args) {

        struct utsname buffer;

        if (uname(&buffer) != 0) {
            perror("uname");
            exit(EXIT_FAILURE);
        }

        return api::Quotes(std::string(buffer.sysname) + " (" +
                           std::string(buffer.release) + ")");
    }


}; // namespace api

#endif
