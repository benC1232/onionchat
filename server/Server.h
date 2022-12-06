#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <thread>
#include "Communicator.h"
#include"IDataBase.h"
#include "RequestHandlerFactory.h"
class Server {
public:
    Server();
    ~Server();
    void run();
private:
    Communicator* m_communicator;
    std::thread* m_communicatorThread;
    IDataBase* m_dataBase;
    RequestHandlerFactory m_handlerFactory;

};


#endif //SERVER_SERVER_H
