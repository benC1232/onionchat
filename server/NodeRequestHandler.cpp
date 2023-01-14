//
// Created by magshimim on 14-Jan-23.
//

#include "NodeRequestHandler.h"

NodeRequestHandler::NodeRequestHandler(RequestHandlerFactory *requestHandler, int socket) {
    this->socket = socket;
    this->m_requestHandlerFactory = requestHandler;
}
