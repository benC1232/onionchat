#include "LoginManager.h"


LoginManager::LoginManager(IDataBase *dataBase) {
    m_dataBase = dataBase;
}

LoginManager::~LoginManager() {
    delete m_dataBase;
}

bool LoginManager::login(std::string s1, std::string s2) {
    return true;
}

bool LoginManager::logout(std::string s1) {
    return true;
}

bool LoginManager::getRoute(std::vector<NodeData> destination) {
    return true;
}
