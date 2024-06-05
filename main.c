#include <xc.h>
#include <sys/attribs.h> /* contains __ISR() Macros */
// #include "extern.h"
#include "global.h"
#include "define.h"

// добавляем внешние фукнции
extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs(struct tag_usart *usart, unsigned char mbs_addres);
extern void mbm_03(struct tag_usart *usart, unsigned char mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short *dest, unsigned long speed);
extern void InitializeSystem(void);

int main(void)
{
    InitializeSystem(); // инициализируем систему
    ENAB_RX5;
    ENAB_RX4;
    usart4.mb_status.tx_mode = DMA_type; // порт 4 слэйв, работа через ДМА
    usart5.mb_status.tx_mode = INT_type; // порт 5 мастер, работа через прерывания
    while (1)
    {
        mbs(&usart4, 1);    // запускаем порт 4 слэйв
        stop_uart_tx_dma(); // после того как передача закончена, перводит на прием

        mbm_03(&usart5, 1, 0, 28, (unsigned short *)&MOPS_arr[1], 115200); // запускаем на 5 порту мастера 3-й функции
        stop_uart_tx();                                                    // сбрасываем все и переводим на прием

        // для вотчдога
        // PORTGbits.RG7 = help_strobe;

        // мигалка
        LED_8 = help_strobe;
    }
}
