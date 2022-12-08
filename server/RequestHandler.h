#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;

class RequestHandler : public IRequestHandler{
public:
    RequestHandler(RequestHandlerFactory* requestHandler);

    ~RequestHandler() = default;
    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;
private:
    RequestResult login(RequestInfo requestInfo) const;
    RequestResult logout(RequestInfo requestInfo) const;
    RequestResult getRoute(RequestInfo requestInfo) const;
    RequestHandlerFactory* m_requestHandlerFactory;
};


