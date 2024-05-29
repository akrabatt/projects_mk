#include "define.h"
#include "global.h"

extern void stop_uart_tx(void);                                     // стоп юсарт
extern void stop_uart_tx_dma(void);                                 // стоп юсарт дма
extern void mbs(struct tag_usart *usart, unsigned char mbs_addres); // модбас слэйв
extern void close_mb(struct tag_usart *usart);                      // закрываем модбас
extern void InitializeSystem(void);                                 // инициализация системы
extern unsigned short swapshort(unsigned short data);               // свап

/* объявляем массив экземпляров объединение для МОПСа */
union tag_MOPS MOPS_arr[10]; // создадим массив структур

int main(void)
{
    InitializeSystem(); // инициализируем систему

    help_reset = 1;
    ENAB_RX5; // направление прередачи порта А на прием    == PORTFbits.RF2 = 0
    ENAB_RX4; // тоже самое но для другого интерфейса
    ENAB_RX3; // тоже самое но для другого интерфейса
    ENAB_RX2; // тоже самое но для другого интерфейса
    ENAB_RX1; // тоже самое но для другого интерфейса

    /* режим работы usart  по ДМА */
    usart5.mb_status.tx_mode = DMA_type;
    usart4.mb_status.tx_mode = DMA_type;
    usart3.mb_status.tx_mode = DMA_type;
    usart2.mb_status.tx_mode = DMA_type;
    usart1.mb_status.tx_mode = DMA_type;
    /* режим работы по прерываниям */
    // usart1.mb_status.tx_mode = INT_type;
    // usart4.mb_status.tx_mode = INT_type;

    while (1)
    {

        mbm_03(&usart1, 1, 0, 28, &MOPS_arr[0], 5); // мастер запрос
        mbm_03(&usart2, 2, 0, 28, &MOPS_arr[1], 5); // мастер запрос
        mbm_03(&usart4, 4, 0, 28, &MOPS_arr[2], 5); // мастер запрос
        mbm_03(&usart5, 5, 0, 28, &MOPS_arr[3], 5); // мастер запрос
        mbs(&usart3, 1);
        stop_uart_tx_dma();
        //    stop_uart_tx();
        Modbus.Modbus_data.cyl_mask = 50;
        Modbus_sw.Modbus_data.cyl_mask = swapshort(Modbus.Modbus_data.cyl_mask);
        //        LED3_TOGGLE;
    }
}
