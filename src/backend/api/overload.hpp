#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#ifndef WEBVIEW_H
#include "webview.h"
#define WEBVIEW_H
#endif

#include "../def.hpp"
#include "misc.hpp"
#include "filesystem/fs.hpp"
#include "sys/os/os.hpp"
#include "sys/hardware/cpu.hpp"
#include "sys/hardware/display.hpp"
#include "sys/hardware/mem.hpp"

using namespace rapidjson;

namespace api {

    using binding_t = std::function<void(std::string, std::string, void *)>;
    using sync_binding_t = std::function<std::string(std::string)>;

    class OverApp {


        private:
            void bind_init() noexcept;
            std::string SetWindowSize(std::string args);
            std::string SetWindowTitle(std::string args);
            std::string CloseWindow(std::string args) noexcept;
            std::string AsyncCPP(std::string args);
            webview::webview w;


        public:
            OverApp(bool debug = false, void *winptr = nullptr)
                : w(debug, winptr) {
            }
            void run();

            void bind(const std::string &func_name, sync_binding_t &func);
            void unbind(std::string func_name);
            void set_title(std::string title) noexcept;
            void set_size(std::uint64_t x, std::uint64_t y) noexcept;
            void navigate_url(const std::string url);
            void navigate_file(const std::string file);
            void navigate_resource(const std::string res);
            void eval(const std::string js);
            void init(const std::string js);
            void terminate() noexcept;
            void *window();
            void dispatch(std::function<void()> f);

            bool set_signal(std::string signal, std::function<void()> f);
            // For C++
            std::string set_signal(std::string args);
            // For JS
            // List of all possible signals below
    };


}; // namespace api


/* "on-close" : execute function when window is terminated
 *
 *
 *
 *
 */