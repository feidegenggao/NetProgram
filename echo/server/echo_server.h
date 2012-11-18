/*
 * ============================================================================
 *
 *       Filename:  echo_server.h
 *
 *    Description:  echo server
 *
 *        Version:  1.0
 *        Created:  11/18/2012 01:29:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     _ECHO_SERVER_HEADER_
#define     _ECHO_SERVER_HEADER_
#include    "NetProgram/unp.h"
void echo_server(int sockfd)
{
    ssize_t     n;
    char        buf[MAXLINE];

again:
    while ( (n = read(sockfd, buf, MAXLINE)) > 0)
    {
        printf("read %d bytes:(%s) from client\n", n, buf);
        writen(sockfd, buf,n);
    }
    if (n < 0 and errno == EINTR)
    {
        goto again;
    }
    else if (n < 0)
    {
        perror("read error");
    }
}
#endif
