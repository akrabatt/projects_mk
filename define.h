#include <xc.h>
#include <sys/attribs.h>

#define num_zone_mops 8 // ����������� ������� ��� ����� ������ �������� (MOPs), ������������� �� 8

#define SYS_CLK_FREQUENCY (199065600ull)         // ������� ��������� ���� (Fsys), ������������� �� 200 ���
#define CPU_CLK_FREQUENCY SYS_CLK_FREQUENCY / 2  // ������� CPU (Fcpu), �������� ������� ��������� ����
#define PB3_CLK_FREQUENCY SYS_CLK_FREQUENCY / 27 // ������� ���� ������������ ��������� (Fpb3), ������� ��������� ���� �������� �� 27 (2 ���)

#define PBCLK2_ 49766400 // ����������� ������� ��� ������� ���� ������������ ��������� PBCLK2_, ������������� �� 49 766 400 ��

#define DMA_type 0 // ����������� ������� DMA_type � ��������� 0, �������������� ��� DMA
#define INT_type 1 // ����������� ������� INT_type � ��������� 1, �������������� ��� ����������

#define ENAB_TX5 PORTFbits.RF2 = 1  // ��������� �������� ��� UART5 ����� ��������� ����� RF2 � 1
#define ENAB_RX5 PORTFbits.RF2 = 0  // ��������� ������ ��� UART5 ����� ��������� ����� RF2 � 0
#define ENAB_TX4 PORTBbits.RB12 = 1 // ��������� �������� ��� UART4 ����� ��������� ����� RB12 � 1
#define ENAB_RX4 PORTBbits.RB12 = 0 // ��������� ������ ��� UART4 ����� ��������� ����� RB12 � 0
#define ENAB_TX3 PORTBbits.RB15 = 1 // ��������� �������� ��� UART3 ����� ��������� ����� RB15 � 1
#define ENAB_RX3 PORTBbits.RB15 = 0 // ��������� ������ ��� UART3 ����� ��������� ����� RB15 � 0
#define ENAB_TX2 PORTDbits.RD13 = 1 // ��������� �������� ��� UART2 ����� ��������� ����� RD13 � 1
#define ENAB_RX2 PORTDbits.RD13 = 0 // ��������� ������ ��� UART2 ����� ��������� ����� RD13 � 0
#define ENAB_TX1 PORTDbits.RD1 = 1  // ��������� �������� ��� UART1 ����� ��������� ����� RD1 � 1
#define ENAB_RX1 PORTDbits.RD1 = 0  // ��������� ������ ��� UART1 ����� ��������� ����� RD1 � 0

#define t9_del_1 timer9_bits.t_del_1 // ����������� ���������� t9_del_1 ��� ���� t_del_1 � ��������� timer9_bits

#define OUT_SIZE 0x100 // ����������� ������� ��������� ������ ��� 256 ���� (0x100 � ����������������� �������)
#define IN_SIZE 0x100  // ����������� ������� �������� ������ ��� 256 ���� (0x100 � ����������������� �������)
#define IN_SIZE1 0xF0  // ����������� ������� �������� ������ 1 ��� 240 ���� (0xF0 � ����������������� �������)

#define timeout1 55                               // ����������� ������� �������� (����-����) ��� 55
#define frame_delay_1 PBCLK2_ / 115200 * timeout1 // ����������� �������� ����� 1 ��� ������� PBCLK2_ �� 115200, ���������� �� timeout1

/////////////////		Modbus alowed areas 		//////////////////////////

#define START_READ 2000 // ��������� ����� ��� ������ � Modbus (MB_swap)
#define END_READ 2078   // �������� ����� ��� ������ � Modbus

#define START_WRITE 2054 // ��������� ����� ��� ������ � Modbus
#define END_WRITE 2078   // �������� ����� ��� ������ � Modbus

// ��������, ��������� �� ������������� �������� ������� ��� ������ � �������� ����������� ���������
#define READ_ ((start_reg >= START_READ) && (last_reg <= END_READ))
// ��������, ��������� �� ������������� �������� ������� ��� ������ � �������� ����������� ���������
#define WRITE_ ((start_reg >= START_WRITE) && (last_reg <= END_WRITE))

#define START_CONF_READ 500 // ��������� ����� ��� ������ ������������ - ��������� ���������� ���������
#define END_CONF_READ 696   // �������� ����� ��� ������ ������������

#define START_CONF_WRITE 500 // ��������� ����� ��� ������ ������������
#define END_CONF_WRITE 696   // �������� ����� ��� ������ ������������

// ��������, ��������� �� ������������� �������� ������� ��� ������ ������������ � �������� ����������� ���������
#define CONF_READ_ ((start_reg >= START_CONF_READ) && (last_reg <= END_CONF_READ))
// ��������, ��������� �� ������������� �������� ������� ��� ������ ������������ � �������� ����������� ���������
#define CONF_WRITE_ ((start_reg >= START_CONF_WRITE) && (last_reg <= END_CONF_WRITE))

#define START_MODBUS_READ 0 // ��������� ����� ��� ������ ������� ������� ���������� ���������� � ��������
#define END_MODBUS_READ 82  // �������� ����� ��� ������ ������� �������

#define START_MODBUS_WRITE 0 // ��������� ����� ��� ������ ������� �������
#define END_MODBUS_WRITE 12  // �������� ����� ��� ������ ������� �������

// ��������, ��������� �� ������������� �������� ������� ��� ������ ������� ������� � �������� ����������� ���������
#define MODBUS_READ_ ((start_reg >= START_MODBUS_READ) && (last_reg <= END_MODBUS_READ))
// ��������, ��������� �� ������������� �������� ������� ��� ������ ������� ������� � �������� ����������� ���������
#define MODBUS_WRITE_ ((start_reg >= START_MODBUS_WRITE) && (last_reg <= END_MODBUS_WRITE))

