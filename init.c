#include "extern.h"

extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void *p)
{
    // ������� _VirtToPhys ������������ ��� �������������� ������������ ������ � ���������� �����.
    // ���������� ���������� �����, ������� �������� ��������� �� 0x40000000 �� ������������ ������,
    // ���� ����������� ����� �������������, ����� ���������� ������� 29 ��� ������������ ������.
    return (int)p < 0 ? ((int)p & 0x1fffffffL) : (unsigned int)((unsigned char *)p + 0x40000000L);
}

// ��������� Ethernet

#pragma config FMIIEN = OFF  // ���������/���������� ���������� Ethernet (��������)
#pragma config FETHIO = ON   // ����� ������� ��� Ethernet (����������� ������)
#pragma config PGL1WAY = ON  // ���������� ����������� ��������� ������ ���������� (��������� ����������� ���������)
#pragma config PMDL1WAY = ON // ���������� ����������� ��������� ������ ��������� (��������� ����������� ���������)
#pragma config IOL1WAY = OFF // ���������� ����������� ��������� ������ ������� (��������� ������������ ���������)
#pragma config FUSBIDIO = ON // ����� ������� USB �������������� (������������� USB �������������� ������� USB)

// DEVCFG2
/* DEVCFG2 - ��� ����������������, ������� ������������ ��� ��������� ������������ DEVCFG2 (Device Configuration 2)
���������������� PIC32MZ1024EFH100. DEVCFG2 ���������� ��������� ����� ��� �������� �������� ������� ���������� PLL (FPLLIDIV),
�������� �������� ������� ���������� PLL (FPLLRNG), �������� ��������� ������� ���������� PLL (FPLLICLK), ��������� ����������
PLL (FPLLMULT), �������� ��������� ������� ���������� PLL (FPLLODIV) � ������� �������� ������� USB PLL (UPLLFSEL). ��� ���������
��������� ��������� ������ ���������� � USB PLL ��� ���������� ��������� ������� ���� � ������������ ���������
����������������. */
#pragma config FPLLIDIV = DIV_1         // �������� �������� ������� ��� ��������� PLL (�������� �� 3)
#pragma config FPLLRNG = RANGE_8_16_MHZ // �������� �������� ������� ��� ��������� PLL (5-10 ���)
#pragma config FPLLICLK = PLL_POSC      // �������� ��������� ������� ��� ��������� PLL (������� ����������)
#pragma config FPLLMULT = MUL_27        // ��������� ��������� PLL (���������� � 50 ���)
#pragma config FPLLODIV = DIV_2         // �������� ��������� ������� ��������� PLL (�������� �� 2)
#pragma config UPLLFSEL = FREQ_24MHZ    // ������� �������� ������� ��� USB PLL (24 ���)

// DEVCFG1
/* DEVCFG1 - ��� ����������������, ������������ ��� ��������� ������������ DEVCFG1 (Device Configuration 1)
���������������� PIC32MZ1024EFH100. DEVCFG1 ���������� ���������, ����� ��� ����� ��������� ��������� ������� (FNOSC),
�������� ����� ���� DMT (DMTINTV), ��������� �����������/�������� ������������ (IESO), ������������ ���������
���������� (POSCMOD), ��������� ����������� ��� ������� (OSCIOFNC), ����� ����������� �������������� FSCM � ������.
��� ��������� ��������� ����������� �������� ��������� �������� ���������� ����������������, ������� ����� �����������,
��������� ����������� ������� � ������ ��������� ������ ����. */
#pragma config FNOSC = SPLL          // ����� ��������� ��������� ������� (��������� PLL)
#pragma config DMTINTV = WIN_127_128 // �������� ����� DMT (127/128 �� �������� ��������)
#pragma config FSOSCEN = OFF         // ���������/���������� ���������� ����������� (��������)
#pragma config IESO = ON             // ���������/���������� ���������������� ��������� ��������� ������� (��������)
#pragma config POSCMOD = EC          // ����� ��������� ����������� (������� �����)
#pragma config OSCIOFNC = OFF        // ��������� ������ CLKO (���������)
#pragma config FCKSM = CSECME        // ��������� ������������ ��������� ������� � �������� (������������ ��������� ������� � ������� ��������)
#pragma config WDTPS = PS1048576     // ������������ ����������� ������� (1:1048576)
#pragma config WDTSPGM = STOP        // ��������� ����������� ������� �� ����� ���������������� Flash (���������� ������ ��������������� �� ����� ���������������� Flash)
#pragma config WINDIS = NORMAL       // ����� ���������� ����������� ������� (����������)
#pragma config FWDTEN = OFF          // ���������/���������� ����������� ������� (���������)
#pragma config FWDTWINSZ = WINSZ_25  // ������ ���������� ����������� ������� (25%)
#pragma config DMTCNT = DMT31        // ����� �������� �������� Deadman Timer (2^31)
#pragma config FDMTEN = OFF          // ���������/���������� Deadman Timer (���������)

