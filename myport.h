#ifndef MYPORT_H
#define MYPORT_H
#include <stdint.h>
#define MYPORT_SUCCESS 0
#define MYPORT_FAILURE -1

enum{
    PortA,
    PortB,
    PortD,
    _Ports_amount
};

int bitSet(int _port,uint8_t _bit_starting_from_zero);
int bitClr(int _port,uint8_t _bit_starting_from_zero);
int bitGet(int _port,uint8_t _bit_starting_from_zero);
int bitToggle(int _port,uint8_t _bit_starting_from_zero);
int maskOn(int _port,uint16_t mask); //estaria bueno usar una union para determinar cual puede
//ser la mascara teorica mas grande, no se si solo se puede con _Generic();
int maskOff(int _port,uint16_t mask);
int maskToggle(int _port,uint16_t mask);
void showPorts(void);
#endif