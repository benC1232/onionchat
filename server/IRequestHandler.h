#ifndef SERVER_IREQUESTHANDLER_H
#define SERVER_IREQUESTHANDLER_H
#include "HandlerStructs.h"

class IRequestHandler {
public:
    virtual ~IRequestHandler() = default;
    virtual bool isRequestRelevant(RequestInfo request) = 0;
    virtual RequestResult handleRequest(RequestInfo request) = 0;
private:
    RequestResult RequestHandler::login(RequestInfo requestInfo);
    RequestResult RequestHandler::getRoute(RequestInfo requestInfo)

};


#endif //SERVER_IREQUESTHANDLER_H
