#pragma once

#include "webview.h"
#include "../def.hpp"

namespace api {


    class OverApp {


        public:
            template <typename pointer>
            OverApp::OverApp(bool debug = false, pointer window = nullptr);
            ~OverApp::OverApp();
            void run();
            void bind();
            void set_title(std::string title) noexcept;
            void set_size(std::uint64_t x, std::uint64_t y) noexcept;
            void navigate(const std::string url);
            void eval(const std::string js);
            void init(const std::string js);
            void terminate() noexcept;
            void* window();
            void dispatch(std::function<void()> f);

            bool set_signal(std::string signal, std::function<void()> f);
            // For C++
            std::string set_signal(std::string args);
            // For JS
            // List of all possible signals below


        private:
            webview::webview w(debug, window);
            constexpr char* ApplicationData = [
                APP_NAME, APP_INTERNAL_NAME, VERSION, LICENSE, REFERENCE,
                DEBUG
            ];
    };


}; // namespace api


/* "on-close" : execute function when window is terminated
 *
 *
 *
 *
 */