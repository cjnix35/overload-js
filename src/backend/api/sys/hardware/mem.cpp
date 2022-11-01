#include "ram.hpp"

#ifdef _WIN32

namespace api {


    std::string GetTotalPhysicalMemory(std::string args) {

        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
        DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

        return std::to_string(totalPhysMem / 1024);
    }

    std::string GetPhysicalMemoryUsage(std::string args) {

        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
        DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;

        return std::to_string(physMemUsed / 1024);
    }

    std::string GetProcPhysMemoryUsage(std::string args) {

        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(),
                             (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
        SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

        return std::to_string(physMemUsedByMe / 1024);
    }

    std::string GetTotalVirtualMemory(std::string args) {

        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

        return std::to_string(totalVirtualMem / 1024);
    }

    std::string GetVirtualMemoryUsage(std::string args) {

        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&memInfo);
        DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
        DWORDLONG virtualMemUsed = memInfo.ullTotalPageFile -
                                   memInfo.ullAvailPageFile;

        return std::to_string(virtualMemUsed / 1024);
    }

    std::string GetProcVirtualMemoryUsage(std::string args) {

        PROCESS_MEMORY_COUNTERS_EX pmc;
        GetProcessMemoryInfo(GetCurrentProcess(),
                             (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
        SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

        return std::to_string(virtualMemUsedByMe / 1024);
    }


}; // namespace api

#elif __linux__

namespace api {


    std::uint64_t parseLine(char* line) {
        std::uint64_t i = strlen(line);
        const char* p = line;
        while (*p < '0' || *p > '9') p++;
        line[i - 3] = '\0';
        i = atoi(p);
        return i;
    }


    std::string GetTotalPhysicalMemory(std::string args) {

        struct sysinfo memInfo;

        sysinfo(&memInfo);

        std::uint64_t totalPhysMem = memInfo.totalram;
        totalPhysMem *= memInfo.mem_unit;

        return std::to_string(totalPhysMem / 1024);
    }

    std::string GetPhysicalMemoryUsage(std::string args) {

        struct sysinfo memInfo;

        sysinfo(&memInfo);

        std::uint64_t physMemUsed = memInfo.totalram - memInfo.freeram;
        physMemUsed *= memInfo.mem_unit;

        return std::to_string(physMemUsed / 1024);
    }

    std::string GetProcPhysMemoryUsage(std::string args) {

        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];

        while (fgets(line, 128, file) != NULL) {
            if (strncmp(line, "VmRSS:", 6) == 0) {
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return std::to_string(result);
    }

    std::string GetTotalVirtualMemory(std::string args) {

        struct sysinfo memInfo;

        sysinfo(&memInfo);

        long long totalVirtualMem = memInfo.totalram;
        totalVirtualMem += memInfo.totalswap;
        totalVirtualMem *= memInfo.mem_unit;

        return std::to_string(totalVirtualMem / 1024);
    }

    std::string GetVirtualMemoryUsage(std::string args) {

        struct sysinfo memInfo;

        sysinfo(&memInfo);

        std::uint64_t virtualMemUsed = memInfo.totalram - memInfo.freeram;
        virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
        virtualMemUsed *= memInfo.mem_unit;

        return std::to_string(virtualMemUsed / 1024);
    }

    std::string GetProcVirtualMemoryUsage(std::string args) {

        FILE* file = fopen("/proc/self/status", "r");
        int result = -1;
        char line[128];

        while (fgets(line, 128, file) != NULL) {
            if (strncmp(line, "VmSize:", 7) == 0) {
                result = parseLine(line);
                break;
            }
        }
        fclose(file);
        return std::to_string(result / 1024);
    }


}; // namespace api

#elif (__APPLE__ && __MACH__)

namespace api {


    std::string GetTotalPhysicalMemory(std::string args) {

        return "\"Memory library is not supported on MacOS.\"";
    }

    std::string GetPhysicalMemoryUsage(std::string args) {

        return "\"Memory library is not supported on MacOS.\"";
    }

    std::string GetProcPhysMemoryUsage(std::string args) {

        return "\"Memory library is not supported on MacOS.\"";
    }

    std::string GetTotalVirtualMemory(std::string args) {

        return "\"Memory library is not supported on MacOS.\"";
    }

    std::string GetVirtualMemoryUsage(std::string args) {

        return "\"Memory library is not supported on MacOS.\"";
    }

    std::string GetProcVirtualMemoryUsage(std::string args) {

        return "\"Memory library is not supported on MacOS.\"";
    }


}; // namespace api

#endif
