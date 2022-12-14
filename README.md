<p align="center">
    <img src="https://github.com/cjnix35/overload-js/blob/main/LOGO.svg" alt="LOGO"/>
</p>

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![TypeScript](https://img.shields.io/badge/TypeScript-007ACC?style=for-the-badge&logo=typescript&logoColor=white)
![TailwindCSS](https://img.shields.io/badge/Tailwind_CSS-38B2AC?style=for-the-badge&logo=tailwind-css&logoColor=white)
![React](https://img.shields.io/badge/React-20232A?style=for-the-badge&logo=react&logoColor=61DAFB)

[![build](https://github.com/cjnix35/overload-js/actions/workflows/test_compiling.yml/badge.svg)](https://github.com/cjnix35/overload-js/actions/workflows/test_compiling.yml)

### Overload.js enables you to create _blazingly fast_ desktop apps with beautiful React.js-powered UI and C++ on backend.

## Features

- Unopinionated 
- Cross-platform
- Blazingly fast
- Access every bit of OS
- Create Beautiful UI
- Relatively lightweight

## Tech

#### Rendering libraries

|Linux|Windows|MacOS|
|-----|-------|-----|
|[WebKitGTK](https://webkitgtk.org/)|[Microsoft Edge WebView2](https://learn.microsoft.com/en-us/microsoft-edge/webview2/)|[Apple WebKit2](https://webkit.org/)|

#### Frameworks and Libraries

- [React.js](https://reactjs.org/)
- [Rapidjson](https://github.com/nlohmann/json)
- [Tailwind CSS](https://tailwindcss.com/)
- C++17

#### Build tools

- [Vite](https://vitejs.dev/)
- [CMake](https://cmake.org/)

#### Code prettifiers

- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- [Prettier](https://prettier.io/)

## Installation

Overload.JS requires [Node.js](https://nodejs.org/) and [Python](https://www.python.org/) to run.

**Ubuntu**

```sh
cd overload-js
npm i
sudo apt-get update && sudo apt-get install libwebkit2gtk-4.0-dev
```

**Windows**

- Install [Visual Studio 17 2022](https://visualstudio.microsoft.com/downloads/)
- Install [NuGet package manager](https://www.nuget.org/)
- Install [CMake](https://cmake.org/)

```cmd
cd overload-js
npm i
```

**MacOS**

```sh
cd overload-js
npm i
```

## Build

### Frontend

**development**

```sh
npm run dev
```

**production**

```sh
npm run build
```

### Backend

#### Linux/MacOS

```sh
mkdir build
cd build
cmake -GNinja ..
ninja -j 16
```

#### Windows

```cmd
mkdir build
cd build
cmake ..
msbuild overload_js.sln -m /property:Configuration=Release
```

## Development

#### **Overload.js is currently not ready for production use yet.**

??urrently Overload.js is under development, there is still a lot of work to be done. 

Want to contribute? Great!

Contributions are welcome!

## License

MIT
