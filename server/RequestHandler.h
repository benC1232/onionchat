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
    RequestResult login(RequestInfo requestInfo);
    RequestResult getRoute(RequestInfo requestInfo)
};


#endif //SERVER_REQUESTHANDLER_H
