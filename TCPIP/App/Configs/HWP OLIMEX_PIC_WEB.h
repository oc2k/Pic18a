 /*********************************************************************
 *
 *	Hardware specific definitions for:
 *    - Olimex PIC-WEB
 *    - PIC18F67J60
 *    - Internal 10BaseT Ethernet
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    Compiler.h
 * Processor:       PIC18
 * Compiler:        Microchip C18 v3.36 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
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
 * Howard Schlunder		09/16/2010	Regenerated for specific boards
 ********************************************************************/
#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#include "Compiler.h"

// Set configuration fuses (but only in Main.c where THIS_IS_STACK_APPLICATION is defined)
#if defined(THIS_IS_STACK_APPLICATION)
	#pragma config WDT=OFF, FOSC2=ON, FOSC=HSPLL, ETHLED=ON

	// Automatically set Extended Instruction Set fuse based on compiler setting
	#if defined(__EXTENDED18__)
		#pragma config XINST=ON
	#else
		#pragma config XINST=OFF
	#endif
#endif

//======================================
#define _TRUE			1
#define _FALSE			0
#define __constPIC18F67J60_FlashRomEndPTR					0x01FFF6 // REMINDER: the configuration bits address: 30000-3FFFFF
#define __constPIC18F67J60_RWProgMemStartPTR				0x010000 //160104a8 Detect Program Code overlap to RomPARAM (0x010000) //__>>0x***400 as erase AREA// Read WRITE start from (***400 - ..) as Rom Parameters store Zone in 0o3G project
#define __constPIC18F67J60_ROProgMemStartPTR				0x001000 //__>>0x***400 // Read ONLY start from (***400 - ..) as Rom Parameters store Zone in 0o3G project
//	V
	#define __rom01SystemReadONLYAddressID						__constPIC18F67J60_ROProgMemStartPTR
	#define __rom04SystemStartYEAR								0x2018
	#define __rom06w8VersionINFO1								01
	#define __rom07w8RES_PARAM1									0x05
//	#define __rom08w16RES_zero
	#define __rom0Aw16RES_PARAM2								0x7809
	#define __rom0Cw16RES_PARAM3								0x200
	#define __rom0Ew16RES_THRESHOLD								0x600
	#define __strVersionINFO2			"V1.00T1"
	#define __strVI2SPACE				"\0\0\0\0\0\0\0"
	#define __strVersionINFO3			"OCT 07 2018"
	#define __strVI3SPACE				"\0\0\0"
	#define __strVersionINFO4			"14:44:35"
	#define __strVI4SPACE				"\0\0\0\0\0\0"
	#define __strVersionINFO5			"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	#define __strVersionINFO6			"0.1"
	#define __strVI6SPACE				"\0\0\0\0\0\0\0\0\0\0\0"
	#define __strVersionINFO7			"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	#define __strVer8HostNAME			"nn1BOARD\0\0\0\0\0\0\0"
//	^
//======================================
// Clock frequency values
// These directly influence timed events using the Tick module.  They also are used for UART and SPI baud rate generation.
#define GetSystemClock()		(41666667ul)			// Hz
#define GetInstructionClock()	(GetSystemClock()/4)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/4)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.

// PIC-Web uses ATMEL flash AT45DB011, so the file SPIFlash.c and SPIFlash.h are patched to use
// functions according description in the datasheet of the memory: http://www.atmel.com/Images/doc1123.pdf
#define	USE_ATMEL_FLASH
// Olimex applications
#define	WEBPAGE_DEMO_UART
#define	WEBPAGE_DEMO_I2C
#define	WEBPAGE_DEMO_SPI

// Hardware I/O pin mappings

// LEDs
// I/O pins
#define LED0_TRIS			(PRODL)	/* NC */
#define LED0_IO				(PRODL)	/* NC */
#define LED1_TRIS			(TRISBbits.TRISB4)
#define LED1_IO				(LATBbits.LATB4)
#define LED2_TRIS			(PRODL)
#define LED2_IO				(PRODL)
#define LED3_TRIS			(PRODL)
#define LED3_IO				(PRODL)
#define LED4_TRIS			(PRODL)
#define LED4_IO				(PRODL)
#define LED5_TRIS			(PRODL)
#define LED5_IO				(PRODL)
#define LED6_TRIS			(PRODL)
#define LED6_IO				(PRODL)
#define LED7_TRIS			(PRODL)
#define LED7_IO				(PRODL)
#define LED_GET()			(LED1_IO)
#define LED_PUT(a)			(LED1_IO = (a))

// Buttons
#define BUTTON0_TRIS		(TRISBbits.TRISB0)
#define	BUTTON0_IO			(PORTBbits.RB0)
#define BUTTON1_TRIS		(PRODL)
#define	BUTTON1_IO			1
#define BUTTON2_TRIS		(PRODL)
#define	BUTTON2_IO			1
#define BUTTON3_TRIS		(PRODL)
#define	BUTTON3_IO			1

