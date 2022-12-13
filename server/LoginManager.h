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
    bool login(std::string s1, std::string s2);
    bool logout(std::string s1);
    bool getRoute(std::vector<NodeData> destination);
};


#endif //SERVER_LOGINMANAGER_H
