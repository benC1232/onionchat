#include "LoginManager.h"


LoginManager::LoginManager(IDataBase *dataBase) {
    m_dataBase = dataBase;
}

LoginManager::~LoginManager() {
    delete m_dataBase;
}

bool LoginManager::login(std::string username, std::string password) {
    return true;
}

bool LoginManager::logout(std::string username) {
    return true;
}