// DEVCFG0
/* DEVCFG0 - ��� ����������������, ������������ ��� ��������� ������������ DEVCFG0 (Device Configuration 0) ����������������
PIC32MZ1024EFH100. DEVCFG0 ���������� ���������, ����� ��� ���������� ��������� �� ������� ����� (DEBUG), ��������� JTAG
(JTAGEN), ����� ������ ����� ICE/ICD (ICESEL), ���������� ����������� (TRCEN), ����� ISA ������������ ���� (BOOTISA),
������������ ECC ��� Flash-������ (FECCCON), ����� ��� Flash (FSLEEP), ������ � ������ ������� ��� CPU (DBGPER), �����������
����� (SMCLR), �������� ���������� ����������� (SOSCGAIN), ��������� ��������� ���������� ����������� (SOSCBOOST), ��������
��������� ����������� (POSCGAIN), ��������� ��������� ��������� ����������� (POSCBOOST), ��������� EJTAG (EJTAGBEN), � �����
������� ������ (CP). ��� ��������� ���������� ��������� ������� ������ ����������������, ����� ��� ��������� �������, ������ ���,
������������ ����������� � ������ ���������. */
#pragma config DEBUG = OFF            // ���������/���������� ��������� (��������)
#pragma config JTAGEN = OFF           // ���������/���������� JTAG (��������)
#pragma config ICESEL = ICS_PGx1      // ����� ������ ������� ICE/ICD (PGEC2/PGED2)
#pragma config TRCEN = ON             // ���������/���������� ����������� (��������)
#pragma config BOOTISA = MIPS32       // ����� ISA ��� �������� (MIPS32)
#pragma config FECCCON = OFF_UNLOCKED // ������������ ������������ ECC ��� Flash (ECC � ������������ ECC ���������)
#pragma config FSLEEP = OFF           // ����� ��� ��� Flash (Flash ��//��������� �� ����� ���)
#pragma config DBGPER = ALLOW_PG2     // ���������� ������� ����������� ������ � CPU (�������� ������ � Permission Group 2)
#pragma config SMCLR = MCLR_NORM      // ���������/���������� ������� ������ (���������� ����� ������)
#pragma config SOSCGAIN = GAIN_2X     // ��������� �������� ���������� ����������� (�������� � 2 ����)
#pragma config SOSCBOOST = ON         // ���������/���������� ��������� ������ ���������� ����������� (��������� ������ �����������)
#pragma config POSCGAIN = GAIN_2X     // ��������� �������� ���������� ����������� (�������� � 2 ����)
#pragma config POSCBOOST = ON         // ���������/���������� ��������� ������ ���������� ����������� (��������� ������ �����������)
#pragma config EJTAGBEN = NORMAL      // �������� EJTAG (���������� EJTAG-����������������)

// DEVCP0
/* DEVCP0 - ��� ����������������, ������������ ��� ��������� ������������ DEVCP0 (Device Code Protection 0)
���������������� PIC32MZ1024EFH100. DEVCP0 ���������� ��������� ������ ����, ����� ��� ������ ���� (CP),
������� ����� ���� �������� ��� ���������. ����� ������ ���� �������� (CP = ON), ��� ��������, ��� ������
������������ ���� �������, ��� ������ ����������� ������ �/��� ������ ������������ ���� � ��������������� ���
����������� ���������� ��� ���������� ��������. */
#pragma config CP = OFF // ������ ���� (������ ���������)

/*** Ports System Service Configuration ***/

// ��������� ����� A
#define SYS_PORT_A_ANSEL 0x0600 // ��������� �������� ANSEL ��� ����� A
#define SYS_PORT_A_TRIS 0xc6e3  // ��������� �������� TRIS ��� ����� A
#define SYS_PORT_A_LAT 0x0      // ��������� �������� LAT ��� ����� A
#define SYS_PORT_A_ODC 0x0      // ��������� �������� ODC ��� ����� A
#define SYS_PORT_A_CNPU 0x0     // ��������� �������� CNPU ��� ����� A
#define SYS_PORT_A_CNPD 0x0     // ��������� �������� CNPD ��� ����� A
#define SYS_PORT_A_CNEN 0x0     // ��������� �������� CNEN ��� ����� A

// ��������� ����� B
#define SYS_PORT_B_ANSEL 0x8000 // ��������� �������� ANSEL ��� ����� B
#define SYS_PORT_B_TRIS 0xe6ff  // ��������� �������� TRIS ��� ����� B
#define SYS_PORT_B_LAT 0x8000   // ��������� �������� LAT ��� ����� B
#define SYS_PORT_B_ODC 0x0      // ��������� �������� ODC ��� ����� B
#define SYS_PORT_B_CNPU 0x0     // ��������� �������� CNPU ��� ����� B
#define SYS_PORT_B_CNPD 0x0     // ��������� �������� CNPD ��� ����� B
#define SYS_PORT_B_CNEN 0x0     // ��������� �������� CNEN ��� ����� B

