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
#define PORT 5032
#define MESSAGE_SIZE 65536
#define JSON_OFFSET 5
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
    void handleNewClient(int clientSocket);
    //helper functions for reading and writing to a socket
    RequestInfo read();
    void write(RequestResult message);
    int getJsonSize(char *buffer);
};


#endif //SERVER_COMMUNICATOR_H
