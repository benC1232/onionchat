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



typedef struct Blacklist{
    std::vector<std::string> continent;
    std::vector<std::string> country;
    std::vector<std::string> regionName;
    std::vector<std::string> city;
    std::vector<std::string> isp;
}Blacklist;

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
    static Blacklist deserializeGetRouteRequest(Buffer buffer);
    static ipData deserializeIpData(std::string buffer);
};


