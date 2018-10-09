/*********************************************************************
 *
 *	HalA2D Header
 *
 *********************************************************************
 * FileName:        HalA2D.h
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

#include "hal/halA2dDEFS.h"

#ifndef halA2D_H
#define halA2D_H 

//for example_/#define DNS_TYPE_A				(1u)		// Constant for...

	extern CHAR8 AdTMR;
	extern CHAR8 AdCNT;
	extern WORD_VAL AdRESULT;




// ----------------------------------------------------------------------------------------------------
// -ssdInitREGs
//--------------------
// HalA2D.h >> ssdInitHalA2DREGs();
#define ssdInitHalA2DREGs()						\
	AdRESULT.Val = 0;  /* Clear Adc Result */	\
	__doCalibADC();
/** AdTMR = AdCNT = 0; /* Just sample for AppUSE */

//for example_/void DNSResolve(BYTE* HostName, BYTE Type);
	void aHalA2d_MainMeasurePerSEC(void);

#endif

// =====================================
// ADC INITIAL
// --------
// --------------ADCON0
// #ADCON0 (00) OP REG
// --------
//	REGISTER 22-1: ADCON0: A/D CONTROL REGISTER 0
//	R/W-0 U-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0
//	ADCAL — [CHS3 CHS2 CHS1 CHS0]    GO/DONE   ADON
//	bit 7 bit 0
// --------------ADCON0
// ------------------ADCON1
// #ADCON1 (0E) CONF REG (remark: Just AN0 as analog)
// --------
//	REGISTER 22-2: ADCON1: A/D CONTROL REGISTER 1
//	U-0 U-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0
//	— — [VCFG1 VCFG0]    [PCFG3 PCFG2 PCFG1 PCFG0]
//	bit 7 bit 0
// ------------------
//	PCFG<3:0>, AN15(1), AN14(1), AN13(1), AN12(1), AN11, AN10, AN9, AN8, AN7, AN6, AN5(2), AN4, AN3, AN2, AN1(3), AN0(3)
//	0000 A A A A A A A A A A A A A A A A
//	0001 D D A A A A A A A A A A A A A A
//	0010 D D D A A A A A A A A A A A A A
//	0011 D D D D A A A A A A A A A A A A
//	0100 D D D D D A A A A A A A A A A A
//	0101 D D D D D D A A A A A A A A A A
//	0110 D D D D D D D A A A A A A A A A
//	0111 D D D D D D D D A A A A A A A A
//	1000 D D D D D D D D D A A A A A A A
//	1001 D D D D D D D D D D A A A A A A
//	1010 D D D D D D D D D D D A A A A A
//	1011 D D D D D D D D D D D D A A A A
//	1100 D D D D D D D D D D D D D A A A
//	1101 D D D D D D D D D D D D D D A A
// *0E:	1110 D D D D D D D D D D D D D D D A
// 0F:	1111 D D D D D D D D D D D D D D D D
// ------------------ADCON1
// ---------------------------ADCON2
// #ADCON2 (BE) CONTROL REG
// --------
//	REGISTER 22-3: ADCON2: A/D CONTROL REGISTER 2
//	R/W-0 U-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0 R/W-0
//	ADFM — [ACQT2 ACQT1 ACQT0] [ADCS2 ADCS1 ADCS0]
//	bit 7 bit 0
// ---------------------------ADCON2
// =====================================
#if defined(STACK_USE_HAL_A2D_UART)
//
	#define __InitA2d()											\
		ADCON0 = _selCh00(); ad_Off();							\
		ADCON1 = 0x0E; 											\
		ADCON2 = ADFM_ADJUSTIFY | ACQT_CONFIG | ADCS_CONFIG ;
//
#endif //>>if defined(STACK_USE_HAL_A2D_UART)

// =====================================
// ADCON1 SETTING
// --------------
// ADCON2, ADFM:0 -> HH|L,xxxx As 12 Bit AD RESULT -- ADCON1(7)
// ADCON0, ADCAL:0 -> Normal; 1 -> Calibration is performed on the next AD -- ADCON1(6)
// =====================================
#define ADCON0_ADON				(0x01)

