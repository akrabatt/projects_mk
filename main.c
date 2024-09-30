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
//            change_mups_strategy_separately(&usart2m);
//            control_mups_reley(&usart2m);
//            if(conf_stand.stand_commands.mops_diagnostics_in_progress == 0 && conf_stand_sw.stand_commands.mops_diagnostics_in_progress == 0)
//            {
//                mups_service_check(&usart4m, &usart2m, &usart5m);
//            }
//            mups_service_check(&usart4m, &usart1m, &usart5m);
//            MUPS_S_control_flag(&usart2m, &iiii);
//            MOPS_S_control(&usart1m);
            // u1
//            MOPS_S_control(&usart1m);
            // u4
//            board_530_mode_common(&usart4m);
            // u5
//            board_530_mode_common(&usart5m);
//            if(conf_stand.stand_commands.mups_diagnostics_in_progress == 0 && conf_stand_sw.stand_commands.mups_diagnostics_in_progress == 0)
//            {
                mops_service_check(&usart4m, &usart5m, &usart1m);
//            }
            
            mbm_sync = 0;
        }
    stop_uart_tx();
    
    LED_8 = help_strobe;
    }
} 


