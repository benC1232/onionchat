#include "Server.h"
Server::Server()
{
    this->m_communicator = new Communicator();
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
