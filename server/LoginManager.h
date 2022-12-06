#ifndef SERVER_LOGINMANAGER_H
#define SERVER_LOGINMANAGER_H
#include <vector>
#include "IDataBase.h"

class LoginManager {
private:
    IDataBase* m_dataBase;
public:
    LoginManager(IDataBase* dataBase);
    ~LoginManager();
    bool login(std::string username, std::string password);
    bool logout(std::string username);
};


#endif //SERVER_LOGINMANAGER_H
