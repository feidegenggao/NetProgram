/*
 * ============================================================================
 *
 *       Filename:  client.cpp
 *
 *    Description:  get time client
 *
 *        Version:  1.0
 *        Created:  11/12/2012 11:04:45 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "NetProgram/unp.h"

int connect_nob(int sockfd, const SA* saptr, socklen_t salen, int nsec);
int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "USAGE:%s serverAddr serverPort\n", argv[0]);
        exit(-1);
    }
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 3)
    {
        printf("uage: %s serverip serverport\n", argv[0]);
        if (atoi(argv[2]) > 65535)
        {
            perror("server port is wrong, should less than 65535");
        }
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    //connect(sockfd, (SA *) &servaddr, sizeof(servaddr));
    if (-1 == (connect_nob(sockfd, (const SA*) &servaddr, sizeof(servaddr), 10)))
    {
        fprintf(stderr, "non block connect error\n");
        perror("connect error");
        exit(-1);
    }

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
        {
            perror("fputs error");
        }
    }

    if (n < 0)
    {
        perror("fputs error");
    }

    exit(0);
}

int connect_nob(int sockfd, const SA* saptr, socklen_t salen, int nsec)
{
    int n , error;
    socklen_t len;
    fd_set rset, wset;
    struct timeval tval;

    setNonBlock(sockfd);
    error = 0;
    if ( (n = connect(sockfd, saptr, salen)) < 0)
    {
        if (errno != EINPROGRESS)
        {
            return -1;
        }
    }

    if (n == 0)
    {
        goto done;
    }

    FD_ZERO(&rset);
    FD_SET(sockfd, &rset);
    wset = rset;
    tval.tv_sec = nsec;
    tval.tv_usec = 0;

    if ( (n = select(sockfd + 1, &rset, &wset, NULL, nsec ? &tval : NULL)) == 0)
    {
        close(sockfd);
        errno = ETIMEDOUT;
        return (-1);
    }

    if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset))
    {
        len = sizeof(error);
        if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
        {
            fprintf(stderr, "getsockopt error(%d):%s\n", error, strerror(errno));
            return (-1);
        }
    }
    else
    {
        fprintf(stderr, "select error, sockfd not set");
        exit(-1);
    }

done:
    clrNonBlock(sockfd);
    if (error)
    {
        fprintf(stderr, "getsockopt error is :%d\n", error);
        close(sockfd);
        errno = error;
        return (-1);
    }
    return (0);
}
