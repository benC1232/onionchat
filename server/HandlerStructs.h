
#ifndef SERVER_HANDLERSTRUCTS_H
#define SERVER_HANDLERSTRUCTS_H
#include <vector>
#include "IRequestHandler.h"
class IRequestHandler;

using Buffer = std::vector<unsigned char>;

struct RequestResult
{
    Buffer buffer;
    int bufferSize;
    IRequestHandler* newHandler;
};

struct RequestInfo
{
    unsigned char id;
    std::vector<unsigned char> buffer;
};



#endif //SERVER_HANDLERSTRUCTS_H
