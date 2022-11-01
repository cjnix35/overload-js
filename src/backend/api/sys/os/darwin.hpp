#ifdef __APPLE__

#include <cstdint>
#include <cstring>
#include <sys/sysctl.h>
#include <sys/types.h>

template <class T>
static std::pair<bool, T>
    deconstruct_specific_int(const std::vector<char>& data);

std::vector<char> sysctl(const char* name);

std::vector<char> sysctl(int mib_0, int mib_1);


std::pair<bool, std::uint64_t>
    deconstruct_sysctl_int(const std::vector<char>& data);

#endif