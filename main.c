#include <stdio.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
//#include "extern.h"
#include "global.h"
#include "define.h"


int main(void)
{
    InitializeSystem();
    help_reset = 1;
    ENAB_RX5;
    ENAB_RX4;
//    usart5m.mb_status.tx_mode = DMA_type;
//    usart5.mb_status.tx_mode = DMA_type;
    usart4.mb_status.tx_mode = DMA_type;
    usart5.mb_status.tx_mode = INT_type;
    usart5m.mb_status.tx_mode = INT_type;
//    usart4.mb_status.tx_mode = INT_type;
//    load_config ();
//    IC1CONbits.ON = 1; 
//    IC6CONbits.ON = 1; 
//    load_config ();   
    while(1)
    {
        mbs (&usart4, 1);				// порт  4
        stop_uart_tx_dma();   
        //    mbm_03_str(&usart5m, 2, 200, 100, (unsigned short*) &MUPS_arr[1], 115200);
        //    stop_uart_tx();
        //    MUPS_control (&usart5m);
        if ( mbm_sync ==  1 ) {  
        //        mbm_03 (&usart5, 1, 0, 28, (unsigned short * ) &MOPS_arr [1], 115200);
        //        mbm_03_str (&usart5m, 1, 0, 108, (unsigned short * ) &MOPS_arr [1], 115200);
        //        MOPS_S_control (&usart5m);
//        MUPS_S_control (&usart5m);
//        memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy));
//        mbm_16(&usart5m, 2, 212, 4, mups_strategy, 115200);
//            change_mups_strategy(1, 1);
            change_mups_strategy_wp(&usart5m);
            mbm_sync = 0;
    }
    stop_uart_tx();
    PORTGbits.RG7 = help_strobe;
    LED_8 = help_strobe;
    }
} 


