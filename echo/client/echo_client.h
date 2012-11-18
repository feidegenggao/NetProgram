/*
 * ============================================================================
 *
 *       Filename:  echo_client.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/18/2012 12:27:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     _ECHO_CLIENT_HEADER_
#define     _ECHO_CLIENT_HEADER_
#include    "NetProgram/unp.h"
void echo_client(FILE* fp, int connfd)
{
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    while(fgets(sendline, MAXLINE, fp) != NULL)
    {
        writen(connfd, sendline, strlen(sendline));
        if (readline(connfd, recvline, MAXLINE) == 0)
        {
            perror("echo_client(FILE*, int):serer terminated prematurely");
            exit(-1);
        }
        fputs(recvline, stdout);
    }
}
#endif
