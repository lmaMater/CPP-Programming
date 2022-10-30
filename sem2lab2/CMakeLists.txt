cmake_minimum_required(VERSION 3.20)
project(sem2lab2)

set(CMAKE_CXX_STANDARD 20)

set(libcurl_INCLUDE_DIR "C:/Users/NataYar/Desktop/curl-7.82.0-win32-mingw/include")
include_directories(${libcurl_INCLUDE_DIR})

add_executable(sem2lab2 main.cpp currency.h)

target_link_libraries(sem2lab2 C:/Users/NataYar/Desktop/curl-7.82.0-win32-mingw/lib/libcurl.dll.a)