/*
 * ============================================================================
 *
 *       Filename:  client.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/23/2012 02:46:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "NetProgram/unp.h"

void argCheck(int argc, char** argv);
void dg_cli(FILE *fp, int clientfd, 
        const struct sockaddr* pserveraddr, socklen_t servlen);

int main(int argc, char** argv)
{
    argCheck(argc, argv);
    int serverport = atoi(argv[2]);
    int clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serveraddr, clientaddr;

    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &serveraddr.sin_addr);
    serveraddr.sin_port = htons(serverport);

    dg_cli(stdin, clientfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
}

void argCheck(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "USAGE:%s serverAddr serverPort\n", argv[0]);
        exit(FAILED);
    }
    return;
}

void dg_cli(FILE *fp, int clientfd, 
        const struct sockaddr* pserveraddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    while(fgets(sendline, MAXLINE, fp) != NULL)
    {
        sendto(clientfd, sendline, strlen(sendline), 0, pserveraddr, servlen);
        n = recvfrom(clientfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;
        fputs(recvline, stdout);
    }
}
