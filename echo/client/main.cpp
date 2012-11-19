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

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "USAGE:%s serverAddr serverPort\n", argv[0]);
        exit(-1);
    } 
    int connport = atoi(argv[2]);

    struct sockaddr_in connaddr;
    connaddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(connaddr.sin_addr.s_addr));
    connaddr.sin_port = htons(connport);
    socklen_t connaddrlen = sizeof(connaddr);


    int connnu = 5;
    int connfd[connnu];
    for (int i = 0; i < connnu; i++)
    {
        connfd[i] = socket(AF_INET, SOCK_STREAM, 0);

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
