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
    bool login(std::string IP, int port);
    bool logout(std::string IP);



    std::tuple<bool, std::vector<NodeData>> getRoute(Blacklist blacklist);
};


#endif //SERVER_LOGINMANAGER_H
