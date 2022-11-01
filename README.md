![LOGO](https://github.com/cjnix35/overload-js/.github/LOGO.svg)

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![JavaScript](https://img.shields.io/badge/javascript-%23323330.svg?style=for-the-badge&logo=javascript&logoColor=%23F7DF1E)

[![build](https://github.com/cjnix35/overload-js/actions/workflows/test_compiling.yml/badge.svg)](https://github.com/cjnix35/overload-js/actions/workflows/test_compiling.yml)

### Overload.js enables you to create _blazingly fast_ desktop apps with beautiful React.js-powered UI and C++ on backend.

## Features

- Cross-platform
- Blazingly fast
- Access every bit of OS
- Create Beautiful UI
- Relatively lightweight

## Tech

#### Rendering libraries

- [Linux](https://github.com/torvalds/linux) -- [WebKitGTK](https://webkitgtk.org/)
- Windows -- [Microsoft Edge WebView2](https://learn.microsoft.com/en-us/microsoft-edge/webview2/)
- MacOS -- [Apple WebKit2](https://webkit.org/)

#### Frameworks and Libraries

- [React.js](https://reactjs.org/)
- [JSON C++ lib -- nlohmann::json](https://github.com/nlohmann/json)
- [Tailwind CSS](https://tailwindcss.com/)
- C++ 17

#### Build tools

- [Webpack](https://webpack.js.org/)
- [CMake](https://cmake.org/)
- [Babel](https://babeljs.io/)

#### Code prettifiers

- C++ -- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- JS/TS and other -- [Prettier](https://prettier.io/)

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
cmake ..
make -j4
```

#### Windows

```cmd
mkdir build
cd build
cmake ..
msbuild overload_js.sln -m /property:Configuration=Release
```

## Development

Сurrently Overload.js is under development, there is still a lot of work to be done.

Want to contribute? Great!

Contributions are welcome!

## License

MIT
