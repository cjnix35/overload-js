#include "overload.hpp"


namespace api {


    template <typename pointer>
    OverApp::OverApp(bool debug = false, pointer window = nullptr) {

        is_debug = debug;
        winptr = window;
    }

    ~OverApp::OverApp() {
    }

    void OverApp::set_title(std::string title) noexcept {

        w.set_title(title);
    }

    void OverApp::set_size(std::uint64_t x, std::uint64_t y) {

        w.set_size(x, y, WEBVIEW_HINT_NONE);
    }

    void OverApp::unbind(std::string func_name) {

        w.unbind(func_name);
    }

    void OverApp::navigate_url(const std::string url) {

        w.navigate(url);
    }

    void OverApp::navigate_file(const std::string file) {

        w.navigate("file://" + std::filesystem::absolute(file).u8string());
    }
    void OverApp::navigate_resource(const std::string res) {

        w.navigate(
            "file://" +
            std::filesystem::absolute("." APP_INTERNAL_NAME + res).u8string());
    }

    void OverApp::eval(const std::string js) {

        w.eval(js);
    }

    void OverApp::init(const std::string js) {

        w.init(js);
    }

    void OverApp::terminate() noexcept {

        w.terminate();
    }

    void OverApp::bind(std::string func_name, api::binding_t func) {

        w.bind(func_name, func);
    }

    void OverApp::run() {

        w.run();
    }

    void* OverApp::window() {

        return w.window();
    }

    void OverApp::dispatch(std::function<void()> f) {

        w.dispatch(f);
    }


}; // namespace api