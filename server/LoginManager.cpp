#include "LoginManager.h"
#include "APICommunicator.h"
#include "SqliteDataBase.h"

#include <iostream>
#include <tuple>

LoginManager::LoginManager(IDataBase *dataBase) {
    m_dataBase = dataBase;
}

LoginManager::~LoginManager() {

}

bool LoginManager::login(std::string IP, int port) {
    IpData ipDataVar = getIpData(IP);
    if (ipDataVar.ip == "") {
        return false;
    }
    NewNode newNode;
    newNode.port = port;
    newNode.ipdata = ipDataVar;

    newNode.encryptionType = "";
    newNode.publicKey = 0;
    newNode.privateKey = 0;

    return m_dataBase->addNewNode(newNode);

}

bool LoginManager::logout(std::string IP) {
    return m_dataBase->deleteNode(IP);
}



std::vector<NodeData> nodeDataArrayToVector(NodeData* nodeDataArray){
    std::vector<NodeData> vec;
    for(int i = 0;i<NUM_OF_NODES;i++){
        vec.push_back(nodeDataArray[i]);
    }
    return vec;
}

std::tuple<bool,std::vector<NodeData>> LoginManager::getRoute(Blacklist blacklist) {
    bool found = false;
    NodeData* nodeData = m_dataBase->getRoute(blacklist);
    found = nodeData[0].ip != "";
    auto vec = nodeDataArrayToVector(nodeData);
    return std::make_tuple(found,vec);

}