// ��������� ����� C
#define SYS_PORT_C_ANSEL 0x0   // ��������� �������� ANSEL ��� ����� C
#define SYS_PORT_C_TRIS 0xb01e // ��������� �������� TRIS ��� ����� C
#define SYS_PORT_C_LAT 0x0     // ��������� �������� LAT ��� ����� C
#define SYS_PORT_C_ODC 0x0     // ��������� �������� ODC ��� ����� C
#define SYS_PORT_C_CNPU 0x0    // ��������� �������� CNPU ��� ����� C
#define SYS_PORT_C_CNPD 0x0    // ��������� �������� CNPD ��� ����� C
#define SYS_PORT_C_CNEN 0x0    // ��������� �������� CNEN ��� ����� C

// ��������� ����� D
#define SYS_PORT_D_ANSEL 0x0 // ��������� �������� ANSEL ��� ����� D
#define SYS_PORT_D_TRIS 0x14 // ��������� �������� TRIS ��� ����� D
#define SYS_PORT_D_LAT 0x0   // ��������� �������� LAT ��� ����� D
#define SYS_PORT_D_ODC 0x0   // ��������� �������� ODC ��� ����� D
#define SYS_PORT_D_CNPU 0x0  // ��������� �������� CNPU ��� ����� D
#define SYS_PORT_D_CNPD 0x0  // ��������� �������� CNPD ��� ����� D
#define SYS_PORT_D_CNEN 0x0  // ��������� �������� CNEN ��� ����� D

// ��������� ����� E
#define SYS_PORT_E_ANSEL 0x0  // ��������� �������� ANSEL ��� ����� E
#define SYS_PORT_E_TRIS 0x3e0 // ��������� �������� TRIS ��� ����� E
#define SYS_PORT_E_LAT 0x10   // ��������� �������� LAT ��� ����� E
#define SYS_PORT_E_ODC 0x0    // ��������� �������� ODC ��� ����� E
#define SYS_PORT_E_CNPU 0x0   // ��������� �������� CNPU ��� ����� E
#define SYS_PORT_E_CNPD 0x0   // ��������� �������� CNPD ��� ����� E
#define SYS_PORT_E_CNEN 0x0   // ��������� �������� CNEN ��� ����� E

// ��������� ����� F
#define SYS_PORT_F_ANSEL 0x0   // ��������� �������� ANSEL ��� ����� F
#define SYS_PORT_F_TRIS 0x113b // ��������� �������� TRIS ��� ����� F
#define SYS_PORT_F_LAT 0x0     // ��������� �������� LAT ��� ����� F
#define SYS_PORT_F_ODC 0x0     // ��������� �������� ODC ��� ����� F
#define SYS_PORT_F_CNPU 0x0    // ��������� �������� CNPU ��� ����� F
#define SYS_PORT_F_CNPD 0x0    // ��������� �������� CNPD ��� ����� F
#define SYS_PORT_F_CNEN 0x0    // ��������� �������� CNEN ��� ����� F

// ��������� ����� G
#define SYS_PORT_G_ANSEL 0x0   // ��������� �������� ANSEL ��� ����� G
#define SYS_PORT_G_TRIS 0x8343 // ��������� �������� TRIS ��� ����� G
#define SYS_PORT_G_LAT 0x0     // ��������� �������� LAT ��� ����� G
#define SYS_PORT_G_ODC 0x0     // ��������� �������� ODC ��� ����� G
#define SYS_PORT_G_CNPU 0x0    // ��������� �������� CNPU ��� ����� G
#define SYS_PORT_G_CNPD 0x0    // ��������� �������� CNPD ��� ����� G
#define SYS_PORT_G_CNEN 0x0    // ��������� �������� CNEN ��� ����� G

