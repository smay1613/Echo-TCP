#include "mastersocket.h"
#include <iostream>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

MasterSocket::MasterSocket()
{
    m_socket = socket(
                        AF_INET,
                        SOCK_STREAM,
                        0);
    if (m_socket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
    } else {
        std::cout << "Socket creation success" << std::endl;
    }

    m_isOpened = true;
}

MasterSocket::~MasterSocket()
{
    bool shutdownFailed = shutdown(m_socket, SHUT_RDWR);

    if (shutdownFailed) {
        std::cerr << "Socket shutdown failed!" << std::endl;
    }

    bool closeFailed = close(m_socket);

    if (closeFailed) {
        std::cerr << "Closing socket failed." << std::endl;
    } else {
        std::cout << "Socket closed successfully!" << std::endl;
    }

    m_isOpened = false;
}

int MasterSocket::getSocket() const
{
    return m_socket;
}

bool MasterSocket::isOpened() const
{
    return m_isOpened;
}
