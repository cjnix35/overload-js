#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "webview.h"

#include "def.hpp"
#include "misc.hpp"
#include "filesystem/fs.hpp"
#include "sys/os/os.hpp"
#include "sys/hardware/cpu.hpp"
#include "sys/hardware/display.hpp"
#include "sys/hardware/mem.hpp"

namespace over {

    using binding_t = std::function<void(std::string, std::string, void *)>;
    using sync_binding_t = std::function<std::string(std::string)>;

    class Application {

            using namespace rapidjson;

        private:
            void bind_init() noexcept;
            std::string SetWindowSize(std::string args);
            std::string SetWindowTitle(std::string args);
            std::string CloseWindow(std::string args) noexcept;
            std::string AsyncCPP(std::string args);
            webview::webview w;

        public:
            Application(bool debug = false, void *winptr = nullptr)
                : w(debug, winptr) {

                this->bind_init();
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

            void LoadResourcesFromFile(std::string filename);
            template <typename uint>
            void LoadResourcesFromMemory(std::uint8_t *buf, uint *buf_len);
            // std::string ResourcePath(std::string
            // res_name); Resource
            // GetResourceContent(std::string
            // res_name);

            bool set_signal(std::string signal, std::function<void()> f);
            // For C++
            std::string set_signal(std::string args);
            // For JS
            // List of all possible signals below
    };


}; // namespace over


/* "on-close" : execute function when window is terminated
 *
 *
 *
 *
 */

namespace over {


    void Application::set_title(std::string title) noexcept {

        w.set_title(title);
    }

    void Application::set_size(std::uint64_t x, std::uint64_t y) noexcept {

        w.set_size(x, y, WEBVIEW_HINT_NONE);
    }

    void Application::unbind(std::string func_name) {

        w.unbind(func_name);
    }

    void Application::navigate_url(const std::string url) {

        w.navigate(url);
    }

    void Application::navigate_file(const std::string file) {

        w.navigate("file://" + std::filesystem::absolute(file).u8string());
    }
    void Application::navigate_resource(const std::string res) {

        w.navigate_res("overload:" + res);
    }

    void Application::eval(const std::string js) {

        w.eval(js);
    }

    void Application::init(const std::string js) {

        w.init(js);
    }

    void Application::terminate() noexcept {

        w.terminate();
    }

    void Application::bind(const std::string &func_name,
                           over::sync_binding_t &func) {

        w.bind(func_name, func);
    }

    void Application::run() {

        w.run();
    }

    void *Application::window() {

        return w.window();
    }

    void Application::dispatch(std::function<void()> f) {

        w.dispatch(f);
    }

    std::string Application::SetWindowSize(std::string args) {

        Document d;
        d.Parse(args.c_str());

        w.set_size(d[0].GetUint64(), d[1].GetUint64(), WEBVIEW_HINT_NONE);

        return JTrue;
    }

    std::string Application::SetWindowTitle(std::string args) {

        Document d;
        d.Parse(args.c_str());

        w.set_title(d[0].GetString());

        return JTrue;
    }

    std::string Application::CloseWindow(std::string args) noexcept {

        w.terminate();

        return JNoRet;
    }

    template <typename uint>
    void Application::LoadResourcesFromMemory(std::uint8_t *buf,
                                              uint *buf_len) {

        load_resource_mem(buf, buf_len);
    }

    void Application::LoadResourcesFromFile(std::string filename) {

        load_resource_file(filename);
    }


    typedef std::string (*FnPtr)(std::string);
    std::map<std::string, FnPtr> Functions = {

        {"fs_makeDir", over::fs::MakeDir},
        {"fs_readFile", over::fs::ReadFile},
        {"fs_writeFile", over::fs::WriteFile},
        {"fs_appendFile", over::fs::AppendFile},
        {"fs_removeFile", over::fs::RemoveFile},
        {"fs_removeDir", over::fs::RemoveDir},
        {"fs_listDir", over::fs::ListDir},
        {"fs_absolutePath", over::fs::AbsolutePath},

        {"sys_version", over::sys::Version},
        {"sys_platform", over::sys::Platform},
        {"sys_cpuFrequency", over::sys::CPUFrequency},
        {"sys_cpuVendor", over::sys::CPUVendor},
        {"sys_cpuModel", over::sys::CPUModel},
        {"sys_displaySize", over::sys::GetDisplaySize},
        {"sys_totalPhysMemory", over::sys::GetTotalPhysicalMemory},
        {"sys_physMemoryUsage", over::sys::GetPhysicalMemoryUsage},
        {"sys_procPhysMemoryUsage", over::sys::GetProcPhysMemoryUsage},
        {"sys_totalVirtualMemory", over::sys::GetTotalVirtualMemory},
        {"sys_virtualMemoryUsage", over::sys::GetVirtualMemoryUsage},
        {"sys_procVirtualMemoryUsage", over::sys::GetProcVirtualMemoryUsage}};

    static std::string AsyncWithoutValueCPP(std::string args) {

        Document d;
        d.Parse(args.c_str());
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        const auto &Func = d[0].GetString();
        d.Erase(d.Begin());

        d.Accept(writer);

        args = buffer.GetString();

        std::thread(over::Functions[Func], args).detach();

        return JNoRet;
    }

