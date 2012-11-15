/*
 * ============================================================================
 *
 *       Filename:  unp.h
 *
 *    Description:  headers of NetProgram
 *
 *        Version:  1.0
 *        Created:  11/12/2012 10:30:04 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#ifndef     _NET_PROGRAM_HEADER_
#define     _NET_PROGRAM_HEADER_
#include    <iostream>
#include    <arpa/inet.h>
#include    <netinet/in.h>
#include    <string.h>
#include    <strings.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <error.h>
#include    <errno.h>
#include    <unistd.h>
#include    <time.h>

const int MAXLINE = 1024;
const int LISTENQ = 1024;
typedef const struct sockaddr SA;
#endif
