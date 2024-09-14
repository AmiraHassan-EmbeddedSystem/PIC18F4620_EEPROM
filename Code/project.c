/*
 * File:   project.c
 * Author: ah427
 *
 * Created on 14 ??????, 2024, 08:26 ?
 */


#include <xc.h>
#include "project.h"
#define _XTAL_FREQ 80000000UL


void initialization(void);
volatile uint8 writeData = 0, readData = 0;

void main(void) {
    initialization();
    EEPROM_WriteByte(0x3ff, writeData);
    EEPROM_ReadByte(0x3ff, &readData);
    while(1){
        __delay_ms(250);
        EEPROM_WriteByte(0x3ff, ++writeData);
        EEPROM_ReadByte(0x3ff, &readData);
        if(writeData == 20){
            writeData = 0;
        }
    }
    
    return;
}

void initialization(void){

}