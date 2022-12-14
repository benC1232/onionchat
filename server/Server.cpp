#include "Server.h"
#include "SqliteDataBase.h"

Server::Server()
{
    this->m_dataBase = new SqliteDataBase();
    this->m_handlerFactory = new RequestHandlerFactory(this->m_dataBase);
    this->m_communicator = new Communicator(*this->m_handlerFactory);

}

Server::~Server()
{
    delete this->m_communicatorThread;
    delete this->m_communicator;
}

//creates the t_connector and detaches it
void Server::run()
{
    this->m_communicatorThread = new std::thread(&Communicator::startHandleRequests, m_communicator);
}
