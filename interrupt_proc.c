#include "extern.h"

extern void uart1_init(void); // �������� �������
extern void uart4_init(void); // �������� �������

/**
 * @brief �������������� ������������ ������ � ���������� �����.
 *
 * ������� ��������� �������������� ������������ ������ � ���������� �����.
 * ���� ���������� ����� ������ 0, �� ����������� ����� 0x1fffffffL.
 * � ��������� ������, � ������ ������������ �������� 0x40000000L.
 *
 * @param p ��������� �� ����������� �����, ������� ���������� �������������.
 * @return unsigned int ���������� �����, ���������� � ���������� ��������������.
 */
extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void *p)
{
    return (int)p < 0 ? ((int)p & 0x1fffffffL) : (unsigned int)((unsigned char *)p + 0x40000000L);
}
/* ��� ���� ������� _VirtToPhys. ���� ����������� ����� p ����������� (������� �� ������� ��������� ���������),
�� ����������� ��������� � � ������ 0x1fffffffL, ����� ���������� �� ������� �����. � ��������� ������ � ������������
������ ����������� �������� 0x40000000L, ������� ������������� �������� ������ ���������� ������ � �������� ������������
MIPS, ����� �������� ���������� �����. ������� ���������� ���������� ����� � ���� unsigned int. */

/**
 * @brief ���������� ���������� �� ������� 1.
 *
 * ������� ��������� ��������� ���������� �� ������� 1. ��������� ������ 1 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T1Interrupt_(struct tag_usart *usart)
{
    T1CONbits.TON = 0;                   // ��������� ������ 1
    IFS0bits.T1IF = 0;                   // ���������� ���� ���������� �� ������� 1
    if (usart->mb_status.modb_receiving) // ���������, ����������� �� ����� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ������������� ���� ��������� ������ ������ Modbus
        usart->mb_status.modb_receiving = 0; // ���������� ���� ������ ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 2.
 *
 * ������� ��������� ��������� ���������� �� ������� 2. ��������� ������ 2 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T2Interrupt_(struct tag_usart *usart)
{
    T2CONbits.TON = 0;                   // ��������� ������ 2
    IFS0bits.T2IF = 0;                   // ���������� ���� ���������� �� ������� 2
    if (usart->mb_status.modb_receiving) // ���������, ����������� �� ����� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ������������� ���� ��������� ������ ������ Modbus
        usart->mb_status.modb_receiving = 0; // ���������� ���� ������ ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 3.
 *
 * ������� ��������� ��������� ���������� �� ������� 3. ��������� ������ 3 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T3Interrupt_(struct tag_usart *usart)
{
    T3CONbits.TON = 0;                   // ��������� ������ 3
    IFS0bits.T3IF = 0;                   // ���������� ���� ���������� �� ������� 3
    if (usart->mb_status.modb_receiving) // ���������, ����������� �� ����� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ������������� ���� ��������� ������ ������ Modbus
        usart->mb_status.modb_receiving = 0; // ���������� ���� ������ ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 4.
 *
 * ������� ��������� ��������� ���������� �� ������� 4. ��������� ������ 4 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T4Interrupt_(struct tag_usart *usart)
{
    T4CONbits.TON = 0;                   // ��������� ������ 4
    IFS0bits.T4IF = 0;                   // ���������� ���� ���������� �� ������� 4
    if (usart->mb_status.modb_receiving) // ���������, ����������� �� ����� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ������������� ���� ��������� ������ ������ Modbus
        usart->mb_status.modb_receiving = 0; // ���������� ���� ������ ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 5.
 *
 * ������� ��������� ��������� ���������� �� ������� 5. ��������� ������ 5 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T5Interrupt_(struct tag_usart *usart)
{
    T5CONbits.TON = 0;                   // ��������� ������ 5
    IFS0bits.T5IF = 0;                   // ���������� ���� ���������� �� ������� 5
    if (usart->mb_status.modb_receiving) // ���������, ����������� �� ����� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ������������� ���� ��������� ������ ������ Modbus
        usart->mb_status.modb_receiving = 0; // ���������� ���� ������ ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 6.
 *
 * ������� ��������� ��������� ���������� �� ������� 6. ��������� ������ 6 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T6Interrupt_(struct tag_usart *usart)
{
    T6CONbits.TON = 0;                   // ��������� ������ 6
    IFS0bits.T6IF = 0;                   // ���������� ���� ���������� �� ������� 6
    if (usart->mb_status.modb_receiving) // ���������, ����������� �� ����� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ������������� ���� ��������� ������ ������ Modbus
        usart->mb_status.modb_receiving = 0; // ���������� ���� ������ ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 7.
 *
 * ������� ��������� ��������� ���������� �� ������� 7. ��������� ������ 7 � ���������� ����
 * ����������. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� �� ����������
 * ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 � ����������
 * ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T7Interrupt_(struct tag_usart *usart)
{
    T7CONbits.TON = 0;                   // ���������� ������� T7
    IFS1bits.T7IF = 0;                   // ����� ����� ���������� �� ������� T7
    if (usart->mb_status.modb_receiving) // ���� ��������������� ���� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ��������� ����� ���������� ������ Modbus
        usart->mb_status.modb_receiving = 0; // ����� ����� ������ Modbus
    }
}

/**
 * @brief ���������� ���������� �� ������� 9.
 *
 * ��� ������� ��������� ��������� ���������� �� ������� 9. ��� ��������� ������ 9 � ���������� ����
 * ���������� �� ������� 9. ���� � ��������� usart ���������� ���� modb_receiving, ��� ��������� ��
 * ���������� ������ ������ Modbus, ������� ������������� ���� ��������� ������ ������ modb_received � 1 �
 * ���������� ���� modb_receiving.
 *
 * @param usart ��������� �� ��������� tag_usart, ���������� ���������� � USART.
 *
 * @return void
 */
