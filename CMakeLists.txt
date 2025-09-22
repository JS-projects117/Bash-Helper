cmake_minimum_required(VERSION 3.5)
project(BashHelper C)

set(CMAKE_C_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(BashHelper main.c)

target_link_libraries(BashHelper ${GTK3_LIBRARIES})
