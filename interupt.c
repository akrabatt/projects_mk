#include "extern.h"

extern void mbm_timeout_control(struct tag_usart *usart);

// TIMERS
/**
 * @brief ���������� ���������� �� ������� 1.
 *
 * ��� ������� ���������� ��� ���������� �� ������� 1. ��� ��������� ��������� ��������:
 * - ��������� ������ 1 ��� �������������� ��������� ����������.
 * - �������� ������� ������� T1Interrupt_ ��� ��������� ����������. � �������� ��������� ���������� ��������� �� ��������� usart1.
 * - ����������� ��������� ����� RE3, �������, ��������, ������������ ��� ���������� �����������.
 * - ���������� ���� ���������� �� ������� 1, ����� CPU ��� ������� � ������ �������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void)
{
    /*  ���������� ������� 1. ������������ ��� ������ ��� �������������� ��������� ����������. */
    T1CONbits.TON = 0;
    /*  ����� ������� ������� T1Interrupt_, ������� ������������ ����������. � �������� ���������
    ���������� ��������� �� ��������� usart1.*/
    T1Interrupt_(&usart1);
    /* �������������� ��������� ����� RE3, �������, ��������, ������������ ��� ���������� �����������. */
    PORTEbits.RE3 = LATEbits.LATE3 ^ 1;
    /* ����� ����� ���������� �� ������� 1. ��� ���������� ��� ����, ����� CPU ����, ��� ����������
    ���� ���������� � ����� ������� � ������ ������� */
    IFS0bits.T1IF = 0;
}

/**
 * @brief ���������� ���������� �� ������� 2.
 *
 * ��� ������� ���������� ��� ���������� �� ������� 2. ��� ��������� ��������� ��������:
 * - ��������� ������ 2 ��� �������������� ��������� ����������.
 * - �������� ������� ������� T2Interrupt_ ��� ��������� ����������. � �������� ��������� ���������� ��������� �� ��������� usart2.
 * - ����������� ��������� ����� RG13, �������, ��������, ������������ ��� ���������� �����������.
 * - ���������� ���� ���������� �� ������� 2, ����� CPU ��� ������� � ������ �������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL4SRS) T2Interrupt(void)
{
    T2CONbits.TON = 0;
    T2Interrupt_(&usart2);
    PORTGbits.RG13 = LATGbits.LATG13 ^ 1;
    IFS0bits.T2IF = 0;
}

/**
 * @brief ���������� �� ������� 3.
 *
 * ��� ������� ������������ ����� ���������� ���������� �� ������� 3. ������� ��� ���������
 * ������ 3, ����� �������� ������� ������� T3Interrupt_, ��������� ��������� �� ��������� usart3.
 * ����� ���������� �������� ��������� ������ RG14 ����� G. ����� ������������ ���� ����������
 * �� ������� 3.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_3_VECTOR, IPL4SRS) T3Interrupt(void)
{
    T3CONbits.TON = 0;
    T3Interrupt_(&usart3);
    PORTGbits.RG14 = LATGbits.LATG14 ^ 1;
    IFS0bits.T3IF = 0;
}

/**
 * @brief ���������� �� ������� 4.
 *
 * ��� ������� ������������ ���������� �� ������� 4. ��� ��������� ������, �������� ������� ��������� ����������
 * ��� USART4 � ���������� ���� ����������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void)
{
    T4CONbits.TON = 0;
    T4Interrupt_(&usart4);
    IFS0bits.T4IF = 0;
}

<<<<<<< HEAD
void __ISR_AT_VECTOR(_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void) { 
    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void) {
    ignit_stop();
    ADCCON3bits.GSWTRG = 1;
    IFS0bits.T4IF = 0;
    counters();
    start_pid_reg = 1; //pid_control(MB_conf.CV_KP, MB_conf.CV_KD, MB_conf.CV_KI);
}

void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void) {
=======
/**
 * @brief ���������� �� ������� 5.
 *
 * ��� ������� ������������ ���������� �� ������� 5. ��� ��������� ������, �������� ������� ��������� ����������
 * ��� USART5 � ���������� ���� ����������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void)
{
>>>>>>> dev_branch
    T5CONbits.TON = 0;
    T5Interrupt_(&usart5);
    IFS0bits.T5IF = 0;
}

<<<<<<< HEAD
void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void) {
    Timer6Interrupt();
=======
/**
 * @brief ���������� �� ������� 6.
 *
 */