void T9Interrupt_(struct tag_usart *usart)
{
    T9CONbits.TON = 0;                   // ���������� ������� T9
    IFS1bits.T9IF = 0;                   // ����� ����� ���������� �� ������� T9
    if (usart->mb_status.modb_receiving) // ���� ��������������� ���� ������ Modbus
    {
        usart->mb_status.modb_received = 1;  // ��������� ����� ���������� ������ Modbus
        usart->mb_status.modb_receiving = 0; // ����� ����� ������ Modbus
    }
}

/**
 * @brief ������� ��� ���������� ������� DMA ��� �������� ������ ����� USART.
 *
 * ��� ������� ��������� ������� DMA ��� �������� ������ ����� USART. ��� ����������� ��������� ������ DMA � ������������
 * � ������������ USART, ����� ��� �������� ������, ���������� ������, ������ ������ � �. �.
 *
 * @param usart ��������� �� ��������� usart, ����� ������� ����� �������������� �������� ������.
 * @param cnt ���������� ������ ��� ��������.
 * @param on ����, �����������, ������� �� �������� ����� DMA (1 - ��������, 0 - ���������).
 * @param force ����, �����������, ������� �� ������������� ��������� �������� DMA (1 - ��, 0 - ���).
 * @return void
 */
void DMA_uni(struct tag_usart *usart, unsigned short cnt, unsigned short on, unsigned short force)
{
    if (usart == &usart5) // ���� usart �������� usart5
    {
        DCH5SSA = _VirtToPhys(&buf_tx5);               // ������������� ���������� ����� ��������� ��� ������ DMA 5
        DCH5DSA = _VirtToPhys((const void *)&U5TXREG); // ������������� ���������� ����� ���������� (������� �������� UART5)
        DCH5SSIZ = cnt;                                // ������������� ������ ��������� (���������� ������ ��� ��������)
        DCH5DSIZ = 1;                                  // ������������� ������ ���������� (1 ����)
        DCH5CSIZ = 1;                                  // ������������� ������ ������ (1 ���� �� ������ ������ �������� UART)
        DCH5CONbits.CHEN = on;                         // �������� ��� ��������� ����� DMA
        DCH5ECONbits.CFORCE = force;                   // ������������� ��������� �������� DMA, ���� ����������
    }
    if (usart == &usart4) // ���� usart �������� usart4
    {
        DCH4SSA = _VirtToPhys(&buf_tx4);               // ������������� ���������� ����� ��������� ��� ������ DMA 4
        DCH4DSA = _VirtToPhys((const void *)&U4TXREG); // ������������� ���������� ����� ���������� (������� �������� UART4)
        DCH4SSIZ = cnt;                                // ������������� ������ ��������� (���������� ������ ��� ��������)
        DCH4DSIZ = 1;                                  // ������������� ������ ���������� (1 ����)
        DCH4CSIZ = 1;                                  // ������������� ������ ������ (1 ���� �� ������ ������ �������� UART)
        DCH4CONbits.CHEN = on;                         // �������� ��� ��������� ����� DMA
        DCH4ECONbits.CFORCE = force;                   // ������������� ��������� �������� DMA, ���� ����������
    }
    if (usart == &usart3) // ���� usart �������� usart3
    {
        DCH3SSA = _VirtToPhys(&buf_tx3);               // ������������� ���������� ����� ��������� ��� ������ DMA 3
        DCH3DSA = _VirtToPhys((const void *)&U3TXREG); // ������������� ���������� ����� ���������� (������� �������� UART3)
        DCH3SSIZ = cnt;                                // ������������� ������ ��������� (���������� ������ ��� ��������)
        DCH3DSIZ = 1;                                  // ������������� ������ ���������� (1 ����)
        DCH3CSIZ = 1;                                  // ������������� ������ ������ (1 ���� �� ������ ������ �������� UART)
        DCH3CONbits.CHEN = on;                         // �������� ��� ��������� ����� DMA
        DCH3ECONbits.CFORCE = force;                   // ������������� ��������� �������� DMA, ���� ����������
    }
    if (usart == &usart2) // ���� usart �������� usart2
    {
        DCH2SSA = _VirtToPhys(&buf_tx2);               // ������������� ���������� ����� ��������� ��� ������ DMA 2
        DCH2DSA = _VirtToPhys((const void *)&U2TXREG); // ������������� ���������� ����� ���������� (������� �������� UART2)
        DCH2SSIZ = cnt;                                // ������������� ������ ��������� (���������� ������ ��� ��������)
        DCH2DSIZ = 1;                                  // ������������� ������ ���������� (1 ����)
        DCH2CSIZ = 1;                                  // ������������� ������ ������ (1 ���� �� ������ ������ �������� UART)
        DCH2CONbits.CHEN = on;                         // �������� ��� ��������� ����� DMA
        DCH2ECONbits.CFORCE = force;                   // ������������� ��������� �������� DMA, ���� ����������
    }
    if (usart == &usart1) // ���� usart �������� usart1
    {
        DCH1SSA = _VirtToPhys(&buf_tx1);               // ������������� ���������� ����� ��������� ��� ������ DMA 1
        DCH1DSA = _VirtToPhys((const void *)&U1TXREG); // ������������� ���������� ����� ���������� (������� �������� UART1)
        DCH1SSIZ = cnt;                                // ������������� ������ ��������� (���������� ������ ��� ��������)
        DCH1DSIZ = 1;                                  // ������������� ������ ���������� (1 ����)
        DCH1CSIZ = 1;                                  // ������������� ������ ������ (1 ���� �� ������ ������ �������� UART)
        DCH1CONbits.CHEN = on;                         // �������� ��� ��������� ����� DMA
        DCH1ECONbits.CFORCE = force;                   // ������������� ��������� �������� DMA, ���� ����������
    }
}
/* ���������� �������:
- ������������� DMA: ������� ������������� ���������� ������ ��������� � ���������� ��� �������� ������.
- ��������� ���������� ��������: ���������� ������ ������, ������� ����� ��������, � ��������� �������� �� ������� �����.
- ���������� ����������/����������� DMA ������: �������� ��� ��������� ����� DMA.
- �������������� ������ ��������: ��� ������������� ������������� ��������� �������� ������.
����
��� ������� DMA_uni ������������ ��� ������������� � ���������� �������� DMA ��� �������� ������ ����� ���������
UART ���������� �� ���������������� PIC32MZ. ��� ����������� ��������� DMA ��������, ���������/���������� ������ �
�������������� ������ ��������, ���� ��� ����������.*/

