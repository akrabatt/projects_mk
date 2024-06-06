
#include <xc.h>
#include <sys/attribs.h> /* contains __ISR() Macros */
#include "define.h"
#include "extern.h"

extern void conf_read(void);

/**
 * @brief Преобразует виртуальный адрес в физический адрес.
 *
 * Эта функция преобразует виртуальный адрес в физический для использования в операциях DMA или других
 * низкоуровневых операций, которые требуют физического адреса.
 *
 * @param p Указатель на виртуальный адрес.
 * @return Преобразованный физический адрес.
 *
 * @note Функция работает с адресами, представленными в виде указателей типа void*.
 *       В случае если входной адрес является отрицательным, выполняется побитовая операция И с маской 0x1fffffffL.
 *       В противном случае к адресу прибавляется смещение 0x40000000L.
 *
 * @note Атрибут always_inline заставляет компилятор всегда встраивать эту функцию, что снижает накладные расходы на вызов функции.
 */
extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void *p)
{
    return (int)p < 0 ? ((int)p & 0x1fffffffL) : (unsigned int)((unsigned char *)p + 0x40000000L);
}

/******************************************************************************************************************************************************************
 *
 * START INIT SYS
 *
 */
#pragma config FMIIEN = OFF  // Ethernet RMII/MII Enable (RMII Enabled)
#pragma config FETHIO = ON   // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON  // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = OFF // Peripheral Pin Select Configuration (Allow multiple reconfigurations)
#pragma config FUSBIDIO = ON // USB USBID Selection (Controlled by the USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (3x Divider)
#pragma config FPLLRNG = RANGE_8_16_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_27        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (2x Divider)
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)

// DEVCFG1
#pragma config FNOSC = SPLL          // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128 // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF         // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = ON             // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = EC          // Primary Oscillator Configuration (External clock mode)
#pragma config OSCIOFNC = OFF        // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME        // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576     // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP        // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL       // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF          // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25  // Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31        // Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF          // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = ON            // Background Debugger Enable (Debugger is disabled)
#pragma config JTAGEN = OFF           // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx1      // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config TRCEN = ON             // Trace Enable (Trace features in the CPU are enabled)
#pragma config BOOTISA = MIPS32       // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF           // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = ALLOW_PG2     // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config SMCLR = MCLR_NORM      // Soft Master Clear Enable bit (MCLR pin generates a normal system Reset)
#pragma config SOSCGAIN = GAIN_2X     // Secondary Oscillator Gain Control bits (2x gain setting)
#pragma config SOSCBOOST = ON         // Secondary Oscillator Boost Kick Start Enable bit (Boost the kick start of the oscillator)
#pragma config POSCGAIN = GAIN_2X     // Primary Oscillator Gain Control bits (2x gain setting)
#pragma config POSCBOOST = ON         // Primary Oscillator Boost Kick Start Enable bit (Boost the kick start of the oscillator)
#pragma config EJTAGBEN = NORMAL      // EJTAG Boot (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF // Code Protect (Protection Disabled)

/**
 *
 * END INIT SYS
 *
 ******************************************************************************************************************************************************************/

/*** Ports System Service Configuration ***/

#define SYS_PORT_A_ANSEL 0x0600
#define SYS_PORT_A_TRIS 0xc6e3
#define SYS_PORT_A_LAT 0x0
#define SYS_PORT_A_ODC 0x0
#define SYS_PORT_A_CNPU 0x0
#define SYS_PORT_A_CNPD 0x0
#define SYS_PORT_A_CNEN 0x0

#define SYS_PORT_B_ANSEL 0x8000
#define SYS_PORT_B_TRIS 0xe6ff
#define SYS_PORT_B_LAT 0x8000
#define SYS_PORT_B_ODC 0x0
#define SYS_PORT_B_CNPU 0x0
#define SYS_PORT_B_CNPD 0x0
#define SYS_PORT_B_CNEN 0x0

