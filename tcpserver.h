#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <netinet/in.h>
#include <string>
#include "mastersocket.h"

class TCPServer
{
public:
    TCPServer();
    TCPServer(unsigned short port, std::string ip);

    bool initialize(unsigned short port, std::string ip);
    bool start();

    void acceptData() const;

private:
    MasterSocket m_masterSocket;
    sockaddr_in m_sockAddress;
    const size_t MAX_BUF_LENGTH = 8;
};

#endif // TCPSERVER_H
