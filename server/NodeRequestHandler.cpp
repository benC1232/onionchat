//
// Created by magshimim on 14-Jan-23.
//

#include "NodeRequestHandler.h"

NodeRequestHandler::NodeRequestHandler(RequestHandlerFactory *requestHandler, int socket) {
    this->socket = socket;
    this->m_requestHandlerFactory = requestHandler;
    // sending the first keepalive message
    char msg[1] = {char(150)};
    ssize_t sent_bytes = send(socket, msg, 1, 0);
    if (sent_bytes < 0) {
        throw std::runtime_error("message not sent successfully");
    }
}
