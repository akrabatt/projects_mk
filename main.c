#include <xc.h>
#include <sys/attribs.h> /* contains __ISR() Macros */
// #include "extern.h"
#include "global.h"
#include "define.h"

int main(void)
{
    InitializeSystem();

    help_reset = 1;
    ENAB_RX5;
    ENAB_RX4;
    //    TAP_ON = 1;
    //    close_mbs ( &usart1);
    //    usart5.mb_status.tx_mode = DMA_type;
    usart4.mb_status.tx_mode = DMA_type;
    usart5.mb_status.tx_mode = INT_type;
    usart5m.mb_status.tx_mode = INT_type;
    //    usart4.mb_status.tx_mode = INT_type;

    //    load_config ();
    //    IC1CONbits.ON = 1;
    //    IC6CONbits.ON = 1;
    //    load_config ();
    while (1)

<<<<<<< HEAD
        mbs(&usart3, 1);
        stop_uart_tx_dma();
        mbm_03(&usart1, 1, 0, 28, &MOPS_arr[0], 115200); // мастер запрос
//        mbm_03(&usart2, 2, 0, 28, &MOPS_arr[1], 5); // мастер запрос
//        mbm_03(&usart4, 4, 0, 28, &MOPS_arr[2], 5); // мастер запрос
//        mbm_03(&usart5, 5, 0, 28, &MOPS_arr[3], 5); // мастер запрос
        //    stop_uart_tx();
//        Modbus.Modbus_data.cyl_mask = 50;
//        Modbus_sw.Modbus_data.cyl_mask = swapshort(Modbus.Modbus_data.cyl_mask);
        //        LED3_TOGGLE;
//        MOPS_arr[0].info[0] = swapshort(22);
//        MOPS_arr[1].info[0] = swapshort(111);
//        MOPS_arr[8].info[0] = swapshort(88);
=======
    {
        mbs(&usart4, 1); // порт  1
        stop_uart_tx_dma();
        //    mbs (&usart4, 1);				//4
        if (mbm_sync == 1)
        {
            // mbm_03 (&usart5, 1, 0, 28, (unsigned short * ) &MOPS_arr [1], 115200);
            // mbm_03_str(&usart5m, 1, 0, 108, (unsigned short *)&MOPS_arr[1], 115200);
            MM_control(&usart5m);
            mbm_sync = 0;
        }
        stop_uart_tx();
        PORTGbits.RG7 = help_strobe;

        LED_8 = help_strobe;
>>>>>>> origin/feature_mbm_03
    }
}
