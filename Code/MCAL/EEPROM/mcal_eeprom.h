/* 
 * File:   mcal_eeprom.h
 * Author: ah427
 *
 * Created on 14 ??????, 2024, 08:18 ?
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/* SECTION: Include */
#include "../GPIO/hal_gpio.h"

/* SECTION: Macro Function Declarations */

//Flash Program or Data EEPROM Memory Select bit
#define EEPROM_MEMORY()   (EECON1bits.EEPGD = 0)
#define FLASH_MEMORY()   (EECON1bits.EEPGD = 1)

// Flash Program/Data EEPROM or Configuration Select bit
#define CONFIGURATION_REGISTER()    (EECON1bits.CFGS = 1)
#define EEPROM_OR_FLASH()          (EECON1bits.CFGS = 0)

// Flash Program/Data EEPROM Write Enable bit
#define ALLOW_WRITE_FLASH_EEPROM()      (EECON1bits.WREN = 1)
#define INHIBITS_WRITE_FLASH_EEPROM()      (EECON1bits.WREN = 0)

// Disable All Interrupts
#define Interrupt_globalInterruptDisable()   (INTCONbits.GIE = 0)

// Initiate Writing In EEPROM
#define INITIATE_WRITING_EEPROM()   (EECON1bits.WR = 1) 

// Initiate Reading From EEPROM
#define INITIATE_READING_EEPROM()   (EECON1bits.RD = 1) 

/* SECTION: Data Type Declarations */

/* SECTION: Macro Declarations */

/* SECTION: Interface Function Declarations */
Std_ReturnType EEPROM_WriteByte(uint16 address, uint8 data);
Std_ReturnType EEPROM_ReadByte(uint16 address, uint8 *data);

#endif	/* MCAL_EEPROM_H */

