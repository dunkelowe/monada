
//=== Includes =====================================================================================

#include "std_c.h"
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <stdlib.h>
#include "i2c.h"
#include "sht21.h"
#include "raspi.h"

//=== Preprocessing directives (#define) ===========================================================

//=== Type definitions (typedef) ===================================================================

//=== Global constants =============================================================================

//=== Global variables =============================================================================

//=== Local constants  =============================================================================

//=== Local variables ==============================================================================

//=== Local function prototypes ====================================================================

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{ 
	uint32	Counter;
	int16 Temperature;
	uint8 Humidity;
	uint8 HwRev;
	char Mode;	
	
	Counter = 0;
	Mode = 0;
	
	HwRev = GetRaspberryHwRevision();
	
	if((argc > 1) &&  ((argv[1][0]=='S') || (argv[1][0]=='T') || (argv[1][0]=='H'))) Mode = argv[1][0];
		
	if(!Mode) 
	{
		
		//printf("Raspi-SHT21 V3.0.0 by Martin Steppuhn (www.emsystech.de) [" __DATE__ " " __TIME__"]\n");
		//printf("Options:\n");
		printf("Temperatura y Humedad RM5 - Investigación IATM\n");
		//printf("   S : [20.0 99]\n");	aaaaaaaaa
		//printf("   L : [temperature=20.0][humidity=99]\n");	
		//printf("   C : [Temperature,20,0][Humidity,99]\n");
		printf("RaspberryHwRevision=%i\r\n",HwRev);
	}	
	
	if(HwRev < 2) 	I2C_Open("/dev/i2c-0");	 // Hardware Revision 1.0
		else		I2C_Open("/dev/i2c-1");  // Hardware Revision 2.0
	I2C_Setup(I2C_SLAVE, 0x40);
	
	if(I2cError)
	{	
		I2C_PrintError();
		exit(1);
	}
			
	SHT21_Read(&Temperature,&Humidity);
	if(Sht21Error == 0)
	{
		if(     Mode == 'S') printf("%.1f\t%u\n",((float)Temperature)/10,Humidity);
		else if(Mode == 'T') printf("%.1f\n",((float)Temperature)/10);
		else if(Mode == 'H') printf("%u\n",(Humidity));
		else
		{
			while(1)
			{
				SHT21_Read(&Temperature,&Humidity);
				if(Sht21Error == 0) printf("%lu\t%.1f\t%u\n",Counter++,((float)Temperature)/10,Humidity);
					else		{	PrintSht21Error();	I2cError = 0;	}
				DelayMs(10000);
			}
		}
	}
	else
	{
		PrintSht21Error();
	}
	I2C_Close();
	return(0);
}

