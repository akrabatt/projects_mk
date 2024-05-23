#include "extern.h"

extern void mbm_timeout_control(struct tag_usart *usart);

// TIMERS
/**
 * @brief Обработчик прерывания от таймера 1.
 *
 * Эта функция вызывается при прерывании от таймера 1. Она выполняет несколько действий:
 * - Отключает таймер 1 для предотвращения повторных прерываний.
 * - Вызывает внешнюю функцию T1Interrupt_ для обработки прерывания. В качестве аргумента передается указатель на структуру usart1.
 * - Инвертирует состояние порта RE3, который, вероятно, используется для управления светодиодом.
 * - Сбрасывает флаг прерывания от таймера 1, чтобы CPU мог перейти к другим задачам.
 *
 * @param void
 * @return void
 */
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

/**
 * @brief Обработчик прерывания от таймера 2.
 *
 * Эта функция вызывается при прерывании от таймера 2. Она выполняет несколько действий:
 * - Отключает таймер 2 для предотвращения повторных прерываний.
 * - Вызывает внешнюю функцию T2Interrupt_ для обработки прерывания. В качестве аргумента передается указатель на структуру usart2.
 * - Инвертирует состояние порта RG13, который, вероятно, используется для управления светодиодом.
 * - Сбрасывает флаг прерывания от таймера 2, чтобы CPU мог перейти к другим задачам.
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
 * @brief Прерывание от таймера 3.
 *
 * Эта функция представляет собой обработчик прерывания от таймера 3. Вначале она отключает
 * таймер 3, затем вызывает внешнюю функцию T3Interrupt_, передавая указатель на структуру usart3.
 * Далее происходит инверсия состояния вывода RG14 порта G. Затем сбрасывается флаг прерывания
 * от таймера 3.
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
 * @brief Прерывание от таймера 4.
 *
 * Эта функция обрабатывает прерывание от таймера 4. Она отключает таймер, вызывает функцию обработки прерывания
 * для USART4 и сбрасывает флаг прерывания.
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
 * @brief Прерывание от таймера 5.
 *
 * Эта функция обрабатывает прерывание от таймера 5. Она отключает таймер, вызывает функцию обработки прерывания
 * для USART5 и сбрасывает флаг прерывания.
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
 * @brief Прерывание от таймера 6.
 *
 */
