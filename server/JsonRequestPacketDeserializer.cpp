#include"JsonRequestPacketDeserializer.h"


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buffer) {
    std::string jsonString(buffer.begin()+JSON_OFFSET,buffer.end());
    nlohmann::json jsonObject = nlohmann::json::parse(jsonString);
    //---------------
}