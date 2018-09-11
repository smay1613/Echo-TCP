#include <iostream>
#include <thread>
#include "tcpserver.h"

using namespace std;

int main()
{
    TCPServer tst;
    thread t1(&TCPServer::acceptData, &tst);
//    tst.acceptData();
    t1.join();
    return 0;
}