void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void)
{
    // T6CONbits.TON = 0;
    if ((--SECOND) == 0) // если переменная(200)-1 секунда равна нулю
    {
        SECOND = 200; // обнуляем
        LED3_TOGGLE;  // переключаем светодиод
        /* ставим флаг модбас мастера */
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
 * @brief Прерывание от таймера 7.
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
 * @brief Прерывание от таймера 9.
 *
 * Эта функция обрабатывает прерывание от таймера 9. Она вызывает функцию управления миганием светодиода
 * или другими действиями с заданной периодичностью. Затем она проверяет, включен ли режим таймаута передачи
 * по Modbus (tm_on) для USART1. Если установлен флаг таймаута передачи (mbm_timeout_counter == 0), уменьшается
 * его значение. Далее сбрасывается флаг таймаута передачи, и если установлен флаг начала мастер-передачи,
 * устанавливается флаг таймаута мастера. В конце сбрасывается флаг прерывания от таймера 9.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void)
{
    // Вызов функции для управления миганием светодиода или другими действиями с заданной периодичностью
    fun_blink_counter();
>>>>>>> dev_branch

    // Проверка, включен ли режим таймаута передачи по Modbus (tm_on)
    if (usart1.mb_status.tm_on == 1)
    {
        // Если установлен флаг таймаута передачи (mbm_timeout_counter == 0), уменьшаем значение
        if (!(usart1.mbm_timeout_counter--))
            ; // Ничего не делаем, пропускаем блок кода

        // Сброс флага таймаута передачи
        usart1.mb_status.tm_on = 0;

        // Если установлен флаг начала мастер-передачи, устанавливаем флаг таймаута мастера
        if (usart1.mb_status.master_start)
            usart1.mb_status.master_timeout_flag = 1;
    }

    // Сброс флага прерывания от таймера 9
    IFS1bits.T9IF = 0;
}

// TX/RX

/**
 * @brief Прерывание от приемника UART5.
 *
 * Эта функция обрабатывает прерывание от приемника UART5. Она снимает флаг прерывания от UART5 RX,
 * устанавливает флаг приема Modbus в структуре usart5, считывает данные из приемного буфера UART5 и сохраняет
 * их в буфере приема. Затем она проверяет, не превышен ли размер буфера приема. Если размер превышен,
 * устанавливается флаг получения Modbus, иначе сбрасывается флаг приема Modbus. Далее инициализируется таймер 5
 * для задержки передачи данных, и снова снимается флаг прерывания от UART5 RX.
 *
 * @param void
 * @return void
 */
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

/**
 * @brief Прерывание от передатчика UART5.
 *
 * Эта функция обрабатывает прерывание от передатчика UART5. Она сбрасывает флаг прерывания передачи UART5
 * и осуществляет передачу данных из буфера отправки. Передача данных происходит, пока буфер передачи не
 * заполнен и пока текущий байт не является последним. Когда количество переданных байт достигает общего
 * количества, устанавливается флаг последнего байта, и прерывание передачи UART5 отключается.
 *
 * @param void
 * @return void
 */
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

/**
 * @brief Прерывание от приемника UART4.
 *
 * Эта функция обрабатывает прерывание от приемника UART4. Она сбрасывает флаг прерывания UART4 приемника
 * и осуществляет прием данных из UART4. Прием данных продолжается, пока в приемном буфере UART4 есть данные.
 * Когда буфер входных данных становится полным, устанавливается флаг получения MODBUS по UART4, а флаг приема
 * MODBUS по UART4 сбрасывается. Затем инициализируется таймер 6 для задержки между кадрами.
 *
 * @param void
 * @return void
 */
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
    tmr_4_init(frame_delay_1, 1, 1); // Инициализация таймера 6 для задержки между кадрами
    IFS5bits.U4RXIF = 0;             // Сброс флага прерывания UART4 приемника
}

/**
 * @brief Прерывание от передатчика UART4.
 *
 * Эта функция обрабатывает прерывание от передатчика UART4. Она сбрасывает флаг прерывания UART4 передатчика
 * и осуществляет передачу данных через UART4. Передача данных продолжается, пока буфер передатчика UART4 не
 * заполнен и не отправлен последний байт. После отправки всех данных из буфера устанавливается флаг последнего
 * байта передачи, и прерывание передачи UART4 отключается.
 *
 * @param void
 * @return void
 */
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

