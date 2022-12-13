#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"
#include <string>

class RequestHandlerFactory;

class RequestHandler : public IRequestHandler{
public:
    RequestHandler(RequestHandlerFactory* requestHandler, std::string ip);

    ~RequestHandler() = default;
    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;
private:
    RequestResult login(RequestInfo requestInfo);
    RequestResult logout(RequestInfo requestInfo) const;
    RequestResult getRoute(RequestInfo requestInfo) const;
    RequestHandlerFactory* m_requestHandlerFactory;
    std::string ip;
};


