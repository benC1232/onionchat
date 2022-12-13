#pragma once
#include<iostream>
#include<vector>
#include "NodeData.h"

using Buffer = std::vector<unsigned char>;


typedef struct LoginResponse{
    unsigned int status;
}LoginResponse;

typedef struct LogoutResponse{
    unsigned int status;
}LogoutResponse;

typedef struct GetRouteResponse{
    unsigned int status;
    std::vector<NodeData> route;
}GetRouteResponse;

typedef struct ErrorResponse{
    std::string message;
}ErrorResponse;

class JsonResponsePacketSerializer{
public:
    static Buffer serializeResponse(ErrorResponse errorResponse);
    static Buffer serializeResponse(LoginResponse loginResponse);
    static Buffer serializeResponse(LogoutResponse logoutResponse);
    static Buffer serializeResponse(GetRouteResponse getRouteResponse);
};