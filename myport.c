#include "myport.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    uint8_t bit0 :1;
    uint8_t bit1 :1;
    uint8_t bit2 :1;
    uint8_t bit3 :1;
    uint8_t bit4 :1;
    uint8_t bit5 :1;
    uint8_t bit6 :1;
    uint8_t bit7 :1;
}myBITS_t;

typedef struct{
    uint8_t low :4;
    uint8_t high :4;
}myNYBBLE_t;

typedef union{
    uint8_t byte;
    myBITS_t bits;
    myNYBBLE_t nybbles;
}myBYTE_t;

typedef  myBYTE_t _8BITPORT;

typedef union 
{
    uint16_t full;
    struct{
        _8BITPORT low;
        _8BITPORT high;
    };
    uint16_t bit0 :1;
    uint16_t bit1 :1;
    uint16_t bit2 :1;
    uint16_t bit3 :1;
    uint16_t bit4 :1;
    uint16_t bit5 :1;
    uint16_t bit6 :1;
    uint16_t bit7 :1;
    uint16_t bit8 :1;
    uint16_t bit9 :1;
    uint16_t bit10 :1;
    uint16_t bit11 :1;
    uint16_t bit12 :1;
    uint16_t bit13 :1;
    uint16_t bit14 :1;
    uint16_t bit15 :1;
}_16BITPORT;

//Este static solo es suficiente para limitar el scope,no?
static  union{
    struct{
        _8BITPORT B;
        _8BITPORT A; //La consigna pedia B como LSBYTE
    };
    _16BITPORT D;
}PORT;


static void binary_print(void * value, uint8_t size)
{
    uint64_t *ptr = (uint64_t *)value;
    uint64_t mask = 1ULL<<(size * 8 - 1);
    for (uint8_t a = 0; a < size*8; a++,mask>>=1)
    {    
        *ptr & mask ? printf("1") : printf("0");
        if ((a % 8) == 7)
        {
            printf(" ");
        }
    }
    printf("\n");
}



//Asume que los valores estan en rangos, las funciones superiores salvaguardan eso
static int bitValue(uint8_t _port, uint8_t bit, uint8_t value)
{

    switch(_port)
    {
        case PortA:
        {
            switch(bit)
            {
                case 0:
                    PORT.A.bits.bit0 = value;
                    break;
                case 1:
                    PORT.A.bits.bit1 = value;
                    break;
                case 2:
                    PORT.A.bits.bit2 = value;
                    break;
                case 3:
                    PORT.A.bits.bit3 = value;
                    break;
                case 4:
                    PORT.A.bits.bit4 = value;
                    break;
                case 5:
                    PORT.A.bits.bit5 = value;
                    break;
                case 6:
                    PORT.A.bits.bit6 = value;
                    break;
                case 7:
                    PORT.A.bits.bit7 = value;
                    break;
            }
            break;
        }   

        case PortB:
        {
            switch(bit)
            {
                case 0:
                    PORT.B.bits.bit0 = value;
                    break;
                case 1:
                    PORT.B.bits.bit1 = value;
                    break;
                case 2:
                    PORT.B.bits.bit2 = value;
                    break;
                case 3:
                    PORT.B.bits.bit3 = value;
                    break;
                case 4:
                    PORT.B.bits.bit4 = value;
                    break;
                case 5:
                    PORT.B.bits.bit5 = value;
                    break;
                case 6:
                    PORT.B.bits.bit6 = value;
                    break;
                case 7:
                    PORT.B.bits.bit7 = value;
                    break;
            }
            break;
        }         
        case PortD:
        {
            switch(bit)
            {
                case 0:
                    PORT.D.low.bits.bit0 = value;
                    break;
                case 1:
                    PORT.D.low.bits.bit1 = value;
                    break;
                case 2:
                    PORT.D.low.bits.bit2 = value;
                    break;
                case 3:
                    PORT.D.low.bits.bit3 = value;
                    break;
                case 4:
                    PORT.D.low.bits.bit4 = value;
                    break;
                case 5:
                    PORT.D.low.bits.bit5 = value;
                    break;
                case 6:
                    PORT.D.low.bits.bit6 = value;
                    break;
                case 7:
                    PORT.D.low.bits.bit7 = value;
                    break;    
                case 8:
                    PORT.D.high.bits.bit0 = value;
                    break;
                case 9:
                    PORT.D.high.bits.bit1 = value;
                    break;
                case 10:
                    PORT.D.high.bits.bit2 = value;
                    break;
                case 11:
                    PORT.D.high.bits.bit3 = value;
                    break;
                case 12:
                    PORT.D.high.bits.bit4 = value;
                    break;
                case 13:
                    PORT.D.high.bits.bit5 = value;
                    break;
                case 14:
                    PORT.D.high.bits.bit6 = value;
                    break;
                case 15:
                    PORT.D.high.bits.bit7 = value;
                    break;    
            }

            break;
        }
        default: return MYPORT_FAILURE;
    }

    return MYPORT_SUCCESS;
}

