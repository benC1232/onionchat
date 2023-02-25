//
// Created by magshimim on 14-Jan-23.
//

#ifndef SERVER_NODEREQUESTHANDLER_H
#define SERVER_NODEREQUESTHANDLER_H

#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonResponsePacketSerializer.h"

#define LOG_OUT_CODE 215
#define KEEPALIVE_CODE 220
#define ERROR_CODE 100
class RequestHandlerFactory;

class NodeRequestHandler: public IRequestHandler {
public:
    NodeRequestHandler(RequestHandlerFactory* requestHandler, std::string ip, int socket);
    ~NodeRequestHandler() = default;
    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;

private:
    RequestResult logout(RequestInfo requestInfo);
    RequestResult keepalive(RequestInfo requestInfo);
    RequestHandlerFactory* m_requestHandlerFactory;
    int socket;
    std::string ip;

};


#endif //SERVER_NODEREQUESTHANDLER_H
