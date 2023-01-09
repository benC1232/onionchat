#include"JsonRequestPacketDeserializer.h"


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buffer) {
    std::string jsonString(buffer.begin()+JSON_OFFSET,buffer.end());
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    //---------------
}

 LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(Buffer buffer){
    std::string jsonString(buffer.begin()+JSON_OFFSET,buffer.end());
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    //---------------
}

GetRouteRequest JsonRequestPacketDeserializer::deserializeGetRouteRequest(Buffer buffer){
    std::string jsonString(buffer.begin()+JSON_OFFSET,buffer.end());
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    //---------------
}

ipData JsonRequestPacketDeserializer::deserializeIpData(std::string buffer) {
    nlohmann::json jsonObject = nlohmann::json::parse(buffer);
    if(jsonObject["status"] == "fail")
    {
        throw std::runtime_error("api request failed");
    }
    ipData data;
    data.ip = jsonObject["query"];
    data.continent = jsonObject["continent"];
    data.country = jsonObject["country"];
    data.regionName = jsonObject["regionName"];
    data.city = jsonObject["city"];
    data.isp = jsonObject["isp"];

    return data;
}

Blacklist JsonRequestPacketDeserializer::deserializeBlacklist(Buffer buffer) {
    std::string jsonString(buffer.begin() ,buffer.end());
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    Blacklist data;
    data.continent = jsonObject["continent"];
    data.country = jsonObject["country"];
    data.regionName = jsonObject["regionName"];
    data.city = jsonObject["city"];
    data.isp = jsonObject["isp"];
    return data;
}


