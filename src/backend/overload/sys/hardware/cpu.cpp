#include "cpu.hpp"

#ifdef _WIN32

namespace over {

    namespace sys {

        std::string CPUFrequency(std::string args) {

            HKEY hkey;
            if (RegOpenKeyExA(
                    HKEY_LOCAL_MACHINE,
                    R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)", 0,
                    KEY_READ, &hkey)) {
                LARGE_INTEGER freq;
                QueryPerformanceFrequency(&freq);
                return std::to_string(freq.QuadPart * 1'000);
            }

            DWORD freq_mhz;
            DWORD freq_mhz_len = sizeof(freq_mhz);
            if (RegQueryValueExA(
                    hkey, "~MHz", nullptr, nullptr,
                    static_cast<LPBYTE>(static_cast<void*>(&freq_mhz)),
                    &freq_mhz_len))
                return over::JNoRet;

            return std::to_string(freq_mhz);
        }

        template <std::uint32_t IdentLen>
        static std::string CentralProcessorSubkey(const char* key) {
            HKEY hkey;
            if (RegOpenKeyExA(
                    HKEY_LOCAL_MACHINE,
                    R"(HARDWARE\DESCRIPTION\System\CentralProcessor\0)", 0,
                    KEY_READ, &hkey))
                return {};

            char identifier[IdentLen];
            DWORD identifier_len = sizeof(identifier);
            LPBYTE lpdata = static_cast<LPBYTE>(
                static_cast<void*>(&identifier[0]));
            if (RegQueryValueExA(hkey, key, nullptr, nullptr, lpdata,
                                 &identifier_len))
                return {};

            return identifier;
        }

        std::string CPUVendor(std::string args) {
            return over::Quotes(
                CentralProcessorSubkey<12 + 1>("VendorIdentifier"));
        }

        std::string CPUModel(std::string args) {
            return over::Quotes(
                CentralProcessorSubkey<64 + 1>("ProcessorNameString"));
        }

    }; // namespace sys

}; // namespace over

#elif __linux__

namespace over {

    namespace sys {

        std::string CPUFrequency(std::string args) {

            std::ifstream f("/proc/cpuinfo");

            if (f.is_open()) {

                for (std::string tmp; std::getline(f, tmp);) {
                    if (tmp.find("cpu MHz") == 0) {
                        const auto colon_id = tmp.find_first_of(':');
                        return std::to_string(static_cast<std::uint64_t>(
                            std::strtod(tmp.c_str() + colon_id + 1, nullptr)));
                    }
                }
            }

            return over::JNoRet;
        }

        static std::string cpuinfo_value(const char* key) {
            std::ifstream f("/proc/cpuinfo");

            if (f.is_open()) {

                for (std::string line; std::getline(f, line);)
                    if (line.find(key) == 0) {
                        const auto colon_id = line.find_first_of(':');
                        const auto nonspace_id = line.find_first_not_of(
                            " \t", colon_id + 1);
                        return line.c_str() + nonspace_id;
                    }
            }
            return over::JNoRet;
        }


        std::string CPUVendor(std::string args) {
            return over::Quotes(cpuinfo_value("vendor"));
        }

        std::string CPUModel(std::string args) {
            return over::Quotes(cpuinfo_value("model name"));
        }

    }; // namespace sys

}; // namespace over

#elif (__APPLE__ && __MACH__)

namespace over {

    namespace sys {

        std::string CPUFrequency(std::string args) {

            const auto ctl_data = sysctl("hw.cpufrequency");
            if (ctl_data.empty()) return 0;

            const auto data = deconstruct_sysctl_int(ctl_data);
            if (!data.first) return 0;

            return std::to_string(data.second);
        }

        static std::string sysctl_value(const char* subkey) {
            auto ctl_data = sysctl(
                (std::string("machdep.cpu.") + subkey).c_str());
            if (ctl_data.empty()) return {};
            else return ctl_data.data();
        }

        std::string CPUVendor(std::string args) {
            return over::Quotes(sysctl_value("vendor"));
        }

        std::string CPUModel(std::string args) {
            return over::Quotes(sysctl_value("brand_string"));
        }

    }; // namespace sys

}; // namespace over

#endif
