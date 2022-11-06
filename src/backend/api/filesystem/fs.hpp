#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../json.hpp"

using json = nlohmann::json;

namespace api {


    std::string MakeDirectory(std::string args);
    std::string ReadFile(std::string args);
    std::string WriteFile(std::string args);
    std::string AppendFile(std::string args);
    std::string RemoveFile(std::string args);
    std::string RemoveDirectory(std::string args);
    std::string ListDirectory(std::string args);
    std::string AbsolutePath(std::string args);


}; // namespace api