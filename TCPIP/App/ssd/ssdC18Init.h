/*********************************************************************
 *
 *	start/shutdown (SSD) Header
 *
 *********************************************************************
 * FileName:        ssdC18Init.h
 * Dependencies:    None
 * Processor:       PIC18
 * Compiler:        Microchip C18 v3.30 or higher
 *					
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
#ifndef __SSDC18INIT_H
#define __SSDC18INIT_H

#if defined(STACK_USE_HAL_A2D)
#include "hal/halA2d.h"
#endif
//for example_/#define DNS_TYPE_A				(1u)		// Constant for...

/*-----------==-------------------------------------------------------------
// Timer0 configuration
// -------------------
//	REGISTER 12-1: T0CON: TIMER0 CONTROL REGISTER
//	R/W-1 R/W-1 R/W-1 R/W-1 R/W-1 R/W-1 R/W-1 R/W-1
//	TMR0ON(1) T08BIT(0) T0CS T0SE PSA [T0PS2 T0PS1 T0PS0]
//	bit 7 bit 0
// -------------------
// T0CON: (88) as bypass prescaler
// -------------------
#define	T0Rate				1000 // critical adjust parameter
#define T0Offset			0 // to be adjust parameter
#define T0Prescale			1 // bypass Prescale
#define Tmr0Control_init()	T0CON = 0x88; // Include Assert Tmr0, bypassPreScale
#define	TMRDIVIDE			((GetPeripheralClock()/T0Rate/T0Prescale)+T0Offset) //__>>((picFreqOfOSC/T0Rate/T0Prescale/4)+T0Offset)
#define _invTMR0			(unsigned int) (-TMRDIVIDE)
#define Tmr0Resetting()\
	TMR0H = (unsigned char)(_invTMR0/0x100); \
	TMR0L = (unsigned char)(_invTMR0%0x100);
#define AssertTmr0()		(T0CONbits.TMR0ON = 1)
#define DeassertTmr0()		(T0CONbits.TMR0ON = 0)
#define AssertTmr0INT() 	(INTCONbits.TMR0IE=1)
#define DeassertTmr0INT()	(INTCONbits.TMR0IE=0)
#define Tmr0IntHiPRIORITY() (INTCON2bits.TMR0IP=1)
#define Tmr0IntLoPRIORITY()	(INTCON2bits.TMR0IP=0)
/*-----------==-------------------------------------------------------------*/

//------------------------------------------------------------------------
// Timer1 configuration
// -------------------
//	REGISTER 13-1: T1CON: TIMER1 CONTROL REGISTER
//	R/W-0 R-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0
//	RD16 (1) T1RUN (0)  [T1CKPS1 T1CKPS0] (00)   || T1OSCEN (0) T1SYNC (0) TMR1CS (0) TMR1ON (1)
//	bit 7 bit 0
// -------------------
// T1CON: (81) as 1ms Timer
// -------------------
#define	T1Rate				1000 // critical adjust parameter
#define T1Offset			0 // to be adjust parameter
#define T1Prescale			1 // bypass Prescale
#define Tmr1Control_init()	T1CON = 0x81;
#define	TMR1DIVIDE			((GetPeripheralClock()/T1Rate/T1Prescale)+T1Offset) //__>>((picFreqOfOSC/T0Rate/T0Prescale/4)+T0Offset)
#define _invTMR1			(unsigned int) (-TMR1DIVIDE)
#define Tmr1Resetting()\
	TMR1H = (unsigned char)(_invTMR1/0x100); \
	TMR1L = (unsigned char)(_invTMR1%0x100);
#define AssertTmr1()		(T1CONbits.TMR1ON = 1)
#define DeassertTmr1()		(T1CONbits.TMR1ON = 0)
#define AssertTmr1INT() 	(PIE1bits.TMR1IE=1)
#define DeassertTmr1INT()	(PIE1bits.TMR1IE=0)
#define Tmr1IntHiPRIORITY() (IPR1bits.TMR1IP=1)
#define Tmr1IntLoPRIORITY()	(IPR1bits.TMR1IP=0)

//------------------------------------------------------------------------
// A2D configuration
// -------------------
// Detail see also "halA2D" 

//------------------------------------------------------------------------
// Interrupte configuration
// -------------------
#define ITPenable()				(RCONbits.IPEN=1)
#define ITPic16Compatibility()	(RCONbits.IPEN=0) // default
//------------------------------------------------------------------------
// INTCON:   GIE/GIEH PEIE/GIEL TMR0IE    INT0IE    RBIE     TMR0IF  INT0IF RBIF
// INTCON2: RBPU        INTEDG0   INTEDG1 INTEDG2  —        TMR0IP  —        RBIP
// INTCON3: INT2IP      INT1IP      —            INT2IE     INT1IE — I        NT2IF  INT1IF
// PIR1, PIR2; PIE1, PIE2; IPR1, IPR2
//------------------------------------------------------------------------
#define GINTenable()			(INTCONbits.GIE=1)
#define GINTdisable()			(INTCONbits.GIE=0)
#define PEINTenable()			(INTCONbits.PEIE=1)
#define PEINTdisable()			(INTCONbits.PEIE=0)
//-->
#define ITPHiEnable()			(INTCONbits.GIEH=1)
#define ITPHiDisable()			(INTCONbits.GIEH=0)
#define ITPLoEnable()			(INTCONbits.GIEL=1)
#define ITPLoDisable()			(INTCONbits.GIEL=0)
//-->
#define INTenableALL()\
	ITPHiEnable(); ITPLoEnable();

#define INTdisableALL()\
	ITPHiDisable(); ITPLoDisable();

#define GINTSetting() \
{ \
	 ITPenable(); /* Interrupte Priority Enable */ \
	 ITPHiDisable();  /* Disable High Interrupte Service at first */ \
	 ITPLoDisable();	/* Disable Low Interrupte Service at first */ \
}
	// -----------------------------
	// Register interrupte service area
	// (1) Timer 0 interrupte High Priority
	// (2) Rx interrupte High Priority

	void bSsdOscllatorControl(void);
	void bSsdWdtSetting(void);
	void bSsdPortInit(void);
	void bSsdTimer0CFG(void);
	void bSsdA2dCFG(void);
	void bSsdIntCFG(void);
	void bSsdCleanRAM(void);
	void aSsdInitMcu(void);
	void __init(void);

#endif
