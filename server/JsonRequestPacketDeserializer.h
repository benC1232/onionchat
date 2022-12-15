#pragma once
#include<iostream>
#include<vector>
#include <string>
#include "NodeData.h"
#include "json.hpp"

#define JSON_OFFSET 5


using Buffer = std::vector<unsigned char>;

typedef struct LoginRequest{
    unsigned int status;
    std::string IP;
    int port;
}LoginRequest;

typedef struct LogoutRequest{
    unsigned int status;
    std::string IP;
}LogoutRequest;

typedef struct GetRouteRequest{
    unsigned int status;
    std::vector<NodeData> route;
}GetRouteRequest;

typedef struct ipData{
    std::string ip;
    std::string continent;
    std::string country;
    std::string regionName;
    std::string city;
    std::string isp;
}ipData;



class JsonRequestPacketDeserializer {
public:
    static LoginRequest deserializeLoginRequest(Buffer buffer);
    static LogoutRequest deserializeLogoutRequest(Buffer buffer);
    static GetRouteRequest deserializeGetRouteRequest(Buffer buffer);
    static ipData deserializeIpData(std::string buffer);

};


