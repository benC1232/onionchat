#ifndef SERVER_IDATABASE_H
#define SERVER_IDATABASE_H
#include "NodeData.h"

class IDataBase {
public:
    IDataBase() = default;
    virtual ~IDataBase() = default;

    virtual NodeData* getRoute() = 0;
    virtual void addNewNode(std::string placeHolder1, std::string placeHolder2, std::string placeHolder3) = 0;
    virtual void deleteNode(std::string placeHolder1) = 0;
    virtual bool isUserExist(std::string placeHolder1) = 0;
    virtual void addUser(std::string username, std::string password) = 0;
    virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
};


#endif //SERVER_IDATABASE_H
