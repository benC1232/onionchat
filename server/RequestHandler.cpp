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


RequestHandler::RequestHandler(RequestHandlerFactory *requestHandler, std::string ip) {
    this->m_requestHandlerFactory = requestHandler;
    this->ip = ip;
}



bool RequestHandler::isRequestRelevant(RequestInfo request) {
    return true;
}


RequestResult RequestHandler::handleRequest(RequestInfo request) {
    RequestResult result;

    std::cout << getIpData(this->ip) << std::endl;
    //log in
    if(request.id == LOGIN_CODE){
        result = login(request);
    }
    //log out
    else if(request.id == LOG_OUT_CODE){
        result = logout(request);
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
    if(this->m_requestHandlerFactory->getLoginManager()->login(loginRequest.IP,loginRequest.port)){
        result.newHandler = this;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();

    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler(this->ip);
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Login failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.bufferSize = result.buffer.size();
    }
    return result;

}

RequestResult RequestHandler::logout(RequestInfo requestInfo) const{
    RequestResult result;
    LogoutResponse num;
    num.status = LOG_OUT_CODE;
    LogoutRequest logoutRequest = JsonRequestPacketDeserializer::deserializeLogoutRequest(requestInfo.buffer);
    if(this->m_requestHandlerFactory->getLoginManager()->logout(logoutRequest.IP)){
        result.newHandler = nullptr;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();
    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler(this->ip);
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Logout failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.bufferSize = result.buffer.size();
    }
    return result;

}


RequestResult RequestHandler::getRoute(RequestInfo requestInfo) const {
    RequestResult result;
    GetRouteResponse num;
    num.status = GET_ROUTE_CODE;
    num.route.push_back({"127.0.0.1", 8686, "None", 0});

    //missing deserializer content in the current iteration
    //if (this->m_requestHandlerFactory->getLoginManager()->getRoute(nullptr)) {
        result.newHandler = nullptr;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
        result.bufferSize = result.buffer.size();
    //}
    /*else {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler();
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Get route failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
        result.bufferSize = result.buffer.size();
    }*/
    return result;
}



