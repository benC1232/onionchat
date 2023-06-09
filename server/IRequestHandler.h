#pragma once
#include "HandlerStructs.h"

class IRequestHandler {
public:
    virtual ~IRequestHandler() = default;
    virtual bool isRequestRelevant(RequestInfo request) = 0;
    virtual RequestResult handleRequest(RequestInfo request) = 0;
};


