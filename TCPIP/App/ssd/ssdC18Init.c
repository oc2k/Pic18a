/*********************************************************************
 *
 *	start/shutdown (SSD)  code
 *  Module for Microchip TCP/IP Stack
 *	 -as basically Provides __init to skip main code
 *	 -Reference: RFC 0000
 *
 *********************************************************************
 * FileName:        ssdC18Init.c
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
#define __SSDC18INIT_C

#include "TCPIP Stack/TCPIP.h"

/****************************************************************************
  Section:
	Constants and Global Variables
  ***************************************************************************/

//for example_/#define DNS_PORT		53u					// Default port for DNS resolutions
//for example_/static UDP_SOCKET MySocket = INVALID_UDP_SOCKET;	// UDP socket to use for DNS queries


/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/



/*****************************************************************************
  Function:
	void bSsdOscllatorControl(void)

  Description:
// ----------- as default setting ---
//	REGISTER 3-2: OSCCON: OSCILLATOR CONTROL REGISTER
//	R/W-0 U-0 U-0 U-0 R-q U-0 R/W-0 R/W-0
//	IDLEN — — — OSTS(1) — SCS1 SCS0
//	bit 7 bit 0
// ----------- as default setting ---
//	bit 7 IDLEN: Idle Enable bit
//	bit 3 OSTS: Oscillator Status bit(1)
//	bit 1-0 SCS<1:0>: System Clock Select bits
//	+	When FOSC2 = 1; (FOSC2=ON)
//	+	00 = Primary oscillator
//		When FOSC2 = 0;
//		00 = Internal oscillator
// ----------- as default setting ---
// Switch to primary oscillator mode, regardless of if the config fuses 
// tell us to start operating using the the internal RC
// The external clock must be running and must be 25MHz for the 
// Ethernet module and thus this Ethernet bootloader to operate.
//	OSCCON = 0x00;
// ----------- as default setting ---

// ----------- (0),(1),(0),(0),-,-,-,-
//	REGISTER 3-1: OSCTUNE: PLL BLOCK CONTROL REGISTER
//	R/W-0 R/W-0 R/W-0 R/W-0 U-0 U-0 U-0 U-0
//	PPST1 PLLEN(1) PPST0 PPRE — — — —
// --- (0),         (1),      (0),  (0),-,-,-,-
//	bit 7 bit 0
// DEFAULT>> (Divide-by-3),(PLL is enabled),(Postscaler is disabled),(Divide-by-3) Conclusion: OSC=41.666667Mhz
// Enable 4x/5x/96MHz PLL on PIC18F87J10, PIC18F97J60, PIC18F87J50, etc.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:

  ***************************************************************************/
void bSsdOscllatorControl(void)
{
	OSCTUNE = 0x40;
}

/*****************************************************************************
  Function:
	void bSsdWdtSetting(void)

  Description:
    ...

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:

  ***************************************************************************/
void bSsdWdtSetting(void)
{
	WDTCONbits.SWDTEN = 1; // to set Watchdog timer
}

/*****************************************************************************
  Function:
	void bSsdPortInit(void)

  Description:
    ...

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Remarks:

  ***************************************************************************/
void bSsdPortInit(void)
{
	// Ports clear output, and configuration
		PORTA=0; LATA=0;
		PORTB=0; LATB=0;
		PORTC=0; LATC=0;
		PORTD=0; LATD=0;
		PORTE=0; LATE=0;
	// -------------------------------------
	// ADC configruation initial
	#if defined(STACK_USE_HAL_A2D)
		__InitA2d();
	#elif 0

		// AD Channel
		ADCON0 = 0x01;		  // ADON, Channel 0
		ADCON1 = 0x0E;		  // Vdd/Vss is +/-REF, AN0 is analog
		ADCON2 = 0xBE;            // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)

		// Enable internal PORTB pull-ups
		INTCON2bits.RBPU = 0;
	#else
	// ------------------
	//	bit 7 bit 0
	//	— — [VCFG1 VCFG0]	 [PCFG3 PCFG2 PCFG1 PCFG0]
	//	PCFG<3:0>, AN15(1), AN14(1), AN13(1), AN12(1), AN11, AN10, AN9, AN8, AN7, AN6, AN5(2), AN4, AN3, AN2, AN1(3), AN0(3)
	// 0E:	1110 D D D D D D D D D D D D D D D A
	// 0F:	1111 D D D D D D D D D D D D D D D D
		ADCON1 = 0x0F; // All Digitials
	// ------------------
	#endif
}

/*****************************************************************************
  Function:
	void bSsdTimer1CFG(void)

  Summary:
	None
	
  Description:
	...

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None

  ***************************************************************************/
void bSsdTimer1CFG(void)
{

	Tmr1Control_init();
	Tmr1Resetting();
	AssertTmr1INT(), Tmr1IntLoPRIORITY(); // Enable Timer0 interrupt and set to high priority
}

/*****************************************************************************
  Function:
	void bSsdIntCFG(void)

  Summary:
	None
	
  Description:
	...

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None

  ***************************************************************************/
void bSsdIntCFG(void)
{

	ITPic16Compatibility();
}

/*****************************************************************************
  Function:
	void aSsdInitMcu(void)

  Summary:
	None
	
  Description:
	...

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None

  ***************************************************************************/
void aSsdInitMcu(void)
{
	// -------------------------------------
	// System clock configuration
		bSsdOscllatorControl();
	//
	// WatchDOGTimer
	bSsdWdtSetting();
	bSsdPortInit();
	// Timer# configuration
	#if 0 //ie:_/!defined(TICKS_PER_SECOND)
		bSsdTimer0CFG();
	#endif
	//
		bSsdTimer1CFG();
	// Interrupt configuration
	bSsdIntCFG();
	// -------------------------------------

	// -----------==--------------------------
	//	vv
		#if defined(STACK_USE_HAL_A2D)
			ssdInitOsREGs();	// main.h >> 
			ssdInitHalA2DREGs();// HalA2D.h >> 
		#endif
		#if defined(STACK_USE_HAL_SCI_UART)
			initE16UartONE();			// HalSCI.h >>
		#endif
		#if defined(STACK_USE_HAL_UART2TCP)
			ssdInitHalTCPREGs();		// UART2TCPBridge.h >> 
		#endif
		#if defined(STACK_USE_IF_TKNCMD)
			ssdInitIfTknCMDREGs(); // ifTknCMD.h >> 
		#endif

		#if defined(STACK_USE_HMI_PROTOCOL)
			ssdInitHmiREGs(); // HmiMstMSG.h >> 
		#endif
	//	^^
	// -----------==--------------------------
}

/*****************************************************************************
  Function:
	void __init(void)

  Summary:
	None
	
  Description:
	in between c018i to main

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None

  ***************************************************************************/
void __init(void)
{

	__NOP();  // Help to track startup CODE
	__NOP();
	__NOP();
	__NOP();  // Help to track startup CODE
}

