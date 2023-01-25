#include "RequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "APICommunicator.h"
#include "HandlerStructs.h"
#include"NodeData.h"
#include <vector>
#define LOGIN_CODE 210
#define LOG_OUT_CODE 215
#define ERROR_CODE 100
#define GET_ROUTE_CODE 150


RequestHandler::RequestHandler(RequestHandlerFactory *requestHandler, std::string ip, int socket) {
    this->m_requestHandlerFactory = requestHandler;
    this->ip = ip;
    this->socket = socket;
}



bool RequestHandler::isRequestRelevant(RequestInfo request) {
    return true;
}


RequestResult RequestHandler::handleRequest(RequestInfo request) {
    RequestResult result;

    //log in
    if(request.id == LOGIN_CODE){
        result = login(request);
    }
    //get route
    else if(request.id == GET_ROUTE_CODE){
        result = getRoute(request);
    }
    //error
    else{
        ErrorResponse num;
        num.message = "error while handling request [login request handler has received a wrong code]";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();
        result.newHandler = this;

    }
    return result;

}

RequestResult RequestHandler::login(RequestInfo requestInfo) {
    RequestResult result;
    LoginResponse num;
    num.status = LOGIN_CODE;
    LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
    //missing deserializer content in the current iteration
    if(this->m_requestHandlerFactory->getLoginManager()->login(this->ip,loginRequest.port)){
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler(this->ip, 0);
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();

    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createNodeRequestHandler(this->ip, 0);
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Login failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.bufferSize = result.buffer.size();
    }
    return result;

}


RequestResult RequestHandler::getRoute(RequestInfo requestInfo) const {
    RequestResult result;
    GetRouteResponse num;
    num.status = GET_ROUTE_CODE;
    Blacklist blacklist = JsonRequestPacketDeserializer::deserializeGetRouteRequest(requestInfo.buffer);
    auto [found, route] = this->m_requestHandlerFactory->getLoginManager()->getRoute(blacklist);
    if(found){
        num.route = route;
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler(this->ip, 0);
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();
    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler(this->ip, 0);
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Get route failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.bufferSize = result.buffer.size();
    }
    return result;

}



