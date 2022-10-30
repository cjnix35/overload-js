# Backend

## About backend

Overload.js mainly uses C++17 as backend. Backend is divided on three folders:

- `api/`
- `app/`

### API

Folder `api` contains all necessary libraries, overload.js headers and other necessary stuff. Usually, you do **not** need to touch something there.

### App

Folder `app` contains source files for basic overload.js app. It's app that is used in development time and for production build. For production build in function `webview::navigate()` you have to set path to main static file as argument. For development build you have to `http://localhost:8080/` as argument. By default `app` is configured to be used in development.

## Compilation

Compilation can be done using `CMakeLists.txt` provided in root directory of this repository. Use these commands in root directory to compile this project:

### Linux & MacOS
On Linux, you need `webkit2gtk-4.0` to compile this project. On MacOS, you need working XCode environment with `clang` or `g++` compiler. If you already have installed all dependencies, then this is how you can compile this framework:
```
mkdir build
cd build
cmake ..
make -j4
```
### Windows
On Windows, Visual Studio 2022 and above are supported. You also need `nuget` package manager set in `$PATH` environment:
```
mkdir build
cd build
cmake ..
msbuild overload_js.sln -m /property:Configuration=Release
```
Congratulations! You've built overload.js.
