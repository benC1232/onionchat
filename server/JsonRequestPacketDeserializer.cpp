#include"JsonRequestPacketDeserializer.h"


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buffer) {
    std::string jsonString(buffer.begin(),buffer.end());
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    LoginRequest ret;
    ret.port = jsonObject["Port"];
    return ret;
}

Blacklist JsonRequestPacketDeserializer::deserializeGetRouteRequest(Buffer buffer){
    std::string jsonString(buffer.begin() ,buffer.end());
    if(jsonString.length() == 0)
    {
        Blacklist blacklist = {};
        return blacklist;
    }
    nlohmann::json j = nlohmann::json::parse(jsonString);
    Blacklist location;
    location.continent = j.value("continent", std::vector<std::string>{});
    location.country = j.value("country", std::vector<std::string>{});
    location.regionName = j.value("regionName", std::vector<std::string>{});
    location.city = j.value("city", std::vector<std::string>{});
    location.isp = j.value("isp", std::vector<std::string>{});
    return location;
}

IpData JsonRequestPacketDeserializer::deserializeIpData(std::string buffer) {
    nlohmann::json jsonObject = nlohmann::json::parse(buffer);
    if(jsonObject["status"] == "fail")
    {
        throw std::runtime_error("api request failed");
    }
    IpData data;
    if(jsonObject["query"] == "1.1.1.1")
    {
        data.ip = "127.0.0.1";
    }
    else
    {
        data.ip = jsonObject["query"];
    }
    data.continent = jsonObject["continent"];
    data.country = jsonObject["country"];
    data.regionName = jsonObject["regionName"];
    data.city = jsonObject["city"];
    data.isp = jsonObject["isp"];

    return data;
}

