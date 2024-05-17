#include "extern.h"

// TIMERS
/* Объявление функции прерывания. Она ассоциируется с прерыванием от таймера 1 (_TIMER_1_VECTOR) и
    устанавливает приоритет прерывания на уровень 4. */
void __ISR_AT_VECTOR(_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void)
{
    /*  Выключение таймера 1. Прекращается его работа для предотвращения повторных прерываний. */
    T1CONbits.TON = 0;
    /*  Вызов внешней функции T1Interrupt_, которая обрабатывает прерывание. В качестве аргумента
    передается указатель на структуру usart1.*/
    T1Interrupt_(&usart1);
    /* Инвертирование состояния порта RE3, который, вероятно, используется для управления светодиодом. */
    PORTEbits.RE3 = LATEbits.LATE3 ^ 1;
    /* Сброс флага прерывания от таймера 1. Это необходимо для того, чтобы CPU знал, что прерывание
    было обработано и может перейти к другим задачам */
    IFS0bits.T1IF = 0;
}

/* таймер 2 - юсарт 2 */
void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL4SRS) T2Interrupt(void)
{
    T2CONbits.TON = 0;
    T2Interrupt_(&usart2);
    //    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;
    PORTGbits.RG13 = LATGbits.LATG13 ^ 1;
    IFS0bits.T2IF = 0;
}

/* таймер 4 */
void __ISR_AT_VECTOR(_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void)
{
    T4CONbits.TON = 0;
    IFS0bits.T4IF = 0;
}

/* таймер 5 - юсарт 5 */
void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void)
{
    T5CONbits.TON = 0;
    T5Interrupt_(&usart5);
    IFS0bits.T5IF = 0;
}

/* таймер 6 - юсарт 6 */
void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void)
{
    T6CONbits.TON = 0;
    T6Interrupt_(&usart4);
    IFS0bits.T6IF = 0;
}

/* таймер 7 - юсарт 3 */
void __ISR_AT_VECTOR(_TIMER_7_VECTOR, IPL4SRS) T7Interrupt(void)
{
    T7CONbits.TON = 0;
    T4Interrupt_(&usart3);
    PORTGbits.RG14 = LATGbits.LATG14 ^ 1;
    IFS1bits.T7IF = 0;
}

/* таймер 9 */
void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void)
{
    // Вызов функции для управления миганием светодиода или другими действиями с заданной периодичностью
    fun_blink_counter();

    // Проверка, включен ли режим таймаута передачи по Modbus (tm_on)
    if (usart1.mb_status.tm_on == 1)
    {
        // Если установлен флаг таймаута передачи (mbm_timeout == 0), уменьшаем значение
        if (!(usart1.mbm_timeout--))
            ; // Ничего не делаем, пропускаем блок кода

        // Сброс флага таймаута передачи
        usart1.mb_status.tm_on = 0;

        // Если установлен флаг начала мастер-передачи, устанавливаем флаг таймаута мастера
        if (usart1.mb_status.master_start)
            usart1.mb_status.master_timeout = 1;
    }

    // Сброс флага прерывания от таймера 9
    IFS1bits.T9IF = 0;
}

// TX/RX

/* прерывание на прием данных */
void __ISR_AT_VECTOR(_UART5_RX_VECTOR, IPL4SRS) U5RXInterrupt(void)
{
    IFS5bits.U5RXIF = 0;                 // Снимаем флаг прерывания от UART5 RX.
    usart5.mb_status.modb_receiving = 1; // Устанавливаем флаг приема Modbus в структуре usart5.
    while (U5STAbits.URXDA)
    {                                                         // Пока в приемном буфере UART5 есть данные...
        usart5.in_buffer[usart5.in_buffer_count++] = U5RXREG; // ...считываем данные и сохраняем их в буфере приема.
    }
    if (usart5.in_buffer_count >= IN_SIZE1)
    {                                        // Проверяем, не превышен ли размер буфера приема.
        usart5.mb_status.modb_received = 1;  // Устанавливаем флаг получения Modbus в структуре usart5.
        usart5.mb_status.modb_receiving = 0; // Сбрасываем флаг приема Modbus в структуре usart5.
    }
    tmr_5_init(frame_delay_1, 1, 1); // Инициализируем таймер 5 для задержки передачи данных.
    IFS5bits.U5RXIF = 0;             // Снова снимаем флаг прерывания от UART5 RX.
}
/* этот код обрабатывает прерывание от UART5, считывает данные из его буфера приема и обрабатывает их в
соответствии с протоколом Modbus, гарантируя, что принятый пакет не превышает максимально допустимый размер
и что обработка данных не блокируется. */

