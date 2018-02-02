
//=== Includes =====================================================================================

#include "std_c.h"
#include "i2c.h"
#include "sht21.h"
#include "raspi.h"
#include <stdio.h>

//=== Preprocessing directives (#define) ===========================================================

//=== Type definitions (typedef) ===================================================================

//=== Global constants =============================================================================

//=== Global variables =============================================================================

uint8	Sht21Error;

//=== Local constants  =============================================================================

//=== Local variables ==============================================================================

//=== Local function prototypes ====================================================================

uint8 CalcSht21Crc(uint8 *data,uint8 nbrOfBytes);

//--------------------------------------------------------------------------------------------------
// Name:      SHT21_Read
// Function:  
//            
// Parameter: 
// Return:    
//--------------------------------------------------------------------------------------------------
uint8 SHT21_Read(int16 *temperature,uint8 *humidity)
{
	uint32	val;
	uint8	buf[4];
		
	Sht21Error = 0;
	
	//=== Softreset ==================================================
	
	I2C_Write1(0xFE);			// softreset < 15ms
	DelayMs(50);
	
	//=== Temperature =================================================

	I2C_Write1(0xF3);			// start temperature measurement
	DelayMs(260);				// Temperature@14Bit typ=66ms max=85ms
	I2C_Read(buf,3);			// read temperature data
	
	if(buf[2] == CalcSht21Crc(buf,2))  // check CRC
	{
		val = buf[0];
		val <<= 8;
		val += buf[1];
		val &= 0xFFFC;
  		  		
		//	T = -46,85 + 175,72 * St/65535      da 1/10K -->  * 10
		//	T = -468,5 + 1757,2 * St/65535		verinfachen
		//	T = -468,5 + St / 37,2956..			damit Konstante ganzzahlig wird mit 2 erweitern
		//  T = -937 + 2*St / 37,2956..			Bruch für Division mit 256 erweitern  
		//	T = (-937 +  (St * 512) / (37,2956.. * 256)  )  / 2
		//	T = (((St * 512) / 9548) - 937) / 2
  	  		
		//	val = (((val * 512) / 9548) - 937) / 2;
		*temperature = ((val * 512) / 9548);
		*temperature = ((*temperature) - 937) / 2;       
	}
	else
	{
		Sht21Error |= ERROR_SHT21_CRC_TEMP;
	}
	
	//=== Humidity ===================================================

	I2C_Write1(0xF5);			// start humidity measurement
	DelayMs(60);				// RH@12Bit typ=22ms max=20ms 
	I2C_Read(buf,3);			// read humidity data
	
  	if(buf[2] == CalcSht21Crc(buf,2))
	{	
  		val = buf[0];
  		val <<= 8;
  		val += buf[1];
  		val &= 0xFFFC;
  		  			
  		//   T = -6 + 125* Srh/65535      
  		//	 T = -6 + Srh / 524,28
  		//   T = -6 + (Srh * 256) / 134215      |  *256	 wegen Numerik erweitern
  	  		  		
  		val = ((val * 256) / 134215) - 6;
  		*humidity = val;
	}	
	else
	{
		Sht21Error |= ERROR_SHT21_CRC_TEMP;
	}
	
	if(I2cError) Sht21Error |= ERROR_SHT21_I2C;
	
	
	
	return Sht21Error;
}

//------------------------------------------------------------------------------
// Name:      
// Function:  
//            
// Parameter: 
// Return:    
//------------------------------------------------------------------------------
uint8 CalcSht21Crc(uint8 *data,uint8 nbrOfBytes)
{
	// CRC
	//const u16t POLYNOMIAL = 0x131; //P(x)=x^8+x^5+x^4+1 = 100110001
	
	uint8 byteCtr,bit,crc;

	crc = 0;

	//calculates 8-Bit checksum with given polynomial
	for (byteCtr = 0; byteCtr < nbrOfBytes; ++byteCtr)
	{ 
		crc ^= (data[byteCtr]);
		for (bit = 8; bit > 0; --bit)
		{
			if (crc & 0x80) crc = (crc << 1) ^ 0x131;
				else 		crc = (crc << 1);
		}
	}
	return(crc);
}

//--------------------------------------------------------------------------------------------------
// Name:      PrintSht21Error
// Function:  Print error flags as readable text.
//            
// Parameter: -
// Return:    -
//--------------------------------------------------------------------------------------------------
void PrintSht21Error(void)
{	
	if(Sht21Error & ERROR_SHT21_I2C)			printf("ERROR I2C-Port\n");
	if(Sht21Error & ERROR_SHT21_CRC_TEMP)		printf("ERROR Temperature CRC\n");
	if(Sht21Error & ERROR_SHT21_CRC_HUMIDITY)	printf("ERROR Humidity CRC\n");
}


