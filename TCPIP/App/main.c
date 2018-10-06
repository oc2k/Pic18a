/*********************************************************************
 *
 *  Main Application Entry Point and TCP/IP Stack Demo
 *  Module for Microchip TCP/IP Stack
 *   -Demonstrates how to call and use the Microchip TCP/IP stack
 *   -Reference: Microchip TCP/IP Stack Help (TCPIP Stack Help.chm)1150

 *
 *********************************************************************
 * FileName:        Main.c
 * Dependencies:    TCPIP.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.11b or higher
 *                  Microchip C30 v3.24 or higher
 *                  Microchip C18 v3.36 or higher
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
 *      ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *      used in conjunction with a Microchip ethernet controller for
 *      the sole purpose of interfacing with the ethernet controller.
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
 * File Description:
 * Change History:
 * Rev   Description
 * ----  -----------------------------------------
 * 1.0   Initial release
 * V5.36 ---- STACK_USE_MPFS support has been removed 
 ********************************************************************/
/*
 * This macro uniquely defines this file as the main entry point.
 * There should only be one such definition in the entire project,
 * and this file must define the AppConfig variable as described below.
 */
#define THIS_IS_STACK_APPLICATION

// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"

// Include functions specific to this stack application
#include "Main.h"
#include "Custom_SPI.h"

// Declare AppConfig structure and some other supporting stack variables
APP_CONFIG AppConfig;
static unsigned short wOriginalAppConfigChecksum;    // Checksum of the ROM defaults for AppConfig
BYTE AN0String[8];
#ifdef	WEBPAGE_DEMO_UART
#pragma udata UART_BUFFER
char UART_Buffer[BUFFER_SIZE];
#pragma udata
volatile unsigned char RCIndex=0, TCIndex=0;
#endif

// Use UART2 instead of UART1 for stdout (printf functions).  Explorer 16 
// serial port hardware is on PIC UART2 module.
//#if defined(EXPLORER_16) || defined(PIC24FJ256DA210_DEV_BOARD)
//    int __C30_UART = 2;
//#endif


// Private helper functions.
// These may or may not be present in all applications.
static void InitAppConfig(void);
static void InitializeBoard(void);
static void ProcessIO(void);
//
// PIC18 Interrupt Service Routines
// 
// NOTE: Several PICs, including the PIC18F4620 revision A3 have a RETFIE FAST/MOVFF bug
// The interruptlow keyword is used to work around the bug when using C18
    #pragma interruptlow LowISR
    void LowISR(void)
    {
        TickUpdate();
    }
    
    #pragma interruptlow HighISR
    void HighISR(void)
    {
		#ifdef WEBPAGE_DEMO_UART
		if (PIR1 & 0x20)
			// using the fact that the buffer size is 256 so RCIndex values are between 0 and 255, so no masking is needed
			UART_Buffer[RCIndex++] = RCREG;	
		#endif

        #if defined(STACK_USE_UART2TCP_BRIDGE)
            UART2TCPBridgeISR();
        #endif

    }

    #pragma code lowVector=0x18
    void LowVector(void){_asm goto LowISR _endasm}
    #pragma code highVector=0x8
    void HighVector(void){_asm goto HighISR _endasm}
    #pragma code // Return to default code section

