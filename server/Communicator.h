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
#define PORT 5032
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
    void write();
    void read();
};


#endif //SERVER_COMMUNICATOR_H
