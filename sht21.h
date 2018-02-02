//--------------------------------------------------------------------------------------------------

#ifndef SHT21_H
#define SHT21_H

//=== Includes =====================================================================================	

#include "std_c.h"

//=== Preprocessing directives (#define) ===========================================================

#define	ERROR_SHT21_I2C				1
#define	ERROR_SHT21_CRC_TEMP		2
#define	ERROR_SHT21_CRC_HUMIDITY	4

//=== Type definitions (typedef) ===================================================================

//=== Global constants (extern) ====================================================================

//=== Global variables (extern) ====================================================================

uint8	Sht21Error;

//=== Global function prototypes ===================================================================

uint8 SHT21_Read(int16 *temp,uint8 *humidity);
void PrintSht21Error(void);

#endif

