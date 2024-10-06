#include <stdio.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "global.h"
#include "define.h"

// main
int main(void)
{
    InitializeSystem();
    while(1)
    {
        mbs (&usart3, 1);
        stop_uart_tx_dma();   
        if ( mbm_sync ==  1 ) 
        {  
            // u2
//            change_mups_strategy_separately(&usart2m);
//            control_mups_reley(&usart2m);
            mups_service_check(&usart4m, &usart2m, &usart5m);
//            MUPS_S_control_flag(&usart2m, &iiii);
//            MOPS_S_control(&usart1m);
            // u1
//            MOPS_S_control(&usart1m);
            // u4
//            board_530_mode_common(&usart4m);
            // u5
//            board_530_mode_common(&usart5m);
//            mops_service_check(&usart4m, &usart5m, &usart1m);
            
            mbm_sync = 0;
        }
    stop_uart_tx();
    
    LED_8 = help_strobe;
    }
} 