void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void)
{
    // T6CONbits.TON = 0;
    if ((--SECOND) == 0) // ���� ����������(200)-1 ������� ����� ����
    {
        SECOND = 200; // ��������
        LED3_TOGGLE;  // ����������� ���������
        /* ������ ���� ������ ������� */
        usart1.mb_status.master_timeout_flag = 1;
    }
//    mbm_timeout_control(&usart5);
//    mbm_timeout_control(&usart4);
//    mbm_timeout_control(&usart2);
//    mbm_timeout_control(&usart1);
>>>>>>> dev_branch
    IFS0bits.T6IF = 0;
}

/**
 * @brief ���������� �� ������� 7.
 *
 */
void __ISR_AT_VECTOR(_TIMER_7_VECTOR, IPL4SRS) T7Interrupt(void)
{
    T7CONbits.TON = 0;
    IFS1bits.T7IF = 0;
}

<<<<<<< HEAD
void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void) {
    T9CONbits.TON = 0;
    T9Interrupt_(&usart4);
    IFS1bits.T9IF = 0;
}
=======
/**
 * @brief ���������� �� ������� 9.
 *
 * ��� ������� ������������ ���������� �� ������� 9. ��� �������� ������� ���������� �������� ����������
 * ��� ������� ���������� � �������� ��������������. ����� ��� ���������, ������� �� ����� �������� ��������
 * �� Modbus (tm_on) ��� USART1. ���� ���������� ���� �������� �������� (mbm_timeout_counter == 0), �����������
 * ��� ��������. ����� ������������ ���� �������� ��������, � ���� ���������� ���� ������ ������-��������,
 * ��������������� ���� �������� �������. � ����� ������������ ���� ���������� �� ������� 9.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void)
{
    // ����� ������� ��� ���������� �������� ���������� ��� ������� ���������� � �������� ��������������
    fun_blink_counter();
>>>>>>> dev_branch

    // ��������, ������� �� ����� �������� �������� �� Modbus (tm_on)
    if (usart1.mb_status.tm_on == 1)
    {
        // ���� ���������� ���� �������� �������� (mbm_timeout_counter == 0), ��������� ��������
        if (!(usart1.mbm_timeout_counter--))
            ; // ������ �� ������, ���������� ���� ����

        // ����� ����� �������� ��������
        usart1.mb_status.tm_on = 0;

        // ���� ���������� ���� ������ ������-��������, ������������� ���� �������� �������
        if (usart1.mb_status.master_start)
            usart1.mb_status.master_timeout_flag = 1;
    }

    // ����� ����� ���������� �� ������� 9
    IFS1bits.T9IF = 0;
}

// TX/RX

/**
 * @brief ���������� �� ��������� UART5.
 *
 * ��� ������� ������������ ���������� �� ��������� UART5. ��� ������� ���� ���������� �� UART5 RX,
 * ������������� ���� ������ Modbus � ��������� usart5, ��������� ������ �� ��������� ������ UART5 � ���������
 * �� � ������ ������. ����� ��� ���������, �� �������� �� ������ ������ ������. ���� ������ ��������,
 * ��������������� ���� ��������� Modbus, ����� ������������ ���� ������ Modbus. ����� ���������������� ������ 5
 * ��� �������� �������� ������, � ����� ��������� ���� ���������� �� UART5 RX.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART5_RX_VECTOR, IPL4SRS) U5RXInterrupt(void)
{
    IFS5bits.U5RXIF = 0;                 // ������� ���� ���������� �� UART5 RX.
    usart5.mb_status.modb_receiving = 1; // ������������� ���� ������ Modbus � ��������� usart5.
    while (U5STAbits.URXDA)
    {                                                         // ���� � �������� ������ UART5 ���� ������...
        usart5.in_buffer[usart5.in_buffer_count++] = U5RXREG; // ...��������� ������ � ��������� �� � ������ ������.
    }
    if (usart5.in_buffer_count >= IN_SIZE1)
    {                                        // ���������, �� �������� �� ������ ������ ������.
        usart5.mb_status.modb_received = 1;  // ������������� ���� ��������� Modbus � ��������� usart5.
        usart5.mb_status.modb_receiving = 0; // ���������� ���� ������ Modbus � ��������� usart5.
    }
    tmr_5_init(frame_delay_1, 1, 1); // �������������� ������ 5 ��� �������� �������� ������.
    IFS5bits.U5RXIF = 0;             // ����� ������� ���� ���������� �� UART5 RX.
}

/**
 * @brief ���������� �� ����������� UART5.
 *
 * ��� ������� ������������ ���������� �� ����������� UART5. ��� ���������� ���� ���������� �������� UART5
 * � ������������ �������� ������ �� ������ ��������. �������� ������ ����������, ���� ����� �������� ��
 * �������� � ���� ������� ���� �� �������� ���������. ����� ���������� ���������� ���� ��������� ������
 * ����������, ��������������� ���� ���������� �����, � ���������� �������� UART5 �����������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART5_TX_VECTOR, IPL4SRS) U5TXInterrupt(void)
{
    IFS5bits.U5TXIF = 0; // ����� ����� ���������� �������� UART5.

    while ((!U5STAbits.UTXBF) && (!usart5.mb_status.last_byte))
    {                                                           // ���� ����� �������� �� �������� � ������� ���� �� ���������...
        U5TXREG = usart5.out_buffer[usart5.out_buffer_count++]; // ...�������� ���� �� ������ ��������.

        if (usart5.out_buffer_count >= (usart5.number_send))
        {                                   // ���� ���������� ���������� ���� �������� ������ ����������...
            usart5.mb_status.last_byte = 1; // ...������������� ���� ���������� �����...
            IEC5bits.U5TXIE = 0;            // ...� ��������� ���������� �������� UART5.
        }
    }

    IFS5bits.U5TXIF = 0; // ����� ���������� ���� ���������� �������� UART5.
}

/**
 * @brief ���������� �� ��������� UART4.
 *
 * ��� ������� ������������ ���������� �� ��������� UART4. ��� ���������� ���� ���������� UART4 ���������
 * � ������������ ����� ������ �� UART4. ����� ������ ������������, ���� � �������� ������ UART4 ���� ������.
 * ����� ����� ������� ������ ���������� ������, ��������������� ���� ��������� MODBUS �� UART4, � ���� ������
 * MODBUS �� UART4 ������������. ����� ���������������� ������ 6 ��� �������� ����� �������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART4_RX_VECTOR, IPL4SRS) U4RXInterrupt(void)
{
    IFS5bits.U4RXIF = 0;                 // ����� ����� ���������� UART4 ���������
    usart4.mb_status.modb_receiving = 1; // ��������� ����� ������ MODBUS �� UART4
    while (U4STAbits.URXDA)              // ���� � �������� ������ UART4 ���� ������
    {
        usart4.in_buffer[usart4.in_buffer_count++] = U4RXREG; // ������ ������ �� UART4 � ������ � ����� ������� ������
    }
    if (usart4.in_buffer_count >= IN_SIZE1) // ���� ����� ������� ������ �����
    {
        usart4.mb_status.modb_received = 1;  // ��������� ����� ��������� MODBUS �� UART4
        usart4.mb_status.modb_receiving = 0; // ����� ����� ������ MODBUS �� UART4
    }
    tmr_4_init(frame_delay_1, 1, 1); // ������������� ������� 6 ��� �������� ����� �������
    IFS5bits.U4RXIF = 0;             // ����� ����� ���������� UART4 ���������
}

/**
 * @brief ���������� �� ����������� UART4.
 *
 * ��� ������� ������������ ���������� �� ����������� UART4. ��� ���������� ���� ���������� UART4 �����������
 * � ������������ �������� ������ ����� UART4. �������� ������ ������������, ���� ����� ����������� UART4 ��
 * �������� � �� ��������� ��������� ����. ����� �������� ���� ������ �� ������ ��������������� ���� ����������
 * ����� ��������, � ���������� �������� UART4 �����������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART4_TX_VECTOR, IPL4SRS) U4TXInterrupt(void)
{
    IFS5bits.U4TXIF = 0;                                        // ����� ����� ���������� UART4 �����������
    while ((!U4STAbits.UTXBF) && (!usart4.mb_status.last_byte)) // ���� ����� ����������� UART4 �� �������� � �� ��������� ��������� ����
    {
        U4TXREG = usart4.out_buffer[usart4.out_buffer_count++]; // �������� ������ �� ������ �������� UART4
        if (usart4.out_buffer_count >= (usart4.number_send))    // ���� ���������� ��� ������ �� ������
        {
            usart4.mb_status.last_byte = 1; // ��������� ����� ���������� ����� ��������
            IEC5bits.U4TXIE = 0;            // ���������� ���������� �������� UART4
        }
    }
    IFS5bits.U4TXIF = 0; // ����� ����� ���������� UART4 �����������
}

/**
 * @brief ���������� �� ��������� UART1.
 *
 * ��� ������� ������������ ���������� �� ��������� UART1. ��� ���������� ���� ���������� UART1 ���������
 * � ������������ ����� ������ ����� UART1. ����� ������ ������������, ���� � ������ ��������� UART1 ���� ������.
 * ���� ������� ������������ ���������� ����, ��������������� ���� ��������� ������ MODBUS ��� UART1, � ����������
 * ��������� UART1 �����������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART1_RX_VECTOR, IPL4SRS) U1RXInterrupt(void)
{
    IFS3bits.U1RXIF = 0;                 // ����� ����� ���������� UART1 ���������
    usart1.mb_status.modb_receiving = 1; // ��������� ����� ������ MODBUS ��� UART1
    while (U1STAbits.URXDA)              // ���� � ������ ��������� UART1 ���� ������
    {
        usart1.in_buffer[usart1.in_buffer_count++] = U1RXREG; // ������ ������ �� ������ ��������� UART1
    }
    if (usart1.in_buffer_count >= IN_SIZE1) // ���� ������� ������������ ���������� ����
    {
        usart1.mb_status.modb_received = 1;  // ��������� ����� ��������� ������ MODBUS ��� UART1
        usart1.mb_status.modb_receiving = 0; // ����� ����� ������ MODBUS ��� UART1
    }
    tmr_1_init(frame_delay_1, 1, 1); // ������������� ������� 1 ��� ��������
    IFS3bits.U1RXIF = 0;             // ����� ����� ���������� UART1 ���������
}

/**
 * @brief ���������� �� ����������� UART1.
 *
 * ��� ������� ������������ ���������� �� ����������� UART1. ��� ���������� ���� ���������� UART1 �����������
 * � ������������ �������� ������ ����� UART1. �������� ������ ������������, ���� ����� ����������� UART1 �� ��������
 * � �� ������� ��������� ����. ����� �������� ���������� ����� ����������� ���������� ����������� UART1.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART1_TX_VECTOR, IPL1SRS) U1TXInterrupt(void)
{
    IFS3bits.U1TXIF = 0;                                        // ����� ����� ���������� UART1 �����������
    while ((!U1STAbits.UTXBF) && (!usart1.mb_status.last_byte)) // ���� ����� ����������� UART1 �� �������� � �� ������� ��������� ����
    {
        U1TXREG = usart1.out_buffer[usart1.out_buffer_count++]; // ������ ������ �� ������ ����������� UART1 � ������� ��������
        if (usart1.out_buffer_count >= (usart1.number_send))    // ���� �������� ������������ ���������� ����
        {
            usart1.mb_status.last_byte = 1; // ��������� ����� ���������� ����� ��� UART1
            IEC3bits.U1TXIE = 0;            // ������ ���������� �� UART1 �����������
        }
    }
    IFS3bits.U1TXIF = 0; // ����� ����� ���������� UART1 �����������
}

/**
 * @brief ���������� �� ��������� UART2.
 *
 * ��� ������� ������������ ���������� �� ��������� UART2. ��� ���������� ���� ���������� UART2 ���������
 * � ������������ ����� ������ ����� UART2. ����� ������ ������������, ���� � �������� ������ UART2 ���� ������.
 * ���� ����� ������ UART2 ����������, ��������������� ��������������� ����. ����� ���������������� ������ 2.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART2_RX_VECTOR, IPL4SRS) U2RXInterrupt(void)
{
    IFS4bits.U2RXIF = 0;                 // ����� ����� ���������� UART2 ���������
    usart2.mb_status.modb_receiving = 1; // ��������� ����� ������ MODBUS ��� UART2
    while (U2STAbits.URXDA)              // ���� � �������� ������ UART2 ���� ������
    {
        usart2.in_buffer[usart2.in_buffer_count++] = U2RXREG; // ������ ������ �� �������� ������ UART2 � ����� ������
    }
    if (usart2.in_buffer_count >= IN_SIZE1) // ���� ����� ������ UART2 ����������
    {
        usart2.mb_status.modb_received = 1;  // ��������� ����� ������ MODBUS ��� UART2
        usart2.mb_status.modb_receiving = 0; // ����� ����� ������ MODBUS ��� UART2
    }
    tmr_2_init(frame_delay_1, 1, 1); // ������������� ������� 2
    IFS4bits.U2RXIF = 0;             // ����� ����� ���������� UART2 ���������
    //    PORTEbits.RE2 = LATEbits.LATE2 ^ 1; // ���������� ������ ������ E2
}

/**
 * @brief ���������� �� ����������� UART2.
 *
 * ��� ������� ������������ ���������� �� ����������� UART2. ��� ���������� ���� ���������� UART2 �����������
 * � ������������ �������� ������ ����� UART2. �������� ������ ������������, ���� ����� ����������� UART2 �� ��������
 * � ���� �� ����� ������� ��������� ����. ����� ��� ������ ��������, ��������������� ��������������� ����,
 * � ���������� �������� UART2 �����������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART2_TX_VECTOR, IPL1SRS) U2TXInterrupt(void)
{
    IFS4bits.U2TXIF = 0;                                        // ����� ����� ���������� UART2 �����������
    while ((!U2STAbits.UTXBF) && (!usart2.mb_status.last_byte)) // ���� ����� ����������� UART2 �� �������� � ���� �� ���������
    {
        U2TXREG = usart2.out_buffer[usart2.out_buffer_count++]; // ������ ������ �� ������ �������� � ������� �������� UART2
        if (usart2.out_buffer_count >= (usart2.number_send))    // ���� ��������� ����� ������ ��� ��������
        {
            usart2.mb_status.last_byte = 1; // ��������� ����� ���������� ����� ��� UART2
            IEC4bits.U2TXIE = 0;            // ���������� ���������� �������� ��� UART2
        }
    }
    IFS4bits.U2TXIF = 0; // ����� ����� ���������� UART2 �����������
}

/**
 * @brief ���������� �� ��������� UART3.
 *
 * ��� ������� ������������ ���������� �� ��������� UART3. ��� ���������� ���� ���������� UART3 ���������
 * � ������������ ����� ������ ����� UART3. ����� ������ ������������, ���� ����� ��������� UART3 �� ��������.
 * ����� ����� ����������� �� ������������� �������, ��������������� ��������������� ����, ����������� �� ���������� ������.
 * ����� ���������������� ������ 7 ��� �������� ����� �������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART3_RX_VECTOR, IPL4SRS) U3RXInterrupt(void)
{
    IFS4bits.U3RXIF = 0;                 // ����� ����� ���������� UART3 ���������
    usart3.mb_status.modb_receiving = 1; // ��������� ����� ������ ��� UART3
    while (U3STAbits.URXDA)              // ���� ����� ��������� UART3 �� ����
    {
        usart3.in_buffer[usart3.in_buffer_count++] = U3RXREG; // ������ ������ �� �������� ��������� UART3 � ����� ������
    }
    if (usart3.in_buffer_count >= IN_SIZE1) // ���� ��������� ������������ ������ ������ ������
    {
        usart3.mb_status.modb_received = 1;  // ��������� ����� ���������� ������ ��� UART3
        usart3.mb_status.modb_receiving = 0; // ����� ����� ������ ��� UART3
    }
    tmr_3_init(frame_delay_1, 1, 1); // ������������� ������� 7 ��� �������� ����� �������

    IFS4bits.U3RXIF = 0; // ����� ����� ���������� UART3 ���������
}

/**
 * @brief ���������� �� ����������� UART3.
 *
 * ��� ������� ������������ ���������� �� ����������� UART3. ��� ���������� ���� ���������� UART3 �����������
 * � ������������ �������� ������ ����� UART3. �������� ������ ������������, ���� ����� ����������� UART3 �� ����������.
 * ����� ������� ��������� ���� ������, ��������������� ��������������� ����, ����������� �� ���������� ��������.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART3_TX_VECTOR, IPL1SRS) U3TXInterrupt(void)
{
    IFS4bits.U3TXIF = 0;                                        // ����� ����� ���������� UART3 �����������
    while ((!U3STAbits.UTXBF) && (!usart3.mb_status.last_byte)) // ���� ����� ����������� UART3 �� �������� � ��������� ���� �� ���������
    {
        U3TXREG = usart3.out_buffer[usart3.out_buffer_count++]; // �������� ������ �� ������ �������� UART3 � ������� ��������
        if (usart3.out_buffer_count >= (usart3.number_send))    // ���� ��������� ������������ ������ ������ ��������
        {
            usart3.mb_status.last_byte = 1; // ��������� ����� ���������� ����� ��� UART3
            IEC4bits.U3TXIE = 0;            // ���������� ���������� UART3 �����������
        }
    }
    IFS4bits.U3TXIF = 0; // ����� ����� ���������� UART3 �����������
}

/**
 * @brief ���������� �� DMA ������ 0.
 *
 * ��� ������� ������������ ���������� �� DMA ������ 0. ��� ��������� ����� ���������� DMA ������ 0,
 * ��������� ����������� �������� � ����� �� ������������� ����� ���������� � ����� ���������� ��� �����.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void)
{
    int dmaFlags = DCH0INT & 0xff; // ������ ������ ���������� DMA ������ 0

    // ���������� ���������� �������� � ����� �� ����� ������������� ���� ����������

    DCH0INTCLR = 0x000000ff; // ����� ������ ���������� ������ DMA 0
    IFS4bits.DMA0IF = 0;     // ����������� ���������� ����� ���������� DMA0
    // ����� ������� �� ����������� ����������.
}