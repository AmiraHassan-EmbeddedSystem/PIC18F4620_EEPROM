#include "mcal_eeprom.h"
Std_ReturnType EEPROM_WriteByte(uint16 address, uint8 data)
{
    Std_ReturnType ret = E_OK;
    // Take the state of interrupt
    uint8 state_interrupt = INTCONbits.GIE;
    
    // Store Address
    EEADRH = (uint8)((address >> 8) & 0x03);
    EEADR =  (((uint8)address) & 0xFF);
    
    // Stroe Data
    EEDATA = data;
    
    // Select Data EEPROM Memory -> EECON1bits.EEPGD = 0
    EEPROM_MEMORY();
//    EECON1bits.EEPGD = 0
    //Select Flash Program/Data EEPROM -> EECON1bits.CFGS = 0
    EEPROM_OR_FLASH();
//    EECON1bits.CFGS = 0
    
    // Enable Writing On Data EEPROM
    ALLOW_WRITE_FLASH_EEPROM();
//    EECON1bits.WREN = 1;
    
    // Disable All Interrupts
    Interrupt_globalInterruptDisable();
//    INTCONbits.GIE = 0;
    
    // Store Sequence
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    // Initiate Writing On EPPROM
    INITIATE_WRITING_EEPROM();
//    EECON1bits.WR = 1;
    while(EECON1bits.WR);
    
    // Inhibits Writing On Data EEPROM
    INHIBITS_WRITE_FLASH_EEPROM();
    
    // return state of interrupt
    INTCONbits.GIE = state_interrupt;
    
    return ret;
}

Std_ReturnType EEPROM_ReadByte(uint16 address, uint8 *data)
{
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == data){
        ret = E_NOT_OK;
    }
    else{
        ret = E_OK;
        // Store Address
        EEADRH = (uint8)((address >> 8) & 0x03);
        EEADR =  (((uint8)address) & 0xFF);
        
        // Select Data EEPROM Memory -> EECON1bits.EEPGD = 0
        EEPROM_MEMORY();
        //Select Flash Program/Data EEPROM -> EECON1bits.CFGS = 0
        EEPROM_OR_FLASH();
        
        // Initiate Reading From EPPROM
        INITIATE_READING_EEPROM();
        
        // Wait Until Reading Operation Is Finished -> Delay with 2 cycle
        Nop(); Nop();
        
        // Return Data
        *data = EEDATA;   
    }
    return ret;
}

