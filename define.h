#include <xc.h>
#include <sys/attribs.h>

#define num_zone_mops 8 // Определение макроса для числа зонных операций (MOPs), установленное на 8

#define SYS_CLK_FREQUENCY (199065600ull)         // Частота системной шины (Fsys), установленная на 200 МГц
#define CPU_CLK_FREQUENCY SYS_CLK_FREQUENCY / 2  // Частота CPU (Fcpu), половина частоты системной шины
#define PB3_CLK_FREQUENCY SYS_CLK_FREQUENCY / 27 // Частота шины периферийных устройств (Fpb3), частота системной шины деленная на 27 (2 МГц)

#define PBCLK2_ 49766400 // Определение макроса для частоты шины периферийных устройств PBCLK2_, установленной на 49 766 400 Гц

#define DMA_type 0 // Определение макроса DMA_type с значением 0, представляющим тип DMA
#define INT_type 1 // Определение макроса INT_type с значением 1, представляющим тип прерывания

#define ENAB_TX5 PORTFbits.RF2 = 1  // Включение передачи для UART5 путем установки порта RF2 в 1
#define ENAB_RX5 PORTFbits.RF2 = 0  // Включение приема для UART5 путем установки порта RF2 в 0
#define ENAB_TX4 PORTBbits.RB12 = 1 // Включение передачи для UART4 путем установки порта RB12 в 1
#define ENAB_RX4 PORTBbits.RB12 = 0 // Включение приема для UART4 путем установки порта RB12 в 0
#define ENAB_TX3 PORTBbits.RB15 = 1 // Включение передачи для UART3 путем установки порта RB15 в 1
#define ENAB_RX3 PORTBbits.RB15 = 0 // Включение приема для UART3 путем установки порта RB15 в 0
#define ENAB_TX2 PORTDbits.RD13 = 1 // Включение передачи для UART2 путем установки порта RD13 в 1
#define ENAB_RX2 PORTDbits.RD13 = 0 // Включение приема для UART2 путем установки порта RD13 в 0
#define ENAB_TX1 PORTDbits.RD1 = 1  // Включение передачи для UART1 путем установки порта RD1 в 1
#define ENAB_RX1 PORTDbits.RD1 = 0  // Включение приема для UART1 путем установки порта RD1 в 0

#define t9_del_1 timer9_bits.t_del_1 // Определение псевдонима t9_del_1 для бита t_del_1 в структуре timer9_bits

#define OUT_SIZE 0x100 // Определение размера выходного буфера как 256 байт (0x100 в шестнадцатеричной системе)
#define IN_SIZE 0x100  // Определение размера входного буфера как 256 байт (0x100 в шестнадцатеричной системе)
#define IN_SIZE1 0xF0  // Определение размера входного буфера 1 как 240 байт (0xF0 в шестнадцатеричной системе)

#define timeout1 55                               // Определение времени ожидания (тайм-аута) как 55
#define frame_delay_1 PBCLK2_ / 115200 * timeout1 // Определение задержки кадра 1 как деления PBCLK2_ на 115200, умноженное на timeout1

/////////////////		Modbus alowed areas 		//////////////////////////

#define START_READ 2000 // Начальный адрес для чтения в Modbus (MB_swap)
#define END_READ 2078   // Конечный адрес для чтения в Modbus

#define START_WRITE 2054 // Начальный адрес для записи в Modbus
#define END_WRITE 2078   // Конечный адрес для записи в Modbus

// Проверка, находится ли запрашиваемый диапазон адресов для чтения в пределах допустимого диапазона
#define READ_ ((start_reg >= START_READ) && (last_reg <= END_READ))
// Проверка, находится ли запрашиваемый диапазон адресов для записи в пределах допустимого диапазона
#define WRITE_ ((start_reg >= START_WRITE) && (last_reg <= END_WRITE))

#define START_CONF_READ 500 // Начальный адрес для чтения конфигурации - настройки параметров двигателя
#define END_CONF_READ 696   // Конечный адрес для чтения конфигурации

#define START_CONF_WRITE 500 // Начальный адрес для записи конфигурации
#define END_CONF_WRITE 696   // Конечный адрес для записи конфигурации

// Проверка, находится ли запрашиваемый диапазон адресов для чтения конфигурации в пределах допустимого диапазона
#define CONF_READ_ ((start_reg >= START_CONF_READ) && (last_reg <= END_CONF_READ))
// Проверка, находится ли запрашиваемый диапазон адресов для записи конфигурации в пределах допустимого диапазона
#define CONF_WRITE_ ((start_reg >= START_CONF_WRITE) && (last_reg <= END_CONF_WRITE))

#define START_MODBUS_READ 0 // Начальный адрес для чтения рабочей области управления двигателем и статусов
#define END_MODBUS_READ 82  // Конечный адрес для чтения рабочей области

#define START_MODBUS_WRITE 0 // Начальный адрес для записи рабочей области
#define END_MODBUS_WRITE 12  // Конечный адрес для записи рабочей области

// Проверка, находится ли запрашиваемый диапазон адресов для чтения рабочей области в пределах допустимого диапазона
#define MODBUS_READ_ ((start_reg >= START_MODBUS_READ) && (last_reg <= END_MODBUS_READ))
// Проверка, находится ли запрашиваемый диапазон адресов для записи рабочей области в пределах допустимого диапазона
#define MODBUS_WRITE_ ((start_reg >= START_MODBUS_WRITE) && (last_reg <= END_MODBUS_WRITE))

