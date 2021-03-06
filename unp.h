/*
 * ============================================================================
 *
 *       Filename:  unp.h
 *
 *    Description:  common header of unix network programing
 *
 *        Version:  1.0
 *        Created:  11/17/12 19:59:50
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     _UNIX_NETWORK_PROGRAMING_HEADER_
#define     _UNIX_NETWORK_PROGRAMING_HEADER_
#include    <stdio.h>
#include    <unistd.h>
#include    <stdlib.h>
#include    <errno.h>
#include    <sys/types.h>
#include    <string.h>
#include    <wait.h>
#include    <signal.h>
#include    <fcntl.h>

#include    <iostream>

#include    <sys/socket.h>
#include    <arpa/inet.h>

const int SUCCESSFUL = 0;
const int FAILED = -1;
const int MAXLINE = 1024;
const int LISTEN_Q = 1024;
typedef struct sockaddr SA;

ssize_t writen(int sockfd, const void* vptr, size_t sendlen)
{
    ssize_t writedlen = 0;
    const char* sendbuf;
    sendbuf = (const char*)vptr;
    while(sendlen > 0)
    {
        writedlen = write(sockfd, sendbuf, sendlen);
        if (writedlen < 0)
        {
            if (errno == EINTR)
            {
                writedlen = 0;
            }
            else
            {
                //error
                return -1;
            }

        }
        sendlen -= writedlen;
        sendbuf += writedlen;
    }
    //successfull,return bytes number of not sended
    return sendlen;
}

ssize_t readline(int fd, void* vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c;
    char* ptr;

    ptr = (char*) vptr;
    for (n = 1; n < maxlen; n++)
    {
again:
        if ( (rc = read(fd, &c, 1)) == 1)
        {
            *ptr++ = c;
            if (c == '\n')
            {
                break;
            }
        }
        else if (rc == 0)
        {
            *ptr = 0;
            return (n-1);
        }
        else 
        {
            if (errno == EINTR)
            {
                goto again;
            }
            return (-1);
        }
    }
    *ptr = 0;
    return (n);
}

static int setSockReUseAddr(int listenfd)
{
    int optval = 1;
    socklen_t optlen = sizeof(optval);
    if (FAILED == setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, 
                            (const void*)&optval, optlen))
    {
        return FAILED;
    }
    return SUCCESSFUL;
}

static int setNonBlock(int sockfd)
{
    int flags;
    if ( (flags = fcntl(sockfd, F_GETFL, 0)) < 0)
    {
        return flags;
    }
    flags |= O_NONBLOCK;
    int result;
    if ( (result = fcntl(sockfd, F_SETFL, flags)) < 0)
    {
        return result;
    }
    return SUCCESSFUL;
}

static int clrNonBlock(int sockfd)
{
    int flags;
    if ( (flags = fcntl(sockfd, F_GETFL, 0)) < 0)
    {
        return flags;
    }
    flags &= ~O_NONBLOCK;
    int result;
    if ( (result = fcntl(sockfd, F_SETFL, flags)) < 0)
    {
        return result;
    }
    return SUCCESSFUL;
}

#endif