void port_init(void)
{
    // ��������� ����� A
    TRISA = SYS_PORT_A_TRIS;   // ��������� ����������� ����� A � ������������ � ����������������� ����������
    ANSELA = SYS_PORT_A_ANSEL; // ��������� ���������� ������ ����� A � ������������ � ����������������� ����������

    // ��������� ����� B
    TRISB = SYS_PORT_B_TRIS;   // ��������� ����������� ����� B � ������������ � ����������������� ����������
    ANSELB = SYS_PORT_B_ANSEL; // ��������� ���������� ������ ����� B � ������������ � ����������������� ����������

    // ��������� ����� C
    TRISC = SYS_PORT_C_TRIS;   // ��������� ����������� ����� C � ������������ � ����������������� ����������
    ANSELC = SYS_PORT_C_ANSEL; // ��������� ���������� ������ ����� C � ������������ � ����������������� ����������

    // ��������� ����� D
    TRISD = SYS_PORT_D_TRIS; // ��������� ����������� ����� D � ������������ � ����������������� ����������
    ANSELD = 0;              // ���������� ���������� ������ ����� D
    LATD = SYS_PORT_D_LAT;   // ��������� ��������� ����� D � ������������ � ����������������� ����������

    // ��������� ����� E
    TRISE = SYS_PORT_E_TRIS;   // ��������� ����������� ����� E � ������������ � ����������������� ����������
    ANSELE = SYS_PORT_E_ANSEL; // ��������� ���������� ������ ����� E � ������������ � ����������������� ����������

    // ��������� ����� F
    TRISF = SYS_PORT_F_TRIS;   // ��������� ����������� ����� F � ������������ � ����������������� ����������
    ANSELF = SYS_PORT_F_ANSEL; // ��������� ���������� ������ ����� F � ������������ � ����������������� ����������

    // ��������� ����� G
    TRISG = SYS_PORT_G_TRIS;   // ��������� ����������� ����� G � ������������ � ����������������� ����������
    ANSELG = SYS_PORT_G_ANSEL; // ��������� ���������� ������ ����� G � ������������ � ����������������� ����������

    // �������������� ��������� ��������� ������������� ������ � �� �������
    TRISBbits.TRISB15 = 0; // ��������� ����������� ����� B, 15-� �����, � �������� ������ ��� ���������� 3-� UART
    TRISDbits.TRISD1 = 0;  // ��������� ����������� ����� D, 1-� �����, � �������� ������ ��� ���������� 1-� UART

    // ���������� ������� ��� ������ ������ UART �� ��������������� ������
    U1RXRbits.U1RXR = 0b0000; // ����������� ��������� UART1 � ����� RPD2
    U2RXRbits.U2RXR = 0b0100; // ����������� ��������� UART2 � ����� RPD4
    U3RXRbits.U3RXR = 0b0111; // ����������� ��������� UART3 � ����� RPC13
    U4RXRbits.U4RXR = 0b0010; // ����������� ��������� UART4 � ����� RPB14
    U5RXRbits.U5RXR = 0b1101; // ����������� ��������� UART5 � ����� RPA14

    // ���������� ������� ��� �������� ������ UART �� ��������������� ������
    RPD3Rbits.RPD3R = 0b0001;   // ����������� ����������� UART1 � ����� RPD3
    RPD5Rbits.RPD5R = 0b0010;   // ����������� ����������� UART2 � ����� RPD5
    RPC14Rbits.RPC14R = 0b0001; // ����������� ����������� UART3 � ����� RPC14
    RPF12Rbits.RPF12R = 0b0010; // ����������� ����������� UART4 � ����� RPF12
    RPA15Rbits.RPA15R = 0b0011; // ����������� ����������� UART5 � ����� RPA15

    // ���������� ������� SPI ��� ����� B, 10-� �����
    RPB10Rbits.RPB10R = 0b1001; // ����������� SPI � ����� RPB10
}

void tmr_1_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON)
{
    T1CONbits.TON = 0;
    TMR1 = 0x0000;
    PR1 = T_delay; //
    IEC0bits.T1IE = TMR_IE;
    IPC1bits.T1IP = 0b10; // priority = 2
    T1CONbits.TCKPS = 0;  // T1 prescaler 1:8
    T1CONbits.TON = TMR_ON;
}

void tmr_2_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON)
{
    T2CONbits.TON = 0;
    TMR2 = 0x0000;
    PR2 = T_delay; //
    IEC0bits.T2IE = TMR_IE;
    IPC2bits.T2IP = 0b10; // priority = 2
    T2CONbits.TCKPS = 0;  // T1 prescaler 1:8
    T2CONbits.TON = TMR_ON;
}

void tmr_5_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON)
{
    T5CONbits.TON = 0;
    TMR5 = 0x0000;
    PR5 = T_delay; //
    IEC0bits.T5IE = TMR_IE;
    IPC6bits.T5IP = 0b10; // priority = 2
    T5CONbits.TCKPS = 0;  // T1 prescaler 1:8
    T5CONbits.TON = TMR_ON;
}

void tmr_9_init(unsigned short T9_delay, unsigned short TMR9_IE, unsigned short TMR9_ON)
{
    T9CONbits.TON = 0;
    TMR9 = 0x0000;
    PR9 = T9_delay; //
    IEC1bits.T9IE = TMR9_IE;
    IPC10bits.T9IP = 0b10;  // priority = 2
    T9CONbits.TCKPS = 0b11; // T1 prescaler 1:8
    T9CONbits.TON = TMR9_ON;
}

