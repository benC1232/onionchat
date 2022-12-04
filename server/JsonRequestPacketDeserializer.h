#pragma once
#include<iostream>
#include<vector>
#include "NodeData.h"
#include "json.hpp"

#define JSON_OFFSET 5



using Buffer = std::vector<unsigned char>;

typedef struct LoginRequest{
    unsigned int status;
}LoginRequest;

typedef struct LogoutRequest{
    unsigned int status;
}LogoutRequest;

typedef struct GetRouteRequest{
    unsigned int status;
    std::vector<NodeData> route;
}GetRouteRequest;




class JsonRequestPacketDeserializer {
public:
    static LoginRequest deserializeLoginRequest(Buffer buffer);
    static LogoutRequest deserializeLogoutRequest(Buffer buffer);
    static GetRouteRequest deserializeGetRouteRequest(Buffer buffer);

};


