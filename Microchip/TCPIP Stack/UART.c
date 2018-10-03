/*********************************************************************
 *
 *     UART access routines for C18 and C30
 *
 *********************************************************************
 * FileName:        UART.c
 * Dependencies:    Hardware UART module
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F
 * Compiler:        Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
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
 * Author               Date   		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		4/04/06		Copied from dsPIC30 libraries
 * Howard Schlunder		6/16/06		Added PIC18
********************************************************************/
#define __UART_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_UART)

#include "TCPIP Stack/TCPIP.h"


BYTE ReadStringUART(BYTE *Dest, BYTE BufferLen)
{
	BYTE c;
	BYTE count = 0;

	while(BufferLen--)
	{
		*Dest = '\0';

		while(!DataRdyUART());
		c = ReadUART();

		if(c == '\r' || c == '\n')
			break;

		count++;
		*Dest++ = c;
	}

	return count;
}



	char BusyUSART(void)
	{
		return !TXSTAbits.TRMT;
	}
	
	void CloseUSART(void)
	{
	  RCSTA &= 0x4F;  // Disable the receiver
	  TXSTAbits.TXEN = 0;   // and transmitter
	
	  PIE1 &= 0xCF;   // Disable both interrupts
	}
	
	char DataRdyUSART(void)
	{
		if(RCSTAbits.OERR)
		{
			RCSTAbits.CREN = 0;
			RCSTAbits.CREN = 1;
		}
	  return PIR1bits.RCIF;
	}
	
	char ReadUSART(void)
	{
	  return RCREG;                     // Return the received data
	}
	
	void WriteUSART(char data)
	{
	  TXREG = data;      // Write the data byte to the USART
	}
	
	void getsUSART(char *buffer, unsigned char len)
	{
	  char i;    // Length counter
	  unsigned char data;
	
	  for(i=0;i<len;i++)  // Only retrieve len characters
	  {
	    while(!DataRdyUSART());// Wait for data to be received
	
	    data = getcUART();    // Get a character from the USART
	                           // and save in the string
	    *buffer = data;
	    buffer++;              // Increment the string pointer
	  }
	}
	
	void putsUSART( char *data)
	{
	  do
	  {  // Transmit a byte
	    while(BusyUSART());
	    putcUART(*data);
	  } while( *data++ );
	}
	
	void putrsUSART(const rom char *data)
	{
	  do
	  {  // Transmit a byte
	    while(BusyUSART());
	    putcUART(*data);
	  } while( *data++ );
	}




#endif	//STACK_USE_UART