#define START_MB_DIAGN_READ 200 // ��������� ����� ��� ������ ����������� Modbus
#define END_MB_DIAGN_READ 312   // �������� ����� ��� ������ ����������� Modbus

#define START_MB_DIAGN_WRITE 200 // ��������� ����� ��� ������ ����������� Modbus
#define END_MB_DIAGN_WRITE 312   // �������� ����� ��� ������ ����������� Modbus

// ��������, ��������� �� ������������� �������� ������� ��� ������ ����������� Modbus � �������� ����������� ���������
#define MB_DIAGN_READ_ ((start_reg >= START_MB_DIAGN_READ) && (last_reg <= END_MB_DIAGN_READ))
// ��������, ��������� �� ������������� �������� ������� ��� ������ ����������� Modbus � �������� ����������� ���������
#define MB_DIAGN_WRITE_ ((start_reg >= START_MB_DIAGN_WRITE) && (last_reg <= END_MB_DIAGN_WRITE))

#define RAMTRON_START 64         // ��������� ����� ��� ������ � EEPROM
#define RAMTRON_START_CONFIG 512 // ��������� ����� ��� ������ � ������������� EEPROM

#define CUR_CTRL_VAL 10 // ����������� �������� ����

#define TMR4CLK 49776400 // ������� ������������ ������� 4

#define OC_FREQ 3000 // ������� ��� Output Compare

#define FILT_DISCRET 500 // ������� ����������
#define CYCLE 10         // ����

////////////////	End Modbus alowed area 	/////////////////////

#define CONF1 PORTCbits.RC2 // ���� ��� ������������ 1
#define CONF2 PORTCbits.RC3 // ���� ��� ������������ 2
#define CONF3 PORTCbits.RC4 // ���� ��� ������������ 3
#define CONF4 PORTGbits.RG6 // ���� ��� ������������ 4
#define CONF5 PORTEbits.RE5 // ���� ��� ������������ 5
#define CONF6 PORTEbits.RE6 // ���� ��� ������������ 6
#define CONF7 PORTEbits.RE7 // ���� ��� ������������ 7
#define CONF8 PORTCbits.RC1 // ���� ��� ������������ 8

#define DI_1 PORTAbits.RA5  // ���� ��� ��������� ����� 1
#define DI_2 PORTGbits.RG15 // ���� ��� ��������� ����� 2
#define DI_3 PORTFbits.RF4  // ���� ��� ��������� ����� 3

//  ����������� ������ Modbus
#define CYLINDERS_NUM 10 // ���������� ���������

// ��� ������� UARTx_init
#define URXISEL1 U1STAbits.URXISEL // ��������� ������ ���������� ��� ������ UART1
#define URXISEL2 U2STAbits.URXISEL // ��������� ������ ���������� ��� ������ UART2
#define URXISEL4 U4STAbits.URXISEL // ��������� ������ ���������� ��� ������ UART4
#define URXISEL5 U5STAbits.URXISEL // ��������� ������ ���������� ��� ������ UART5

#define PDSEL1 U1MODEbits.PDSEL // ��������� ���������� ����� ������ � ���� �������� ��� UART1
#define STSEL1 U1MODEbits.STSEL // ��������� ���������� �������� ����� ��� UART1
#define PDSEL2 U2MODEbits.PDSEL // ��������� ���������� ����� ������ � ���� �������� ��� UART2
#define STSEL2 U2MODEbits.STSEL // ��������� ���������� �������� ����� ��� UART2
#define PDSEL4 U4MODEbits.PDSEL // ��������� ���������� ����� ������ � ���� �������� ��� UART4
#define STSEL4 U4MODEbits.STSEL // ��������� ���������� �������� ����� ��� UART4
#define PDSEL5 U5MODEbits.PDSEL // ��������� ���������� ����� ������ � ���� �������� ��� UART5
#define STSEL5 U5MODEbits.STSEL // ��������� ���������� �������� ����� ��� UART5

#define UARTEN1 U1MODEbits.UARTEN // ��� ��������� UART1
#define UTXEN1 U1STAbits.UTXEN    // ��� ���������� �������� UART1
#define UARTEN2 U2MODEbits.UARTEN // ��� ��������� UART2
#define UTXEN2 U2STAbits.UTXEN    // ��� ���������� �������� UART2
#define UARTEN4 U4MODEbits.UARTEN // ��� ��������� UART4
#define UTXEN4 U4STAbits.UTXEN    // ��� ���������� �������� UART4
#define UARTEN5 U5MODEbits.UARTEN // ��� ��������� UART5
#define UTXEN5 U5STAbits.UTXEN    // ��� ���������� �������� UART5

#define FOSC 9216000                // ������� �������� ���������� ����������
#define PLL_rate 4                  // ��������� PLL
#define Fcy ((FOSC * PLL_rate) / 4) // ������� ������ CPU (Fcy = FOSC * PLL_rate / 4)
#define rx_timeout1 35              // ����� �������� ������
#define receive 0                   // ���������� ��� ������

// leds
//  #define LED3_ON     PORTEbits.RE2 = 1;
//  #define LED3_OFF     PORTEbits.RE2 = 0;
//  #define LED3_TOGGLE         PORTEbits.RE2 = LATEbits.LATE2 ^ 1;

// leds
#define LED3_OFF PORTE &= 0xfffb;
#define LED3_ON PORTE |= 0x0004;
#define LED3_TOGGLE PORTE = LATE ^ 0x0004;
