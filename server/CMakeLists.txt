cmake_minimum_required(VERSION 3.20)
project(server)

set(CMAKE_CXX_STANDARD 17 THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(server main.cpp Communicator.cpp Communicator.h IRequestHandler.cpp IRequestHandler.h HandlerStructs.h Server.cpp Server.h)
target_link_libraries(server PRIVATE Threads::Threads)
