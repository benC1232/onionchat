#include "LoginManager.h"
#include "APICommunicator.h"

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
    newNode.ip = ipDataVar.ip;
    newNode.port = port;
    newNode.isp = ipDataVar.isp;

    newNode.encryptionType = "";
    newNode.publicKey = 0;
    newNode.privateKey = 0;

    return m_dataBase->addNewNode(newNode);




}

bool LoginManager::logout(std::string IP) {
    return m_dataBase->deleteNode(IP);
}

bool LoginManager::getRoute(std::vector<NodeData> destination) {
    return true;
}
