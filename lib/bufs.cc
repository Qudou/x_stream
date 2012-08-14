#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <sys/socket.h>
#include <sys/types.h>
#include "../include/bufs.hpp"

SocketStreamBuf::SocketStreamBuf(int sock)
{
    sockfd = sock;
    setp(readbuf, readbuf + 1023);
    setg(writebuf, writebuf, writebuf + 1023);
}

SocketStreamBuf::~SocketStreamBuf()
{
  if(close(sockfd) != 0)
    if(errno != EBADF)
    {
        std::cerr << "fatal error: closing socket failed\n";
        exit(1);
    }
}

int SocketStreamBuf::sync()
{
    int status;
    *pptr() = '\0';
    status = send(sockfd, pbase(), pptr() - pbase(), 0);
    pbump(pbase() - pptr());
    return(status);
}

int SocketStreamBuf::overflow()
{
    int status;
    status = send(sockfd, writebuf, 1024, 0);
    pbump(pbase() - pptr());
    return(status);
}

int SocketStreamBuf::underflow()
{
    int status;
    status = recv(sockfd, readbuf, 1024, 0);
    gbump(eback() - gptr());
    return(status);
}