/* ������� DMAx_init �������������� � ����������� ����� DMA x ��� ������ � UARTx �� ����������������  PIC32MZ.  */
/**
 * @brief ������������� ������ DMA ��� �������� ������ ����� USART5.
 *
 * ��� ������� �������������� ����� DMA ��� �������� ������ ����� USART5. ��� ����������� ��������� ������ DMA, ����� ��� �������� ������,
 * ���������� ������, ������� ������ � �. �.
 *
 * @return void
 */
void DMA5_init(void)
{
    DMACONSET = 0x00008000;                        // �������� ���������� DMA
    DCH5CON = 0x2;                                 // ��������� ����� 5, ���������� ��������� 2
    DCH5ECONbits.CHSIRQ = _UART5_TX_VECTOR;        // ���������� ������ ���������� ��� �������� UART5
    DCH5ECONbits.SIRQEN = 1;                       // ��������� ���������� �� ������������� ����������
    DCH5SSA = _VirtToPhys(&buf_tx5);               // ���������� ���������� ����� ��������� ������ ��� ������ DMA 5
    DCH5DSA = _VirtToPhys((const void *)&U5TXREG); // ���������� ���������� ����� �������� �������� UART5
    DCH5SSIZ = 38;                                 // ���������� ������ ��������� ������ (�������� 200 ����)
    DCH5DSIZ = 1;                                  // ���������� ������ ���������� (1 ����)
    DCH5CSIZ = 1;                                  // ���������� ������ ������ (1 ���� �� ������ ������ �������� UART)
    DCH5INTCLR = 0x00ff00ff;                       // �������� ������� � ��������� ���������� ��� ������ DMA 5
    DCH5CONbits.CHEN = 0;                          // ��������� ����� DMA 5
}