void tmr_6_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON)
{
    T6CONbits.TON = 0;
    TMR6 = 0x0000;
    PR6 = T_delay; //
    IEC0bits.T6IE = TMR_IE;
    IPC7bits.T6IP = 0b10; // priority = 2
    T6CONbits.TCKPS = 0;  // T1 prescaler 1:8
    T6CONbits.TON = TMR_ON;
}

void tmr_7_init(unsigned short T_delay, unsigned short TMR_IE, unsigned short TMR_ON)
{
    T7CONbits.TON = 0;
    TMR7 = 0x0000;
    PR7 = T_delay; //
    IEC1bits.T7IE = TMR_IE;
    IPC8bits.T7IP = 0b10; // priority = 2
    T7CONbits.TCKPS = 0;  // T1 prescaler 1:8
    T7CONbits.TON = TMR_ON;
}

void OC3_init(void)
{                    // ����� ���
    OC3CON = 0x0000; // Turn off the OC3 when performing the setup
    T4CON = 0;
    OC3R = 100;      // Initialize primary Compare register
    OC3RS = 3000;    // Initialize secondary Compare register
    OC3CON = 0x0006; // Configure for PWM mode without Fault pin enabled
    T4CONbits.TCKPS = 0;
    PR4 = TMR4CLK / OC_FREQ; // Set period
    IFS0bits.T4IF = 0;       // Clear the T4 interrupt flag
    IEC0bits.T4IE = 1;       // Enable T4 interrupt
    IPC4bits.T4IP = 4;       // Set T4 interrupt priority to 4
    // T4CONbits.ON = 1;      // Enable Timer4
    // OC3CONbits.ON = 1;     // Enable OC3//
}

void uart5_init(void)
{
    U5MODEbits.USIDL = 0;                  /* Continue in Idle mode */
    U5MODEbits.LPBACK = 0;                 /* Disable LoopBack */
    U5MODEbits.PDSEL = 0b00;               /* 8-bit data, no parity */
    U5MODEbits.STSEL = 0;                  /* One Stop bit */
    U5MODEbits.BRGH = 0;                   /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U5BRG = PBCLK2_ / (U5_speed * 16) - 1; // 1Mbit
    IFS5bits.U5TXIF = 0;                   /* Clear interrupt flag */
    IPC45bits.U5TXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC45bits.U5TXIS = 0;                  // sub priority, 0 is Low priority
    IEC5bits.U5TXIE = 0;                   /* Enable receive interrupts */
    IFS5bits.U5RXIF = 0;                   /* Clear interrupt flag */
    IPC45bits.U5RXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC45bits.U5RXIS = 0;                  // sub priority, 0 is Low priority
    IEC5bits.U5RXIE = 1;                   /* Enable receive interrupts */
    U5STAbits.UTXEN = 1;                   /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U5STAbits.URXEN = 1;                   /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U5STAbits.UTXISEL = 0b10;              /* 10 =Interrupt is generated and asserted while the transmit buffer is empty*/
    U5MODEbits.ON = 1;                     /* Enable UART module 1 */
}

void uart4_init(void)
{
    U4MODEbits.USIDL = 0;                  /* Continue in Idle mode */
    U4MODEbits.LPBACK = 0;                 /* Disable LoopBack */
    U4MODEbits.PDSEL = 0b00;               /* 8-bit data, no parity */
    U4MODEbits.STSEL = 0;                  /* One Stop bit */
    U4MODEbits.BRGH = 0;                   /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U4BRG = PBCLK2_ / (U5_speed * 16) - 1; // 1Mbit
    IFS5bits.U4TXIF = 0;                   /* Clear interrupt flag */
    IPC43bits.U4TXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC43bits.U4TXIS = 0;                  // sub priority, 0 is Low priority
    IEC5bits.U4TXIE = 0;                   /* Enable receive interrupts */
    IFS5bits.U4RXIF = 0;                   /* Clear interrupt flag */
    IPC42bits.U4RXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC42bits.U4RXIS = 0;                  // sub priority, 0 is Low priority
    IEC5bits.U4RXIE = 1;                   /* Enable receive interrupts */
    U4STAbits.UTXEN = 1;                   /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U4STAbits.URXEN = 1;                   /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U4STAbits.UTXISEL = 0b10;
    U4MODEbits.ON = 1;
}

