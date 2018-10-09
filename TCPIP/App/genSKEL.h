/*********************************************************************
 *
 *	General (GEN) Skeleton Header
 *
 *********************************************************************
 * FileName:        genSKEL.h
 * Dependencies:    stacktsk.h,..
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


#ifndef __GENSKEL_H
#define __GENSKEL_H

//-----------------------------------
// -> Word8SIZE
#define __word8SizeOfUCHAR8			sizeof(UCHAR8) //__>>1
#define __word8SizeOfBYTE			sizeof(BYTE) //__>>1
//-----------------------------------
// -> Word16SIZE
#define __WORDSize					sizeof(WORD) //__>>2
#define __UINT16Size				sizeof(UINT16) //__>>2
//-----------------------------------
// -> Word32SIZE
#define __DWORDSize					sizeof(DWORD) //__>>4
#define __UINT32Size				sizeof(UINT32) //__>>4
//-----------------------------------

		extern BYTE u8i;
		extern BYTE u8j;
		extern BYTE u8k;
		extern BYTE u8retVAL;
		extern WORD u16i;
		extern DWORD u32i;
		extern BYTE w8i;
		extern BYTE w8j;
		extern BYTE w8s;
		extern BYTE w8t;
		extern WORD w16i;
		extern WORD w16j;
		extern DWORD w32i;

	// Re-definitions function temp REGs 
	// ------------
#define __u8iB6 (((BYTE_VAL*)&u8i)->bits.b6)
#define __u8retVALB7 (((BYTE_VAL*)&u8retVAL)->bits.b7)
#define __u8retVALB0 (((BYTE_VAL*)&u8retVAL)->bits.b0)
#define __u8sB7 (((BYTE_VAL*)&u8s)->bits.b7)
#define __u8sB0 (((BYTE_VAL*)&u8s)->bits.b0)
	// ------------
#define __u16iHB	(((WORD_VAL*)&u16i)->byte.HB)
#define __u16iLB	(((WORD_VAL*)&u16i)->byte.LB)
#define __u16iB15	(((WORD_VAL*)&u16i)->bits.b15)
#define __u16iB11	(((WORD_VAL*)&u16i)->bits.b11)
#define __u16iB9	(((WORD_VAL*)&u16i)->bits.b9)
#define __u16iB0	(((WORD_VAL*)&u16i)->bits.b0)
#define u16j	(((DWORD_VAL*)&u32i)->word.LW)
#define u16k	(((DWORD_VAL*)&u32i)->word.HW)
		// ------------
#define __u32iMB	(((DWORD_VAL*)&u32i)->byte.MB) //__>>(u32i.fcun[3].value)
#define __u32iUB	(((DWORD_VAL*)&u32i)->byte.UB) //__>>(u32i.fcun[2].value)
#define __u32iHB	(((DWORD_VAL*)&u32i)->byte.HB) //__>>(u32i.fcun[1].value)
#define __u32iLB	(((DWORD_VAL*)&u32i)->byte.LB) //__>>(u32i.fcun[0].value)
		// ------------
	#define __u32iFUNval	(((FUN*)&u32i)->val) //__>>(u32i.Val) xxx__>>((LONG*)&u32i) <<_xxx
		// ------------
	// ------------=u32i=--
	// ----------------=u32j=--
	// ----------------=u32j=--
	//-----------------------------------
	#define __w8iB7	(((BYTE_VAL*)&w8i)->bits.b7)
	#define __w8iB0	(((BYTE_VAL*)&w8i)->bits.b0)
	// ----------------=word16i=--
	#define __w16iB15	(((WORD_VAL*)&w16i)->bits.b15)
	#define __w16iB11	(((WORD_VAL*)&w16i)->bits.b11)
	#define __w16iB9	(((WORD_VAL*)&w16i)->bits.b9)
	#define __w16iB0	(((WORD_VAL*)&w16i)->bits.b0)
		// ------------
		#define __w16iHB	(((WORD_VAL*)&w16i)->byte.HB)
		#define __w16iLB	(((WORD_VAL*)&w16i)->byte.LB)
		// ------------
	// ----------------=word16i=--
	//
	//------- ---------------------=word32i=--
	#define __w32iB31	(((DWORD_VAL*)&w32i)->bits.b31)
	#define __w32iB0	(((DWORD_VAL*)&w32i)->bits.b0)
		#define __w32iHW	(((DWORD_VAL*)&w32i)->word.HW)
		#define __w32iLW	(((DWORD_VAL*)&w32i)->word.LW)
	#define __w32iMB	(((DWORD_VAL*)&w32i)->byte.MB)
	#define __w32iUB	(((DWORD_VAL*)&w32i)->byte.UB)
	#define __w32iHB	(((DWORD_VAL*)&w32i)->byte.HB)
	#define __w32iLB	(((DWORD_VAL*)&w32i)->byte.LB)
	//------- ---------------------=word32i=--
	// -----=OsCLOCKs=-----------------------------------------------------------------------------------------------
#define __hmSecondB2 (((BYTE_VAL*)&hmSecond)->bits.b2)
#define __oSecondB1 (((BYTE_VAL*)&oSecond)->bits.b1)
	// -----=OsCLOCKs=-----------------------------------------------------------------------------------------------
		// ----------------------=LKZDdsa908ad90lk=---------------------------------------------------
	
		extern BYTE sys,sys2,sys5,sys6,sys7;//__>>,sys3; //and sys4 as tempoary testing use
		extern BYTE isrMs,isrHms;
		extern BYTE hmSecond, oSecond, oMinute, oHour;
		extern WORD sysErr; //system error BITs as reporting
	// ----------------------------------------------------------------------------------------------------
	// -ssdInitREGs
	// -----------==--------------------------
#define sysCLEAR() 				(sys = sys2 = sys5 = sys6 = sys7 = 0) //__>> = sys3 = 0) //tmp__>> = 0) // as initial OR Reset
#define __initOsCLOCKs()		\
				hmSecond	=		\
				oSecond 	=		\
				oMinute 	=		\
				oHour		=		\
				isrHms		=		\
				isrMs		= 0;	// Clear internal system clock value
	//--------------------
	// osPUBLIC.h >> ssdInitOsREGs();
#define ssdInitOsREGs()			\
				sysERRClear();		\
				sysCLEAR(); 		\
				__initOsCLOCKs();
	/* -----------==--------------------------*/
