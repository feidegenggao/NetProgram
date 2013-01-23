/*
 * ============================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/23/2012 02:37:20 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "NetProgram/unp.h"

//这句话是编译通不过的，为什么呢？第二个参数类型加了括号。这是为什么呢？
//void dg_echo(int serverfd, (struct sockaddr*) cliaddr, int cliaddrlen);
void dg_echo(int serverfd, struct sockaddr* cliaddr, int cliaddrlen);
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE:%s serverport\n", argv[0]);
        exit(FAILED);
    }
    int serverfd;
    uint16_t serverport = atoi(argv[1]);
    struct sockaddr_in serveraddr, cliaddr;

    serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddr.sin_family   = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port     = htons(serverport);

    socklen_t serveraddrlen = sizeof(serveraddr);
    bind(serverfd, (const struct sockaddr*)&serveraddr, serveraddrlen);

    dg_echo(serverfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr)); 
}
void dg_echo(int serverfd, struct sockaddr* cliaddr, int cliaddrlen)
{
    int n;
    socklen_t len;
    char recvbuf[MAXLINE];

    for (; ; )
    {
        len = cliaddrlen;
        n = recvfrom(serverfd, recvbuf, MAXLINE, 0, cliaddr, &len);
        sendto(serverfd, recvbuf, n, 0, cliaddr, len);
    }
}