    std::string Application::AsyncCPP(std::string args) {

        const auto lambda = [this](std::string function, std::string var,
                                   std::string args) -> void {
            std::string value = Functions[function](args);
            w.eval(var + " = " + value + ";");
        };


        Document d;
        d.Parse(args.c_str());

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        const auto &FunctionName = d[0].GetString();
        const auto &VariableName = d[d.Size() - 1].GetString();

        d.Erase(d.Begin());
        d.Erase(d.End() - 1);
        d.Accept(writer);

        args = buffer.GetString();

        std::thread(lambda, std::move(FunctionName), std::move(VariableName),
                    std::move(args))
            .detach();

        return JNoRet;
    }

    void Application::bind_init() noexcept {

        // Takes 2 arguments and resizes window
        // JS: function win_setWindowSize(width, height)
        w.bind("win_setWindowSize", [this](std::string args) -> std::string {
            return this->SetWindowSize(args);
        });

        // Takes 1 argument and changes title of window
        // JS: function win_setWindowTitle(title)
        w.bind("win_setWindowTitle", [this](std::string args) -> std::string {
            return this->SetWindowTitle(args);
        });

        // Doesn't take anything as argument. Simply closes the application
        // JS: function win_closeWindow()
        w.bind("win_closeWindow", [this](std::string args) -> std::string {
            return this->CloseWindow(args);
        });

        // Takes as argument function name (first argument) and any arguments
        // that is necessary for function
        // JS: function asyncWithoutValue()
        w.bind("asyncWithoutValue", over::AsyncWithoutValueCPP);

        // Takes as argument function name (first argument), all arguments
        // necessary for this function and variable name (last argument)
        // JS: function asyncWithValue()
        w.bind("asyncWithValue", [this](std::string args) -> std::string {
            return this->AsyncCPP(args);
        });

        // Takes as argument path where dir has to be created
        // JS: function fs_makeDir(path)
        w.bind("fs_makeDir", over::fs::MakeDir);

        // Takes path to file as argument and reads file
        // JS: function fs_readFile(filename)
        w.bind("fs_readFile", over::fs::ReadFile);

        // Takes 2 arguments: path to file and what to write. Writes provided
        // data in the provided file JS: function fs_writeFile(filename, data)
        w.bind("fs_writeFile", over::fs::WriteFile);

        // Do the same as function above, but if file exists, doesn't re-write
        // existing data in file. Instead write at the end of the file
        // JS:function fs_appendFile(filename, data)
        w.bind("fs_appendFile", over::fs::AppendFile);

        // Takes path to file as argument. Deletes file that is provided
        // JS: function fs_removeFile(filename)
        w.bind("fs_removeFile", over::fs::RemoveFile);

        // Do the same as function above, but can delete directory with files
        // JS: function fs_removeDir(dirname)
        w.bind("fs_removeDir", over::fs::RemoveDir);

        // Takes directory as argument. Lists directory and returns array of
        // files
        // JS: function fs_listDir(dirname)
        w.bind("fs_listDir", over::fs::ListDir);

        // Takes relative path as argument. Converts relative path to absolute
        // JS: function fs_absolutePath(path)
        w.bind("fs_absolutePath", over::fs::AbsolutePath);

        // Doesn't take any arguments. Returns system version, for example:
        // Linux (6.0.6-arch1-1)
        // JS: function sys_version()
        w.bind("sys_version", over::sys::Version);

        // Doesn't take any arguments. Returns system name in lowercase
        // JS: function sys_platform()
        w.bind("sys_platform", over::sys::Platform);

        // Doesn't take any arguments. Returns current CPU frequency in kHz
        // JS: function sys_cpuFrequency()
        w.bind("sys_cpuFrequency", over::sys::CPUFrequency);

        // Doesn't take any arguments. Returns CPU vendor
        // JS: function sys_cpuVendor()
        w.bind("sys_cpuVendor", over::sys::CPUVendor);

        // Doesn't take any arguments. Returns CPU model name
        // JS: function sys_cpuModel()
        w.bind("sys_cpuModel", over::sys::CPUModel);

        // Doesn't take any arguments. Returns display width and height in JSON
        // JS: function sys_displaySize()
        w.bind("sys_displaySize", over::sys::GetDisplaySize);

        // Doesn't take any arguments. Returns how much physical memory is
        // installed on current device
        // JS: function sys_totalPhysMemory()
        w.bind("sys_totalPhysMemory", over::sys::GetTotalPhysicalMemory);

        // Doesn't take any arguments. Returns how much physical memory is
        // currently in use
        // JS: function sys_totalPhysMemoryUsage()
        w.bind("sys_physMemoryUsage", over::sys::GetPhysicalMemoryUsage);

        // Doesn't take any arguments. Returns how much physical memory is
        // currently in use by this process
        // JS: function sys_procPhysMemoryUsage()
        w.bind("sys_procPhysMemoryUsage", over::sys::GetProcPhysMemoryUsage);

        // Doesn't take any arguments. Returns how much total virtual memory is
        // on current device
        // JS: function sys_totalVirtualMemory()
        w.bind("sys_totalVirtualMemory", over::sys::GetTotalVirtualMemory);

        // Doesn't take any arguments. Returns how much virtual memory is
        // currently in use
        // JS: function sys_virtualMemoryUsage()
        w.bind("sys_virtualMemoryUsage", over::sys::GetVirtualMemoryUsage);

        // Doesn't take any arguments. Returns how much virtual memory is
        // currently in use by this process
        // JS: function sys_procVirtualMemoryUsage()
        w.bind("sys_procVirtualMemoryUsage",
               over::sys::GetProcVirtualMemoryUsage);
    }


}; // namespace over