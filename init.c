#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "define.h"
#include "extern.h"


extern void DMA1_init(void);
extern void DMA4_init(void);
extern void conf_read(void);

extern void DMA2_init(void);
extern void DMA3_init(void);
extern void DMA5_init(void);

extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void* p) {
    return (int) p < 0 ? ((int) p & 0x1fffffffL) : (unsigned int) ((unsigned char*) p + 0x40000000L);
}



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
#pragma config SMCLR = MCLR_NORM        // Soft Master Clear Enable bit (MCLR pin generates a normal system Reset)
#pragma config SOSCGAIN = GAIN_2X       // Secondary Oscillator Gain Control bits (2x gain setting)
#pragma config SOSCBOOST = ON           // Secondary Oscillator Boost Kick Start Enable bit (Boost the kick start of the oscillator)
#pragma config POSCGAIN = GAIN_2X       // Primary Oscillator Gain Control bits (2x gain setting)
#pragma config POSCBOOST = ON           // Primary Oscillator Boost Kick Start Enable bit (Boost the kick start of the oscillator)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

/*** Ports System Service Configuration ***/

#define SYS_PORT_A_ANSEL        0x0600
#define SYS_PORT_A_TRIS         0xc6e3
#define SYS_PORT_A_LAT          0x0
#define SYS_PORT_A_ODC          0x0
#define SYS_PORT_A_CNPU         0x0
#define SYS_PORT_A_CNPD         0x0
#define SYS_PORT_A_CNEN         0x0

#define SYS_PORT_B_ANSEL        0x8000
#define SYS_PORT_B_TRIS         0xe6ff
#define SYS_PORT_B_LAT          0x8000
#define SYS_PORT_B_ODC          0x0
#define SYS_PORT_B_CNPU         0x0
#define SYS_PORT_B_CNPD         0x0
#define SYS_PORT_B_CNEN         0x0

#define SYS_PORT_C_ANSEL        0x0
#define SYS_PORT_C_TRIS         0xd01e
#define SYS_PORT_C_LAT          0x0
#define SYS_PORT_C_ODC          0x0
#define SYS_PORT_C_CNPU         0x0
#define SYS_PORT_C_CNPD         0x0
#define SYS_PORT_C_CNEN         0x0

#define SYS_PORT_D_ANSEL        0x0
#define SYS_PORT_D_TRIS         0x4
#define SYS_PORT_D_LAT          0x0
#define SYS_PORT_D_ODC          0x0
#define SYS_PORT_D_CNPU         0x0
#define SYS_PORT_D_CNPD         0x0
#define SYS_PORT_D_CNEN         0x0

#define SYS_PORT_E_ANSEL        0x0
#define SYS_PORT_E_TRIS         0x3e0
#define SYS_PORT_E_LAT          0x10
#define SYS_PORT_E_ODC          0x0
#define SYS_PORT_E_CNPU         0x0
#define SYS_PORT_E_CNPD         0x0
#define SYS_PORT_E_CNEN         0x0

#define SYS_PORT_F_ANSEL        0x0
#define SYS_PORT_F_TRIS         0x313b
#define SYS_PORT_F_LAT          0x0
#define SYS_PORT_F_ODC          0x0
#define SYS_PORT_F_CNPU         0x0
#define SYS_PORT_F_CNPD         0x0
#define SYS_PORT_F_CNEN         0x0

#define SYS_PORT_G_ANSEL        0x0
#define SYS_PORT_G_TRIS         0x8343
#define SYS_PORT_G_LAT          0x0
#define SYS_PORT_G_ODC          0x0
#define SYS_PORT_G_CNPU         0x0
#define SYS_PORT_G_CNPD         0x0
#define SYS_PORT_G_CNEN         0x0

