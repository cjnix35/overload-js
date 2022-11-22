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

#include <archive.h>
#include <archive_entry.h>

#ifdef __linux__ //|| (__APPLE__ && __MACH__)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#elif _WIN32

#define WIN32_LEAN_AND_MEAN
#include <direct.h>
#define chdir _chdir

#endif

using namespace rapidjson;
using Resource = std::string;

namespace api {

    std::string MakeDir(std::string args);
    std::string ReadFile(std::string args);
    std::string WriteFile(std::string args);
    std::string AppendFile(std::string args);
    std::string RemoveFile(std::string args);
    std::string RemoveDir(std::string args);
    std::string ListDir(std::string args);
    std::string AbsolutePath(std::string args);

    static int copy_data(struct archive *ar, struct archive *aw);
    static int extract_file(const char *filename);
    static int extract_mem(std::uint8_t *buf, std::uint64_t buf_len);

    bool LoadResourcesFromFile(std::string filename);
    bool LoadResourcesFromMemory(std::uint8_t *buf, std::uint64_t *buf_len);
    std::string ResourcePath(std::string res_name);
    Resource GetResourceContent(std::string res_name);


}; // namespace api