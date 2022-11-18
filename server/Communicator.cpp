
#include "Communicator.h"

Communicator::Communicator() {
    this->m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_serverSocket < 0) {
        throw std::runtime_error("socket wasnt created successfully");
    }
}

Communicator::~Communicator() {
    close(this->m_serverSocket);
}