#define START_MB_DIAGN_READ 200 // Начальный адрес для чтения диагностики Modbus
#define END_MB_DIAGN_READ 312   // Конечный адрес для чтения диагностики Modbus

#define START_MB_DIAGN_WRITE 200 // Начальный адрес для записи диагностики Modbus
#define END_MB_DIAGN_WRITE 312   // Конечный адрес для записи диагностики Modbus

// Проверка, находится ли запрашиваемый диапазон адресов для чтения диагностики Modbus в пределах допустимого диапазона
#define MB_DIAGN_READ_ ((start_reg >= START_MB_DIAGN_READ) && (last_reg <= END_MB_DIAGN_READ))
// Проверка, находится ли запрашиваемый диапазон адресов для записи диагностики Modbus в пределах допустимого диапазона
#define MB_DIAGN_WRITE_ ((start_reg >= START_MB_DIAGN_WRITE) && (last_reg <= END_MB_DIAGN_WRITE))

#define RAMTRON_START 64         // Начальный адрес для работы с EEPROM
#define RAMTRON_START_CONFIG 512 // Начальный адрес для работы с конфигурацией EEPROM

#define CUR_CTRL_VAL 10 // Управляющее значение тока

#define TMR4CLK 49776400 // Частота тактирования таймера 4

#define OC_FREQ 3000 // Частота для Output Compare

#define FILT_DISCRET 500 // Дискрет фильтрации
#define CYCLE 10         // Цикл

////////////////	End Modbus alowed area 	/////////////////////

#define CONF1 PORTCbits.RC2 // Порт для конфигурации 1
#define CONF2 PORTCbits.RC3 // Порт для конфигурации 2
#define CONF3 PORTCbits.RC4 // Порт для конфигурации 3
#define CONF4 PORTGbits.RG6 // Порт для конфигурации 4
#define CONF5 PORTEbits.RE5 // Порт для конфигурации 5
#define CONF6 PORTEbits.RE6 // Порт для конфигурации 6
#define CONF7 PORTEbits.RE7 // Порт для конфигурации 7
#define CONF8 PORTCbits.RC1 // Порт для конфигурации 8

#define DI_1 PORTAbits.RA5  // Порт для цифрового входа 1
#define DI_2 PORTGbits.RG15 // Порт для цифрового входа 2
#define DI_3 PORTFbits.RF4  // Порт для цифрового входа 3

//  Определение данных Modbus
#define CYLINDERS_NUM 10 // Количество цилиндров

// для функции UARTx_init
#define URXISEL1 U1STAbits.URXISEL // Настройка выбора прерывания для приема UART1
#define URXISEL2 U2STAbits.URXISEL // Настройка выбора прерывания для приема UART2
#define URXISEL4 U4STAbits.URXISEL // Настройка выбора прерывания для приема UART4
#define URXISEL5 U5STAbits.URXISEL // Настройка выбора прерывания для приема UART5

#define PDSEL1 U1MODEbits.PDSEL // Настройка количества битов данных и бита четности для UART1
#define STSEL1 U1MODEbits.STSEL // Настройка количества стоповых битов для UART1
#define PDSEL2 U2MODEbits.PDSEL // Настройка количества битов данных и бита четности для UART2
#define STSEL2 U2MODEbits.STSEL // Настройка количества стоповых битов для UART2
#define PDSEL4 U4MODEbits.PDSEL // Настройка количества битов данных и бита четности для UART4
#define STSEL4 U4MODEbits.STSEL // Настройка количества стоповых битов для UART4
#define PDSEL5 U5MODEbits.PDSEL // Настройка количества битов данных и бита четности для UART5
#define STSEL5 U5MODEbits.STSEL // Настройка количества стоповых битов для UART5

#define UARTEN1 U1MODEbits.UARTEN // Бит включения UART1
#define UTXEN1 U1STAbits.UTXEN    // Бит разрешения передачи UART1
#define UARTEN2 U2MODEbits.UARTEN // Бит включения UART2
#define UTXEN2 U2STAbits.UTXEN    // Бит разрешения передачи UART2
#define UARTEN4 U4MODEbits.UARTEN // Бит включения UART4
#define UTXEN4 U4STAbits.UTXEN    // Бит разрешения передачи UART4
#define UARTEN5 U5MODEbits.UARTEN // Бит включения UART5
#define UTXEN5 U5STAbits.UTXEN    // Бит разрешения передачи UART5

#define FOSC 9216000                // Частота внешнего кварцевого резонатора
#define PLL_rate 4                  // Множитель PLL
#define Fcy ((FOSC * PLL_rate) / 4) // Частота работы CPU (Fcy = FOSC * PLL_rate / 4)
#define rx_timeout1 35              // Время ожидания приема
#define receive 0                   // Переменная для приема

// leds
//  #define LED3_ON     PORTEbits.RE2 = 1;
//  #define LED3_OFF     PORTEbits.RE2 = 0;
//  #define LED3_TOGGLE         PORTEbits.RE2 = LATEbits.LATE2 ^ 1;

// leds
#define LED3_OFF PORTE &= 0xfffb;
#define LED3_ON PORTE |= 0x0004;
#define LED3_TOGGLE PORTE = LATE ^ 0x0004;