void DMA4_init(void)
{
    DMACONSET = 0x00008000;                        // �������� ���������� DMA
    DCH4CON = 0x2;                                 // ��������� ����� 4, ���������� ��������� 2
    DCH4ECONbits.CHSIRQ = _UART4_TX_VECTOR;        // ���������� ������ ���������� ��� �������� UART4
    DCH4ECONbits.SIRQEN = 1;                       // ��������� ���������� �� ������������� ����������
    DCH4SSA = _VirtToPhys(&buf_tx4);               // ���������� ���������� ����� ��������� ������ ��� ������ DMA 4
    DCH4DSA = _VirtToPhys((const void *)&U4TXREG); // ���������� ���������� ����� �������� �������� UART4
    DCH4SSIZ = 38;                                 // ���������� ������ ��������� ������ (�������� 200 ����)
    DCH4DSIZ = 1;                                  // ���������� ������ ���������� (1 ����)
    DCH4CSIZ = 1;                                  // ���������� ������ ������ (1 ���� �� ������ ������ �������� UART)
    DCH4INTCLR = 0x00ff00ff;                       // �������� ������� � ��������� ���������� ��� ������ DMA 4
    // DCH4INTbits.CHSDIF = 0;       // �� ������������, ��������� ��� �������
    DCH4CONbits.CHEN = 0; // ��������� ����� DMA 4
}

void DMA3_init(void)
{
    DMACONSET = 0x00008000;                        // ��������� ����������� DMA
    DCH3CON = 0x2;                                 // ���������� ������ 3, ��������� ���������� 2
    DCH3ECONbits.CHSIRQ = _UART3_TX_VECTOR;        // ��������� ������� ���������� ��� �������� UART3
    DCH3ECONbits.SIRQEN = 1;                       // ���������� ���������� �� ������������� ����������
    DCH3SSA = _VirtToPhys(&buf_tx3);               // ��������� ����������� ������ ��������� ������ ��� ������ DMA 3
    DCH3DSA = _VirtToPhys((const void *)&U3TXREG); // ��������� ����������� ������ �������� �������� UART3
    DCH3SSIZ = 38;                                 // ��������� ������� ��������� ������ (�������� 200 ����)
    DCH3DSIZ = 1;                                  // ��������� ������� ���������� (1 ����)
    DCH3CSIZ = 1;                                  // ��������� ������� ������ (1 ���� �� ������ ������ �������� UART)
    DCH3INTCLR = 0x00ff00ff;                       // ������� ������� � ���������� ���������� ��� ������ DMA 3
    // DCH4INTbits.CHSDIF = 0;       // �� ������������, ��������� ��� �������
    DCH3CONbits.CHEN = 0; // ���������� ������ DMA 3
}

