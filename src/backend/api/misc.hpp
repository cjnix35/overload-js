#pragma once

#include <string>

namespace api {

    std::string Quotes(std::string args) {

        return "\"" + args + "\"";
    }

    constexpr auto JTrue = "\"true\"";
    constexpr auto JFalse = "\"false\"";
    constexpr auto JNoRet = "";

}; // namespace api