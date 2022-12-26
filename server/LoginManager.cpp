#include "LoginManager.h"
#include "APICommunicator.h"
#include <tuple>

LoginManager::LoginManager(IDataBase *dataBase) {
    m_dataBase = dataBase;
}

LoginManager::~LoginManager() {

}

bool LoginManager::login(std::string IP, int port) {
    ipData ipDataVar = getIpData(IP);
    if (ipDataVar.ip == "") {
        return false;
    }
    NewNode newNode;
    newNode.port = port;
    newNode.ipData = ipDataVar;

    newNode.encryptionType = "";
    newNode.publicKey = 0;
    newNode.privateKey = 0;

    return m_dataBase->addNewNode(newNode);




}

bool LoginManager::logout(std::string IP) {
    return m_dataBase->deleteNode(IP);
}

std::vector<NodeData> nodeDataArrayToVector(NodeData* nodeDataArray) {
    std::vector<NodeData> nodeDataVector;
    for (int i = 0; i < 10; i++) {
        nodeDataVector.push_back(nodeDataArray[i]);
    }
    return nodeDataVector;
}

std::tuple<bool,std::vector<NodeData>>  LoginManager::getRoute(ipData ipData,Blacklist blacklist) {
    bool found = false;
    NodeData* nodeData = m_dataBase->getRoute(ipData,blacklist);
    found = nodeData!= nullptr;
    return std::make_tuple(found,nodeDataArrayToVector(nodeData));

}


