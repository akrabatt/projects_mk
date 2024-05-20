#include "define.h"
#include "global.h" 

extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs(struct tag_usart * usart, unsigned char mbs_addres);
extern void close_mb(struct tag_usart * usart);
extern void InitializeSystem(void);
extern unsigned short swapshort(unsigned short data);

int main(void) {
    InitializeSystem();

    help_reset = 1;
    ENAB_RX5; //направление прередачи порта А на прием    == PORTFbits.RF2 = 0	
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

    while (1) {

        mbs(&usart5, 1); // вызов modbus slave usart5 по 5му порту с 1-м адрессом 
        mbs(&usart4, 1); 
        mbs(&usart3, 1); 
        mbs(&usart2, 1); 
        mbs(&usart1, 1); 
        stop_uart_tx_dma();
        //    stop_uart_tx();
        Modbus.Modbus_data.cyl_mask = 20;
        Modbus_sw.Modbus_data.cyl_mask = swapshort(Modbus.Modbus_data.cyl_mask);
    }
}