// ----------------
typedef struct _Pic18RomSystemPPRWParam //Rev01b__>>_Pic18RomSystemRWParam
{

	// ----------------0x00
	WORD wSPIProjPARAM0;		// (PI1), _n_rom00 as [0L,1H] would be received the default value 356 (ie: 0x164)
	WORD wSPIProjPARAM1;		// PP1,..
	WORD wSPIProjPARAM2;		// PP2,..
	WORD wSPIProjPARAM3;		// PP3,..
	WORD wSPIProjPARAM4;		// PP4,..
	WORD wSPIProjPARAM5;		// PP5,..
	WORD wSPIProjPARAM6;		// PP6,..
	WORD wSPIProjPARAM7;		// PP7,..
	DWORD		dRESERVED[0x10];			// (dw) RESERVED
} Pic18RomSystemPPRWParam; //Pic18RomSystemRWParam; // size: 40h (ie: 010000 - 01003F)
#define __constPic18RomSystemPIRWParamSIZE		sizeof(Pic18RomSystemPPRWParam)
typedef union Pic18RomSystemPIRWParamTAG{ //Rev01b__>>Pic18RomSystemRWParamTAG{
	Pic18RomSystemPPRWParam RomVALUE;
	BYTE RomBYTE[__constPic18RomSystemPIRWParamSIZE];
} RomUNsysPPRWParam;
	extern	ROM RomUNsysPPRWParam Pic18RomSysPPnnParam;
