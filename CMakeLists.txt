cmake_minimum_required(VERSION 3.30)
project(linux_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(linux_server
        src/linux_server.cpp
        src/Server.cpp
        src/Server.h
)
