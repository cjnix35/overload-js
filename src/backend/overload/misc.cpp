#include "misc.hpp"

namespace over {

    std::string Quotes(std::string args) noexcept {

        std::string result;
        result.push_back('"');
        result.append(args);
        result.push_back('"');
        return result;
    }

}; // namespace over