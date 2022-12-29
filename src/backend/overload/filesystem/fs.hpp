#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"

#include "../misc.hpp"

#include "../../def.hpp"

#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <direct.h>
#define chdir _chdir

#endif

namespace over {

    using namespace rapidjson;
    using Resource = std::string;

    std::string MakeDir(std::string args);
    std::string ReadFile(std::string args);
    std::string WriteFile(std::string args);
    std::string AppendFile(std::string args);
    std::string RemoveFile(std::string args);
    std::string RemoveDir(std::string args);
    std::string ListDir(std::string args);
    std::string AbsolutePath(std::string args);
    std::string exists(std::string args);
    Resource GetResourceContent(std::string res_name);


}; // namespace over