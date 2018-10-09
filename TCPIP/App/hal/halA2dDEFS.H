/*********************************************************************
 *
 *	HalA2dDefines Header
 *
 *********************************************************************
 * FileName:        halA2dDEFS.h
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
#ifndef halA2dDEFINES_H
#define halA2dDEFINES_H 

//for example_/#define DNS_TYPE_A				(1u)		// Constant for...

// -------------- ADCON0
// -> DEFINE: ADC_NEG_PIN_CONF
// --------------
#define ADC_CFG_VSS_REFERENCE_PIN
//or ->efine ADC_CFG_NEG_REFERENCE_PIN

// -------------- ADCON0
// -> DEFINE: ADC_POS_PIN_CONF
// --------------
#define ADC_CFG_VDD_REFERENCE_PIN
//or ->efine ADC_CFG_POS_REFERENCE_PIN

// -------------- ADCON1
// -> DEFINE: ADFM_ADJUSTIFY
// --------------
//or->efine ADFM_RIGHT_ADJUSTIFY
#define ADFM_LEFT_ADJUSTIFY

/* --------------no ADCAL Function --------------
// -------------- ADCON1
// -> DEFINE: ADCAL_CONFIG
// --------------
// or ->efine AD_With_CALIBRATION
#define AD_Without_CALIBRATION
/* --------------no ADCAL Function --------------*/

// -------------- ADCON1
// -> DEFINE: ADCS_CONFIG
// --------------
// or ->efine ADCS_FoscDivBY2
// or ->efine ADCS_FoscDivBY8
// or ->efine ADCS_FoscDivBY32
// or ->efine ADCS_Frc
// or ->efine ADCS_FoscDivBY4
// or ->efine ADCS_FoscDivBY16
#define ADCS_FoscDivBY64
// --------------

// -------------- ADCON1
// -> DEFINE: ACQT_CONFIG
// --------------
#define ACQT_20Tad
// or ->efine ACQT_16Tad
// or ->efine ACQT_12Tad
// or ->efine ACQT_08Tad
// or ->efine ACQT_06Tad
// or ->efine ACQT_04Tad
// or ->efine ACQT_02Tad
// or ->efine ACQT_00Tad
// --------------

/* -------------- ANCON#, _FALSE: Analog, _TRUE: Digital -------- (look up table)
// -> DEFINE: A/D PORT CONF As Digital (1) / Analog (0)
// --------------
#define AN0PortConfToDIG		_FALSE // Analog
#define AN1PortConfToDIG		_FALSE
#define AN2PortConfToDIG		_FALSE
#define AN3PortConfToDIG		_FALSE	
#define AN4PortConfToDIG				_TRUE // Digital
// -> AN5,6 No available
#define AN7PortConfToDIG				_TRUE
// -> AN8,9 No available
#define AN10PortConfToDIG				_TRUE
#define AN11PortConfToDIG				_TRUE
#define AN12PortConfToDIG				_TRUE
#define AN13PortConfToDIG				_TRUE
#define AN14PortConfToDIG				_TRUE
#define AN15PortConfToDIG				_TRUE
/* -------------- ANCON#, _FALSE: Analog, _TRUE: Digital --------*/

//######################################################################
//## END OF TOP DEFINATION###################################################
//######################################################################


#endif // !halA2dDEFINES_H

