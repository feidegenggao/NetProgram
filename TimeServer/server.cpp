/*
 * ============================================================================
 *
 *       Filename:  client.cpp
 *
 *    Description:  Get current time of server
 *
 *        Version:  1.0
 *        Created:  11/12/2012 09:46:07 AM
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
    if (argc != 2)
    {
        printf("using:%s port \n", argv[0]);
        if ((atoi(argv[1]) > 65535))
        {
            perror("listen port should less than 65535");
        }
        exit(0);
    }
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(argv[1]));
    std::cout<<"htonl"<<htons(atoi(argv[1]))<<std::endl;

    if ( -1 == bind(listenfd, (SA *) &servaddr, sizeof(servaddr)))
    {
        perror("bind error");
    }
    if ( - 1 == (listen(listenfd, LISTENQ)))
    {
        perror("listen error");
    }

    for (; ; )
    {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}
