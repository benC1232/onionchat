//
// Created by magshimim on 14-Jan-23.
//

#ifndef SERVER_NODEREQUESTHANDLER_H
#define SERVER_NODEREQUESTHANDLER_H

#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "Communicator.h"

class NodeRequestHandler: public IRequestHandler {
public:
    NodeRequestHandler(RequestHandlerFactory* requestHandler, int socket);
    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;

private:
    RequestHandlerFactory* m_requestHandlerFactory;
    int socket;
};


#endif //SERVER_NODEREQUESTHANDLER_H
