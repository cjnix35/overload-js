#include "ui.hpp" // including class header

WebUI::WebUI() {
}

WebUI::~WebUI() {

    delete files;
    delete path;
    delete url;
}

void WebUI::Load() {

    std::fstream fstr("layout.json", std::ios_base::in);
    if (fstr.is_open()) {

        *files = json::parse(fstr);
        fstr.close();

    } else return;

    for (auto it = files->begin(); it != files->end(); ++it) {

        std::string type = (*it)["type"].get<std::string>();
        std::string provided_path = (*it)["path"].get<std::string>();

        if (type == "file") {

            *url = "file:" +
                   std::filesystem::absolute(provided_path).u8string();

        }

        else if (type == "folder") {

            *path = provided_path;
        }
    }
}

std::string WebUI::GetPath() noexcept {
    return *path;
}

std::string WebUI::GetUrl() noexcept {
    return *url;
}