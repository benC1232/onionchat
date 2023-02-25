#pragma once

#include "LoginManager.h"
#include "IDataBase.h"
#include "IRequestHandler.h"
#include "RequestHandler.h"
#include "NodeRequestHandler.h"
class RequestHandler;
class NodeRequestHandler;
class RequestHandlerFactory {
private:
    LoginManager* m_loginManager;
    IDataBase* m_dataBase;
public:
    RequestHandlerFactory(IDataBase* dataBase);
    ~RequestHandlerFactory();
    RequestHandler *createRequestHandler(std::string ip, int socket);
    NodeRequestHandler *createNodeRequestHandler(std::string ip, int socket);
    LoginManager* getLoginManager();
};





