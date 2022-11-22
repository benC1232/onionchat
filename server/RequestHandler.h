#ifndef SERVER_REQUESTHANDLER_H
#define SERVER_REQUESTHANDLER_H

#include "IRequestHandler.h"
class RequestHandler : public IRequestHandler{
public:
    RequestHandler() = default;
    ~RequestHandler() = default;
    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;
private:
    //functions such as login signout and route request
};


#endif //SERVER_REQUESTHANDLER_H
