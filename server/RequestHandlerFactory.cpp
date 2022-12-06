//
// Created by orime on 12/6/2022.
//

#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDataBase *dataBase) {
    m_dataBase = dataBase;
    m_loginManager = new LoginManager(this->dataBase);
}

RequestHandlerFactory::~RequestHandlerFactory() {
    delete m_loginManager;
    delete m_dataBase;
}

IRequestHandler* RequestHandlerFactory::createRequestHandler() {
    return new LoginRequestHandler(m_loginManager);
}
