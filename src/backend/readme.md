# Backend

## About backend

Overload.js mainly uses C++17 as backend. Backend is divided on three folders:

- `api/`
- `examples/`
- `preview/`

### API

Folder `api` contains all necessary libraries, overload.js headers and other necessary stuff. Usually, you do **not** need to touch something there.

### Examples

Folder `examples` contains simple example of production application using overload.js.

### Preview

Folder `preview` contains an application that we call **preview**. It's app that is used in development time. Main difference between **preview** and examples is live reload built-in **preview**. It means that if you change some frontend file, you don't need to restart or reload your application to see changes. Changes will be seen as soon as you save file you are changing.

## Compilation

Compilation can be done using `CMakeLists.txt` provided in root directory of this repository. Use these commands in root directory to compile this project:

```
mkdir build
cd build
cmake ..
make -j4
```

Congratulations! You've built overload.js.
