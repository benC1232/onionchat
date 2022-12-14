#ifndef SERVER_APICOMMUNICATOR_H
#define SERVER_APICOMMUNICATOR_H
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>

std::string getIpData(std::string ip);
std::string getResponseBody(std::string response);

#endif //SERVER_APICOMMUNICATOR_H
