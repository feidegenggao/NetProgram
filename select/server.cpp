/*
 * ============================================================================
 *
 *       Filename:  server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/21/2012 05:26:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL@UESTC
 *
 * ============================================================================
 */
#include    "NetProgram/unp.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE:%s listenport\n", argv[0]);
        exit(FAILED);
    }
    int listenport = atoi(argv[1]);
    if (!(listenport > 0 and listenport < 65535))
    {
        fprintf(stderr, "listenport should (0, 65535)\
                and we recommond do not use well known port");
        exit(FAILED);
    }

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == FAILED)
    {
        fprintf(stderr, "Create listenfd error:%s\n", strerror(errno));
        exit(FAILED);
    }
    setSockReUseAddr(listenfd);

    struct sockaddr_in listenaddr;
    bzero(&listenaddr, sizeof(listenaddr));
    listenaddr.sin_family = AF_INET;
    listenaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenaddr.sin_port = htons(listenport);

    socklen_t listenaddrlen = sizeof(listenaddr);
    if ( FAILED == bind(listenfd, 
                        (const struct sockaddr *)&listenaddr, 
                        listenaddrlen))
    {
        fprintf(stderr, "Bind error:%s\n", strerror(errno));
        exit(FAILED);
    }

    if ( FAILED == listen(listenfd, LISTEN_Q))
    {
        fprintf(stderr, "Listen error:%s\n", strerror(errno));
        exit(FAILED);
    }

    int maxfd = -1;
    int client[FD_SETSIZE];
    int nready = -1;
    int maxindex = -1;
    char recvbuf[MAXLINE];

    fd_set rset, allset;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    for (int i = 0;i < FD_SETSIZE; i++)
    {
        client[i] = -1;
    }
    maxfd = listenfd;

    for (; ;)
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                fprintf(stderr, "Select error:%s\n", strerror(errno));
                exit(FAILED);
            }
        }

        if (FD_ISSET(listenfd, &rset))
        {
            //Assume clientfd > 0
            int clientfd = accept(listenfd, NULL, NULL);
            int i = 0;
            for (; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = clientfd;
                    break;
                }
            }
            if (i == FD_SETSIZE) { fprintf(stderr, "Too many clients"); exit(FAILED);}
            FD_SET(clientfd, &allset);
            if (i > maxindex ) { maxindex = i;}
            if (clientfd > maxfd ) { maxfd = clientfd;}
        }

        for (int i = 0; i <= maxindex; i++)
        {
            int sockfd = client[i];
            if (sockfd < 0) continue;

            int readnu = 0;
            if (FD_ISSET(sockfd, &rset))
            {
                if ((readnu = read(sockfd, recvbuf, MAXLINE)) == 0)
                {
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                {
                    writen(sockfd, recvbuf, readnu);
                }
            }
        }
    }
}