void port_init(void) {
    TRISA = SYS_PORT_A_TRIS;
    ANSELA = SYS_PORT_A_ANSEL;
    TRISB = SYS_PORT_B_TRIS;
    ANSELB = SYS_PORT_B_ANSEL;
    TRISC = SYS_PORT_C_TRIS;
    ANSELC = SYS_PORT_C_ANSEL;
    TRISD = SYS_PORT_D_TRIS;
    ANSELD = 0;
    LATD = SYS_PORT_D_LAT;
    TRISE = SYS_PORT_E_TRIS;
    ANSELE = SYS_PORT_E_ANSEL;
    TRISF = SYS_PORT_F_TRIS;
    ANSELF = SYS_PORT_F_ANSEL;
    TRISG = SYS_PORT_G_TRIS;
    ANSELG = SYS_PORT_G_ANSEL;
    //    TRISDbits.TRISD2 = 1;   //77 ножка в режим входа
    TRISBbits.TRISB15 = 0; //44 ножка энейбл на выход 3uart
    TRISDbits.TRISD13 = 0; //80 ножка энейбл на выход 2uart
    TRISDbits.TRISD1 = 0; //76 ножка энейбл на выход 1uart


    /*Rx*/
    U1RXRbits.U1RXR = 0b0000; //U1RX --> RPD2
    U2RXRbits.U2RXR = 0b0100; //U2RX --> RPD4
    U3RXRbits.U3RXR = 0b0111; //U3RX --> RPC13
    U4RXRbits.U4RXR = 0b0010; //U4RX --> RPB14 /назначаем 14-ю ножку порта В на приемник для UART5
    U5RXRbits.U5RXR = 0b1101; //U5RX --> RPA14    

    SDI5Rbits.SDI5R = 0b0101; //SDI5 --> RPB9 /назначаем как вход последовательных данных

    RPC14Rbits.RPC14R = 0b1011; //OC3   //генерирует прерывания на сравнении с таймером 4
    /*Tx*/
    RPD3Rbits.RPD3R = 0b0001; //U1TX
    RPD5Rbits.RPD5R = 0b0010; //U2TX
    RPC14Rbits.RPC14R = 0b0001; //U3TX
    RPF12Rbits.RPF12R = 0b0010; //U4TX  
    RPA15Rbits.RPA15R = 0b0011; //U5TX

    RPB10Rbits.RPB10R = 0b1001; //SDO5
}

void tmr_1_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON) {
    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1 = T_delay; //
    IEC0bits.T1IE = TMR_IE;
    IPC1bits.T1IP = 0b10; // priority = 2
    T1CONbits.TCKPS = 0; //T1 prescaler 1:8
    T1CONbits.TON = TMR_ON;
}

void tmr_2_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON) {
    T2CONbits.TON = 0;
    TMR2 = 0x0000;
    PR2 = T_delay; //
    IEC0bits.T2IE = TMR_IE;
    IPC2bits.T2IP = 0b10; // priority = 2
    T2CONbits.TCKPS = 0; //T1 prescaler 1:8
    T2CONbits.TON = TMR_ON;
}

void tmr_5_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON) {
    T5CONbits.TON = 0;
    TMR5 = 0x0000;
    PR5 = T_delay; //
    IEC0bits.T5IE = TMR_IE;
    IPC6bits.T5IP = 0b10; // priority = 2
    T5CONbits.TCKPS = 0; //T1 prescaler 1:8
    T5CONbits.TON = TMR_ON;
}

void tmr_9_init(unsigned short T9_delay, unsigned short TMR9_IE, unsigned short TMR9_ON) {
    T9CONbits.TON = 0;
    TMR9 = 0x0000;
    PR9 = T9_delay; //
    IEC1bits.T9IE = TMR9_IE;
    IPC10bits.T9IP = 0b10; // priority = 2
    T9CONbits.TCKPS = 0b11; //T1 prescaler 1:8
    T9CONbits.TON = TMR9_ON;
}

void tmr_6_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON) {
    T6CONbits.TON = 0;
    TMR6 = 0x0000;
    PR6 = T_delay; //
    IEC0bits.T6IE = TMR_IE;
    IPC7bits.T6IP = 0b10; // priority = 2
    T6CONbits.TCKPS = 0; //T1 prescaler 1:8
    T6CONbits.TON = TMR_ON;
}

void tmr_7_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON) {
    T7CONbits.TON = 0;
    TMR7 = 0x0000;
    PR7 = T_delay; //
    IEC1bits.T7IE = TMR_IE;
    IPC8bits.T7IP = 0b10; // priority = 2
    T7CONbits.TCKPS = 0; //T1 prescaler 1:8
    T7CONbits.TON = TMR_ON;
}

void OC3_init(void) { //пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
    OC3CON = 0x0000; // Turn off the OC3 when performing the setup
    T4CON = 0;
    OC3R = 100; // Initialize primary Compare register
    OC3RS = 3000; // Initialize secondary Compare register
    OC3CON = 0x0006; // Configure for PWM mode without Fault pin enabled
    T4CONbits.TCKPS = 0;
    PR4 = TMR4CLK / OC_FREQ; // Set period
    IFS0bits.T4IF = 0; // Clear the T4 interrupt flag
    IEC0bits.T4IE = 1; // Enable T4 interrupt
    IPC4bits.T4IP = 4; // Set T4 interrupt priority to 4
    //T4CONbits.ON = 1;      // Enable Timer4
    //OC3CONbits.ON = 1;     // Enable OC3//
}