void __ISR_AT_VECTOR(_UART5_TX_VECTOR, IPL4SRS) U5TXInterrupt(void)
{
    IFS5bits.U5TXIF = 0; // Сброс флага прерывания передачи UART5.

    while ((!U5STAbits.UTXBF) && (!usart5.mb_status.last_byte))
    {                                                           // Пока буфер передачи не заполнен и текущий байт не последний...
        U5TXREG = usart5.out_buffer[usart5.out_buffer_count++]; // ...передаем байт из буфера отправки.

        if (usart5.out_buffer_count >= (usart5.number_send))
        {                                   // Если количество переданных байт достигло общего количества...
            usart5.mb_status.last_byte = 1; // ...устанавливаем флаг последнего байта...
            IEC5bits.U5TXIE = 0;            // ...и отключаем прерывание передачи UART5.
        }
    }

    IFS5bits.U5TXIF = 0; // Снова сбрасываем флаг прерывания передачи UART5.
}
/* Этот код представляет собой прерывание передачи данных по UART5. Он выполняет следующие действия:

Сбрасывает флаг прерывания передачи UART5.
Запускает цикл передачи данных из буфера usart5.out_buffer по UART5.
Передает байты из буфера, пока буфер передачи не заполнен (U5STAbits.UTXBF) и пока текущий байт не является последним (usart5.mb_status.last_byte).
Если количество переданных байт достигает общего количества (usart5.number_send), устанавливает флаг последнего байта и отключает прерывание передачи UART5.
После завершения передачи снова сбрасывает флаг прерывания передачи UART5.
Таким образом, этот код обеспечивает передачу данных по UART5 с учетом обработки последнего байта и управления прерываниями. */

/*  */
void __ISR_AT_VECTOR(_UART4_RX_VECTOR, IPL4SRS) U4RXInterrupt(void)
{
    IFS5bits.U4RXIF = 0;                 // Сброс флага прерывания UART4 приемника
    usart4.mb_status.modb_receiving = 1; // Установка флага приема MODBUS по UART4
    while (U4STAbits.URXDA)              // Пока в приемном буфере UART4 есть данные
    {
        usart4.in_buffer[usart4.in_buffer_count++] = U4RXREG; // Чтение данных из UART4 и запись в буфер входных данных
    }
    if (usart4.in_buffer_count >= IN_SIZE1) // Если буфер входных данных полон
    {
        usart4.mb_status.modb_received = 1;  // Установка флага получения MODBUS по UART4
        usart4.mb_status.modb_receiving = 0; // Сброс флага приема MODBUS по UART4
    }
    tmr_6_init(frame_delay_1, 1, 1); // Инициализация таймера 6 для задержки между кадрами
    IFS5bits.U4RXIF = 0;             // Сброс флага прерывания UART4 приемника
}

void __ISR_AT_VECTOR(_UART4_TX_VECTOR, IPL4SRS) U4TXInterrupt(void)
{
    IFS5bits.U4TXIF = 0;                                        // Сброс флага прерывания UART4 передатчика
    while ((!U4STAbits.UTXBF) && (!usart4.mb_status.last_byte)) // Пока буфер передатчика UART4 не заполнен и не отправлен последний байт
    {
        U4TXREG = usart4.out_buffer[usart4.out_buffer_count++]; // Отправка данных из буфера передачи UART4
        if (usart4.out_buffer_count >= (usart4.number_send))    // Если отправлены все данные из буфера
        {
            usart4.mb_status.last_byte = 1; // Установка флага последнего байта передачи
            IEC5bits.U4TXIE = 0;            // Отключение прерывания передачи UART4
        }
    }
    IFS5bits.U4TXIF = 0; // Сброс флага прерывания UART4 передатчика
}

