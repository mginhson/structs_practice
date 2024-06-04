#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "myport.h"

//add coment


int main(int argc, char *argv[])
{
    
    maskOff(PortD,0xFFFF);
    showPorts();
    maskOn(PortD,0xABCD);
    showPorts();
    
    return 0;
}