// --------------
// ADC result format CONFIG of ADCON1
// --------------
#if defined(ADFM_RIGHT_ADJUSTIFY)
	#define ADFM_ADJUSTIFY		(0x80) // AD RESULT MAX = (03FF), ADFM_RIGHT_ADJUSTIFY
#elif defined (ADFM_LEFT_ADJUSTIFY)
	#define ADFM_ADJUSTIFY		(0x00) // AD RESULT MAX = (FFC0), ADFM_LEFT_ADJUSTIFY
#else
	#error "no define ADFM_ADJUSTIFY"
#endif // !ADFM_RIGHT_ADJUSTIFY

// --------------no ADCAL Function --------------
// ADCAL CONFIG of ADCON1
// --------------
//	#if defined(AD_With_CALIBRATION)
//		#define ADCAL_CONFIG		(0x40)
//	#elif defined (AD_Without_CALIBRATION)
//		#define ADCAL_CONFIG		(0x00)
//	#else
//		#error "no define ADCAL_CONFIG"
//	#endif // !ADCAL_CONFIG
// --------------no ADCAL Function --------------

// ====ADCON2=================================
// ADC Operation REG Left/Righ, ADCON2'bit7
// --------------
// ADC_NEG_REF_CONF: ADC configuration of negitive voltage reference
#if defined(ADC_CFG_NEG_REFERENCE_PIN)
	#define ADC_NEG_REF_CONF		(0x80) // Neg reference is AN2, ADC_CFG_NEG_REFERENCE_PIN
#elif defined (ADC_CFG_VSS_REFERENCE_PIN)
	#define ADC_NEG_REF_CONF		(0x00) //  Neg reference is VSS, ADC_CFG_VSS_REFERENCE_PIN
#else
	#error "no define ADC_NEG_PIN_CONF"
#endif // !ADC_CFG_NEG_REFERENCE_PIN

// --------------
// ACQT CONFIG of ADCON2'bit3-5
// --------------
#if defined(ACQT_20Tad)
	#define ACQT_CONFIG			(0x38) // ADCON1(20Tad): **11,1***
#elif defined (ACQT_16Tad)
	#define ACQT_CONFIG			(0x30) // ADCON1(16Tad): **11,0***
#elif defined (ACQT_12Tad)
	#define ACQT_CONFIG			(0x28) // ADCON1(12Tad): **10,1***
#elif defined (ACQT_08Tad)
	#define ACQT_CONFIG			(0x20) // ADCON1(08Tad): **10,0***
#elif defined (ACQT_06Tad)
	#define ACQT_CONFIG			(0x18) // ADCON1(06Tad): **01,1***
#elif defined (ACQT_04Tad)
	#define ACQT_CONFIG			(0x10) // ADCON1(04Tad): **01,0***
#elif defined (ACQT_02Tad)
	#define ACQT_CONFIG			(0x08) // ADCON1(02Tad): **00,1***
#elif defined (ACQT_00Tad)
	#define ACQT_CONFIG			(0x00) // ADCON1(00Tad): **00,0***
#else
	#error "no define ADCS_20Tad"
#endif // !ADCS_CONFIG

// --------------
// ADCS CONFIG of ADCON2'bit0-2
// --------------
#if defined(ADCS_FoscDivBY2)
	#define ADCS_CONFIG			(0x00) // ADCS_FoscDivBY2
#elif defined (ADCS_FoscDivBY8)
	#define ADCS_CONFIG			(0x01) // ADCS_FoscDivBY8
#elif defined (ADCS_FoscDivBY32)
	#define ADCS_CONFIG			(0x02) // ADCS_FoscDivBY32
#elif defined (ADCS_Frc)
	#define ADCS_CONFIG			(0x03) // ADCS_Frc
#elif defined (ADCS_FoscDivBY4)
	#define ADCS_CONFIG			(0x04) // ADCS_FoscDivBY4
#elif defined (ADCS_FoscDivBY16)
	#define ADCS_CONFIG			(0x05) // ADCS_FoscDivBY16
#elif defined (ADCS_FoscDivBY64)
	#define ADCS_CONFIG			(0x06) // ADCS_FoscDivBY64
#else
	#error "no define ADCS_CONFIG"
#endif // !ADCS_CONFIG
/* ====ADCON2=================================*/


