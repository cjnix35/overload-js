#pragma once

#include "webview.h"

#include "window/window.hpp"
#include "filesystem/fs.hpp"

extern webview::webview w;

namespace api {


    void BindInit() noexcept {

        w.bind("win_setWindowSize", api::SetWindowSize);
        w.bind("win_setWindowTitle", api::SetWindowTitle);
        w.bind("win_closeWindow", api::CloseWindow);
        w.bind("fs_makeDir", api::MakeDirectory);
        w.bind("fs_readFile", api::ReadFile);
        w.bind("fs_writeFile", api::WriteFile);
        w.bind("fs_appendFile", api::AppendFile);
        w.bind("fs_removeFile", api::RemoveFile);
    }


}; // namespace api