void DMA2_init(void)
{
    DMACONSET = 0x00008000;                        // ��������� ����������� DMA
    DCH2CON = 0x2;                                 // ���������� ������ 2, ��������� ���������� 2
    DCH2ECONbits.CHSIRQ = _UART2_TX_VECTOR;        // ��������� ������� ���������� ��� �������� UART2
    DCH2ECONbits.SIRQEN = 1;                       // ���������� ���������� �� ������������� ����������
    DCH2SSA = _VirtToPhys(&buf_tx2);               // ��������� ����������� ������ ��������� ������ ��� ������ DMA 2
    DCH2DSA = _VirtToPhys((const void *)&U2TXREG); // ��������� ����������� ������ �������� �������� UART2
    DCH2SSIZ = 38;                                 // ��������� ������� ��������� ������ (�������� 200 ����)
    DCH2DSIZ = 1;                                  // ��������� ������� ���������� (1 ����)
    DCH2CSIZ = 1;                                  // ��������� ������� ������ (1 ���� �� ������ ������ �������� UART)
    DCH2INTCLR = 0x00ff00ff;                       // ������� ������� � ���������� ���������� ��� ������ DMA 2
    // DCH4INTbits.CHSDIF = 0;       // �� ������������, ��������� ��� �������
    DCH2CONbits.CHEN = 0; // ���������� ������ DMA 2
}

void DMA1_init(void)
{
    DMACONSET = 0x00008000;                        // ��������� ����������� DMA
    DCH1CON = 0x2;                                 // ���������� ������ 1, ��������� ���������� 2
    DCH1ECONbits.CHSIRQ = _UART1_TX_VECTOR;        // ��������� ������� ���������� ��� �������� UART1
    DCH1ECONbits.SIRQEN = 1;                       // ���������� ���������� �� ������������� ����������
    DCH1SSA = _VirtToPhys(&buf_tx1);               // ��������� ����������� ������ ��������� ������ ��� ������ DMA 1
    DCH1DSA = _VirtToPhys((const void *)&U1TXREG); // ��������� ����������� ������ �������� �������� UART1
    DCH1SSIZ = 38;                                 // ��������� ������� ��������� ������ (�������� 200 ����)
    DCH1DSIZ = 1;                                  // ��������� ������� ���������� (1 ����)
    DCH1CSIZ = 1;                                  // ��������� ������� ������ (1 ���� �� ������ ������ �������� UART)
    DCH1INTCLR = 0x00ff00ff;                       // ������� ������� � ���������� ���������� ��� ������ DMA 1
    // DCH4INTbits.CHSDIF = 0;       // �� ������������, ��������� ��� �������
    DCH1CONbits.CHEN = 0; // ���������� ������ DMA 1
}
/* ��� ������� ������������� DMA (Direct Memory Access) ������� ������������� ��� ��������� � ���������� ��������� ������ ����� ������������
���������� (UART � ������ ������) ��� ������������� ������������ ����������. ��� ������� �� ������ ����������� ��������� DMA �������,
�� � ������������ ��������� ����������� �������� ������ ����� ������������� ������������ � ������� ��� ����������������� ������� ������������
����������, ��� �������� ������������� ������ ����������������. */

