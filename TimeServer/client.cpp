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
#include    "unp.h"

int main(int argc, char** argv)
{
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

    connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

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