//----------------------------89293475ljadlj9409b--------------------------------------
// ----------------------------------------------
// ----------------
typedef struct _Pic18RomSystemROParam
{
	DWORD dSysROAddressID;	// __rom00,01,02,03,SystemReadONLYAddressID,
	WORD dSysStartYEAR; 	// __rom04,05,System(Project)StartYEAR
	BYTE bSysEP2RI; 		// __rom06,System(Project)NameRVI
	BYTE bCFM_AbsTOL;		// 0x05, __rom07BYTE, the "5" is Half Degree as Generate Confirm Trigger pulse tolerance, ie: (0.5)*11.3777777=5.68888 (05h), keyword "CFM_ABS";
	WORD wRESERVED; //__>>JOG_AvaRANGE; 	// 0x17, __rom08BYTE, the "23" is Two Degree as JOG Up/Dn Available Action Range, ie: (2.0)*11.3777777=22.7555555=23 (17h), keyword "JOG_AvaRANGE"; Abbrev: AVA denote Available;
	WORD wJOG_StpRANGE; 	// 0x0B, __rom0aBYTE, the "11" is One Degree as JOG Up/Dn Stop Action Range, ie: (1.0)*11.3777777=11 (0Bh), keyword "JOG_StpRANGE"; Abbrev: STP denote Stop;
	WORD wCycWoTRI_THRESHOLD;	// 0x0200, set the threshold to 45 degree, As "Cycle Without Trigger" Encoder Difference Threshold, keyword "CycWoTRI"; Abbrev: "Cyc" denote Cycle; "Wo" denoted Without; "Tri" denoted Trigger;
	WORD wPssCycOVER_THRESHOLD; // 0x600 // set the threshold to 135 degree in speed 7, As "Press Cycle Over" Encoder Difference Threshold, keyword "PssCycOVR"; Abbrev: "Pss" denote Press; "Cyc" denoted Cycle; "Ove" denoted Over; current mechine speed 7 brake angle (237 degree), ie: stop to stopped distance around 123 degree, thus tolerance should be 12 degree;//__>>wRESERVED; 		// 0x0000, 0eWORD
} Pic18RomSystemROParam; // size: xxh
#define __constPic18RomSystemROParamSIZE		sizeof(Pic18RomSystemROParam)
typedef union Pic18RomSystemROParamTAG{
	Pic18RomSystemROParam RomVALUE;
	BYTE RomBYTE[__constPic18RomSystemROParamSIZE];
} RomUNsysROParam;
	extern	ROM RomUNsysROParam Pic18RomSysROParam;
//----------------------------89293475ljadlj9409b--------------------------------------

//------------------------------------------------------------ROM
// Application-dependent structure used to contain address information
typedef struct _Pic18RomAPPConfigROStruct  //__>>__attribute__((__packed__)) appConfigStruct 
{

	// ---------------=mROMStructs**COPYTo**RAM=---------------------------(30h)
	//	mROMStructsCOPYToRAM
	//-----------------------(SPIBrakeAngle share to BrakeAngle and SplitBrakeAngle)-----
	WORD	wSPIProjPARAM0;		// _n_rom00 as [0,1] default value () 
	WORD	wSPIProjPARAM1;		// _n_rom02 as [2,3] default value () 
	WORD	wSPIProjPARAM2;		// _n_rom04 as [4,5] default value () 
	WORD	wSPIProjPARAM3;		// _n_rom06 as [6,7] default value () 
	WORD	wSPIProjPARAM4;		// _n_rom08 as [8,9] default value () 
	WORD	wSPIProjPARAM5;		// _n_rom0A as [a,b] default value () 
	WORD	wSPIProjPARAM6;		// _n_rom0C as [c,d] default value () 
	WORD	wSPIProjPARAM7;		// _n_rom0E as [e,f] default value () 
	IP_ADDR		MyIPAddr;               // IP address
	IP_ADDR		MyMask;                 // Subnet mask
	IP_ADDR		MyGateway;              // Default Gateway
	IP_ADDR		PrimaryDNSServer;       // Primary DNS Server
	IP_ADDR		SecondaryDNSServer;     // Secondary DNS Server
	IP_ADDR		DefaultIPAddr;          // Default IP address
	IP_ADDR		DefaultMask;            // Default subnet mask
	DWORD		dRESERVED;			// (dw) RESERVED
	// ---------------=mROMStructs**COPYTo**RAM=---------------------------(30h)

} Pic18RomAPPConfigRO; // ByteSIZE = 2x8+4x8 = 48 ..__/APP_CONFIG (ROM); 
#define __constPic18RomAPPConfigROSIZE			sizeof(Pic18RomAPPConfigRO)
#define __constSPIProjPARAMSIZE					8 * sizeof(WORD)
// ---
typedef union Pic18RomAppCONFIGROTAG{
	Pic18RomAPPConfigRO RomVALUE;
	BYTE RomBYTE[__constPic18RomAPPConfigROSIZE];
} UNAppCONFIGRO;
// ---
	typedef struct _Pic18RomSystemReservedRWParamTAG
	{
		WORD wReserved0;		// _n_rom00 as [0] reserved 0
		WORD wReserved1;
		WORD wReserved2;
		WORD wReserved3;
		WORD wReserved4;
		WORD wReserved5;
		WORD wReserved6;
		WORD wReserved7;
	} Pic18RomSystemReservedRWParam; // size: nnh
	
	// ----------------
	extern	ROM UNAppCONFIGRO Pic18RomAppConfigRO;
	extern	ROM BYTE SerializedMACAddressRO[6];
//------------------------------------------------------------ROM
//	vv

	void aGenSystemClock(void);
	void isrOsSystemCLOCK(void);

#endif
