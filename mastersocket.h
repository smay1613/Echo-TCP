#ifndef MASTERSOCKET_H
#define MASTERSOCKET_H


class MasterSocket
{
public:
    MasterSocket();
    ~MasterSocket();
    int getSocket() const;
    bool isOpened() const;

private:
    int m_socket;
    bool m_isOpened;
};

#endif // MASTERSOCKET_H