void uart5_init(void) {
    U5MODEbits.USIDL = 0; /* Continue in Idle mode */
    U5MODEbits.LPBACK = 0; /* Disable LoopBack */
    U5MODEbits.PDSEL = 0b00; /* 8-bit data, no parity */
    U5MODEbits.STSEL = 0; /* One Stop bit */
    U5MODEbits.BRGH = 0; /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U5BRG = PBCLK2_ / (U5_speed * 16) - 1; //1Mbit
    IFS5bits.U5TXIF = 0; /* Clear interrupt flag */
    IPC45bits.U5TXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC45bits.U5TXIS = 0; // sub priority, 0 is Low priority
    IEC5bits.U5TXIE = 0; /* Enable receive interrupts */
    IFS5bits.U5RXIF = 0; /* Clear interrupt flag */
    IPC45bits.U5RXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC45bits.U5RXIS = 0; // sub priority, 0 is Low priority
    IEC5bits.U5RXIE = 1; /* Enable receive interrupts */
    U5STAbits.UTXEN = 1; /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U5STAbits.URXEN = 1; /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U5STAbits.UTXISEL = 0b10; /* 10 =Interrupt is generated and asserted while the transmit buffer is empty*/
    U5MODEbits.ON = 1; /* Enable UART module 1 */
}

void uart4_init(void) {
    U4MODEbits.USIDL = 0; /* Continue in Idle mode */
    U4MODEbits.LPBACK = 0; /* Disable LoopBack */
    U4MODEbits.PDSEL = 0b00; /* 8-bit data, no parity */
    U4MODEbits.STSEL = 0; /* One Stop bit */
    U4MODEbits.BRGH = 0; /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U4BRG = PBCLK2_ / (U4_speed * 16) - 1; //1Mbit
    IFS5bits.U4TXIF = 0; /* Clear interrupt flag */
    IPC43bits.U4TXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC43bits.U4TXIS = 0; // sub priority, 0 is Low priority
    IEC5bits.U4TXIE = 0; /* Enable receive interrupts */
    IFS5bits.U4RXIF = 0; /* Clear interrupt flag */
    IPC42bits.U4RXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC42bits.U4RXIS = 0; // sub priority, 0 is Low priority
    IEC5bits.U4RXIE = 1; /* Enable receive interrupts */
    U4STAbits.UTXEN = 1; /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U4STAbits.URXEN = 1; /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U4STAbits.UTXISEL = 0b10;
    U4MODEbits.ON = 1;
}

void uart3_init(void) {
    U3MODEbits.USIDL = 0; /* Continue in Idle mode */
    U3MODEbits.LPBACK = 0; /* Disable LoopBack */
    U3MODEbits.PDSEL = 0b00; /* 8-bit data, no parity */
    U3MODEbits.STSEL = 0; /* One Stop bit */
    U3MODEbits.BRGH = 0; /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U3BRG = PBCLK2_ / (U3_speed * 16) - 1; //1Mbit
    IFS4bits.U3TXIF = 0; /* Clear interrupt flag */
    IPC39bits.U3TXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC39bits.U3TXIS = 0; // sub priority, 0 is Low priority
    IEC4bits.U3TXIE = 0; /* Enable receive interrupts */
    IFS4bits.U3RXIF = 0; /* Clear interrupt flag */
    IPC39bits.U3RXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC39bits.U3RXIS = 0; // sub priority, 0 is Low priority
    IEC4bits.U3RXIE = 1; /* Enable receive interrupts */
    U3STAbits.UTXEN = 1; /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U3STAbits.URXEN = 1; /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U3STAbits.UTXISEL = 0b10;
    U3MODEbits.ON = 1;
}

void uart2_init(void) {
    U2MODEbits.USIDL = 0; /* Continue in Idle mode */
    U2MODEbits.LPBACK = 0; /* Disable LoopBack */
    U2MODEbits.PDSEL = 0b00; /* 8-bit data, no parity */
    U2MODEbits.STSEL = 0; /* One Stop bit */
    U2MODEbits.BRGH = 0; /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U2BRG = PBCLK2_ / (U2_speed * 16) - 1; //1Mbit
    IFS4bits.U2TXIF = 0; /* Clear interrupt flag */
    IPC36bits.U2TXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC36bits.U2TXIS = 0; // sub priority, 0 is Low priority
    IEC4bits.U2TXIE = 0; /* Enable receive interrupts */
    IFS4bits.U2RXIF = 0; /* Clear interrupt flag */
    IPC36bits.U2RXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC36bits.U2RXIS = 0; // sub priority, 0 is Low priority
    IEC4bits.U2RXIE = 1; /* Enable receive interrupts */
    U2STAbits.UTXEN = 1; /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U2STAbits.URXEN = 1; /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U2STAbits.UTXISEL = 0b10;
    U2MODEbits.ON = 1;
}