void __ISR_AT_VECTOR(_UART1_RX_VECTOR, IPL4SRS) U1RXInterrupt(void)
{
    IFS3bits.U1RXIF = 0;
    usart1.mb_status.modb_receiving = 1;
    while (U1STAbits.URXDA)
    {
        usart1.in_buffer[usart1.in_buffer_count++] = U1RXREG;
    }
    if (usart1.in_buffer_count >= IN_SIZE1)
    {
        usart1.mb_status.modb_received = 1;
        usart1.mb_status.modb_receiving = 0;
    }
    tmr_1_init(frame_delay_1, 1, 1);

    IFS3bits.U1RXIF = 0;
}

void __ISR_AT_VECTOR(_UART1_TX_VECTOR, IPL1SRS) U1TXInterrupt(void)
{
    IFS3bits.U1TXIF = 0;
    while ((!U1STAbits.UTXBF) && (!usart1.mb_status.last_byte)) // copy if buff  isn't full and byte is not last
    {
        U1TXREG = usart1.out_buffer[usart1.out_buffer_count++];
        if (usart1.out_buffer_count >= (usart1.number_send))
        {
            usart1.mb_status.last_byte = 1;
            IEC3bits.U1TXIE = 0;
        }
    }
    IFS3bits.U1TXIF = 0;
}

void __ISR_AT_VECTOR(_UART2_RX_VECTOR, IPL4SRS) U2RXInterrupt(void)
{
    IFS4bits.U2RXIF = 0;
    usart2.mb_status.modb_receiving = 1;
    while (U2STAbits.URXDA)
    {
        usart2.in_buffer[usart2.in_buffer_count++] = U2RXREG;
    }
    if (usart2.in_buffer_count >= IN_SIZE1)
    {
        usart2.mb_status.modb_received = 1;
        usart2.mb_status.modb_receiving = 0;
    }
    tmr_2_init(frame_delay_1, 1, 1);

    IFS4bits.U2RXIF = 0;
    //    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;
}

void __ISR_AT_VECTOR(_UART2_TX_VECTOR, IPL1SRS) U2TXInterrupt(void)
{
    IFS4bits.U2TXIF = 0;
    while ((!U2STAbits.UTXBF) && (!usart2.mb_status.last_byte)) // copy if buff  isn't full and byte is not last
    {
        U2TXREG = usart2.out_buffer[usart2.out_buffer_count++];
        if (usart2.out_buffer_count >= (usart2.number_send))
        {
            usart2.mb_status.last_byte = 1;
            IEC4bits.U2TXIE = 0;
        }
    }
    IFS4bits.U2TXIF = 0;
}

void __ISR_AT_VECTOR(_UART3_RX_VECTOR, IPL4SRS) U3RXInterrupt(void)
{
    IFS4bits.U3RXIF = 0;
    usart3.mb_status.modb_receiving = 1;
    while (U3STAbits.URXDA)
    {
        usart3.in_buffer[usart3.in_buffer_count++] = U3RXREG;
    }
    if (usart3.in_buffer_count >= IN_SIZE1)
    {
        usart3.mb_status.modb_received = 1;
        usart3.mb_status.modb_receiving = 0;
    }
    tmr_7_init(frame_delay_1, 1, 1);

    IFS4bits.U3RXIF = 0;
    //    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;
}

void __ISR_AT_VECTOR(_UART3_TX_VECTOR, IPL1SRS) U3TXInterrupt(void)
{
    IFS4bits.U3TXIF = 0;
    while ((!U3STAbits.UTXBF) && (!usart3.mb_status.last_byte)) // copy if buff  isn't full and byte is not last
    {
        U3TXREG = usart3.out_buffer[usart3.out_buffer_count++];
        if (usart3.out_buffer_count >= (usart3.number_send))
        {
            usart3.mb_status.last_byte = 1;
            IEC4bits.U3TXIE = 0;
        }
    }
    IFS4bits.U3TXIF = 0;
}

void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void)
{
    int dmaFlags = DCH0INT & 0xff; // read the interrupt flags

    // perform application specific operations in response to any interrupt flag set

    DCH0INTCLR = 0x000000ff; // clear the DMA channel interrupt flags
    IFS4bits.DMA0IF = 0;     // Be sure to clear the DMA0 interrupt flags
    // before exiting the service routine.
}