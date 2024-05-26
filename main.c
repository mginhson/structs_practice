#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    for (uint32_t a = 0; a < argc; a++)
        puts(argv[a]);

    return 0;
}