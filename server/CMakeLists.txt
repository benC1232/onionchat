cmake_minimum_required(VERSION 3.20)
project(server)

set(CMAKE_CXX_STANDARD 17)

add_executable(server main.cpp Communicator.cpp Communicator.h IRequestHandler.cpp IRequestHandler.h)
