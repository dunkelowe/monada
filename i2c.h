
#ifndef I2C_H
#define I2C_H

//=== Includes =====================================================================================	

#include "std_c.h"

//=== Preprocessing directives (#define) ===========================================================

#define	ERROR_I2C_OPEN		1
#define	ERROR_I2C_SETUP		2
#define	ERROR_I2C_READ		4
#define	ERROR_I2C_WRITE		8

//=== Type definitions (typedef) ===================================================================

//=== Global constants (extern) ====================================================================

//=== Global variables (extern) ====================================================================

extern uint8	I2cError;

//=== Global function prototypes ===================================================================

void I2C_Open(char *dev);
void I2C_Close(void);
void I2C_Setup(uint32 mode,uint8 addr);
void I2C_Write1(uint8 d);
void I2C_Write2(uint8 d0,uint8 d1);
void I2C_Read(uint8 *data,uint8 length);
void I2C_PrintError(void);

#endif

