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
extern void close_mb (struct tag_usart * usart);
extern void pid_control(float Kp, float Kd, float Ki);
//extern void load_mem (void);
extern void load_config (void);
//extern void measure (void);
//extern void pid (void);
//extern void regulator (float Kp, float Kd, float Ki);



/** VARIABLES *****************************************************************/


/** LOCAL MACROS **************************************************************/

extern void InitializeSystem(void);

/** LOCAL PROTOTYPES ********************************************************/

//void InitializeSystem(void);            // Initialize hardware and global variables

/** main() ********************************************************************/

int main(void)
{
    InitializeSystem();

    help_reset = 1;
    ENAB_RX5;
    ENAB_RX4;
//    TAP_ON = 1;
//    close_mb ( &usart1);
    usart5.mb_status.tx_mode = DMA_type;
    usart4.mb_status.tx_mode = DMA_type;
//    usart1.mb_status.tx_mode = INT_type;
//    usart4.mb_status.tx_mode = INT_type;
    
//    load_config ();
//    IC1CONbits.ON = 1; 
//    IC6CONbits.ON = 1; 
    IC3CONbits.ON = 1; 
    IC4CONbits.ON = 1; 
    IC7CONbits.ON = 1; 
    IC8CONbits.ON = 1; 
//    load_config ();   
    while(1)

    {
    mbs (&usart5, 1);				// порт  1
    stop_uart_tx_dma();   
    mbs (&usart4, 1);				//  4
//    stop_uart_tx();
    PORTGbits.RG7 = help_strobe & help_reset;
    if (start_ctrl == 1)   { start_ctrl = 0;   main_control ();   }
    if (start_pid_reg == 1) {start_pid_reg = 0; pid_control(MB_conf.CV_KP, MB_conf.CV_KD, MB_conf.CV_KI);}
    
    LED_8 = help_strobe & help_reset;
    }

} 


