#ifndef SERVER_REQUESTHANDLERFACTORY_H
#define SERVER_REQUESTHANDLERFACTORY_H
#include "IRequestHandler.h"
#include "LoginManager"
#include "IDataBase.h"

class RequestHandlerFactory {
private:
    LoginManager* m_loginManager;
    IDataBase* m_dataBase;
public:
    RequestHandlerFactory(IDataBase* dataBase);
    ~RequestHandlerFactory();
    IRequestHandler* createRequestHandler();
};




#endif //SERVER_REQUESTHANDLERFACTORY_H