// Serial Flash/SRAM/UART PICtail
#define SPIFLASH_CS_TRIS		(TRISFbits.TRISF7)
#define SPIFLASH_CS_IO			(LATFbits.LATF7)
#define SPIFLASH_SCK_TRIS		(TRISCbits.TRISC3)
#define SPIFLASH_SDI_TRIS		(TRISCbits.TRISC4)
#define SPIFLASH_SDI_IO			(PORTCbits.RC4)
#define SPIFLASH_SDO_TRIS		(TRISCbits.TRISC5)
#define SPIFLASH_SPI_IF			(PIR1bits.SSPIF)
#define SPIFLASH_SSPBUF			(SSP1BUF)
#define SPIFLASH_SPICON1		(SSP1CON1)
#define SPIFLASH_SPICON1bits	(SSP1CON1bits)
#define SPIFLASH_SPICON2		(SSP1CON2)
#define SPIFLASH_SPISTAT		(SSP1STAT)
#define SPIFLASH_SPISTATbits	(SSP1STATbits)

// UART mapping functions for consistent API names across 8-bit and 16 or 
// 32 bit compilers.  For simplicity, everything will use "UART" instead 
// of USART/EUSART/etc.
#define BusyUART()			BusyUSART()
#define CloseUART()			CloseUSART()
#define ConfigIntUART(a)	ConfigIntUSART(a)
#define DataRdyUART()		DataRdyUSART()
#define OpenUART(a,b,c)		OpenUSART(a,b,c)
#define ReadUART()			ReadUSART()
#define WriteUART(a)		WriteUSART(a)
#define getsUART(a,b,c)		getsUSART(b,a)
#define putsUART(a)			putsUSART(a)
#define getcUART()			ReadUSART()
#define putcUART(a)			WriteUSART(a)
#define putrsUART(a)		putrsUSART((far rom char*)a)

//-----------------------------------
//- Old Project macros for inline assembly
//-----------------------------------
#define __NOP()					{_asm nop _endasm}
#define __CLRWDT()				{_asm clrwdt _endasm}
#define __SLEEP()				{_asm sleep _endasm}
#define __RESET()				{_asm reset _endasm}
#define __MOVLB(f)				{_asm movlb f _endasm}
#define __RLCF(f,dest,access)	{_asm rlcf f,dest,access _endasm}
#define __RLNCF(f,dest,access)	{_asm rlncf f,dest,access _endasm}
#define __RRCF(f,dest,access)	{_asm rrcf f,dest,access _endasm}
#define __RRNCF(f,dest,access)	{_asm rrncf f,dest,access _endasm}
#define __SWAPF(f,dest,access)	{_asm swapf f,dest,access _endasm }
#define __GOTO(loc) 			{_asm goto loc _endasm}
#define __w16LOW(a)				(a & 0xFF)
#define __w16HIGH(a)			((a>>8) & 0xFF)

//-----------------------------------
// Block Pointer (FSR) Operation macro
//-----------------------------------
// - Rev01b, 160120c11 - add output checksum
#define __POSTINC0L(a)			(w8OutputCS += a, INDF0 = a, FSR0L ++) //Rev01b__>>(INDF0 = a, FSR0L ++)
#define __POSTINC0LwoCS(a)		(INDF0 = a, FSR0L ++) // should be use debugMSG
#define __POSTINC0LhexfCS(a)	(w8HexfileCS += a, INDF0 = a, FSR0L ++) //Rev01b__>>(INDF0 = a, FSR0L ++)


//----------------------------------- update in 140402a
// RomREAD
// (1) tblrd (TBLRD*)
// (2) tblrdpostinc (TBLRD*+)
// (3) tblrdpostdec (TBLRD*-)
// (4) tblrdpreinc (TBLRD+*)
// RomWRITE
// (1) tblwt (TBLWT*)
// (2) tblwtpostinc (TBLWT*+)
// (3) tblwtpostdec (TBLWT*-)
// (4) tblwtpreinc (TBLWT+*)
//----------------------------------- update in 140402a
#define __TBLRD() {_asm tblrd _endasm}
#define __TBLRDPOSTINC() {_asm tblrdpostinc _endasm}
#define __TBLRDPOSTDEC() {_asm tblrdpostdec _endasm}
#define __TBLRDPREINC() {_asm tblrdpreinc _endasm}
#define __TBLWT() {_asm tblwt _endasm}
#define __TBLWTPOSTINC() {_asm tblwtpostinc _endasm}
#define __TBLWTPOSTDEC() {_asm tblwtpostdec _endasm}
#define __TBLWTPREINC() {_asm tblwtpreinc _endasm}
//----------------------------------- update in 140402a
#endif // #ifndef HARDWARE_PROFILE_H
