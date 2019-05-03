#include <stdio.h>

#include "server.h"

int main()
{
    setvbuf(stdout, NULL, _IOLBF, 0);

    printf("Hello World!\n");

    server();

    return 0;
}