#define SYS_PORT_C_ANSEL 0x0
#define SYS_PORT_C_TRIS 0xd01e
#define SYS_PORT_C_LAT 0x0
#define SYS_PORT_C_ODC 0x0
#define SYS_PORT_C_CNPU 0x0
#define SYS_PORT_C_CNPD 0x0
#define SYS_PORT_C_CNEN 0x0

#define SYS_PORT_D_ANSEL 0x4000
#define SYS_PORT_D_TRIS 0x4000
#define SYS_PORT_D_LAT 0x0
#define SYS_PORT_D_ODC 0x0
#define SYS_PORT_D_CNPU 0x0
#define SYS_PORT_D_CNPD 0x0
#define SYS_PORT_D_CNEN 0x0

#define SYS_PORT_E_ANSEL 0x0
#define SYS_PORT_E_TRIS 0x3e0
#define SYS_PORT_E_LAT 0x10
#define SYS_PORT_E_ODC 0x0
#define SYS_PORT_E_CNPU 0x0
#define SYS_PORT_E_CNPD 0x0
#define SYS_PORT_E_CNEN 0x0

#define SYS_PORT_F_ANSEL 0x0
#define SYS_PORT_F_TRIS 0x313b
#define SYS_PORT_F_LAT 0x0
#define SYS_PORT_F_ODC 0x0
#define SYS_PORT_F_CNPU 0x0
#define SYS_PORT_F_CNPD 0x0
#define SYS_PORT_F_CNEN 0x0

#define SYS_PORT_G_ANSEL 0x0
#define SYS_PORT_G_TRIS 0x8343
#define SYS_PORT_G_LAT 0x0
#define SYS_PORT_G_ODC 0x0
#define SYS_PORT_G_CNPU 0x0
#define SYS_PORT_G_CNPD 0x0
#define SYS_PORT_G_CNEN 0x0

/**
 * @brief Инициализация портов микроконтроллера и настройка периферийных модулей.
 *
 * Эта функция выполняет инициализацию портов ввода-вывода микроконтроллера и конфигурирует
 * периферийные модули с использованием системы PPS (Peripheral Pin Select).
 *
 * @details
 * В этой функции устанавливаются направления портов (TRIS), конфигурация аналоговых входов (ANSEL)
 * и начальные значения выходов (LAT). Также выполняется настройка PPS для назначения периферийных
 * модулей к определенным выводам.
 */
void port_init(void)
{
    // Настройка порта A
    TRISA = SYS_PORT_A_TRIS;   // Установка направлений портов для A
    ANSELA = SYS_PORT_A_ANSEL; // Настройка аналоговых функций для порта A
    // Настройка порта B
    TRISB = SYS_PORT_B_TRIS;   // Установка направлений портов для B
    ANSELB = SYS_PORT_B_ANSEL; // Настройка аналоговых функций для порта B
    // Настройка порта C
    TRISC = SYS_PORT_C_TRIS;   // Установка направлений портов для C
    ANSELC = SYS_PORT_C_ANSEL; // Настройка аналоговых функций для порта C
    // Настройка порта D
    TRISD = SYS_PORT_D_TRIS;   // Установка направлений портов для D
    ANSELD = SYS_PORT_D_ANSEL; // Настройка аналоговых функций для порта D
    LATD = SYS_PORT_D_LAT;     // Установка начальных значений на порте D
    // Настройка порта E
    TRISE = SYS_PORT_E_TRIS;   // Установка направлений портов для E
    ANSELE = SYS_PORT_E_ANSEL; // Настройка аналоговых функций для порта E
    // Настройка порта F
    TRISF = SYS_PORT_F_TRIS;   // Установка направлений портов для F
    ANSELF = SYS_PORT_F_ANSEL; // Настройка аналоговых функций для порта F
    // Настройка порта G
    TRISG = SYS_PORT_G_TRIS;   // Установка направлений портов для G
    ANSELG = SYS_PORT_G_ANSEL; // Настройка аналоговых функций для порта G
    // Конфигурация PPS (Peripheral Pin Select)
    U4RXRbits.U4RXR = 0b0010; // U4RX подключен к RPB14
    U5RXRbits.U5RXR = 0b1101; // U5RX подключен к RPA14

    IC3Rbits.IC3R = 0b0010; // IC3 подключен к RPF4
    IC4Rbits.IC4R = 0b0010; // IC4 подключен к RPF5

    IC7Rbits.IC7R = 0b0100; // IC7 подключен к RPF1
    IC8Rbits.IC8R = 0b0100; // IC8 подключен к RPF0

    SDI5Rbits.SDI5R = 0b0101; // SDI5 подключен к RPB9

    RPC14Rbits.RPC14R = 0b1011; // OC3 подключен к RPC14
    RPA15Rbits.RPA15R = 0b0011; // U5TX подключен к RPA15
    RPF12Rbits.RPF12R = 0b0010; // U4TX подключен к RPF12
    RPB10Rbits.RPB10R = 0b1001; // SDO5 подключен к RPB10
}

