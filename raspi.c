
//=== Includes =====================================================================================

#include "std_c.h"
#include "raspi.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

//=== Preprocessing directives (#define) ===========================================================

//=== Type definitions (typedef) ===================================================================

//=== Global constants =============================================================================

//=== Global variables =============================================================================

//=== Local constants  =============================================================================

//=== Local variables ==============================================================================

//=== Local function prototypes ====================================================================


//--------------------------------------------------------------------------------------------------
// Name:        GetRaspberryHwRevision
// Function:  	Check wich Hardware is used:
//				http://www.raspberrypi.org/archives/1929
//	
//				Model B Revision 1.0 									2
//				Model B Revision 1.0 + ECN0001 (no fuses, D14 removed) 	3
//				Model B Revision 2.0 									4, 5, 6
//            
// Parameter: 	-
// Return:      0=no info , 1=HW Rev.1, 2=HW Rev.2
//--------------------------------------------------------------------------------------------------
int GetRaspberryHwRevision(void)
{	
	FILE *fp;
	char line[32];
	char s[32];
	int i;
	
	fp = fopen("/proc/cpuinfo", "r");		// open as file
	if(fp != NULL)
	{	
		while(fgets(line,32,fp))			// get line
		{
			sscanf(line,"%s : %x",(char*)&s,&i);	// parse for key and value
			//printf("[%s] [%i]\r\n",s,i);
			if(strcmp(s,"Revision") == 0)		// check for "Revision"
			{			
				//printf("Found: %s=%i\r\n",s,i);
				if(i < 4)  return 1;
				else		return 2;
			}
		}
	}
	else
	{
		//printf("cpuinfo not available.\r\n"); 
		return 0;
	}
	//printf("no revision info available.\r\n"); 
	return 0;
}


/*int GetRaspberryHwRevision(void)
{	
	FILE *fp;
	char line[64];
	char s1[64];
	char s2[64];
	int i;
	
	fp = fopen("/proc/cpuinfo", "r");		// open as file
	if(fp != NULL)
	{	
		while(fgets(line,64,fp))			// get line
		{  
			sscanf(line,"%s %s : %i",(char*)&s1,(char*)&s2,&i);		// parse for key and value
			if((strcmp(s1,"CPU") == 0)	&&  (strcmp(s2,"revision") == 0))			// check for "CPU revision"
			{			
				//printf("Found: %s=%i\r\n",s2,i);
				if(i < 4)  return 1;
					else	return 2;
			}
		}
	}
	else
	{
		//printf("cpuinfo not available.\r\n"); 
		return 0;
	}
	//printf("no revision info available.\r\n"); 
	return 0;
}*/

//--------------------------------------------------------------------------------------------------
// Name:      DelayMs and DelayUs
// Function:  Delay for Milliscond or Microseconds
//            
// Parameter: Time
// Return:    -
//--------------------------------------------------------------------------------------------------
void DelayMs(uint32 ms)
{
  struct timespec t, dummy ;

  t.tv_sec  = (time_t)(ms / 1000) ;
  t.tv_nsec = (long)(ms % 1000) * 1000000 ;
  nanosleep (&t, &dummy);
}

void DelayUs(uint32 us)
{
  struct timespec t, dummy ;

  t.tv_sec  = 0 ;
  t.tv_nsec = (long)(us * 1000) ;
  nanosleep (&t, &dummy);
}