/**
 * @brief Прерывание от приемника UART1.
 *
 * Эта функция обрабатывает прерывание от приемника UART1. Она сбрасывает флаг прерывания UART1 приемника
 * и осуществляет прием данных через UART1. Прием данных продолжается, пока в буфере приемника UART1 есть данные.
 * Если принято максимальное количество байт, устанавливается флаг окончания приема MODBUS для UART1, и прерывание
 * приемника UART1 отключается.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART1_RX_VECTOR, IPL4SRS) U1RXInterrupt(void)
{
    IFS3bits.U1RXIF = 0;                 // Сброс флага прерывания UART1 приемника
    usart1.mb_status.modb_receiving = 1; // Установка флага приема MODBUS для UART1
    while (U1STAbits.URXDA)              // Пока в буфере приемника UART1 есть данные
    {
        usart1.in_buffer[usart1.in_buffer_count++] = U1RXREG; // Чтение данных из буфера приемника UART1
    }
    if (usart1.in_buffer_count >= IN_SIZE1) // Если принято максимальное количество байт
    {
        usart1.mb_status.modb_received = 1;  // Установка флага окончания приема MODBUS для UART1
        usart1.mb_status.modb_receiving = 0; // Сброс флага приема MODBUS для UART1
    }
    tmr_1_init(frame_delay_1, 1, 1); // Инициализация таймера 1 для задержки
    IFS3bits.U1RXIF = 0;             // Сброс флага прерывания UART1 приемника
}

/**
 * @brief Прерывание от передатчика UART1.
 *
 * Эта функция обрабатывает прерывание от передатчика UART1. Она сбрасывает флаг прерывания UART1 передатчика
 * и осуществляет передачу данных через UART1. Передача данных продолжается, пока буфер передатчика UART1 не заполнен
 * и не передан последний байт. После передачи последнего байта отключается прерывание передатчика UART1.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART1_TX_VECTOR, IPL1SRS) U1TXInterrupt(void)
{
    IFS3bits.U1TXIF = 0;                                        // Сброс флага прерывания UART1 передатчика
    while ((!U1STAbits.UTXBF) && (!usart1.mb_status.last_byte)) // Пока буфер передатчика UART1 не заполнен и не передан последний байт
    {
        U1TXREG = usart1.out_buffer[usart1.out_buffer_count++]; // Запись данных из буфера передатчика UART1 в регистр передачи
        if (usart1.out_buffer_count >= (usart1.number_send))    // Если передано максимальное количество байт
        {
            usart1.mb_status.last_byte = 1; // Установка флага последнего байта для UART1
            IEC3bits.U1TXIE = 0;            // Запрет прерываний от UART1 передатчика
        }
    }
    IFS3bits.U1TXIF = 0; // Сброс флага прерывания UART1 передатчика
}

/**
 * @brief Прерывание от приемника UART2.
 *
 * Эта функция обрабатывает прерывание от приемника UART2. Она сбрасывает флаг прерывания UART2 приемника
 * и осуществляет прием данных через UART2. Прием данных продолжается, пока в приемном буфере UART2 есть данные.
 * Если буфер приема UART2 переполнен, устанавливается соответствующий флаг. Также инициализируется таймер 2.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART2_RX_VECTOR, IPL4SRS) U2RXInterrupt(void)
{
    IFS4bits.U2RXIF = 0;                 // Сброс флага прерывания UART2 приемника
    usart2.mb_status.modb_receiving = 1; // Установка флага приема MODBUS для UART2
    while (U2STAbits.URXDA)              // Пока в приемном буфере UART2 есть данные
    {
        usart2.in_buffer[usart2.in_buffer_count++] = U2RXREG; // Запись данных из регистра приема UART2 в буфер приема
    }
    if (usart2.in_buffer_count >= IN_SIZE1) // Если буфер приема UART2 переполнен
    {
        usart2.mb_status.modb_received = 1;  // Установка флага приема MODBUS для UART2
        usart2.mb_status.modb_receiving = 0; // Сброс флага приема MODBUS для UART2
    }
    tmr_2_init(frame_delay_1, 1, 1); // Инициализация таймера 2
    IFS4bits.U2RXIF = 0;             // Сброс флага прерывания UART2 приемника
    //    PORTEbits.RE2 = LATEbits.LATE2 ^ 1; // Управление портом портом E2
}

/**
 * @brief Прерывание от передатчика UART2.
 *
 * Эта функция обрабатывает прерывание от передатчика UART2. Она сбрасывает флаг прерывания UART2 передатчика
 * и осуществляет передачу данных через UART2. Передача данных продолжается, пока буфер передатчика UART2 не заполнен
 * и пока не будет передан последний байт. Когда все данные переданы, устанавливается соответствующий флаг,
 * и прерывание передачи UART2 отключается.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART2_TX_VECTOR, IPL1SRS) U2TXInterrupt(void)
{
    IFS4bits.U2TXIF = 0;                                        // Сброс флага прерывания UART2 передатчика
    while ((!U2STAbits.UTXBF) && (!usart2.mb_status.last_byte)) // Пока буфер передатчика UART2 не заполнен и байт не последний
    {
        U2TXREG = usart2.out_buffer[usart2.out_buffer_count++]; // Запись данных из буфера передачи в регистр передачи UART2
        if (usart2.out_buffer_count >= (usart2.number_send))    // Если достигнут конец данных для передачи
        {
            usart2.mb_status.last_byte = 1; // Установка флага последнего байта для UART2
            IEC4bits.U2TXIE = 0;            // Отключение прерывания передачи для UART2
        }
    }
    IFS4bits.U2TXIF = 0; // Сброс флага прерывания UART2 передатчика
}

/**
 * @brief Прерывание от приемника UART3.
 *
 * Эта функция обрабатывает прерывание от приемника UART3. Она сбрасывает флаг прерывания UART3 приемника
 * и осуществляет прием данных через UART3. Прием данных продолжается, пока буфер приемника UART3 не опустеет.
 * Когда буфер заполняется до максимального размера, устанавливается соответствующий флаг, указывающий на завершение приема.
 * Также инициализируется таймер 7 для задержки между кадрами.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART3_RX_VECTOR, IPL4SRS) U3RXInterrupt(void)
{
    IFS4bits.U3RXIF = 0;                 // Сброс флага прерывания UART3 приемника
    usart3.mb_status.modb_receiving = 1; // Установка флага приема для UART3
    while (U3STAbits.URXDA)              // Пока буфер приемника UART3 не пуст
    {
        usart3.in_buffer[usart3.in_buffer_count++] = U3RXREG; // Запись данных из регистра приемника UART3 в буфер приема
    }
    if (usart3.in_buffer_count >= IN_SIZE1) // Если достигнут максимальный размер буфера приема
    {
        usart3.mb_status.modb_received = 1;  // Установка флага завершения приема для UART3
        usart3.mb_status.modb_receiving = 0; // Сброс флага приема для UART3
    }
    tmr_3_init(frame_delay_1, 1, 1); // Инициализация таймера 7 для задержки между кадрами

    IFS4bits.U3RXIF = 0; // Сброс флага прерывания UART3 приемника
}

/**
 * @brief Прерывание от передатчика UART3.
 *
 * Эта функция обрабатывает прерывание от передатчика UART3. Она сбрасывает флаг прерывания UART3 передатчика
 * и осуществляет передачу данных через UART3. Передача данных продолжается, пока буфер передатчика UART3 не заполнится.
 * Когда передан последний байт данных, устанавливается соответствующий флаг, указывающий на завершение передачи.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_UART3_TX_VECTOR, IPL1SRS) U3TXInterrupt(void)
{
    IFS4bits.U3TXIF = 0;                                        // Сброс флага прерывания UART3 передатчика
    while ((!U3STAbits.UTXBF) && (!usart3.mb_status.last_byte)) // Пока буфер передатчика UART3 не заполнен и последний байт не отправлен
    {
        U3TXREG = usart3.out_buffer[usart3.out_buffer_count++]; // Отправка данных из буфера передачи UART3 в регистр передачи
        if (usart3.out_buffer_count >= (usart3.number_send))    // Если достигнут максимальный размер буфера передачи
        {
            usart3.mb_status.last_byte = 1; // Установка флага последнего байта для UART3
            IEC4bits.U3TXIE = 0;            // Отключение прерывания UART3 передатчика
        }
    }
    IFS4bits.U3TXIF = 0; // Сброс флага прерывания UART3 передатчика
}

/**
 * @brief Прерывание от DMA канала 0.
 *
 * Эта функция обрабатывает прерывание от DMA канала 0. Она считывает флаги прерывания DMA канала 0,
 * выполняет необходимые операции в ответ на установленные флаги прерывания и затем сбрасывает эти флаги.
 *
 * @param void
 * @return void
 */
void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void)
{
    int dmaFlags = DCH0INT & 0xff; // Чтение флагов прерывания DMA канала 0

    // Выполнение прикладных операций в ответ на любой установленный флаг прерывания

    DCH0INTCLR = 0x000000ff; // Сброс флагов прерывания канала DMA 0
    IFS4bits.DMA0IF = 0;     // Обязательно сбрасываем флаги прерывания DMA0
    // перед выходом из обработчика прерывания.
}