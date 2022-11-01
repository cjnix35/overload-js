#pragma once

#include "webview.h"

#include "window/window.hpp"
#include "filesystem/fs.hpp"
#include "sys/os/os.hpp"
#include "sys/hardware/cpu.hpp"
#include "sys/hardware/display.hpp"
#include "sys/hardware/ram.hpp"

extern webview::webview w;

namespace api {


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

        // Takes as argument path where dir has to be created
        // JS: function fs_makeDir(path)
        w.bind("fs_makeDir", api::MakeDirectory);

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
        w.bind("sys_totalPhysMemoryUsage", api::GetPhysicalMemoryUsage);

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