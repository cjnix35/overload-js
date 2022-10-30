#pragma once

#include "webview.h"
#include "json.hpp"

#include "window/window.hpp"
#include "filesystem/fs.hpp"

extern webview::webview w;
using json = nlohmann::json;

namespace api {


    void BindInit() noexcept {
            
        w.bind("SetWindowSize", api::SetWindowSize);
        w.bind("SetWindowTitle", api::SetWindowTitle); 
        w.bind("CloseWindow", api::CloseWindow);
        w.bind("MakeDir", api::MakeDirectory); 
        w.bind("ReadFile", api::ReadFile);
        w.bind("WriteFile", api::WriteFile);
        w.bind("AppendFile", api::AppendFile);
        w.bind("RemoveFile", api::RemoveFile);      

    }


};