void uart3_init(void)
{
    U3MODEbits.USIDL = 0;                  /* Continue in Idle mode */
    U3MODEbits.LPBACK = 0;                 /* Disable LoopBack */
    U3MODEbits.PDSEL = 0b00;               /* 8-bit data, no parity */
    U3MODEbits.STSEL = 0;                  /* One Stop bit */
    U3MODEbits.BRGH = 0;                   /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U3BRG = PBCLK2_ / (U5_speed * 16) - 1; // 1Mbit
    IFS4bits.U3TXIF = 0;                   /* Clear interrupt flag */
    IPC39bits.U3TXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC39bits.U3TXIS = 0;                  // sub priority, 0 is Low priority
    IEC4bits.U3TXIE = 0;                   /* Enable receive interrupts */
    IFS4bits.U3RXIF = 0;                   /* Clear interrupt flag */
    IPC39bits.U3RXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC39bits.U3RXIS = 0;                  // sub priority, 0 is Low priority
    IEC4bits.U3RXIE = 1;                   /* Enable receive interrupts */
    U3STAbits.UTXEN = 1;                   /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U3STAbits.URXEN = 1;                   /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U3STAbits.UTXISEL = 0b10;
    U3MODEbits.ON = 1;
}

void uart2_init(void)
{
    U2MODEbits.USIDL = 0;                  /* Continue in Idle mode */
    U2MODEbits.LPBACK = 0;                 /* Disable LoopBack */
    U2MODEbits.PDSEL = 0b00;               /* 8-bit data, no parity */
    U2MODEbits.STSEL = 0;                  /* One Stop bit */
    U2MODEbits.BRGH = 0;                   /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U2BRG = PBCLK2_ / (U5_speed * 16) - 1; // 1Mbit
    IFS4bits.U2TXIF = 0;                   /* Clear interrupt flag */
    IPC36bits.U2TXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC36bits.U2TXIS = 0;                  // sub priority, 0 is Low priority
    IEC4bits.U2TXIE = 0;                   /* Enable receive interrupts */
    IFS4bits.U2RXIF = 0;                   /* Clear interrupt flag */
    IPC36bits.U2RXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC36bits.U2RXIS = 0;                  // sub priority, 0 is Low priority
    IEC4bits.U2RXIE = 1;                   /* Enable receive interrupts */
    U2STAbits.UTXEN = 1;                   /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U2STAbits.URXEN = 1;                   /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U2STAbits.UTXISEL = 0b10;
    U2MODEbits.ON = 1;
}

void uart1_init(void)
{
    U1MODEbits.USIDL = 0;                  /* Continue in Idle mode */
    U1MODEbits.LPBACK = 0;                 /* Disable LoopBack */
    U1MODEbits.PDSEL = 0b00;               /* 8-bit data, no parity */
    U1MODEbits.STSEL = 0;                  /* One Stop bit */
    U1MODEbits.BRGH = 0;                   /* 1 = High-Speed mode ? 4x baud clock enabled*/
    U1BRG = PBCLK2_ / (U5_speed * 16) - 1; // 1Mbit
    IFS3bits.U1TXIF = 0;                   /* Clear interrupt flag */
    IPC28bits.U1TXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC28bits.U1TXIS = 0;                  // sub priority, 0 is Low priority
    IEC3bits.U1TXIE = 0;                   /* Enable receive interrupts */
    IFS3bits.U1RXIF = 0;                   /* Clear interrupt flag */
    IPC28bits.U1RXIP = 2;                  // 2 (bei 7 geht DISI nicht) is High priority, 0 is Low priority
    IPC28bits.U1RXIS = 0;                  // sub priority, 0 is Low priority
    IEC3bits.U1RXIE = 1;                   /* Enable receive interrupts */
    U1STAbits.UTXEN = 1;                   /* 1 = UARTx transmitter is enabled. UxTX pin is controlled by UARTx (if ON = 1*/
    U1STAbits.URXEN = 1;                   /* 1 = UARTx receiver is enabled. UxRX pin is controlled by UARTx (if ON = 1) */
    U1STAbits.UTXISEL = 0b10;
    U1MODEbits.ON = 1;
}

