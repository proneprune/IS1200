#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


int getsw( void ){

    int Return_Value = (PORTD >> 8) & 0xF; //shift right 8 bits, AND the all bits except the least 4 significant
    return Return_Value;
}


int getbtns(void){
    int Return_Value = (PORTD >> 5) & 0x7; //shift right 5 bits, AND all except the 3 least significant
    return Return_Value;
}