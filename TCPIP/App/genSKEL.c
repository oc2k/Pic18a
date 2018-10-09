/*********************************************************************
 *
 *	General (GEN) Skeleton
 *  Module for Project basic code
 *	 -Provides fixed RAM/ROM parameter defines
 *	 -Reference: RFC 0000
 *
 *********************************************************************
 * FileName:        genSKEL.c
 * Dependencies:    none (need review)
 * Processor:       PIC18
 * Compiler:        Microchip C18 v3.30 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * TPLv1                7/10/18		Original
 ********************************************************************/
#define __GENSKEL_C


#include "TCPIP Stack/TCPIP.h"	// All common header

//for example_/#define DNS_PORT		53u					// Default port for DNS resolutions
/****************************************************************************
  Section:
	Constants and Global Variables
  ***************************************************************************/

    #pragma udata ROMPARAM_BUFFER // 161121a01, Register in "osTools.c" >>>>SECTION    NAME=ROMPARAM_BUFFER  RAM=gpr8 ..__/#pragma udata bank8=0x800 // Register in "halSCI.c" >> 
	APP_CONFIG AppConfig; //							// Pic18APP_CONFIG; // ByteSIZE = 48+16+ (6+1+1) +6x4 = 6(x8) +2(x8) + 1(x8) + 3(x8)=12x8=96,ie: 60h (A0 - FF)..__/APP_CONFIG; ..__Pic18RamAppConfig __>>Pic18APP_CONFIG AppConfig; //APP_CONFIG AppConfig

#pragma udata 
	BYTE u8i;
	BYTE u8j;
	BYTE u8k;
	BYTE u8retVAL;
	WORD u16i;
	DWORD u32i;

	BYTE w8i;
	BYTE w8j;
	BYTE w8s;
	BYTE w8t;
	WORD w16i;
	WORD w16j;
	DWORD w32i;

	BYTE sys,sys2,sys5,sys6,sys7;
	BYTE isrMs,isrHms;
	BYTE hmSecond, oSecond, oMinute, oHour;
	WORD sysErr; //system error code as reporting
// -----------=89293475ljadlj9409aRW=----------------------------------------------------
#pragma romdata rombankRW=__constPIC18F67J60_RWProgMemStartPTR //0x10000-0x10400 as erase AREA
ROM RomUNsysPPRWParam Pic18RomSysPPnnParam =
{

	MY_DEFAULT_PROJ_PARAM0, // WORD w
	MY_DEFAULT_PROJ_PARAM1, // WORD w
	MY_DEFAULT_PROJ_PARAM2, // WORD w
	MY_DEFAULT_PROJ_PARAM3, // WORD w
	MY_DEFAULT_PROJ_PARAM4, // WORD w
	MY_DEFAULT_PROJ_PARAM5, // WORD w
	MY_DEFAULT_PROJ_PARAM6, // WORD w
	MY_DEFAULT_PROJ_PARAM7, // WORD w
	0
};
// -----------=89293475ljadlj9409aRW=----------------------------------------------------
ROM BYTE Pic18RomEraseResRWParam1[0x3A0];
ROM Pic18RomSystemReservedRWParam Pic18RomSysResRWParam1 = {0x55AA,0x55AA,0x55AA,0x55AA,0x55AA,0x55AA,0x55AA,0x55AA};
ROM Pic18RomSystemReservedRWParam Pic18RomSysResRWParam2 = {0x55AA,0x55AA,0x55AA,0x55AA,0x55AA,0x55AA,0x55AA,0x55AA};
// --------=89293475ljadlj9409bRO=-------------------------------------------------------
#pragma romdata rombankRO=__constPIC18F67J60_ROProgMemStartPTR //0x1000
//	VV
	// -- (###00 - ###1F) As system motor parameter area
	// ----------------1400 - ..
	// -----------------------------------------------------
	ROM RomUNsysROParam Pic18RomSysROParam =
	{
		__rom01SystemReadONLYAddressID,
		__rom04SystemStartYEAR,
		__rom06w8VersionINFO1,
		__rom07w8RES_PARAM1, // BYTE b
		0,
		__rom0Aw16RES_PARAM2, // WORD w
		__rom0Cw16RES_PARAM3, //WORD w
		__rom0Ew16RES_THRESHOLD, //WORD wPssCycOVER_THRESHOLD; // 0x600 // set the threshold to 135 degree in speed 7, As "Press Cycle Over" Encoder Difference Threshold, keyword "PssCycOVR"; Abbrev: "Pss" denote Press; "Cyc" denoted Cycle; "Ove" denoted Over; current mechine speed 7 brake angle (237 degree), ie: stop to stopped distance around 123 degree, thus tolerance should be 12 degree;//__>>wRESERVED;			// 0x0000, 0eWORD0x0000, //WORD wRESERVED;			// 0x0000, 0eWORD
	};
	ROM BYTE VI2[] = __strVersionINFO2;
	ROM BYTE VI2s[] = __strVI2SPACE;
	ROM BYTE VI3[] = __strVersionINFO3;
	ROM BYTE VI3s[] = __strVI3SPACE;
	ROM BYTE VI4[] = __strVersionINFO4;
	ROM BYTE VI4s[] = __strVI4SPACE;
	ROM BYTE VI5[] = __strVersionINFO5;
	ROM BYTE VI6[] = __strVersionINFO6;
	ROM BYTE VI6s[] = __strVI6SPACE;
	ROM BYTE VI7[] = __strVersionINFO7;
	ROM BYTE VI8[] = __strVer8HostNAME; //__>>__strVersionINFO8;
