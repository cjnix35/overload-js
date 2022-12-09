#include "../api/webview.h"
#include "../api/overload.hpp"

overmain(argc, argv) {

    api::OverApp app(IS_DEBUG);

    app.set_title("Overload.js");
    app.set_size(1200, 700);
    app.navigate_url("http://localhost:8080");
    app.run();

    return 0;
}