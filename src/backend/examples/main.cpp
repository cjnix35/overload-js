#include <fstream>
#include <cstdlib>
#include <iostream>

#include "../api/json.hpp"
#include "../api/webview.h"

using json = nlohmann::json;
webview::webview w(false, nullptr);

#include "../api/bind.hpp"

int main(int argc, char* argv[]) {

    api::BindInit();

    w.set_title("overload.js");
    w.set_size(1200, 700, WEBVIEW_HINT_NONE);
    w.navigate("file:" + std::filesystem::absolute("../dist/index.html").u8string());
    w.run();

    return 0;

} 
