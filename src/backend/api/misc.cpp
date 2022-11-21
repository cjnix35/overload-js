#include "misc.hpp"

namespace api {

    std::string Quotes(std::string args) noexcept {

        return '"' + args + '"';
    }

}; // namespace api