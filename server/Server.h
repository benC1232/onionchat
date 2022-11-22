#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <thread>
#include "Communicator.h"
class Server {
public:
    Server();
    ~Server();
    void run();
private:
    Communicator* m_communicator;
    std::thread* m_communicatorThread;
};


#endif //SERVER_SERVER_H
