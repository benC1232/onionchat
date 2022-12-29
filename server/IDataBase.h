#ifndef SERVER_IDATABASE_H
#define SERVER_IDATABASE_H
#include "NodeData.h"
#include "JsonRequestPacketDeserializer.h"



typedef struct NewNode{
    std::string encryptionType;
    int publicKey;
    int privateKey;
    int port;
    ipData ipdata;


} NewNode;


class IDataBase {
public:
    IDataBase() = default;
    virtual ~IDataBase() = default;

    virtual bool addNewNode(NewNode newNodeStruct) = 0;
    virtual bool deleteNode(std::string IP) = 0;
    virtual NodeData* getRoute(ipData ipData,Blacklist blackList)  = 0;

    };


#endif //SERVER_IDATABASE_H