//
// Main application entry point.
//
void main(void)
{
    static DWORD t = 0;
    static DWORD dwLastIP = 0;

    // Initialize application specific hardware
    InitializeBoard();

    // Initialize stack-related hardware components that may be 
    // required by the UART configuration routines
    TickInit();

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    // Initiates board setup process if button is depressed 
    // on startup
    if(BUTTON0_IO == 0u)
    {
        #if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        // Invalidate the EEPROM contents if BUTTON0 is held down for more than 4 seconds
        DWORD StartTime = TickGet();
        LED_PUT(0x00);
                
        while(BUTTON0_IO == 0u)
        {
            if(TickGet() - StartTime > 4*TICK_SECOND)
            {
                #if defined(EEPROM_CS_TRIS)
                XEEBeginWrite(0x0000);
                XEEWrite(0xFF);
                XEEWrite(0xFF);
                XEEEndWrite();
                #elif defined(SPIFLASH_CS_TRIS)
                SPIFlashBeginWrite(0x0000);
                SPIFlashWrite(0xFF);
                SPIFlashWrite(0xFF);
				SPIFlashEndWrite ();
                #endif
                
                #if defined(STACK_USE_UART)
                putrsUART("\r\n\r\nBUTTON0 held for more than 4 seconds.  Default settings restored.\r\n\r\n");
                #endif

                LED_PUT(0x0F);
                while((LONG)(TickGet() - StartTime) <= (LONG)(9*TICK_SECOND/2));
                LED_PUT(0x00);
                while(BUTTON0_IO == 0u);
                Reset();
                break;
            }
        }
        #endif

        #if defined(STACK_USE_UART)
        DoUARTConfig();
        #endif
    }
	#ifdef	WEBPAGE_DEMO_UART
	// after no more receiving on the RS we can initialize UART receive interrupt
	PIR1 = PIR1 & (~0x20);
	PIE1 = PIE1 | 0x20;
	IPR1 = IPR1 | 0x20;
	#endif

    // Initialize core stack layers (MAC, ARP, TCP, UDP) and
    // application modules (HTTP, SNMP, etc.)
    StackInit();

    // Initialize any application-specific modules or functions/
    // For this demo application, this only includes the
    // UART 2 TCP Bridge
    #if defined(STACK_USE_UART2TCP_BRIDGE)
    UART2TCPBridgeInit();
    #endif

    // Now that all items are initialized, begin the co-operative
    // multitasking loop.  This infinite loop will continuously 
    // execute all stack-related tasks, as well as your own
    // application's functions.  Custom functions should be added
    // at the end of this loop.
    // Note that this is a "co-operative mult-tasking" mechanism
    // where every task performs its tasks (whether all in one shot
    // or part of it) and returns so that other tasks can do their
    // job.
    // If a task needs very long time to do its job, it must be broken
    // down into smaller pieces so that other tasks can have CPU time.
    while(1)
    {
        // Blink LED0 (right most one) every second.
        if(TickGet() - t >= TICK_SECOND/2ul)
        {
            t = TickGet();
            LED0_IO ^= 1;
        }

        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        StackTask();
        
        // This tasks invokes each of the core stack application tasks
        StackApplications();

	    //180920a2    #if defined(STACK_USE_ICMP_CLIENT)
	    //180920a2    PingDemo();
	    //180920a2    #endif

        ProcessIO();

        // If the local IP address has changed (ex: due to DHCP lease change)
        // write the new IP address to the LCD display, UART, and Announce 
        // service
        if(dwLastIP != AppConfig.MyIPAddr.Val)
        {
            dwLastIP = AppConfig.MyIPAddr.Val;
            
            #if defined(STACK_USE_UART)
                putrsUART((ROM char*)"\r\nNew IP Address: ");
            #endif

            DisplayIPValue(AppConfig.MyIPAddr);

            #if defined(STACK_USE_UART)
                putrsUART((ROM char*)"\r\n");
            #endif


            #if defined(STACK_USE_ANNOUNCE)
                AnnounceIP();
            #endif

        }    
		#if defined(MRF24WG)
		{
			static DWORD t_UpdateImage=0;
			extern UINT8 Flag_ImageUpdate_running;
			if(Flag_ImageUpdate_running == 1)
			{
				UINT8 buf_command[4];
				if( (TickGet() - t_UpdateImage) >= TICK_SECOND * 120ul)
				{
					putsUART((char *)"Update Firmware timeout, begin to restore..\r\n");
					buf_command[0]=UPDATE_CMD_ERASE0; //Erase bank0
					buf_command[1]=UPDATE_SERITY_KEY_1; 
					buf_command[2]=UPDATE_SERITY_KEY_2; 
					buf_command[3]=UPDATE_SERITY_KEY_3; 
					SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
					buf_command[0]=UPDATE_CMD_CPY_1TO0; //Copy bank1 to bank0
					buf_command[1]=UPDATE_SERITY_KEY_1; 
					buf_command[2]=UPDATE_SERITY_KEY_2; 
					buf_command[3]=UPDATE_SERITY_KEY_3; 
					SendSetParamMsg(PARAM_FLASH_update, buf_command, 4);
					putsUART((char *)"restore Done\r\n");
					Flag_ImageUpdate_running = 0;
				}
					
			}
			else
			{
				t_UpdateImage = TickGet();
			}
		}
		#endif
    }
}

