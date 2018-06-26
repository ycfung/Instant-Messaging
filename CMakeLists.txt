cmake_minimum_required(VERSION 3.10)

project(im)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/include/python3.6m)

link_directories(/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu)

set(CMAKE_CXX_FLAGS -L/usr/include/python3.6)

set(CMAKE_CXX_FLAGS -lpython3.6)


add_executable(im main.cpp BaseGroup.cpp BaseGroup.h Date.cpp Date.h BaseUser.cpp BaseUser.h something.h QQGroup.h QQGroup.cpp something.cpp)

target_link_libraries(im curses libpython3.6.so)
# Check out the directories before compiling