static const uint8_t maxBits[_Ports_amount] = {
    [PortA]= sizeof(_8BITPORT) * 8,
    [PortB]= sizeof(_8BITPORT) * 8,
    [PortD]= sizeof(_16BITPORT) * 8
    };

int bitSet(int _port,uint8_t _bit_starting_from_zero)
{
    //lazy eval prevents going out of bounds on maxBits
    if (_port >= _Ports_amount || _bit_starting_from_zero >= maxBits[_port])
    {
        return MYPORT_FAILURE;
    }
    
    bitValue(_port,_bit_starting_from_zero,1);

    return MYPORT_SUCCESS;
}


int bitClr(int _port,uint8_t _bit_starting_from_zero)
{
    if (_port >= _Ports_amount || _bit_starting_from_zero >= maxBits[_port])
    {
        return MYPORT_FAILURE;
    }
    bitValue(_port,_bit_starting_from_zero,0);
     
    return MYPORT_SUCCESS;
    
}

int bitGet(int _port,uint8_t _bit_starting_from_zero)
{
    uint16_t mask;
    if (_port >= _Ports_amount || _bit_starting_from_zero >= maxBits[_port])
    {
        return MYPORT_FAILURE;
    }
    switch(_port)
    {
        case PortD:
        case PortA: 
            mask = 1 << (_bit_starting_from_zero+ sizeof(PORT.A)*8);
            break;

        case PortB:
            mask = 1<< _bit_starting_from_zero;
            break;
    }
    binary_print(&mask,sizeof(mask));
    if (mask & PORT.D.full)
        return 1;
    else
        return 0;
    
}

int bitToggle(int _port,uint8_t _bit_starting_from_zero)
{
    if (_port >= _Ports_amount || _bit_starting_from_zero >= maxBits[_port])
    {
        return MYPORT_FAILURE;
    }
    
    bitValue(_port,_bit_starting_from_zero,!bitGet(_port,_bit_starting_from_zero));

    return MYPORT_SUCCESS;
}


int maskOn(int _port,uint16_t _mask)
{
    uint8_t a;
    if (_port >= _Ports_amount)
    {
        return MYPORT_FAILURE;
    }
    for (a = 0; a < maxBits[_port];a++)
    {
        if (_mask & (1<<a))
        {
            bitValue(_port,a,1);
        }
    }

    return MYPORT_SUCCESS;
} 
int maskOff(int _port,uint16_t _mask)
{
    uint8_t a;
    if (_port >= _Ports_amount)
    {
        return MYPORT_FAILURE;
    }
    for (a = 0; a < maxBits[_port];a++)
    {
        if (_mask & (1<<a))
        {
            bitValue(_port,a,0);
        }
    }
    return MYPORT_SUCCESS;
}
int maskToggle(int _port,uint16_t _mask)
{
    uint8_t a;
    if (_port >= _Ports_amount)
    {
        return MYPORT_FAILURE;
    }
    for (a = 0; a < maxBits[_port];a++)
    {
        if (_mask & (1<<a))
        {
            bitValue(_port,a,!bitGet(_port,a));
        }
    }
    return MYPORT_SUCCESS;
}


void showPorts(void)
{
    printf("Port A:\n");
    binary_print(&PORT.A,sizeof(PORT.A));
    printf("Port B:\n");
    binary_print(&PORT.B,sizeof(PORT.B));
    printf("Port D:\n");
    binary_print(&PORT.D,sizeof(PORT.D));
}