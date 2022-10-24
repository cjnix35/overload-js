cmake_minimum_required(VERSION 3.13)

project(webcpp_template VERSION 1.0
        DESCRIPTION "Framework which allows you to combine together speed & efficiency of C++ and beauty of Web technologies"
        LANGUAGES CXX)

include(CheckIPOSupported)

set(BACKEND_PATH "src/backend" CACHE STRING "Path to backend")
set(EXAMPLE_PATH "src/backend/examples" CACHE STRING "Path to examples")
set(DEFAULT_BUILD_TYPE "Release" CACHE STRING "Define default build type")
set(PREVIEW_PATH "src/backend/preview" CACHE STRING "Path to preview app")

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

if (MSVC)
        add_compile_options(/O2 /Ot)
else()
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(GTK REQUIRED gtk+-3.0 webkit2gtk-4.0)
        add_compile_options(-Ofast)

        include_directories(${GTK_INCLUDE_DIRS})
        link_directories(${GTK_LIBRARY_DIRS})
        add_definitions(${GTK_CFLAGS_OTHER})

endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
        set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE
        STRING "Choose the type of build." FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()



add_library(ui STATIC "$CACHE{PREVIEW_PATH}/ui.cpp" "$CACHE{PREVIEW_PATH}/ui.hpp")
add_executable(preview "$CACHE{PREVIEW_PATH}/main.cpp")
add_executable(main "$CACHE{EXAMPLE_PATH}/main.cpp")

check_ipo_supported(RESULT result)
if(result)
  set_target_properties(preview PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  set_target_properties(main PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
  set_target_properties(ui PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

target_compile_features(ui PUBLIC cxx_std_17)
set_target_properties(ui PROPERTIES CXX_EXTENSIONS OFF)

target_compile_features(preview PUBLIC cxx_std_17)
set_target_properties(preview PROPERTIES CXX_EXTENSIONS OFF)

target_compile_features(main PUBLIC cxx_std_17)
set_target_properties(main PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(main PUBLIC ${BACKEND_PATH})

target_include_directories(preview PUBLIC ${BACKEND_PATH})
target_link_libraries(preview PUBLIC ui)
if (UNIX)
        target_link_libraries(preview PUBLIC ${GTK_LIBRARIES} inotify-cpp)
        target_link_libraries(main PUBLIC ${GTK_LIBRARIES})
endif()

file(WRITE "${CMAKE_BINARY_DIR}/window.json" 
"{\n"
"    \"title\": \"preview\",\n"
"    \"width\": 300,\n"
"    \"height\": 400\n"
"}"
)

file(WRITE "${CMAKE_BINARY_DIR}/layout.json"
"[\n"
"    {\n"
"        \"type\": \"folder\",\n"
"        \"path\": \"../dist/\"\n"
"    },\n"
"    {\n"
"        \"type\": \"file\",\n"
"        \"path\": \"../dist/index.html\"\n"
"    }\n"
"]"
)
