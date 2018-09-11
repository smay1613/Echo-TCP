#include "tcpserver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

TCPServer::TCPServer() {
    if (initialize(8000, "")) {
        std::cout << "Server initialized successfully!" << std::endl;
    }
    if (start()) {
        std::cout << "Server started successfully!" << std::endl;
    }
}

TCPServer::TCPServer(unsigned short port, std::string ip)
{
    if (initialize(port, ip)) {
        std::cout << "Server initialized successfully!" << std::endl;
    }
    if (start()) {
        std::cout << "Server started successfully!" << std::endl;
    }
}

bool TCPServer::initialize(unsigned short port = 8000, std::string ip = "")
{
    m_sockAddress.sin_family = AF_INET;
    m_sockAddress.sin_port = htons(port);
    if (!ip.empty()) {
        inet_pton(AF_INET, ip.c_str(), &m_sockAddress);
    } else {
        m_sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    bool bindFailed = bind(m_masterSocket.getSocket(),
                           (sockaddr*)(&m_sockAddress),
                           sizeof(m_sockAddress));

    if (bindFailed) {
        std::cerr << "Can't initialize server, because bind was failed" << std::endl;
    }

    return !bindFailed;
}

bool TCPServer::start()
{
    bool listenFailed = listen(m_masterSocket.getSocket(),
                               SOMAXCONN); // 128

    if (listenFailed) {
        std::cerr << "Can't start server, because listen was failed" << std::endl;
    }

    return !listenFailed;
}

void TCPServer::acceptData() const
{
    sockaddr clientAddress;
    socklen_t sizeOfClientAddress = sizeof(clientAddress);

    int slaveSocket = accept(m_masterSocket.getSocket(), &clientAddress, &sizeOfClientAddress);

    if (slaveSocket == -1) {
        std::cerr << "Connection with " << clientAddress.sa_data << " cannot be established." << std::endl;
        return; // accepting failed
    }

    std::vector<char> buffer(MAX_BUF_LENGTH);
    int bytesCount = 0;

    do {
        bytesCount = recv(slaveSocket, &buffer[0], buffer.size(), MSG_NOSIGNAL);
        if (bytesCount == -1) {
            std::cerr << "Error when reading... Recv failed." << std::endl;
        } else {
            std::copy(buffer.cbegin(), buffer.cend(), std::ostream_iterator<char>(std::cout, ""));
        }
    } while (bytesCount > 0);
}
