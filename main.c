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
    }
}
