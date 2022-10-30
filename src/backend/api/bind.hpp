#pragma once

#include "webview.h"
#include "json.hpp"

#include "window/window.hpp"
#include "filesystem/fs.hpp"

extern webview::webview w;
using json = nlohmann::json;

namespace api {


    void BindInit() noexcept {

        w.bind("api_setWindowSize", api::SetWindowSize);
        w.bind("api_setWindowTitle", api::SetWindowTitle);
        w.bind("api_closeWindow", api::CloseWindow);
        w.bind("api_makeDir", api::MakeDirectory);
        w.bind("api_readFile", api::ReadFile);
        w.bind("api_writeFile", api::WriteFile);
        w.bind("api_appendFile", api::AppendFile);
        w.bind("api_removeFile", api::RemoveFile);
    }


}; // namespace api