/**
 * @brief Инициализация таймера T1.
 *
 * Эта функция инициализирует таймер T1 с заданной задержкой, состоянием прерываний и состоянием включения.
 *
 * @param delay Значение задержки, которое будет загружено в регистр периодичности PR1.
 *              Определяет, через какое количество тактов таймер T1 вызовет прерывание.
 * @param IE    Флаг разрешения прерывания таймера T1 (1 - прерывания разрешены, 0 - прерывания запрещены).
 * @param ON    Флаг включения таймера T1 (1 - таймер включен, 0 - таймер выключен).
 *
 * @note Значение задержки определяется в зависимости от частоты тактового сигнала и желаемого интервала времени.
 *       При настройке частоты прерывания необходимо учитывать значение предделителя таймера.
 */
void tmr1_init(unsigned short delay, unsigned short IE, unsigned short ON)
{
    T1CONbits.TON = 0;    // Отключение таймера T1 перед началом настройки
    TMR1 = 0x0000;        // Сброс счетчика таймера T1 в 0
    PR1 = delay;          // Установка значения предельного регистра для таймера T1
    IEC0bits.T1IE = IE;   // Разрешение или запрет прерываний таймера T1
    IPC1bits.T1IP = 0b10; // Установка приоритета прерываний таймера T1 на уровень 2
    T1CONbits.TCKPS = 0;  // Установка предделителя таймера T1 на значение 1:1
    T1CONbits.TON = ON;   // Включение или выключение таймера T1 в зависимости от параметра ON
}

// инициализация Т2
void tmr2_init(unsigned short delay, unsigned short IE, unsigned short ON)
{
    T2CONbits.TON = 0;
    TMR2 = 0x0000;
    PR2 = delay; //
    IEC0bits.T2IE = IE;
    IPC3bits.T3IP = 0b10;
    T3CONbits.TCKPS = 0b00;
    T3CONbits.TON = ON;
}

// Т3
void tmr3_init(unsigned short delay, unsigned short IE, unsigned short ON)
{
    T3CONbits.TON = 0;
    TMR3 = 0x0000;
    PR3 = delay; //
    IEC0bits.T3IE = IE;
    IPC3bits.T3IP = 0b10;
    T3CONbits.TCKPS = 0b00;
    T3CONbits.TON = ON;
}

// Т4
void tmr4_init(unsigned short delay, unsigned short IE, unsigned short ON)
{
    T4CONbits.TON = 0;
    TMR4 = 0x0000;
    PR4 = delay; //
    IEC0bits.T4IE = IE;
    IPC4bits.T4IP = 0b10;
    T4CONbits.TCKPS = 0b00;
    T4CONbits.TON = ON;
}

// Т5
void tmr5_init(unsigned short delay, unsigned short IE, unsigned short ON)
{
    T5CONbits.TON = 0;
    TMR5 = 0x0000;
    PR5 = delay; //
    IEC0bits.T5IE = IE;
    IPC6bits.T5IP = 0b10;
    T5CONbits.TCKPS = 0b00;
    T5CONbits.TON = ON;
}

