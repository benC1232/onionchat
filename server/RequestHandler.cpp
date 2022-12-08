#include "RequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "HandlerStructs.h"
#include"NodeData.h"
#include <vector>
#define LOGIN_CODE 210
#define LOG_OUT_CODE 215
#define ERROR_CODE 100
#define GET_ROUTE_CODE 4150


RequestHandler::RequestHandler(RequestHandlerFactory *requestHandler) {
    this->m_requestHandlerFactory = requestHandler;

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
        result.newHandler = this;

    }
    return result;

}

RequestResult RequestHandler::login(RequestInfo requestInfo) const{
    RequestResult result;
    LoginResponse num;
    num.status = LOGIN_CODE;
    const LoginRequest lr{
        status: 1,
        s1: "s1",
        s2: "s2"
    };
    //missing deserializer content in the current iteration
    if(this->m_requestHandlerFactory->getLoginManager()->login(lr.s1,lr.s2)){
        result.newHandler = nullptr;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler();
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Login failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
    }
    return result;

}

RequestResult RequestHandler::logout(RequestInfo requestInfo) const{
    RequestResult result;
    LogoutResponse num;
    num.status = LOG_OUT_CODE;
    const LogoutRequest lr{
        status: 1,
        s1: "s1",
    };
    if(this->m_requestHandlerFactory->getLoginManager()->logout(lr.s1)){
        result.newHandler = nullptr;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
    }
    else
    {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler();
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Logout failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
    }
    return result;

}


RequestResult RequestHandler::getRoute(RequestInfo requestInfo) const {
    RequestResult result;
    GetRouteResponse num;
    num.status = GET_ROUTE_CODE;
    auto r = std::vector<NodeData>();
    r.push_back({"127.0.0.1", 8686, "None", 0});
    GetRouteRequest grr{
        status: 1,
        route: r
    };
    //missing deserializer content in the current iteration
    if (this->m_requestHandlerFactory->getLoginManager()->getRoute(grr.route)) {
        result.newHandler = nullptr;
        result.buffer = JsonResponsePacketSerializer::serializeResponse(num);
    } else {
        result.newHandler = this->m_requestHandlerFactory->createRequestHandler();
        num.status = ERROR_CODE;
        ErrorResponse err;
        err.message = "Get route failed";
        result.buffer = JsonResponsePacketSerializer::serializeResponse(err);
    }
    return result;
}



