
#ifndef SERVER_HANDLERSTRUCTS_H
#define SERVER_HANDLERSTRUCTS_H
#include <vector>
#include "IRequestHandler.h"
class IRequestHandler;

struct RequestResult
{
    unsigned char* buffer;
    int bufferSize;
    IRequestHandler* newHandler;
};

struct RequestInfo
{
    unsigned char id;
    unsigned char* buffer;
};

#endif //SERVER_HANDLERSTRUCTS_H
