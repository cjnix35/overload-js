#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"

#include "../misc.hpp"

using namespace rapidjson;

namespace api {


    std::string MakeDir(std::string args);
    std::string ReadFile(std::string args);
    std::string WriteFile(std::string args);
    std::string AppendFile(std::string args);
    std::string RemoveFile(std::string args);
    std::string RemoveDir(std::string args);
    std::string ListDir(std::string args);
    std::string AbsolutePath(std::string args);


}; // namespace api