//	^
// -----------------------------------------------------
ROM UNAppCONFIGRO Pic18RomAppConfigRO =
{
	MY_DEFAULT_PROJ_PARAM0, //WORD w0;
		MY_DEFAULT_PROJ_PARAM1, //WORD w1;
		MY_DEFAULT_PROJ_PARAM2, //WORD w2;
		MY_DEFAULT_PROJ_PARAM3, //WORD w3;
		MY_DEFAULT_PROJ_PARAM4, //WORD w4;
		MY_DEFAULT_PROJ_PARAM5, //WORD w5;
		MY_DEFAULT_PROJ_PARAM6, //WORD w6;
		MY_DEFAULT_PROJ_PARAM7, //WORD w7;
	MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul, // IP_ADDR	MyIPAddr;				// (dw) IP address
	MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul, // IP_ADDR	MyMask; 				// (dw) Subnet mask
	MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul, // IP_ADDR	MyGateway;				// (dw) Default Gateway
	MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul, // IP_ADDR	PrimaryDNSServer;		// (dw) Primary DNS Server
	MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul, // IP_ADDR	SecondaryDNSServer; 	// (dw) Secondary DNS Server
	MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul, // IP_ADDR	DefaultIPAddr;			// (dw) Default IP address
	MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul, // IP_ADDR	DefaultMask;			// (dw) Default subnet mask
	0x00000000, //DWORD 	dRESERVED;				// (dw) RESERVED
};
// MAC Address Serialization using a MPLAB PM3 Programmer and 
// Serialized Quick Turn Programming (SQTP). 
// The advantage of using SQTP for programming the MAC Address is it
// allows you to auto-increment the MAC address without recompiling 
// the code for each unit.  To use SQTP, the MAC address must be fixed
// at a specific location in program memory.  Uncomment these two pragmas
// that locate the MAC address at 0x1FFF0.  Syntax below is for MPLAB C 
// Compiler for PIC18 MCUs. Syntax will vary for other compilers.
//#pragma romdata MACROM=0x1FFF0
//#pragma romdata
ROM BYTE SerializedMACAddressRO[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
// --------------=018adsfLDFKQ924851_b98678654RO=---------------------------------------
//
// --------=89293475ljadlj9409bRO=-------------------------------------------------------
#pragma code

/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/


/*****************************************************************************
  Function:
	aGenSystemClock

  Summary:
	None
	
  Description:
	normal clock process

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None
  	
  Remarks:
	None
  ***************************************************************************/
	static BYTE savMs, savHms;
void aGenSystemClock(void)
{
	// -------------------------------------
	// Key condition
	// -------------------------------------
	if(isrMs == savMs) return;
	savMs = isrMs;

	//////////////////////////////////////////////////
	// 1 millisecond (Ms)						//
	//////////////////////////////////////////////////
	#if defined(STACK_USE_HAL_UART2TCP)
		__clkstmMsgMSCountdown();
	#endif //!>>if defined(STACK_USE_HAL_UART2TCP)

	if(savHms == isrHms) 
return;

	savHms = isrHms;
	//////////////////////////////////////////////////
	//Per 100millisecond (Ms)						//
	//////////////////////////////////////////////////
	#if defined(STACK_USE_HAL_UART2TCP)
		__clkTCPHmsCountdown();
	#endif

	if(++hmSecond > 9)
	{
		hmSecond = 0;

		//////////////////////////////////////////
		//Per 1 Second (Sec)					//
		//////////////////////////////////////////

		// ======================
		// To test USB transfer stream by "oSecond"
		// ======================
		// --2a__BBBBB-----------------------------------
		// Per Minute
		if( ++oSecond >59){
			oSecond=0;

			//////////////////////////////////
			//Per 1 minute (Mnt)			//
			//////////////////////////////////
			if(++oMinute >119)
			{
				oMinute=0;

				//////////////////////
				//Per 2 Hour (Hr)	//
				//////////////////////
				oHour ++; // clocktick FF'''77''3B' (a cycle equal to 21.33333 day)

			}
			// else rule NOP
			// -------------------------------------

		}
		// else rule NOP
		// -------------------------------------

	}
	// else rule NOP
	// -------------------------------------
	
}

/*****************************************************************************
  Function:
	aGenSystemClock

  Summary:
	None
	
  Description:
	normal clock process

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None
  	
  Remarks:
	None
  ***************************************************************************/
//__
	void isrOsSystemCLOCK(void)
	{
		//----------------------------------------------------------------
		// .. TIMER1 Interrupt process
		//------------------------
		if (PIR1bits.TMR1IF){ // 1Ms timer overflow
	
			// -- user AREA --
			// -- user AREA --
	
			// system clock process
			if(++isrMs > 99)
			{
				// system clock process
				isrMs = 0;
				isrHms ++; //Per 100ms
	
				// -- user AREA --
				#if defined(STACK_USE_HAL_SCI_UART)
					// -------------------------------------XXX
					//	__isrUARTRxIdletmrHMSCountdown();
					// -------------------------------------XXX
				#endif //!>>if defined(STACK_USE_HAL_SCI_UART)
				// -- user AREA --
	
			}
	
			// system clock process
			Tmr1Resetting();
		
			// ----
			// Exit
			// ----
			PIR1bits.TMR1IF = 0;		//clear interrupt flag
		}
	}