// Writes an IP address to the LCD display and the UART as available
void DisplayIPValue(IP_ADDR IPVal)
{
// printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
    BYTE IPDigit[4];
    BYTE i;
    for(i = 0; i < sizeof(IP_ADDR); i++)
    {
        uitoa((WORD)IPVal.v[i], IPDigit);

        #if defined(STACK_USE_UART)
            putsUART((char *) IPDigit);
        #endif

            if(i == sizeof(IP_ADDR)-1)
                break;

        #if defined(STACK_USE_UART)
            while(BusyUART());
            WriteUART('.');
        #endif
    }

}

// Processes A/D data from the potentiometer
static void ProcessIO(void)
{
    // AN0 should already be set up as an analog input
    ADCON0bits.GO = 1;

    // Wait until A/D conversion is done
    while(ADCON0bits.GO);

    // AD converter errata work around (ex: PIC18F87J10 A2)
    #if !defined(__18F87J50) && !defined(_18F87J50) && !defined(__18F87J11) && !defined(_18F87J11) 
    {
        BYTE temp = ADCON2;
        ADCON2 |= 0x7;    // Select Frc mode by setting ADCS0/ADCS1/ADCS2
        ADCON2 = temp;
    }
    #endif

    // Convert 10-bit value into ASCII string
    uitoa(*((WORD*)(&ADRESL)), AN0String);
}


/****************************************************************************
  Function:
    static void InitializeBoard(void)

  Description:
    This routine initializes the hardware.  It is a generic initialization
    routine for many of the Microchip development boards, using definitions
    in HardwareProfile.h to determine specific initialization.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
  ***************************************************************************/