// Т6
void tmr6_init(void)
{
    T6CONbits.TON = 0;
    TMR6 = 0x0000;
    PR6 = 1500; //
    IEC0bits.T6IE = 1;
    IPC7bits.T6IP = 0b10;
    T6CONbits.TCKPS = 7;
    T6CONbits.TON = 0;
}

// Т7
void tmr7_init(void)
{
    T7CONbits.TON = 0;
    TMR7 = 0x0000;
    PR7 = 1500; //
    IEC1bits.T7IE = 1;
    IPC8bits.T7IP = 0b10;
    T7CONbits.TCKPS = 7;
    T7CONbits.TON = 0;
}

// Т8
void tmr8_init(void)
{
    T8CONbits.TON = 0;
    TMR8 = 0x0000;
    PR8 = 1500; //
    IEC1bits.T8IE = 1;
    IPC9bits.T8IP = 0b10;
    T8CONbits.TCKPS = 7;
    T8CONbits.TON = 0;
}

// Т9
void tmr9_init(unsigned short delay, unsigned short IE, unsigned short ON)
{
    T9CONbits.TON = 0;
    TMR9 = 0x0000;
    PR9 = delay; //
    IEC1bits.T9IE = IE;
    IPC10bits.T9IP = 0b10;
    T9CONbits.TCKPS = 0b00;
    T9CONbits.TON = ON;
}

/**
 * @brief Инициализация UART1.
 *
 * Эта функция инициализирует UART1 с заданной скоростью передачи данных.
 * Настройки включают режим работы, формат данных, управление прерываниями и скорость передачи.
 *
 * @param speed Скорость передачи данных в бодах (бит/с).
 */
void uart1_init(unsigned long speed)
{
    U1MODEbits.USIDL = 0;               // Продолжать работу в режиме Idle
    U1MODEbits.LPBACK = 0;              // Отключить LoopBack режим
    U1MODEbits.PDSEL = 0b00;            // 8-битные данные, без контроля четности
    U1MODEbits.STSEL = 0;               // Один стоповый бит
    U1MODEbits.BRGH = 0;                // Нормальный режим скорости, 16x baud clock
    U1BRG = PBCLK2_ / (speed * 16) - 1; // Установка значения регистра скорости передачи для заданной скорости
    IFS3bits.U1TXIF = 0;                // Сбросить флаг прерывания передачи
    IPC28bits.U1TXIP = 2;               // Установить приоритет прерывания передачи на высокий уровень (2)
    IPC28bits.U1TXIS = 0;               // Установить субприоритет прерывания передачи на низкий уровень (0)
    IEC3bits.U1TXIE = 0;                // Отключить прерывания передачи
    IFS3bits.U1RXIF = 0;                // Сбросить флаг прерывания приема
    IPC28bits.U1RXIP = 2;               // Установить приоритет прерывания приема на высокий уровень (2)
    IPC28bits.U1RXIS = 0;               // Установить субприоритет прерывания приема на низкий уровень (0)
    IEC3bits.U1RXIE = 1;                // Включить прерывания приема
    U1STAbits.UTXEN = 1;                // Включить передатчик UART1
    U1STAbits.URXEN = 1;                // Включить приемник UART1
    U1STAbits.UTXISEL = 0b10;           // Прерывание по окончанию передачи
    U1MODEbits.ON = 1;                  // Включить UART1
}

void uart2_init(unsigned long speed)
{
    U2MODEbits.USIDL = 0;
    U2MODEbits.LPBACK = 0;
    U2MODEbits.PDSEL = 0b00;
    U2MODEbits.STSEL = 0;
    U2MODEbits.BRGH = 0;
    U2BRG = PBCLK2_ / (speed * 16) - 1;
    IFS4bits.U2TXIF = 0;
    IPC36bits.U2TXIP = 2;
    IPC36bits.U2TXIS = 0;
    IEC4bits.U2TXIE = 0;
    IFS4bits.U2RXIF = 0;
    IPC36bits.U2RXIP = 2;
    IPC36bits.U2RXIS = 0;
    IEC4bits.U2RXIE = 1;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXISEL = 0b10;
    U2MODEbits.ON = 1;
}

