#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include <p32xxxx.h>
#include "def.h"
#include "str.h"


#pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (RMII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow multiple reconfigurations)
#pragma config FUSBIDIO = ON            // USB USBID Selection (Controlled by the USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (3x Divider)
#pragma config FPLLRNG = RANGE_8_16_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_27        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (2x Divider)
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration (External clock mode)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31           // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = OFF              // Background Debugger Enable (Debugger is disabled)
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config TRCEN = ON               // Trace Enable (Trace features in the CPU are enabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = ALLOW_PG2       // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF 


void InitSys(void){     //init sysem settings
    PRECONbits.PREFEN = 3;  //CONFIG
    PRECONbits.PFMWS = 2;   //CONFIG
    SYSKEY = 0xAA996655;    //CONFIG
    SYSKEY = 0x556699AA;    //CONFIG
    PB2DIVbits.PBDIV = 3;   //CONFIG       // PBCLK = SYSqu
    CFGCONbits.OCACLK = 1;  //CONFIG 
    PB3DIVbits.PBDIV = 3;   //CONFIG      // PBCLK3 = SYSCLK/25 (= 200/25 = 8 MHz)
    SYSKEY = 0x33333333;    //CONFIG
    PRISS = 0x76543210; //CONFIG
    INTCONSET = _INTCON_MVEC_MASK;
    
    // enable interrupts global//
    __builtin_enable_interrupts();  // interrupts enable
}   

void timer_1_init(void) {
    T1CONbits.TON = 0;  // timer off before config
    TMR1 = 0;   //timer counter 0
    T1CON = 0x0020; // init timer; TMR1 on, prescale 1:256
    PR1 = 7776;   // PR1 limit for TMR1 65535
    
    //timer - interrupts settings//
    IEC0bits.T1IE=1;  // interrupt enable/disable
	IPC1bits.T1IP=0b10; // priority = 2
    T1CONbits.ON = 1;
}   //init timer1 settings

void timer_2_init(void) {
    T2CONbits.TON = 0;  
    TMR2 = 0;   
    T2CON = 0x0060; 
    PR2 = 7776;
    
    //timer - interrupts settings//
    IEC0bits.T2IE=1;  
	IPC2bits.T2IP=0b01; 
    T2CONbits.ON = 1;
}   //init timer2

//void port_init(void) {
//    TRISE = 0x0;    // port init in output
////    TRISB = 0x0;
//    ANSELEbits.ANSE4 = 0;   //pin RE4 changed in to D
//    
//    SDI5Rbits.SDI5R = 0b0101;           //SDI5 --> RPB9
//    
//    U4RXRbits.U4RXR = 0b0010;           //U4RX --> RPB14    
//    U5RXRbits.U5RXR = 0b1101;           //U5RX --> RPA14 
//    
//    RPF12Rbits.RPF12R = 0b0010;         //U4TX    
//    RPA15Rbits.RPA15R = 0b0011;         //U5TX
//    
//    RPB10Rbits.RPB10R = 0b1001;         //SDO5
//}   //port init


void port_init (void) {
    TRISA = SYS_PORT_A_TRIS;
    ANSELA = SYS_PORT_A_ANSEL;
    TRISB = SYS_PORT_B_TRIS;
    ANSELB = SYS_PORT_B_ANSEL;
    TRISC = SYS_PORT_C_TRIS;
    ANSELC = SYS_PORT_C_ANSEL;
    TRISD = SYS_PORT_D_TRIS;
    ANSELD = SYS_PORT_D_ANSEL;
    LATD = SYS_PORT_D_LAT  ;
    TRISE = SYS_PORT_E_TRIS;
    ANSELE = SYS_PORT_E_ANSEL;
    TRISF = SYS_PORT_F_TRIS;
    ANSELF = SYS_PORT_F_ANSEL;
    TRISG = SYS_PORT_G_TRIS;
    ANSELG = SYS_PORT_G_ANSEL;
    
    /*  PPS configuration   */
    U4RXRbits.U4RXR = 0b0010;           //U4RX --> RPB14    
    U5RXRbits.U5RXR = 0b1101;           //U5RX --> RPA14    

    IC3Rbits.IC3R = 0b0010;             //IC3 --> RPF4
    IC4Rbits.IC4R = 0b0010;             //IC4 --> RPF5
    
    IC7Rbits.IC7R = 0b0100;             //IC7 --> RPF1
    IC8Rbits.IC8R = 0b0100;             //IC8 --> RPF0
    
    SDI5Rbits.SDI5R = 0b0101;           //SDI5 --> RPB9
    
    RPC14Rbits.RPC14R = 0b1011;         //OC3
    RPA15Rbits.RPA15R = 0b0011;         //U5TX
    RPF12Rbits.RPF12R = 0b0010;         //U4TX    
    RPB10Rbits.RPB10R = 0b1001;         //SDO5
}

void uart5_init(void) {     //init uart settings
    U5MODEbits.USIDL = 0;                   /* Continue in Idle mode */
    U5MODEbits.LPBACK = 0;                  /* Disable LoopBack */
    U5MODEbits.PDSEL = 0b00;                /* 8-bit data, no parity */
    U5MODEbits.STSEL = 0;                   /* One Stop bit */
    U5MODEbits.BRGH = 0;                    /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U5BRG = PBCLK2_ / (U5_speed * 16) - 1;    //1Mbit
    IFS5bits.U5TXIF = 0;                /* Clear interrupt flag */
    IPC45bits.U5TXIP = 2;                // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC45bits.U5TXIS = 0;                // sub priority, 0 is Low priority
    IEC5bits.U5TXIE = 1;                /* Enable receive interrupts */
    IFS5bits.U5RXIF = 0;                /* Clear interrupt flag */
    IPC45bits.U5RXIP = 2;                // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC45bits.U5RXIS = 0;                // sub priority, 0 is Low priority
    IEC5bits.U5RXIE = 1;                /* Enable receive interrupts */
    U5STAbits.UTXEN = 1;                /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U5STAbits.URXEN = 1;                /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U5STAbits.UTXISEL = 0b00;           /* 10 =Interrupt is generated and asserted while the transmit buffer is empty*/
    U5MODEbits.ON = 1;                   /* Enable UART module 1 */     
}   

// void tmr_1_init(unsigned short T1_delay, unsigned short TMR1_IE, unsigned  short  TMR1_ON) {
//     T1CONbits.TON = 0;
// 	TMR1=0x0000;
// 	PR1=T1_delay;					//
// 	IEC0bits.T1IE=TMR1_IE;
// 	IPC1bits.T1IP=0b10;			// priority = 2
// 	T1CONbits.TCKPS=0;				//T1 prescaler 1:8
// 	T1CONbits.TON=TMR1_ON;
// }