/*
 * ============================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/16/2012 10:37:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    <stdio.h>

int main(void)
{
    union {
        short s;
        char c[sizeof(short)];
    }un;

    un.s = 0x0102;
    //CPU_VENDOR_OS will generate after configure in automake
    //printf("%s", CPU_VENDOR_OS);

    if (sizeof(short) == 2)
    {
        if (un.c[0] == 1 && un.c[1] == 2)
        {
            printf("big-endian\n");
        }
        else if (un.c[0] == 2 && un.c[1] == 1)
        {
            printf("little-endian\n");
        }
        else
        {
            printf("un.c[0]:%d\nun.c[1]:%d\n", un.c[0], un.c[1]);
            printf("unkown\n");
        }
    }
    else
    {
        printf("sizeof(short) = %d\n", sizeof(short));
    }

    return 0;
}