void uart3_init(unsigned long speed)
{
    U3MODEbits.USIDL = 0;
    U3MODEbits.LPBACK = 0;
    U3MODEbits.PDSEL = 0b00;
    U3MODEbits.STSEL = 0;
    U3MODEbits.BRGH = 0;
    U3BRG = PBCLK2_ / (speed * 16) - 1;
    IFS4bits.U3TXIF = 0;
    IPC39bits.U3TXIP = 2;
    IPC39bits.U3TXIS = 0;
    IEC4bits.U3TXIE = 0;
    IFS4bits.U3RXIF = 0;
    IPC39bits.U3RXIP = 2;
    IPC39bits.U3RXIS = 0;
    IEC4bits.U3RXIE = 1;
    U3STAbits.UTXEN = 1;
    U3STAbits.URXEN = 1;
    U3STAbits.UTXISEL = 0b10;
    U3MODEbits.ON = 1;
}

void uart4_init(unsigned long speed)
{
    U4MODEbits.USIDL = 0;
    U4MODEbits.LPBACK = 0;
    U4MODEbits.PDSEL = 0b00;
    U4MODEbits.STSEL = 0;
    U4MODEbits.BRGH = 0;
    U4BRG = PBCLK2_ / (speed * 16) - 1;
    IFS5bits.U4TXIF = 0;
    IPC43bits.U4TXIP = 2;
    IPC43bits.U4TXIS = 0;
    IEC5bits.U4TXIE = 0;
    IFS5bits.U4RXIF = 0;
    IPC42bits.U4RXIP = 2;
    IPC42bits.U4RXIS = 0;
    IEC5bits.U4RXIE = 1;
    U4STAbits.UTXEN = 1;
    U4STAbits.URXEN = 1;
    U4STAbits.UTXISEL = 0b10;
    U4MODEbits.ON = 1;
}

void uart5_init(unsigned long speed)
{
    U5MODEbits.USIDL = 0;
    U5MODEbits.LPBACK = 0;
    U5MODEbits.PDSEL = 0b00;
    U5MODEbits.STSEL = 0;
    U5MODEbits.BRGH = 0;
    U5BRG = PBCLK2_ / (speed * 16) - 1;
    IFS5bits.U5TXIF = 0;
    IPC45bits.U5TXIP = 2;
    IPC45bits.U5TXIS = 0;
    IEC5bits.U5TXIE = 0;
    IFS5bits.U5RXIF = 0;
    IPC45bits.U5RXIP = 2;
    IPC45bits.U5RXIS = 0;
    IEC5bits.U5RXIE = 1;
    U5STAbits.UTXEN = 1;
    U5STAbits.URXEN = 1;
    U5STAbits.UTXISEL = 0b10;
    U5MODEbits.ON = 1;
}

/**
 * @brief Инициализация SPI5.
 *
 * Эта функция инициализирует SPI5 с заданной скоростью передачи данных.
 * Настройки включают режим работы, управление буфером, режимы тактирования и другие параметры.
 */
