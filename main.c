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
            change_mups_strategy_separately(&usart2m);
            control_mups_reley(&usart2m);
            MOPS_S_control(&usart1m);
//            MUPS_S_control(&usart2m);
            mbm_sync = 0;
        }
    stop_uart_tx();
    
    LED_8 = help_strobe;
    }
} 


