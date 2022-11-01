#pragma once

#include "../webview.h"
#include "../json.hpp"

extern webview::webview w;
using json = nlohmann::json;

namespace api {


    std::string SetWindowSize(std::string args) {

        json arr = json::parse(args);

        w.set_size(arr[0].get<std::uint16_t>(), arr[1].get<std::uint16_t>(),
                   WEBVIEW_HINT_NONE);


        return "\"true\"";
    }

    std::string SetWindowTitle(std::string args) {

        json title = json::parse(args);

        w.set_title(title[0].get<std::string>());

        return "\"true\"";
    }

    std::string CloseWindow(std::string args) noexcept {

        w.terminate();

        return "";
    }


}; // namespace api