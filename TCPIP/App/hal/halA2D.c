/*********************************************************************
 *
 *	Hardware abstraction layer (HAL) A2D
 *  Module for Microchip TCP/IP Stack
 *	 -Provides hostname to IP address translation
 *	 -Reference: RFC 0000
 *
 *********************************************************************
 * FileName:        HALA2d.c
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
#define __HALA2D_C

#include "TCPIP Stack/TCPIP.h"	// All common header
#include "hal/halA2d.h"

#if defined(STACK_USE_HAL_A2D)
/****************************************************************************
  Section:
	Constants and Global Variables
  ***************************************************************************/
#pragma udata

	CHAR8 AdTMR;
	CHAR8 AdCNT;
	WORD_VAL AdRESULT;
	static CHAR8 adSaveSecond;

/****************************************************************************
  Section:
	Function Prototypes
  ***************************************************************************/
#pragma code


/*****************************************************************************
  Function:
	aHalA2d_MainMeasurePerSEC

  Summary:
	None
	
  Description:
	To Measure ADC Demo code

  Precondition:
	None

  Parameters:
	None

  Return Values:
	None
  	
  Remarks:
	None
  ***************************************************************************/
void aHalA2d_MainMeasurePerSEC()
{
	// -----------------------------
	// Key condition
	// ----------------------------- 
	if(adSaveSecond == oSecond) return; // Keycondition

	// -----------------------------
	// Base condition
	// -----------------------------

	adSaveSecond = oSecond;

	// -----------------------------
	// Core code
	// ----------------------------- 
	_selCh00();
	ad_On();
	ad_Go();
	u8i = 100; do{}while(--u8i); //__>> u8i.value = 100; do{}while(--u8i.value);
	ad_Done();
	AdRESULT.v[0] = ADRESL;
	AdRESULT.v[1] = ADRESH;

	__NOP();
	__NOP();

}


#endif
