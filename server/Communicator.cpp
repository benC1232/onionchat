
#include "Communicator.h"
/*
 * function creates a server socket
 * input: none
 * output: none
 */
Communicator::Communicator()
{
    this->m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_serverSocket < 0)
    {
        throw std::runtime_error("socket wasnt created successfully");
    }
}
/*
 * function closes a server socket
 * input: none
 * output: none
 */
Communicator::~Communicator()
{
    close(this->m_serverSocket);
}
/*
 * function binds server socket to port and starts listening
 * input: none
 * output: none
 */
void Communicator::startHandleRequests()
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);
    if (bind(this->m_serverSocket, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {
        throw std::runtime_error("couldnt bind server to port");
    }
    if (listen(this->m_serverSocket, 5) < 0)
    {
        throw std::runtime_error("couldnt listen to socket");
    }
    while(true)
    {
        bindAndListen();
    }
}
/*
 * function accepts client sockets and creates threads for them
 * input: none
 * output: none
 */
void Communicator::bindAndListen()
{
    static struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(this->m_serverSocket, (struct sockaddr *) &client_sin, &addr_len);

}
/*
 * function handles a clients requests
 * input: socket
 * output: none
 */
void Communicator::handleNewClient(int clientSocket)
{


}

