#ifdef __APPLE__

#include "darwin.hpp"

template <class T>
static std::pair<bool, T>
    deconstruct_specific_int(const std::vector<char>& data) {
    std::pair<bool, T> out{true, {}};
    std::memcpy(&out.second, data.data(), sizeof(out.second));
    return out;
}


#define SYSCTL_IMPL(fname, ...)                                                \
    std::size_t len{};                                                         \
    if (fname(__VA_ARGS__, nullptr, &len, nullptr, 0)) return {};              \
                                                                               \
    std::vector<char> ret(len);                                                \
    if (fname(__VA_ARGS__, ret.data(), &len, nullptr, 0)) return {};           \
                                                                               \
    return ret;

std::vector<char> sysctl(const char* name) {
    SYSCTL_IMPL(::sysctlbyname, name);
}

std::vector<char> sysctl(int mib_0, int mib_1) {
    int name[2]{mib_0, mib_1};

    SYSCTL_IMPL(::sysctl, name, sizeof(name) / sizeof(*name));
}


std::pair<bool, std::uint64_t>
    deconstruct_sysctl_int(const std::vector<char>& data) {
    switch (data.size()) {
        case sizeof(std::uint16_t):
            return deconstruct_specific_int<std::uint16_t>(data);

        case sizeof(std::uint32_t):
            return deconstruct_specific_int<std::uint32_t>(data);

        case sizeof(std::uint64_t):
            return deconstruct_specific_int<std::uint64_t>(data);

        default: return {};
    }
}

#endif