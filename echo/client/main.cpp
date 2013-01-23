/*
 * ============================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  echo client
 *
 *        Version:  1.0
 *        Created:  11/17/12 19:58:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include   "NetProgram/unp.h" 
#include   "echo_client.h"
void sig_pipe(int signu)
{
    printf("pipe error");
    return;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "USAGE:%s serverAddr serverPort\n", argv[0]);
        exit(-1);
    } 
    signal(SIGPIPE, sig_pipe);
    int connport = atoi(argv[2]);

    struct sockaddr_in connaddr;
    connaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(connaddr.sin_addr.s_addr));
    connaddr.sin_port = htons(connport);
    socklen_t connaddrlen = sizeof(connaddr);


    int connnu = 1;
    int connfd[connnu];
    for (int i = 0; i < connnu; i++)
    {
        connfd[i] = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in clientaddr;
        clientaddr.sin_family = AF_INET;
        if ((inet_aton("192.168.13.200", (in_addr*)&clientaddr.sin_addr.s_addr)) == 0)
        {

        }
        //clientaddr.sin_addr.s_addr = htonl("192.168.13.200");
        clientaddr.sin_port = htons(0);

        int binderror = 0;
        if ( 0 > (binderror = bind(connfd[i], (struct sockaddr*)&clientaddr, sizeof(clientaddr))))
        {
            perror("bind error when port is 0");
        }
        printf("binderror:%d\n", binderror);

        if (connfd[i] == -1)
        {

        }
        if (FAILED == connect(connfd[i], (const struct sockaddr*)&connaddr, connaddrlen))
        {
            perror("connect error.");
            exit(-1);
        }
    }

    echo_client(stdin, connfd[0]);
}