void UART1_init(unsigned int speed)
{
    U1MODE = 0x0000; // UART1 transmitter disabled

    URXISEL1 = 0b00; // Int flag is set when a character is received
    //	UTXISEL_1=0;				//Int flag is set when a char is transfering and buff is empty
    PDSEL1 = 0b00; // 8-bit data, no parity
    STSEL1 = 0;    // 1 Stop bit

    IEC3bits.U1RXIE = 0;
    IEC3bits.U1TXIE = 0;

    switch (speed)
    {
    case 1:
    {
        U1BRG = ((Fcy) / 16) / 1200 - 1; // 1200 bod
        frame_delay = Fcy / 8 / 1200 * rx_timeout1;
        break;
    }
    case 2:
    {
        U1BRG = ((Fcy) / 16) / 2400 - 1; // 2400 bod
        frame_delay = Fcy / 8 / 2400 * rx_timeout1;
        break;
    }

    case 3:
    {
        U1BRG = ((Fcy) / 16) / 4800 - 1; // 4800 bod
        frame_delay = Fcy / 8 / 4800 * rx_timeout1;
        break;
    }

    case 4:
    {
        U1BRG = ((Fcy) / 16) / 9600 - 1; // 9600 bod
        frame_delay = Fcy / 8 / 9600 * rx_timeout1;
        break;
    }

    case 5:
    {
        U1BRG = ((Fcy) / 16) / 19200 - 1; // 19200 bod
        frame_delay = Fcy / 8 / 19200 * rx_timeout1;
        break;
    }

    case 6:
    {
        U1BRG = ((Fcy) / 16) / 38400 - 1; // 38400 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }

    case 7:
    {
        U1BRG = ((Fcy) / 16) / 57600 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 57600 * rx_timeout1;
        break;
    }

    case 8:
    {
        U1BRG = ((Fcy) / 16) / 115200 - 1; // 115200 bod
        frame_delay = Fcy / 8 / 115200 * rx_timeout1;
        break;
    }

    default:
    {
        U1BRG = ((Fcy) / 16) / 38400 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }
    }
    UARTEN1 = 1; // UART1 enabled
    UTXEN1 = 1;
    IEC3bits.U1RXIE = 0;
    ENAB_RX1;
}

void UART2_init(unsigned int speed)
{
    U2MODE = 0x0000; // UART2 transmitter disabled

    URXISEL2 = 0b00; // Int flag is set when a character is received
    //	UTXISEL_1=0;				//Int flag is set when a char is transfering and buff is empty
    PDSEL2 = 0b00; // 8-bit data, no parity
    STSEL2 = 0;    // 1 Stop bit

    IEC4bits.U2RXIE = 0;
    IEC4bits.U2TXIE = 0;

    switch (speed)
    {
    case 1:
    {
        U2BRG = ((Fcy) / 16) / 1200 - 1; // 1200 bod
        frame_delay = Fcy / 8 / 1200 * rx_timeout1;
        break;
    }
    case 2:
    {
        U2BRG = ((Fcy) / 16) / 2400 - 1; // 2400 bod
        frame_delay = Fcy / 8 / 2400 * rx_timeout1;
        break;
    }

    case 3:
    {
        U2BRG = ((Fcy) / 16) / 4800 - 1; // 4800 bod
        frame_delay = Fcy / 8 / 4800 * rx_timeout1;
        break;
    }

    case 4:
    {
        U2BRG = ((Fcy) / 16) / 9600 - 1; // 9600 bod
        frame_delay = Fcy / 8 / 9600 * rx_timeout1;
        break;
    }

    case 5:
    {
        U2BRG = ((Fcy) / 16) / 19200 - 1; // 19200 bod
        frame_delay = Fcy / 8 / 19200 * rx_timeout1;
        break;
    }

    case 6:
    {
        U2BRG = ((Fcy) / 16) / 38400 - 1; // 38400 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }

    case 7:
    {
        U2BRG = ((Fcy) / 16) / 57600 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 57600 * rx_timeout1;
        break;
    }

    case 8:
    {
        U2BRG = ((Fcy) / 16) / 115200 - 1; // 115200 bod
        frame_delay = Fcy / 8 / 115200 * rx_timeout1;
        break;
    }

    default:
    {
        U2BRG = ((Fcy) / 16) / 38400 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }
    }
    UARTEN2 = 1; // UART1 enabled
    UTXEN2 = 1;
    IEC4bits.U2RXIE = 0;
    ENAB_RX2;
}

void UART4_init(unsigned int speed)
{
    U4MODE = 0x0000; // UART2 transmitter disabled

    URXISEL4 = 0b00; // Int flag is set when a character is received
    //	UTXISEL_1=0;				//Int flag is set when a char is transfering and buff is empty
    PDSEL4 = 0b00; // 8-bit data, no parity
    STSEL4 = 0;    // 1 Stop bit

    IEC5bits.U4RXIE = 0;
    IEC5bits.U4TXIE = 0;

    switch (speed)
    {
    case 1:
    {
        U4BRG = ((Fcy) / 16) / 1200 - 1; // 1200 bod
        frame_delay = Fcy / 8 / 1200 * rx_timeout1;
        break;
    }
    case 2:
    {
        U4BRG = ((Fcy) / 16) / 2400 - 1; // 2400 bod
        frame_delay = Fcy / 8 / 2400 * rx_timeout1;
        break;
    }

    case 3:
    {
        U4BRG = ((Fcy) / 16) / 4800 - 1; // 4800 bod
        frame_delay = Fcy / 8 / 4800 * rx_timeout1;
        break;
    }

    case 4:
    {
        U4BRG = ((Fcy) / 16) / 9600 - 1; // 9600 bod
        frame_delay = Fcy / 8 / 9600 * rx_timeout1;
        break;
    }

    case 5:
    {
        U4BRG = ((Fcy) / 16) / 19200 - 1; // 19200 bod
        frame_delay = Fcy / 8 / 19200 * rx_timeout1;
        break;
    }

    case 6:
    {
        U4BRG = ((Fcy) / 16) / 38400 - 1; // 38400 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }

    case 7:
    {
        U4BRG = ((Fcy) / 16) / 57600 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 57600 * rx_timeout1;
        break;
    }

    case 8:
    {
        U4BRG = ((Fcy) / 16) / 115200 - 1; // 115200 bod
        frame_delay = Fcy / 8 / 115200 * rx_timeout1;
        break;
    }

    default:
    {
        U4BRG = ((Fcy) / 16) / 38400 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }
    }
    UARTEN4 = 1; // UART1 enabled
    UTXEN4 = 1;
    IEC5bits.U4RXIE = 0;
    ENAB_RX4;
}

void UART5_init(unsigned int speed)
{
    U5MODE = 0x0000; // UART2 transmitter disabled

    URXISEL5 = 0b00; // Int flag is set when a character is received
    //	UTXISEL_1=0;				//Int flag is set when a char is transfering and buff is empty
    PDSEL5 = 0b00; // 8-bit data, no parity
    STSEL5 = 0;    // 1 Stop bit

    IEC5bits.U5RXIE = 0;
    IEC5bits.U5TXIE = 0;

    switch (speed)
    {
    case 1:
    {
        U5BRG = ((Fcy) / 16) / 1200 - 1; // 1200 bod
        frame_delay = Fcy / 8 / 1200 * rx_timeout1;
        break;
    }
    case 2:
    {
        U5BRG = ((Fcy) / 16) / 2400 - 1; // 2400 bod
        frame_delay = Fcy / 8 / 2400 * rx_timeout1;
        break;
    }

    case 3:
    {
        U5BRG = ((Fcy) / 16) / 4800 - 1; // 4800 bod
        frame_delay = Fcy / 8 / 4800 * rx_timeout1;
        break;
    }

    case 4:
    {
        U5BRG = ((Fcy) / 16) / 9600 - 1; // 9600 bod
        frame_delay = Fcy / 8 / 9600 * rx_timeout1;
        break;
    }

    case 5:
    {
        U5BRG = ((Fcy) / 16) / 19200 - 1; // 19200 bod
        frame_delay = Fcy / 8 / 19200 * rx_timeout1;
        break;
    }

    case 6:
    {
        U5BRG = ((Fcy) / 16) / 38400 - 1; // 38400 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }

    case 7:
    {
        U5BRG = ((Fcy) / 16) / 57600 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 57600 * rx_timeout1;
        break;
    }

    case 8:
    {
        U5BRG = ((Fcy) / 16) / 115200 - 1; // 115200 bod
        frame_delay = Fcy / 8 / 115200 * rx_timeout1;
        break;
    }

    default:
    {
        U5BRG = ((Fcy) / 16) / 38400 - 1; // 57600 bod
        frame_delay = Fcy / 8 / 38400 * rx_timeout1;
        break;
    }
    }
    UARTEN5 = 1; // UART1 enabled
    UTXEN5 = 1;
    IEC5bits.U5RXIE = 0;
    ENAB_RX5;
}

void spi5_init(void)
{
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
    if (errorHigh > errorLow)
    {
        t_brg++;
    }
    SPI5BRG = t_brg;
    SPI5CONbits.ON = 1;
}

void InitializeSystem(void)
{
    // PIC32MZ CPU Speed Optimizations (Cache/Wait States/Peripheral Bus Clks)
    // On reset, I+D cache is enabled for max performace setting (write-back with write allocation)
    // No wait setting required for main data RAM

    // Prefetch-cache: Enable prefetch for PFM (any PFM instructions or data)
    PRECONbits.PREFEN = 3; // ��������������� ������� ������ ��������� �� � ���
    // Flash PM Wait States: MZ Flash runs at 2 wait states @ 200 MHz
    PRECONbits.PFMWS = 2; // ���� �� �������� ��������
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
    uart3_init();
    uart2_init();
    uart1_init();
    DMA5_init();
    DMA4_init();
    DMA3_init();
    DMA2_init();
    DMA1_init();

    /* Assign PIC32MZ shadow register sets to specific CPU IPLs */
    PRISS = 0x76543210;

    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK; //

    /* Enable Interrupt Exceptions */
    // set the CP0 status IE bit high to turn on interrupts globally
    __builtin_enable_interrupts();

    /* Enable the peripheral */
    /* ��������� �������� */
    T2CONbits.TON = 1;
    T1CONbits.TON = 1;
    T4CONbits.ON = 1; // Enable Timer 4
    T5CONbits.ON = 1; // Enable Timer 5
    T2CONbits.ON = 1;
    OC3CONbits.ON = 1; // Enable OC3//
    //    ADCCON3bits.GSWTRG = 1;
}