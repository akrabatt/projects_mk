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
        
        if ( mbm_sync ==  1 ) {  
            change_mups_strategy_separately(&usart5m);
            control_mups_reley(&usart5m);
            mbm_sync = 0;
    }
    stop_uart_tx();
    PORTGbits.RG7 = help_strobe;
    LED_8 = help_strobe;
    }
} 


