#pragma once

#include "LoginManager.h"
#include "IDataBase.h"
#include "IRequestHandler.h"
#include "RequestHandler.h"

class RequestHandler;

class RequestHandlerFactory {
private:
    LoginManager* m_loginManager;
    IDataBase* m_dataBase;
public:
    RequestHandlerFactory(IDataBase* dataBase);
    ~RequestHandlerFactory();
    RequestHandler *createRequestHandler(std::string ip, int socket);
    RequestHandler *createNodeRequestHandler(int socket);
    LoginManager* getLoginManager();
};





