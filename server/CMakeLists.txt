cmake_minimum_required(VERSION 3.20)
project(server)

set(CMAKE_CXX_STANDARD 17 THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(server main.cpp Communicator.cpp Communicator.h IRequestHandler.cpp IRequestHandler.h HandlerStructs.h Server.cpp Server.h RequestHandler.cpp RequestHandler.h NodeData.h JsonResponsePacketSerializer.cpp JsonRequestPacketDeserializer.cpp JsonRequestPacketDeserializer.h LoginManager.cpp LoginManager.h IDataBase.cpp IDataBase.h IDataBase.h RequestHandlerFactory.cpp RequestHandlerFactory.h RequestHandlerFactory.h APICommunicator.h APICommunicator.cpp SqliteDataBase.cpp SqliteDataBase.h sqlite3.c sqlite3.h NodeRequestHandler.cpp NodeRequestHandler.h)
target_link_libraries(server PRIVATE Threads::Threads dl)