void spi5_init(void)
{
    unsigned int t_brg;     // Переменная для хранения значения регистра делителя скорости
    unsigned int baudHigh;  // Переменная для хранения значения скорости передачи данных (высокое значение)
    unsigned int baudLow;   // Переменная для хранения значения скорости передачи данных (низкое значение)
    unsigned int errorHigh; // Переменная для хранения значения ошибки скорости передачи (высокое значение)
    unsigned int errorLow;  // Переменная для хранения значения ошибки скорости передачи (низкое значение)
    unsigned int baudRate;  // Переменная для хранения значения требуемой скорости передачи данных

    baudRate = 8294400; // Установка значения скорости передачи данных

    SPI5CONbits.ON = 0;     // Отключение SPI5 перед началом настройки
    SPI5CONbits.MSTEN = 1;  // Установка режима Master
    SPI5CONbits.MSSEN = 0;  // Отключение режима автоматического выбора slave
    SPI5CONbits.SIDL = 0;   // Продолжение работы в Idle режиме
    SPI5CONbits.CKP = 0;    // Установка полярности тактового сигнала: активный высокий
    SPI5CONbits.CKE = 1;    // Установка выборки данных по переднему фронту тактового сигнала
    SPI5CONbits.SMP = 0;    // Установка выборки данных в середине тактового цикла
    SPI5CONbits.MODE16 = 0; // Отключение 16-битного режима
    SPI5CONbits.MODE32 = 0; // Отключение 32-битного режима
    SPI5CONbits.FRMEN = 0;  // Отключение фреймового режима
    SPI5CON2bits.AUDEN = 0; // Отключение аудио режима
    SPI5CONbits.ENHBUF = 1; // Включение расширенного буфера

    // Рассчет значения регистра делителя скорости
    t_brg = (((PBCLK2_ / baudRate) / 2) - 1);
    baudHigh = PBCLK2_ / (2 * (t_brg + 1)); // Высокое значение скорости передачи данных
    baudLow = PBCLK2_ / (2 * (t_brg + 2));  // Низкое значение скорости передачи данных
    errorHigh = baudHigh - baudRate;        // Рассчет ошибки для высокого значения
    errorLow = baudRate - baudLow;          // Рассчет ошибки для низкого значения

    // Корректировка значения делителя скорости в зависимости от ошибок
    if (errorHigh > errorLow)
    {
        t_brg++;
    }

    SPI5BRG = t_brg;    // Установка значения регистра делителя скорости
    SPI5CONbits.ON = 1; // Включение SPI5
}

void InitializeSystem(void)
{
    // PIC32MZ CPU Speed Optimizations (Cache/Wait States/Peripheral Bus Clks)
    // On reset, I+D cache is enabled for max performace setting (write-back with write allocation)
    // No wait setting required for main data RAM

    // Prefetch-cache: Enable prefetch for PFM (any PFM instructions or data)
    PRECONbits.PREFEN = 3;
    // Flash PM Wait States: MZ Flash runs at 2 wait states @ 200 MHz
    PRECONbits.PFMWS = 2;
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
    //    DRV_ADC_Initialize_F();
    //    ADC_init_scan ();
    conf_read();
    tmr1_init(100, 0, 0);
    tmr2_init(100, 0, 0);
    tmr3_init(100, 0, 0);
    tmr4_init(100, 0, 0);
    tmr5_init(100, 0, 0);
    tmr6_init();
    tmr7_init();
    tmr9_init(49765, 1, 1);

    uart5_init(115200);
    uart4_init(115200);
    DMA1_init();
    DMA2_init();
    DMA3_init();
    DMA4_init();
    DMA5_init();
    /* Assign PIC32MZ shadow register sets to specific CPU IPLs */
    PRISS = 0x76543210;

    /* Set Interrupt Controller for multi-vector mode */
    INTCONSET = _INTCON_MVEC_MASK;

    /* Enable Interrupt Exceptions */
    // set the CP0 status IE bit high to turn on interrupts globally
    __builtin_enable_interrupts();

    /* Enable the peripheral */
    T2CONbits.TON = 1;
    T4CONbits.ON = 1;  // Enable Timer 4
    T5CONbits.ON = 1;  // Enable Timer 5
    OC3CONbits.ON = 1; // Enable OC3//
    //    ADCCON3bits.GSWTRG = 1;
}

/******************************************************************************
 * Function:        void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine takes care of all of the system
 *                  initialization that is required.
 *
 * Note:
 *
 *****************************************************************************/

/* *****************************************************************************
 End of File
 */
