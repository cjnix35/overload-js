#include <fstream>
#include <cstdlib>
#include <iostream>

#include "../api/json.hpp"
#include "../api/webview.h"

using json = nlohmann::json;

// If you want to compile production build, change 'true' on 'false'
const bool DEBUG = true;

webview::webview w(DEBUG, nullptr);

#include "../api/bind.hpp"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow) {
#else
int main(int argc, char* argv[]) {
#endif

    api::BindInit();

    w.set_title("Overload.js");
    w.set_size(1200, 700, WEBVIEW_HINT_NONE);

    // If you want to use static file, uncomment lines below and change path to
    // file

    w.navigate("file:" +
               std::filesystem::absolute("../dist/index.html").u8string());

    // If you want to use static file, comment line below

    // w.navigate("http://localhost:8080/");
    w.run();

    return 0;
}
