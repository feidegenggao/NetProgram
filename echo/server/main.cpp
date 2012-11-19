/*
 * ============================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  echo server
 *
 *        Version:  1.0
 *        Created:  11/17/12 19:58:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "NetProgram/unp.h"
#include    "echo_server.h"

void sig_child(int signo)
{
    pid_t   pid;
    int     stat;

    while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
    //pid = wait(&stat);
        printf("child %d terminated\n", pid);
    return;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "USAGE:%s listenport\n", argv[0]);
        exit(FAILED);
    }
    int listenport = atoi(argv[1]);
    if (listenport <= 0 or listenport > 65535)
    {
        fprintf(stderr, "Listen port should in(0, 65535)\n");
        exit(FAILED);
    }

    int listenfd  = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == FAILED)
    {
        perror("create listen socket error");
    }

    struct sockaddr_in listenaddr;
    listenaddr.sin_family = AF_INET;
    listenaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    listenaddr.sin_port = htons(listenport);
    if ( FAILED == (bind(listenfd, (struct sockaddr*)&listenaddr, sizeof(listenaddr))))
    {
        fprintf(stderr, "bind listenport:%d error\n", listenport);
        exit(FAILED);
    }


    if ( SUCCESSFUL != listen(listenfd, LISTEN_Q))
    {
        fprintf(stderr, "listen error:%s\n", strerror(errno));
        exit(FAILED);
    }
    
    signal(SIGCHLD, sig_child);

    pid_t childpid;
    int acceptfd;
    for (; ; )
    {
        if ( FAILED != (acceptfd = accept(listenfd, NULL, NULL)))
        {
            if ( (childpid = fork()) == 0)
            {
                close(listenfd);
                echo_server(acceptfd);
                exit(0);
            }
            close(acceptfd);
        }
        else
        {
            perror("accept error.");
        }
        
    }
}
