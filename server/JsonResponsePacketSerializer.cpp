#include "JsonResponsePacketSerializer.h"
#include "json.hpp"

#define ERROR_RESPONSE_CODE 100
#define LOGIN_RESPONSE_CODE 10
#define GET_ROUTE_RESPONSE_CODE 20
#define LOGOUT_RESPONSE_CODE 60
#define KEEPALIVE_RESPONSE_CODE 50

Buffer intToBuffer(int num)
{
    Buffer buffer(4);
    for (int i = 0; i < 4; i++) buffer[3 - i] = (num << i * 8);
    return buffer;
}

std::string byteArrToString(unsigned char* arr, int size)
{
    std::string str;
    for (int i = 0; i < size; i++) str += arr[i];
    return str;
}



nlohmann::json serializeNodeDataVector(std::vector<NodeData> nodeDataVector)
{
    nlohmann::json json;
    nlohmann::json route;
    for (int i = 0; i < nodeDataVector.size(); i++)
    {
        nlohmann::json node;
        node["ip"] = nodeDataVector[i].ip;
        node["port"] = nodeDataVector[i].port;
        node["encryption"] = nodeDataVector[i].encryption;
        route["node" + std::to_string(i + 1)] = node;
    }
    json["route"] = route;
    return json;
}

std::string NodeDataVecToString(std::vector<NodeData> nodeDataVec){
    std::string output = "";
    for(auto nodeData: nodeDataVec){
        output += nodeData.ip+":"+std::to_string(nodeData.port)+":"+nodeData.encryption+":"+std::to_string(nodeData.key)+",";
    }
    return output;
}


Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse errorResponse) {
    Buffer buffer;
    buffer.push_back(ERROR_RESPONSE_CODE);
    const nlohmann::json jsonResponse {
            {"message", ""+errorResponse.message}
    };
    const std::string jsonString = nlohmann::to_string(jsonResponse);
    Buffer lenBuff = intToBuffer(jsonString.length());
    buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
    for (unsigned char uc: jsonString) buffer.push_back(uc);
    return buffer;
}


Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse loginResponse) {
    Buffer buffer;
    buffer.push_back(LOGIN_RESPONSE_CODE);
    const nlohmann::json jsonResponse {
            {"status", ""+std::to_string(loginResponse.status)}
    };
    const std::string jsonString = nlohmann::to_string(jsonResponse);
    Buffer lenBuff = intToBuffer(jsonString.length());
    buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
    for (unsigned char uc: jsonString) buffer.push_back(uc);
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LogoutResponse logoutResponse) {
    Buffer buffer;
    buffer.push_back(LOGOUT_RESPONSE_CODE);
    const nlohmann::json jsonResponse {
            {"status", ""+std::to_string(logoutResponse.status)}
    };
    const std::string jsonString = nlohmann::to_string(jsonResponse);
    Buffer lenBuff = intToBuffer(jsonString.length());
    buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
    for (unsigned char uc: jsonString) buffer.push_back(uc);
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(GetRouteResponse getRouteResponse) {
    Buffer buffer;
    buffer.push_back(GET_ROUTE_RESPONSE_CODE);
    const nlohmann::json jsonResponse = serializeNodeDataVector(getRouteResponse.route);
    const std::string jsonString = nlohmann::to_string(jsonResponse);
    Buffer lenBuff = intToBuffer(jsonString.length());
    buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
    for (unsigned char uc: jsonString) buffer.push_back(uc);
    return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(KeepAliveResponse keepAliveResponse) {
    Buffer buffer;
    buffer.push_back(KEEPALIVE_RESPONSE_CODE);
    const nlohmann::json jsonResponse {
        {"status", ""+std::to_string(keepAliveResponse.status)}
    };
    const std::string jsonString = nlohmann::to_string(jsonResponse);
    Buffer lenBuff = intToBuffer(jsonString.length());
    buffer.insert(buffer.end(), lenBuff.begin(), lenBuff.end());
    for (unsigned char uc: jsonString) buffer.push_back(uc);
    return buffer;
}