/* ������� DMA_init � DMA_uni ����� ������ ���� � ������������� ��� ������ �����:

DMA_init: ��� ������� ������������� ��� ������������� ���������� DMA ������� � ������� ������������� �����������, ������ ��� �������� ������,
�������� ������, ������ ������������ ������ � ������. ������ ������� DMA_init ����������� ������������ DMA ����� ��� ������������� ����������,
��������, UART5, UART4, UART3 � �. �. ��������� DMA ������ ������� ���������� � ������������ � ������������ ������� ����������.

DMA_uni: ��� ������� ������������� ��� ����� ������ ������������� � ��������� ����������� � ������������ DMA ������ ��� �������� ������
����� ������ ����� ��������� ������. ��� ��������� ��������� �� ��������� tag_usart, ������� ������������ ����� ���������� ���������� USART
(��������, UART1, UART2 � �. �.), � ����� ������ ���������, ����� ��� ���������� ������������ ����, ��������� ������ � �������������� ���������
������.

����� �������, DMA_init ������������ ��� ������������� DMA ������� � ������������� ����������� ��� ������������ ���������,
� �� ����� ��� DMA_uni ����� ���� ������������ ��� ����� ������ ��������� DMA ������� ��� ��������� ����� � ���������. */

test_uart_dma(void)
{
    DMA5_init();             // ������������� DMA ������ ��� �������� ������ ����� UART5.
    ENAB_TX5;                // ��������� �������� ������ ����� UART5.
    ENAB_TX5;                // ��������� �������� ������ ����� UART5 (������������ ������, ��������, ������).
    DCH1CONbits.CHEN = 1;    // ��������� DMA ������ 1.
    DCH1ECONbits.CFORCE = 1; // �������������� ��������� DMA ������ 1 (����� ���� ������������ ��� ������������ ������� �������� ������).
}

unsigned char conf, bconf;   // ���������� ���������� ��� �������� ������� (conf) � ���������� (bconf) ������������ UART4.
unsigned char conf2, bconf2; // ���������� ���������� ��� �������� ������� (conf2) � ���������� (bconf2) ������������ UART5.

/* ������� conf_read() ������������ ��� ���������� ������������ UART ������ (UART4 � UART5) � ���������
��������������� ��������� �������� ������ � ����������� �� ������������� ����� ������������. � �������� ������
������� ��������� ��������� ������ (CONF1 - CONF8) � ������������� ��������������� ���� � ���������� conf � conf2.
����� ��� ���������� �������� �������� ������ ��� ������� �� UART �� ������ ������������� ������������ � ���������
�� � ��������������� ���������� (U4_speed � U5_speed). */
/**
 * @brief ������ ������������ ������ � ��������� ��������� �������� ��� UART4 � UART5.
 *
 * ��� ������� ������ ��������� ������ ��� ����������� ������������� ����� ������������.
 * � ����������� �� ������������� ����� ������������ ������������ �������� �������� ��� UART4 � UART5.
 * ���������� ��������������� � ���������� ���������� U4_speed � U5_speed ��������������.
 *
 * @param void
 * @return void
 */