static void InitializeBoard(void)
{    
    // LEDs
    LED0_TRIS = 0;
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
    LED6_TRIS = 0;
    LED7_TRIS = 0;
    LED_PUT(0x00);

    // Enable 4x/5x/96MHz PLL on PIC18F87J10, PIC18F97J60, PIC18F87J50, etc.
    OSCTUNE = 0x40;

    // Set up analog features of PORTA

    // PICDEM.net 2 board has POT on AN2, Temp Sensor on AN3
    #if defined(PICDEMNET2)
        ADCON0 = 0x09;        // ADON, Channel 2
        ADCON1 = 0x0B;        // Vdd/Vss is +/-REF, AN0, AN1, AN2, AN3 are analog
    #elif defined(PICDEMZ)
        ADCON0 = 0x81;        // ADON, Channel 0, Fosc/32
        ADCON1 = 0x0F;        // Vdd/Vss is +/-REF, AN0, AN1, AN2, AN3 are all digital
    #elif defined(__18F87J11) || defined(_18F87J11) || defined(__18F87J50) || defined(_18F87J50)
        ADCON0 = 0x01;        // ADON, Channel 0, Vdd/Vss is +/-REF
        WDTCONbits.ADSHR = 1;
        ANCON0 = 0xFC;        // AN0 (POT) and AN1 (temp sensor) are anlog
        ANCON1 = 0xFF;
        WDTCONbits.ADSHR = 0;        
    #else
        ADCON0 = 0x01;        // ADON, Channel 0
        ADCON1 = 0x0E;        // Vdd/Vss is +/-REF, AN0 is analog
    #endif
    ADCON2 = 0xBE;            // Right justify, 20TAD ACQ time, Fosc/64 (~21.0kHz)


    // Enable internal PORTB pull-ups
    INTCON2bits.RBPU = 0;

    // Configure USART
    TXSTA = 0x20;
    RCSTA = 0x90;

    // See if we can use the high baud rate setting
    #if ((GetPeripheralClock()+2*BAUD_RATE)/BAUD_RATE/4 - 1) <= 255
        SPBRG = (GetPeripheralClock()+2*BAUD_RATE)/BAUD_RATE/4 - 1;
        TXSTAbits.BRGH = 1;
    #else    // Use the low baud rate setting
        SPBRG = (GetPeripheralClock()+8*BAUD_RATE)/BAUD_RATE/16 - 1;
    #endif

	#ifdef	WEBPAGE_DEMO_SPI
	SPI_Initialize ();	// SPP
	#endif

    // Enable Interrupts
    RCONbits.IPEN = 1;        // Enable interrupt priorities
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

    // Do a calibration A/D conversion
    #if defined(__18F87J10) || defined(__18F86J15) || defined(__18F86J10) || defined(__18F85J15) || defined(__18F85J10) || defined(__18F67J10) || defined(__18F66J15) || defined(__18F66J10) || defined(__18F65J15) || defined(__18F65J10) || defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) || defined(__18F67J60) || defined(__18F66J65) || defined(__18F66J60) || \
         defined(_18F87J10) ||  defined(_18F86J15) || defined(_18F86J10)  ||  defined(_18F85J15) ||  defined(_18F85J10) ||  defined(_18F67J10) ||  defined(_18F66J15) ||  defined(_18F66J10) ||  defined(_18F65J15) ||  defined(_18F65J10) ||  defined(_18F97J60) ||  defined(_18F96J65) ||  defined(_18F96J60) ||  defined(_18F87J60) ||  defined(_18F86J65) ||  defined(_18F86J60) ||  defined(_18F67J60) ||  defined(_18F66J65) ||  defined(_18F66J60)
        ADCON0bits.ADCAL = 1;
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        ADCON0bits.ADCAL = 0;
    #elif defined(__18F87J11) || defined(__18F86J16) || defined(__18F86J11) || defined(__18F67J11) || defined(__18F66J16) || defined(__18F66J11) || \
           defined(_18F87J11) ||  defined(_18F86J16) ||  defined(_18F86J11) ||  defined(_18F67J11) ||  defined(_18F66J16) ||  defined(_18F66J11) || \
          defined(__18F87J50) || defined(__18F86J55) || defined(__18F86J50) || defined(__18F67J50) || defined(__18F66J55) || defined(__18F66J50) || \
           defined(_18F87J50) ||  defined(_18F86J55) ||  defined(_18F86J50) ||  defined(_18F67J50) ||  defined(_18F66J55) ||  defined(_18F66J50)
        ADCON1bits.ADCAL = 1;
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        ADCON1bits.ADCAL = 0;
    #endif


// Deassert all chip select lines so there isn't any problem with 
// initialization order.  Ex: When ENC28J60 is on SPI2 with Explorer 16, 
// MAX3232 ROUT2 pin will drive RF12/U2CTS ENC28J60 CS line asserted, 
// preventing proper 25LC256 EEPROM operation.
#if defined(EEPROM_CS_TRIS)
    EEPROM_CS_IO = 1;
    EEPROM_CS_TRIS = 0;
#endif
#if defined(SPIRAM_CS_TRIS)
    SPIRAM_CS_IO = 1;
    SPIRAM_CS_TRIS = 0;
#endif
#if defined(SPIFLASH_CS_TRIS)
    SPIFLASH_CS_IO = 1;
    SPIFLASH_CS_TRIS = 0;
#endif

#if defined(SPIRAM_CS_TRIS)
    SPIRAMInit();
#endif
#if defined(EEPROM_CS_TRIS)
    XEEInit();
#endif
#if defined(SPIFLASH_CS_TRIS)
    SPIFlashInit();
#endif
}

