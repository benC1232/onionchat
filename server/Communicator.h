#ifndef SERVER_COMMUNICATOR_H
#define SERVER_COMMUNICATOR_H
#include <map>
#include <thread>
#include <iostream>
#include <exception>
#include <fstream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include "IRequestHandler.h"
#include "HandlerStructs.h"
#include "RequestHandler.h"
#define PORT 60005
#define MESSAGE_SIZE 65536
#define JSON_OFFSET 5
#define SIGNOUT 215
#define ROUTE 150
class Communicator {
public:
    Communicator();
    ~Communicator();
    void startHandleRequests();
private:
    int m_serverSocket;
    std::vector<std::thread> threadVector;
    std::map<int, IRequestHandler*> m_clients;
    void bindAndListen();
    static void handleNewClient(int clientSocket, IRequestHandler* handler);
    //helper functions for reading and writing to a socket
    static RequestInfo read(int clientSock);
    static void write(RequestResult message, int clientSock);
    static int getJsonSize(const char *buffer);
};


#endif //SERVER_COMMUNICATOR_H
