cmake_minimum_required(VERSION 3.25)
project(socket2)

set(CMAKE_CXX_STANDARD 17)

add_executable(socket2 main.cpp Server.h ClientHandler.h Server.cpp ClientHandler.cpp)