void conf_read(void)
{
    conf2 = 0; // ������������� ���������� ��� �������� ������������ UART5.
    conf = 0;  // ������������� ���������� ��� �������� ������������ UART4.
    // �������� ��������� ������ �� ������� ������������� ����� ������������ � ��������� ��������������� ����� � ���������� conf � conf2.
    if (CONF1) // �������� ��������� ����� CONF1.
    {
        conf |= 0x01; // ���� ���� ����������, ��������������� ��������������� ��� � ���������� conf.
    }
    else
    {
        conf &= 0xFE; // ���� ���� �� ����������, ������������ ��������������� ��� � ���������� conf.
    }
    if (CONF2) // �������� ��������� ����� CONF2.
    {
        conf |= 0x02; // ���� ���� ����������, ��������������� ��������������� ��� � ���������� conf.
    }
    else
    {
        conf &= 0xFD; // ���� ���� �� ����������, ������������ ��������������� ��� � ���������� conf.
    }
    // ����������� �������� ��� ������ CONF3 � CONF4.
    if (CONF3)
    {
        conf |= 0x04;
    }
    else
    {
        conf &= 0xFB;
    }
    if (CONF4)
    {
        conf |= 0x08;
    }
    else
    {
        conf &= 0xF7;
    }
    conf &= 0x0F; // ������� ������� ������� ����� ���������� conf.
    switch (conf)
    {
    case 7:
    {
        U4_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U4_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U4_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U4_speed = 19200;
        break;
    } // 19200
    default:
    {
        U4_speed = 19200;
        break;
    } // 19200
    }

    if (CONF5)
    {
        conf2 |= 0x01;
    }
    else
    {
        conf2 &= 0xFE;
    }
    if (CONF6)
    {
        conf2 |= 0x02;
    }
    else
    {
        conf2 &= 0xFD;
    }
    if (CONF7)
    {
        conf2 |= 0x04;
    }
    else
    {
        conf2 &= 0xFB;
    }
    if (CONF8)
    {
        conf2 |= 0x08;
    }
    else
    {
        conf2 &= 0xF7;
    }
    conf2 &= 0x0F;
    switch (conf2)
    {
    case 7:
    {
        U5_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U5_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U5_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U5_speed = 19200;
        break;
    } // 19200
    default:
    {
        U5_speed = 19200;
        break;
    } // 19200
    }
    //    U1_speed = 57600;
    help_reset = 1; // ��������� ����� ������ (���������������� ��� ������ ������-�� ���������).
    bconf = conf;   // ���������� ������� ������������ UART4.
    bconf2 = conf2; // ���������� ������� ������������ UART5.
}
/*
1. ���������� ���������� conf, bconf, conf2, bconf2, ������� ����� �������������� ��� �������� ������������ � ��
    ���������� ��������.

2. ��������������� ��������� �������� ���������� conf � conf2 ������ 0.

3. ����������� ��������� ���� CONF1. ���� �� ���������� � ������� ������� (1), ��������������� ��������������� ��� � ���������� conf,
    � ��������� ������ ������������.

4. ����������� ���� ����������� ��� ����� CONF2, CONF3, CONF4, ���������� ������������ � ���������� conf.

5. ����� ���������� �������� ��������������� �����, ����� �������� ������� ������ ���� ���������� conf.

6. ���������� ����� �������� �������� ��� UART4 �� ������ �������� ���������� conf. � ����������� �� ��������
    conf ��������������� ���� �� ��������� ���������: 115200, 57600, 38400, ��� 19200.

7. ����������� ���� ����������� ��� ����� CONF5, CONF6, CONF7, CONF8, ���������� ������������ � ���������� conf2.

8. ����� ���������� �������� ��������������� �����, ����� �������� ������� ������ ���� ���������� conf2.

9. ���������� ����� �������� �������� ��� UART5 �� ������ �������� ���������� conf2. �����, ��� � ��� UART4,
    � ����������� �� �������� conf2 ��������������� ���� �� ��������� ���������: 115200, 57600, 38400, ��� 19200.

10. ���������� help_reset ��������������� � 1.

11. �������� conf � conf2 ����������� � ���������� bconf � bconf2 ��������������.
*/

