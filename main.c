#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
//#include "extern.h"
#include "global.h"
#include "define.h"

extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs(struct tag_usart * usart, unsigned char mbs_addres);
extern void close_mb(struct tag_usart * usart);
extern void pid_control(float Kp, float Kd, float Ki);
//extern void load_mem (void);
extern void load_config(void);
//extern void measure (void);
//extern void pid (void);
//extern void regulator (float Kp, float Kd, float Ki);
extern void InitializeSystem(void);

int main(void) {
    InitializeSystem();

    help_reset = 1;
    ENAB_RX5; //направление прередачи порта А на прием    == PORTFbits.RF2 = 0	
    ENAB_RX4; // тоже самое но для другого интерфейса

    /* режим работы usart  по ДМА */
    usart5.mb_status.tx_mode = DMA_type;
    usart4.mb_status.tx_mode = DMA_type;
    usart3.mb_status.tx_mode = DMA_type;
    usart2.mb_status.tx_mode = DMA_type;
    usart1.mb_status.tx_mode = DMA_type;
    /* режим работы по прерываниям */
    // usart1.mb_status.tx_mode = INT_type;
    // usart4.mb_status.tx_mode = INT_type;
    // load_config ();

    while (1) {

        mbs(&usart5, 1); // вызов modbus slave usart5 по 5му порту с 1-м адрессом 
        stop_uart_tx_dma();
        mbs(&usart4, 1); //  4
        //    stop_uart_tx();
        PORTGbits.RG7 = help_strobe & help_reset; //мигалка и лампочка вотчдог

        if (start_ctrl == 1) {
            start_ctrl = 0;
            main_control();
        }
        LED_8 = help_strobe & help_reset;
    }

}


