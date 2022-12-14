//
// Created by orime on 12/6/2022.
//

#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase *dataBase) {
    m_dataBase = dataBase;
    m_loginManager = new LoginManager(this->m_dataBase);
}

RequestHandlerFactory::~RequestHandlerFactory() {
    delete m_loginManager;
    delete m_dataBase;
}

RequestHandler* RequestHandlerFactory::createRequestHandler(std::string ip) {
    return new RequestHandler(this, ip);
}

LoginManager* RequestHandlerFactory::getLoginManager() {
    return m_loginManager;
}