/* ��� ������� conf_check() ��������� ��������� ������� ����� CONF1 �� CONF8 � ����������� �� �� ���������,
���������� ������������ ����������. */
void conf_check(void)
{
    if (CONF1)
    {
        conf |= 0x01;
    }
    else
    {
        conf &= 0xFE;
    }
    if (CONF2)
    {
        conf |= 0x02;
    }
    else
    {
        conf &= 0xFD;
    }
    if (CONF3)
    {
        conf |= 0x04;
    }
    else
    {
        conf &= 0xFB;
    }
    if (CONF4)
    {
        conf |= 0x08;
    }
    else
    {
        conf &= 0xF7;
    }
    conf &= 0x0F;
    switch (conf)
    {
    case 7:
    {
        U4_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U4_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U4_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U4_speed = 19200;
        break;
    } // 19200
    default:
    {
        U4_speed = 19200;
        break;
    } // 19200
    }

    if (CONF5)
    {
        conf2 |= 0x01;
    }
    else
    {
        conf2 &= 0xFE;
    }
    if (CONF6)
    {
        conf2 |= 0x02;
    }
    else
    {
        conf2 &= 0xFD;
    }
    if (CONF7)
    {
        conf2 |= 0x04;
    }
    else
    {
        conf2 &= 0xFB;
    }
    if (CONF8)
    {
        conf2 |= 0x08;
    }
    else
    {
        conf2 &= 0xF7;
    }
    conf2 &= 0x0F;
    switch (conf2)
    {
    case 7:
    {
        U5_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U5_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U5_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U5_speed = 19200;
        break;
    } // 19200
    default:
    {
        U5_speed = 19200;
        break;
    } // 19200
    }

    if (conf2 != bconf2)
    {
        // uart5_init();
    }
    if (conf != bconf)
    {
        // uart4_init();
    }
    bconf = conf;
    bconf2 = conf2;
}
/* ����������� ��������� ���� CONF1. ���� �� ���������� � ������� ������� (1), ��������������� ��������������� ��� � ���������� conf,
    � ��������� ������ ������������.
����������� ���� ����������� ��� ����� CONF2 �� CONF8, ���������� ������������ � ���������� conf.
����� ���������� �������� ��������������� �����, ����� �������� ������� ������ ���� ���������� conf.
���������� ����� �������� �������� ��� UART4 �� ������ �������� ���������� conf. � ����������� �� �������� conf ���������������
    ���� �� ��������� ���������: 115200, 57600, 38400, ��� 19200.
����������� ���� ����������� ��� ����� CONF5 �� CONF8, ���������� ������������ � ���������� conf2.
����� ���������� �������� ��������������� �����, ����� �������� ������� ������ ���� ���������� conf2.
���������� ����� �������� �������� ��� UART5 �� ������ �������� ���������� conf2. �����, ��� � ��� UART4, � ����������� ��
    �������� conf2 ��������������� ���� �� ��������� ���������: 115200, 57600, 38400, ��� 19200.
���� �������� conf2 ���������� �� ����������� �������� bconf2, ���������� ������� uart5_init(), ����� ���������������� UART5.
���� �������� conf ���������� �� ����������� �������� bconf, ���������� ������� uart4_init(), ����� ���������������� UART4.
�������� conf � conf2 ����������� � ���������� bconf � bconf2 ��������������. */

unsigned int DI1_cnt;
unsigned int DI2_cnt;
unsigned int DI3_cnt;
/* ��� ������� discret_ctrl() ������������� ��� �������� �� ����������� ������� (DI1, DI2, DI3) �
���������� ���������� ��� �������� ������� �����. */
void discret_ctrl(void)
{
    if (DINPUT1 != DI_1)
    {
        DI1_cnt += CYCLE;
        if (DI1_cnt >= FILT_DISCRET)
        {
            DINPUT1 = DI_1;
            DI1_cnt = 0;
        }
    }
    else
    {
        DI1_cnt = 0;
    }

    if (DINPUT2 != DI_2)
    {
        DI2_cnt += CYCLE;
        if (DI2_cnt >= FILT_DISCRET)
        {
            DINPUT2 = DI_2;
            DI2_cnt = 0;
        }
    }
    else
    {
        DI2_cnt = 0;
    }

    if (DINPUT3 != DI_3)
    {
        DI3_cnt += CYCLE;
        if (DI3_cnt >= FILT_DISCRET)
        {
            DINPUT3 = DI_3;
            DI3_cnt = 0;
        }
    }
    else
    {
        DI3_cnt = 0;
    }
}
/* ����������� ���������� DI1_cnt, DI2_cnt, � DI3_cnt, ������� ����� �������������� ��� ������������ ������� ��������� ��������� ���������� ������.
����������� ��������� ����������� ����� DI1 (DINPUT1). ���� ��� ���������� �� ���������� ��������� DI_1, �� � ���������� DI1_cnt ����������� �������� CYCLE.
���� DI1_cnt ���������� ������ ��� ������ ���������� �������� FILT_DISCRET, �� ��������� ����� DINPUT1 ��������������� ������ DI_1, � DI1_cnt ������������.
����������� �������� ����������� ��� ���������� ������ DI2 � DI3.
���� ��������� ����������� ����� �� ����������, ������� DI*_cnt ������������ � ����. */

/* ��� ������� fun_blink_counter() �������� �� ������� ����������� � �������������� �������� blink_counter. */
void fun_blink_counter(void)
{
    if (++blink_counter >= 10)
    {
        blink_counter = 0;
        PORTEbits.RE0 = LATEbits.LATE0 ^ 1;
    }
}
