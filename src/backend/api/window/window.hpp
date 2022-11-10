#pragma once

#include "../webview.h"

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"

extern webview::webview w;
using namespace rapidjson;

namespace api {


    std::string SetWindowSize(std::string args) {

        // json arr = json::parse(args);

        // w.set_size(arr[0].get<std::uint16_t>(), arr[1].get<std::uint16_t>(),
        //            WEBVIEW_HINT_NONE);

        Document d;
        d.Parse(args.c_str());

        w.set_size(d[0].GetUint64(), d[1].GetUint64(), WEBVIEW_HINT_NONE);

        return JTrue;
    }

    std::string SetWindowTitle(std::string args) {

        Document d;
        d.Parse(args.c_str());

        w.set_title(d[0].GetString());

        return JTrue;
    }

    std::string CloseWindow(std::string args) noexcept {

        w.terminate();

        return JNoRet;
    }


}; // namespace api