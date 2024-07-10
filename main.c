/*
** main.c
/** INCLUDES ******************************************************************/

#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
//#include "extern.h"
#include "global.h"
#include "define.h"

extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs (struct tag_usart * usart, unsigned char mbs_addres);
extern void close_mbs (struct tag_usart * usart);
extern void pid_control(float Kp, float Kd, float Ki);
//extern void load_mem (void);
extern void load_config (void);
extern void mbm_03 (struct tag_usart * usart, unsigned char mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short * dest, unsigned long speed);
extern void mbm_03_str (struct tag_usartm * usart, unsigned char mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short * dest, unsigned long speed);
extern void MOPS_control (struct tag_usartm * usart);
extern void InitializeSystem(void);

/** LOCAL MACROS **************************************************************/

extern void InitializeSystem(void);


/** main() ********************************************************************/

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
    
    mbs (&usart4, 1);				// порт  1
    stop_uart_tx_dma();   
//    mbs (&usart4, 1);				//  4
//    mbm_03_str(&usart5m, 2, 200, 100, (unsigned short*) &MUPS_arr[1], 115200);
//    mbm_03_str(&usart5m, 2, 200, 100, (unsigned short*) &MUPS_arr[1], 115200);
//    stop_uart_tx();
//    MUPS_control (&usart5m);
    if ( mbm_sync ==  1 ) {  
//        mbm_03 (&usart5, 1, 0, 28, (unsigned short * ) &MOPS_arr [1], 115200);
//        mbm_03_str (&usart5m, 1, 0, 108, (unsigned short * ) &MOPS_arr [1], 115200);
//        MOPS_control (&usart5m );
//        MUPS_control (&usart5m);
        
//        MUPS_S_control (&usart5m);
        unsigned short mups_strategy[4] = {3, 3, 3, 3};
        mbm_16(&usart5m, 2, 212, 4, (unsigned short *)mups_strategy, 115200);
//        mbm_16(&usart5m, 1, 212, 4, (unsigned short *)mups_strategy, 115200);
//        MOPS_S_control (&usart5m);
        mbm_sync = 0;
        }
    stop_uart_tx();
    PORTGbits.RG7 = help_strobe;

    LED_8 = help_strobe;
    }

} 