/*********************************************************************
 * Function:        void InitAppConfig(void)
 *
 * PreCondition:    MPFSInit() is already called.
 *
 * Input:           None
 *
 * Output:          Write/Read non-volatile config variables.
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
// MAC Address Serialization using a MPLAB PM3 Programmer and 
// Serialized Quick Turn Programming (SQTP). 
// The advantage of using SQTP for programming the MAC Address is it
// allows you to auto-increment the MAC address without recompiling 
// the code for each unit.  To use SQTP, the MAC address must be fixed
// at a specific location in program memory.  Uncomment these two pragmas
// that locate the MAC address at 0x1FFF0.  Syntax below is for MPLAB C 
// Compiler for PIC18 MCUs. Syntax will vary for other compilers.
//#pragma romdata MACROM=0x1FFF0
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};
//#pragma romdata

static void InitAppConfig(void)
{
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
    unsigned char vNeedToSaveDefaults = 0;
#endif
    
    while(1)
    {
        // Start out zeroing all AppConfig bytes to ensure all fields are 
        // deterministic for checksum generation
        memset((void*)&AppConfig, 0x00, sizeof(AppConfig));
        
        AppConfig.Flags.bIsDHCPEnabled = TRUE;
        AppConfig.Flags.bInConfigMode = TRUE;
        memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));
//        {
//            _prog_addressT MACAddressAddress;
//            MACAddressAddress.next = 0x157F8;
//            _memcpy_p2d24((char*)&AppConfig.MyMACAddr, MACAddressAddress, sizeof(AppConfig.MyMACAddr));
//        }
        AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
        AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
        AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
        AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
        AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
        AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
        AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;
    
    
        // Load the default NetBIOS Host Name
        memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
        FormatNetBIOSName(AppConfig.NetBIOSName);
    
        // Compute the checksum of the AppConfig defaults as loaded from ROM
        wOriginalAppConfigChecksum = CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig));

        #if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        {
            NVM_VALIDATION_STRUCT NVMValidationStruct;

            // Check to see if we have a flag set indicating that we need to 
            // save the ROM default AppConfig values.
            if(vNeedToSaveDefaults)
                SaveAppConfig(&AppConfig);
        
            // Read the NVMValidation record and AppConfig struct out of EEPROM/Flash
            #if defined(EEPROM_CS_TRIS)
            {
                XEEReadArray(0x0000, (BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
                XEEReadArray(sizeof(NVMValidationStruct), (BYTE*)&AppConfig, sizeof(AppConfig));
            }
            #elif defined(SPIFLASH_CS_TRIS)
            {
                SPIFlashReadArray(0x0000, (BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
                SPIFlashReadArray(sizeof(NVMValidationStruct), (BYTE*)&AppConfig, sizeof(AppConfig));
            }
            #endif
    
            // Check EEPROM/Flash validitity.  If it isn't valid, set a flag so 
            // that we will save the ROM default values on the next loop 
            // iteration.
            if((NVMValidationStruct.wConfigurationLength != sizeof(AppConfig)) ||
               (NVMValidationStruct.wOriginalChecksum != wOriginalAppConfigChecksum) ||
               (NVMValidationStruct.wCurrentChecksum != CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig))))
            {
                // Check to ensure that the vNeedToSaveDefaults flag is zero, 
                // indicating that this is the first iteration through the do 
                // loop.  If we have already saved the defaults once and the 
                // EEPROM/Flash still doesn't pass the validity check, then it 
                // means we aren't successfully reading or writing to the 
                // EEPROM/Flash.  This means you have a hardware error and/or 
                // SPI configuration error.
                if(vNeedToSaveDefaults)
                {
                    while(1);
                }
                
                // Set flag and restart loop to load ROM defaults and save them
                vNeedToSaveDefaults = 1;
                continue;
            }
            
            // If we get down here, it means the EEPROM/Flash has valid contents 
            // and either matches the ROM defaults or previously matched and 
            // was run-time reconfigured by the user.  In this case, we shall 
            // use the contents loaded from EEPROM/Flash.
            break;
        }
        #endif
        break;
    }
}

#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
void SaveAppConfig(const APP_CONFIG *ptrAppConfig)
{
    NVM_VALIDATION_STRUCT NVMValidationStruct;


    // Get proper values for the validation structure indicating that we can use 
    // these EEPROM/Flash contents on future boot ups
    NVMValidationStruct.wOriginalChecksum = wOriginalAppConfigChecksum;
    NVMValidationStruct.wCurrentChecksum = CalcIPChecksum((BYTE*)ptrAppConfig, sizeof(APP_CONFIG));
    NVMValidationStruct.wConfigurationLength = sizeof(APP_CONFIG);

    // Write the validation struct and current AppConfig contents to EEPROM/Flash
    #if defined(EEPROM_CS_TRIS)
        XEEBeginWrite(0x0000);
        XEEWriteArray((BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
        XEEWriteArray((BYTE*)ptrAppConfig, sizeof(APP_CONFIG));
    #else
        SPIFlashBeginWrite(0x0000);
        SPIFlashWriteArray((BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
        SPIFlashWriteArray((BYTE*)ptrAppConfig, sizeof(APP_CONFIG));
    #endif
}
#endif
