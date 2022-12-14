#include "LoginManager.h"


LoginManager::LoginManager(IDataBase *dataBase) {
    m_dataBase = dataBase;
}

LoginManager::~LoginManager() {
}

bool LoginManager::login(std::string IP, int port) {


}

bool LoginManager::logout(std::string s1) {
    return true;
}

bool LoginManager::getRoute(std::vector<NodeData> destination) {
    return true;
}
