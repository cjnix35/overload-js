#pragma once

#include <filesystem>
#include <fstream>
#include <sstream>

#include "../webview.h"
#include "../json.hpp"

extern webview::webview w;
using json = nlohmann::json;

namespace api {


    std::string MakeDirectory(std::string args){

        json arr = json::parse(args);
        std::string path = arr[0].get<std::string>();

        if (!std::filesystem::exists(path)){

            return std::filesystem::create_directory(path) ? "\"true\"" : "\"false\"";

        } else return "\"false\"";

    }

    std::string ReadFile(std::string args){

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();
        std::stringstream buf;

        std::ifstream f(filename, std::ios_base::in);
        if (f.is_open()) {

            buf << f.rdbuf();
            f.close();

            return "\"" + buf.str() + "\"";

        } else return "\"false\"";


    }

    std::string WriteFile(std::string args){

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();

        std::ofstream f(filename, std::ios_base::trunc);
        if (f.is_open()) {

            f << arr[1].get<std::string>();
            f.close();

            return "\"true\"";

        } else return "\"false\"";


    }

    std::string AppendFile(std::string args){

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();

        std::ofstream f(filename, std::ios_base::app);
        if (f.is_open()) {

            f << arr[1].get<std::string>();
            f.close();

            return "\"true\"";

        } else return "\"false\"";

    }

    std::string RemoveFile(std::string args){

        json arr = json::parse(args);
        std::string filename = arr[0].get<std::string>();

        return std::filesystem::remove(filename) ? "\"true\"" : "\"false\"";

    }


};