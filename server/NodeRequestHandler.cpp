//
// Created by magshimim on 14-Jan-23.
//

#include "NodeRequestHandler.h"



RequestResult NodeRequestHandler::handleRequest(RequestInfo request) {
    RequestResult result;

    if(request.id == LOG_OUT_CODE){
        result = logout(request);
    }
    else if(request.id == KEEPALIVE_CODE)
    {
        result = keepalive(request);
    }
    return result;
}

RequestResult NodeRequestHandler::logout(RequestInfo requestInfo){
    RequestResult result;
    LogoutResponse num;
    num.status = LOG_OUT_CODE;
    if(this->m_requestHandlerFactory->getLoginManager()->logout(this->ip)){
        result.newHandler = nullptr;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();
    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler(this->ip, 0);
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Logout failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.bufferSize = result.buffer.size();
    }
    return result;

}

RequestResult NodeRequestHandler::keepalive(RequestInfo requestInfo){
    RequestResult result;
    LogoutResponse num;
    num.status = LOG_OUT_CODE;
    result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
    result.bufferSize = result.buffer.size();
    result.newHandler = this;
    return result;
}

NodeRequestHandler::NodeRequestHandler(RequestHandlerFactory *requestHandler, std::string ip, int socket) {
    this->m_requestHandlerFactory = requestHandler;
    this->ip = ip;
    this->socket = socket;

}

bool NodeRequestHandler::isRequestRelevant(RequestInfo request) {
    return false;
}
