#include <stdio.h>
#include <string.h>
#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "global.h"
#include "define.h"


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
            change_mups_strategy_separately(&usart2m);
            control_mups_reley(&usart2m);
            // u1
            MOPS_S_control(&usart1m);
            // u3
//            mbm_16(&usart4m, 1, 0, 8, _530_board_normal_mops, 115200);
            board_530_mode_common(&usart4m);
            // u5
            board_530_mode_common(&usart5m);
            
            mbm_sync = 0;
        }
    stop_uart_tx();
    
    LED_8 = help_strobe;
    }
} 


