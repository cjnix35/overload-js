#pragma once

#include <string>

namespace over {

    std::string Quotes(std::string args) noexcept;

    constexpr auto JTrue = "\"true\"";
    constexpr auto JFalse = "\"false\"";
    constexpr auto JNoRet = "";


}; // namespace over

#if defined(_WIN32)
#define argc __argc
#define argv __argv
#define overmain(argc, argv)                                                   \
    int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,   \
                       int nCmdShow)
#elif defined(__linux__) || defined(__APPLE__) || defined(__FreeBSD__)
#define overmain(argc, argv) int main(int argc, char* argv[])
#endif
