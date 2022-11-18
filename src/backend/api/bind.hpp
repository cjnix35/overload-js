#pragma once

#include "webview.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "misc.hpp"
#include "window/window.hpp"
#include "filesystem/fs.hpp"
#include "sys/os/os.hpp"
#include "sys/hardware/cpu.hpp"
#include "sys/hardware/display.hpp"
#include "sys/hardware/mem.hpp"

extern webview::webview w;
using namespace rapidjson;

namespace api {

    typedef std::string (*FnPtr)(std::string);
    std::map<std::string, FnPtr> Functions = {
        {"win_closeWindow", api::CloseWindow},

        {"fs_makeDir", api::MakeDir},
        {"fs_readFile", api::ReadFile},
        {"fs_writeFile", api::WriteFile},
        {"fs_appendFile", api::AppendFile},
        {"fs_removeFile", api::RemoveFile},
        {"fs_removeDir", api::RemoveDir},
        {"fs_listDir", api::ListDir},
        {"fs_absolutePath", api::AbsolutePath},

        {"sys_version", api::Version},
        {"sys_platform", api::Platform},
        {"sys_cpuFrequency", api::CPUFrequency},
        {"sys_cpuVendor", api::CPUVendor},
        {"sys_cpuModel", api::CPUModel},
        {"sys_displaySize", api::GetDisplaySize},
        {"sys_totalPhysMemory", api::GetTotalPhysicalMemory},
        {"sys_physMemoryUsage", api::GetPhysicalMemoryUsage},
        {"sys_procPhysMemoryUsage", api::GetProcPhysMemoryUsage},
        {"sys_totalVirtualMemory", api::GetTotalVirtualMemory},
        {"sys_virtualMemoryUsage", api::GetVirtualMemoryUsage},
        {"sys_procVirtualMemoryUsage", api::GetProcVirtualMemoryUsage}};

    std::string AsyncWithoutValueCPP(std::string args) {

        Document d;
        d.Parse(args.c_str());
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        std::string Func = d[0].GetString();
        d.Erase(d.Begin());

        d.Accept(writer);

        args = buffer.GetString();

        std::thread(api::Functions[Func], args).detach();

        return JNoRet;
    }

    std::string AsyncCPP(std::string args) {

        const auto lambda = [](std::string function, std::string var,
                               std::string args) -> void {
            std::string value = Functions[function](args);
            w.eval(var + " = " + value + ";");
        };


        Document d;
        d.Parse(args.c_str());

        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);

        std::string FunctionName = d[0].GetString();
        std::string VariableName = d[d.Size() - 1].GetString();

        d.Erase(d.Begin());
        d.Erase(d.End() - 1);
        d.Accept(writer);

        args = buffer.GetString();

        std::thread(lambda, std::move(FunctionName), std::move(VariableName),
                    std::move(args))
            .detach();

        return JNoRet;
    }

    void BindInit() noexcept {

        // Takes 2 arguments and resizes window
        // JS: function win_setWindowSize(width, height)
        w.bind("win_setWindowSize", api::SetWindowSize);

        // Takes 1 argument and changes title of window
        // JS: function win_setWindowTitle(title)
        w.bind("win_setWindowTitle", api::SetWindowTitle);

        // Doesn't take anything as argument. Simply closes the application
        // JS: function win_closeWindow()
        w.bind("win_closeWindow", api::CloseWindow);

        // Takes as argument function name (first argument) and any arguments
        // that is necessary for function
        // JS: function asyncWithoutValue()
        w.bind("asyncWithoutValue", api::AsyncWithoutValueCPP);

        // Takes as argument function name (first argument), all arguments
        // necessary for this function and variable name (last argument)
        // JS: function asyncWithValue()
        w.bind("asyncWithValue", api::AsyncCPP);

        // Takes as argument path where dir has to be created
        // JS: function fs_makeDir(path)
        w.bind("fs_makeDir", api::MakeDir);

        // Takes path to file as argument and reads file
        // JS: function fs_readFile(filename)
        w.bind("fs_readFile", api::ReadFile);

        // Takes 2 arguments: path to file and what to write. Writes provided
        // data in the provided file JS: function fs_writeFile(filename, data)
        w.bind("fs_writeFile", api::WriteFile);

        // Do the same as function above, but if file exists, doesn't re-write
        // existing data in file. Instead write at the end of the file
        // JS:function fs_appendFile(filename, data)
        w.bind("fs_appendFile", api::AppendFile);

        // Takes path to file as argument. Deletes file that is provided
        // JS: function fs_removeFile(filename)
        w.bind("fs_removeFile", api::RemoveFile);

        // Do the same as function above, but can delete directory with files
        // JS: function fs_removeDir(dirname)
        w.bind("fs_removeDir", api::RemoveDir);

        // Takes directory as argument. Lists directory and returns array of
        // files
        // JS: function fs_listDir(dirname)
        w.bind("fs_listDir", api::ListDir);

        // Takes relative path as argument. Converts relative path to absolute
        // JS: function fs_absolutePath(path)
        w.bind("fs_absolutePath", api::AbsolutePath);

        // Doesn't take any arguments. Returns system version, for example:
        // Linux (6.0.6-arch1-1)
        // JS: function sys_version()
        w.bind("sys_version", api::Version);

        // Doesn't take any arguments. Returns system name in lowercase
        // JS: function sys_platform()
        w.bind("sys_platform", api::Platform);

        // Doesn't take any arguments. Returns current CPU frequency in kHz
        // JS: function sys_cpuFrequency()
        w.bind("sys_cpuFrequency", api::CPUFrequency);

        // Doesn't take any arguments. Returns CPU vendor
        // JS: function sys_cpuVendor()
        w.bind("sys_cpuVendor", api::CPUVendor);

        // Doesn't take any arguments. Returns CPU model name
        // JS: function sys_cpuModel()
        w.bind("sys_cpuModel", api::CPUModel);

        // Doesn't take any arguments. Returns display width and height in JSON
        // JS: function sys_displaySize()
        w.bind("sys_displaySize", api::GetDisplaySize);

        // Doesn't take any arguments. Returns how much physical memory is
        // installed on current device
        // JS: function sys_totalPhysMemory()
        w.bind("sys_totalPhysMemory", api::GetTotalPhysicalMemory);

        // Doesn't take any arguments. Returns how much physical memory is
        // currently in use
        // JS: function sys_totalPhysMemoryUsage()
        w.bind("sys_physMemoryUsage", api::GetPhysicalMemoryUsage);

        // Doesn't take any arguments. Returns how much physical memory is
        // currently in use by this process
        // JS: function sys_procPhysMemoryUsage()
        w.bind("sys_procPhysMemoryUsage", api::GetProcPhysMemoryUsage);

        // Doesn't take any arguments. Returns how much total virtual memory is
        // on current device
        // JS: function sys_totalVirtualMemory()
        w.bind("sys_totalVirtualMemory", api::GetTotalVirtualMemory);

        // Doesn't take any arguments. Returns how much virtual memory is
        // currently in use
        // JS: function sys_virtualMemoryUsage()
        w.bind("sys_virtualMemoryUsage", api::GetVirtualMemoryUsage);

        // Doesn't take any arguments. Returns how much virtual memory is
        // currently in use by this process
        // JS: function sys_procVirtualMemoryUsage()
        w.bind("sys_procVirtualMemoryUsage", api::GetProcVirtualMemoryUsage);
    }

}; // namespace api
