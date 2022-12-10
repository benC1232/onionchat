#include "Communicator.h"

/*
 * function creates a server socket
 * input: none
 * output: none
 */
Communicator::Communicator(RequestHandlerFactory &mHandlerFactory) : m_handlerFactory(mHandlerFactory) {
    this->m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_serverSocket < 0) {
        throw std::runtime_error("socket wasn't created successfully");
    }
}

/*
 * function closes a server socket
 * input: none
 * output: none
 */
Communicator::~Communicator() {
    close(this->m_serverSocket);
}

/*
 * function binds s/*erver socket to port and starts listening
 * input: none
 * output: none
 */
void Communicator::startHandleRequests() {
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);
    if (bind(this->m_serverSocket, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        throw std::runtime_error("couldn't bind server to port");
    }
    if (listen(this->m_serverSocket, 5) < 0) {
        throw std::runtime_error("couldn't listen to socket");
    }
    while (true) {
        bindAndListen();
    }
}

/*
 * function accepts client sockets and creates threads for them
 * input: none
 * output: none
 */
void Communicator::bindAndListen() {
    static struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(this->m_serverSocket, (struct sockaddr *) &client_sin, &addr_len);
    RequestHandler *handler = this->m_handlerFactory.createRequestHandler();
    this->m_clients.insert({client_sock, handler});
    this->threadVector.push_back(std::thread(&Communicator::handleNewClient, client_sock, handler));
}

/*
 * function handles a clients requests
 * input: socket
 * output: none
 */
void Communicator::handleNewClient(int clientSocket, IRequestHandler *handler) {

    RequestInfo request;
    RequestResult result = {};

    do {
        request = read(clientSocket);
        result = handler->handleRequest(request);
        handler = result.newHandler;
        write(result, clientSocket);
    } while (request.id != SIGNOUT && request.id != ROUTE);
    //closing the communication with the client
    close(clientSocket);
}

/*
 * function sends data over socket
 * input: message to be sent
 * output: none
 */
void Communicator::write(RequestResult message, int clientSock) {
    size_t data_len = message.bufferSize;
    //sending data

    ssize_t sent_bytes = send(clientSock, bufferToStr(message.buffer).c_str(), data_len, 0);
    if (sent_bytes < 0) {
        throw std::runtime_error("message not sent successfully");
    }
}

/*
 * function receives data over socket
 * input: none
 * output: message that was sent to server
 */
RequestInfo Communicator::read(int clientSock) {
    char buffer[MESSAGE_SIZE];
    int expected_data_len = sizeof(buffer);
    ssize_t read_bytes = recv(clientSock, buffer, expected_data_len, 0);
    RequestInfo request;
    request.id = buffer[0];
    int size = Communicator::getJsonSize(buffer);
    for (int i = 0; i < size; i++) {
        request.buffer.push_back(buffer[i + JSON_OFFSET]);
    }
    return request;
}

/*
 * extracts the length field from the packet
 */
int Communicator::getJsonSize(const char *buffer) {
    //don't change!!!!!!!! it works!!!!!!!!
    const int size = buffer[1] << 24 | buffer[2] << 16 | buffer[3] << 8 | buffer[4];
    return size;
}

std::string Communicator::bufferToStr(Buffer input) {
    std::string str;
    for (char byte: input) {
        str.push_back(byte);
    }
    return str;
}