// ADC_POS_REF_CONF: ADC configuration of positive voltage reference
#if defined(ADC_CFG_POS_REFERENCE_PIN)
	#define ADC_POS_REF_CONF			(0x20) // Pos reference is AN3, ADC_CFG_POS_REFERENCE_PIN
#elif defined (ADC_CFG_VDD_REFERENCE_PIN)
	#define ADC_POS_REF_CONF			(0x00) // Pos reference is VDD, ADC_CFG_VDD_REFERENCE_PIN
#else
	#error "no define ADC_POS_PIN_CONF"
#endif // !ADC_NEG_REFERENCE_PIN

// --------------
#define ADC_SEL_CH00			(0x00)
#define ADC_SEL_CH01			(0x04)
#define ADC_SEL_CH02			(0x08)
#define ADC_SEL_CH03			(0x0C)
#define ADC_SEL_CH04			(0x10)
#define ADC_SEL_CH05			(0x14)
#define ADC_SEL_CH06			(0x18)
#define ADC_SEL_CH07			(0x1C)
#define ADC_SEL_CH08			(0x20)
#define ADC_SEL_CH09			(0x24)
#define ADC_SEL_CH10			(0x28)
#define ADC_SEL_CH11			(0x2C)
#define ADC_SEL_CH12			(0x30)
// --------------
#define _selCh00() ADCON0= ADC_SEL_CH00 | ADCON0_ADON; //ADCON0=(0032|10xx)
//	#define _selCh01() ADCON0=ADC_SEL_CH01 | ADCON0_ADON; //ADCON0=(**32|10xx)
// ->
#define ad_On() ADCON0bits.ADON=1;
#define ad_Off() ADCON0bits.ADON=0;
#define ad_Go()   do{ADCON0bits.GO_DONE=1;}while(!ADCON0bits.GO_DONE);
#define ad_Done() do{}while(ADCON0bits.GO_DONE);

// Do a calibration A/D conversion
#if defined(__18F67J60) //|| defined(__18F87J10) || defined(__18F86J15) || defined(__18F86J10) || defined(__18F85J15) || defined(__18F85J10) || defined(__18F67J10) || defined(__18F66J15) || defined(__18F66J10) || defined(__18F65J15) || defined(__18F65J10) || defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) ||  defined(__18F66J65) || defined(__18F66J60) || \
//	 defined(_18F87J10) ||	defined(_18F86J15) || defined(_18F86J10)  ||  defined(_18F85J15) ||  defined(_18F85J10) ||	defined(_18F67J10) ||  defined(_18F66J15) ||  defined(_18F66J10) ||  defined(_18F65J15) ||	defined(_18F65J10) ||  defined(_18F97J60) ||  defined(_18F96J65) ||  defined(_18F96J60) ||	defined(_18F87J60) ||  defined(_18F86J65) ||  defined(_18F86J60) ||  defined(_18F67J60) ||	defined(_18F66J65) ||  defined(_18F66J60)
// ---ADC Calibration Defines
#define __doCalibADC() 		\
	ADCON0bits.ADCAL = 1;	\
	ADCON0bits.GO = 1;		\
	while(ADCON0bits.GO);	\
	ADCON0bits.ADCAL = 0;

#elif 0 // defined(__18F87J11) || defined(__18F86J16) || defined(__18F86J11) || defined(__18F67J11) || defined(__18F66J16) || defined(__18F66J11) || \

/* --2435234sdf--- 
//
		defined(_18F87J11) ||  defined(_18F86J16) ||  defined(_18F86J11) ||	defined(_18F67J11) ||  defined(_18F66J16) ||  defined(_18F66J11) || \
		defined(__18F87J50) || defined(__18F86J55) || defined(__18F86J50) || defined(__18F67J50) || defined(__18F66J55) || defined(__18F66J50) || \
		defined(_18F87J50) ||  defined(_18F86J55) ||  defined(_18F86J50) ||	defined(_18F67J50) ||  defined(_18F66J55) ||  defined(_18F66J50)
	#define __doCalibADC() 		\
		ADCON1bits.ADCAL = 1;	\
		ADCON0bits.GO = 1;		\
		while(ADCON0bits.GO);	\
		ADCON1bits.ADCAL = 0;
//
/* --2435234sdf--- */

#else
	#DetectErrorFor>>define __doCalibADC() 		\
	Nop();
#endif

