#include <inotify-cpp/NotifierBuilder.h>
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "ui.hpp"

#include "../api/json.hpp"
#include "../api/webview.h"
#include "../api/watcher.hpp"

using namespace inotify;
using json = nlohmann::json;

webview::webview w(true, nullptr);
WebUI Interface;

#include "../api/bind.hpp"

void WaitForChanges(){

    using namespace water::watcher;
    watch(Interface.GetPath().c_str(), [](const event::event& this_event) {
        w.eval("window.location.reload()");
    });    

}

int main(int argc, char* argv[]) {

    Interface.Load();
    api::BindInit();

    std::ifstream conf("window.json");
    json j = json::parse(conf);
    conf.close();

    w.set_title(j.at("title").get<std::string>());
    w.set_size(j.at("width").get<std::uint16_t>(), j.at("height").get<std::uint16_t>(), WEBVIEW_HINT_NONE);
    w.navigate(Interface.GetMainFile());
    std::thread(WaitForChanges).detach();
    w.run();

    return 0;

} 
