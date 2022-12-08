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
    IRequestHandler* createRequestHandler();
    LoginManager* getLoginManager();
};





