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
   int connfd = socket(AF_INET, SOCK_STREAM, 0);
   if (connfd == -1)
   {

   }
   struct sockaddr_in connaddr;
   connaddr.sin_family = AF_INET;
   inet_pton(AF_INET, argv[1], &(connaddr.sin_addr.s_addr));
   connaddr.sin_port = htons(connport);
   socklen_t connaddrlen = sizeof(connaddr);

   if (FAILED == connect(connfd, (const struct sockaddr*)&connaddr, connaddrlen))
   {
       perror("connect error.");
       exit(-1);
   }

   echo_client(stdin, connfd);
}
