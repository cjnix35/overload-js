#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

#include "../api/json.hpp"

using json = nlohmann::json;

class WebUI {

    private:

        std::string *main_file = new std::string;
        std::string *path = new std::string;

        json *files = new json;

    public:

        WebUI();
        ~WebUI();
        void Load();
        std::string GetPath() noexcept;
        std::string GetMainFile() noexcept;


};
