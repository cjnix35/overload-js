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
cmake -GNinja ..
ninja -j 16
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

## How to use
In development, you may want to use development server for frontend. For this, you can simply use
```
app.navigate_url("http://localhost:8080/");
```
If you want to navigate to file, simply use
```
app.navigate_file("/path/to/file");
```
When building production build, you have to pack your `dist` folder into `asar` archive
```
npm run build
asar pack dist app.asar
mv app.asar build/app.asar
```
Note that you have to install `asar` utility first. After that, you have to create header that contains all the data from that archive using utility like `xxd`. This will create header file, that you have to include in your main .cpp file, and after that simply use
```
app.load_resources_from_memory(resource, &resource_len);
app.navigate_resource("filename_from_archive");
```