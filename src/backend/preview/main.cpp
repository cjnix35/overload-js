#include <fstream>
#include <cstdlib>
#include <iostream>

#include "ui.hpp"

#include "../api/json.hpp"
#include "../api/webview.h"
#include "../api/watcher.hpp"

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

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif

    Interface.Load();
    api::BindInit();

    std::ifstream conf("window.json");
    json j = json::parse(conf);
    conf.close();

    w.set_title(j.at("title").get<std::string>());
    w.set_size(j.at("width").get<std::uint16_t>(), j.at("height").get<std::uint16_t>(), WEBVIEW_HINT_NONE);
    w.navigate("http://localhost:8080/");
    std::thread(WaitForChanges).detach();
    w.run();

    return 0;

} 