void uart1_init(void) {
    U1MODEbits.USIDL = 0; /* Continue in Idle mode */
    U1MODEbits.LPBACK = 0; /* Disable LoopBack */
    U1MODEbits.PDSEL = 0b00; /* 8-bit data, no parity */
    U1MODEbits.STSEL = 0; /* One Stop bit */
    U1MODEbits.BRGH = 0; /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U1BRG = PBCLK2_ / (U4_speed * 16) - 1; //1Mbit
    IFS3bits.U1TXIF = 0; /* Clear interrupt flag */
    IPC28bits.U1TXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC28bits.U1TXIS = 0; // sub priority, 0 is Low priority
    IEC3bits.U1TXIE = 0; /* Enable receive interrupts */
    IFS3bits.U1RXIF = 0; /* Clear interrupt flag */
    IPC28bits.U1RXIP = 2; // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC28bits.U1RXIS = 0; // sub priority, 0 is Low priority
    IEC3bits.U1RXIE = 1; /* Enable receive interrupts */
    U1STAbits.UTXEN = 1; /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U1STAbits.URXEN = 1; /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U1STAbits.UTXISEL = 0b10;
    U1MODEbits.ON = 1;
}

void spi5_init(void) {
    unsigned int t_brg;
    unsigned int baudHigh;
    unsigned int baudLow;
    unsigned int errorHigh;
    unsigned int errorLow;
    unsigned int baudRate;

    baudRate = 8294400;

    SPI5CONbits.ON = 0;
    SPI5CONbits.MSTEN = 1;
    SPI5CONbits.MSSEN = 0;
    SPI5CONbits.SIDL = 0;
    SPI5CONbits.CKP = 0;
    SPI5CONbits.CKE = 1;
    SPI5CONbits.SMP = 0;
    SPI5CONbits.MODE16 = 0;
    SPI5CONbits.MODE32 = 0;
    SPI5CONbits.FRMEN = 0;
    SPI5CON2bits.AUDEN = 0;
    SPI5CONbits.ENHBUF = 1;
    t_brg = (((PBCLK2_ / baudRate) / 2) - 1);
    baudHigh = PBCLK2_ / (2 * (t_brg + 1));
    baudLow = PBCLK2_ / (2 * (t_brg + 2));
    errorHigh = baudHigh - baudRate;
    errorLow = baudRate - baudLow;
    if (errorHigh > errorLow) {
        t_brg++;
    }
    SPI5BRG = t_brg;
    SPI5CONbits.ON = 1;
}

void InitializeSystem(void) {
    // PIC32MZ CPU Speed Optimizations (Cache/Wait States/Peripheral Bus Clks)
    // On reset, I+D cache is enabled for max performace setting (write-back with write allocation)
    // No wait setting required for main data RAM

    // Prefetch-cache: Enable prefetch for PFM (any PFM instructions or data)
    PRECONbits.PREFEN = 3; //предварительная выборка данных загружать их в кэш
    // Flash PM Wait States: MZ Flash runs at 2 wait states @ 200 MHz
    PRECONbits.PFMWS = 2; //чето со временем связанно
    // PBClk3 set to 8 MHz (assumes SYSCLK = 200 MHz via configuration bits)
    // Unlock Sequence
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    // Modify PB3DIV
    PB2DIVbits.PBDIV = 3; // PBCLK = SYSCLK/8 = 24883200 Hz)
    CFGCONbits.OCACLK = 1;
    PB3DIVbits.PBDIV = 3; // PBCLK3 = SYSCLK/25 (= 200/25 = 8 MHz)
    // Lock sequence
    SYSKEY = 0x33333333;

    port_init();
    spi5_init();
    help_load = 1;
    conf_read();

    tmr_1_init(100, 0, 0);
    tmr_2_init(100, 0, 0);
    tmr_5_init(100, 0, 0);
    tmr_6_init(100, 0, 0);
    tmr_7_init(100, 0, 0);
    tmr_9_init(65000, 1, 1);
    OC3_init();
    uart5_init();
    uart4_init();
    //    uart3_init();
    //    uart2_init();
    uart1_init();
    DMA5_init();
    DMA4_init();
    DMA1_init();

    /* Assign PIC32MZ shadow register sets to specific CPU IPLs */
    PRISS = 0x76543210;

    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK; //

    /* Enable Interrupt Exceptions */
    // set the CP0 status IE bit high to turn on interrupts globally
    __builtin_enable_interrupts();

    /* Enable the peripheral */
    /* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
    T2CONbits.TON = 1;
    T1CONbits.TON = 1;
    T4CONbits.ON = 1; // Enable Timer 4
    T5CONbits.ON = 1; // Enable Timer 5
    OC3CONbits.ON = 1; // Enable OC3//
    //    ADCCON3bits.GSWTRG = 1;
}