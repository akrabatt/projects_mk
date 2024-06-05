/*
** main.c
/** INCLUDES ******************************************************************/

#include <xc.h>
#include <sys/attribs.h> /* contains __ISR() Macros */
// #include "extern.h"
#include "global.h"
#include "define.h"

extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs(struct tag_usart *usart, unsigned char mbs_addres);
extern void close_mb(struct tag_usart *usart);
extern void pid_control(float Kp, float Kd, float Ki);
// extern void load_mem (void);
extern void load_config(void);
extern void mbm_03(struct tag_usart *usart, unsigned char mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short *dest, unsigned long speed);
// extern void pid (void);
// extern void regulator (float Kp, float Kd, float Ki);

/** VARIABLES *****************************************************************/

/** LOCAL MACROS **************************************************************/

extern void InitializeSystem(void);

/** LOCAL PROTOTYPES ********************************************************/

// void InitializeSystem(void);            // Initialize hardware and global variables

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
    //    load_config ();
    while (1)

    {
        mbs(&usart4, 1); // порт  1
        stop_uart_tx_dma();
        //    mbs (&usart4, 1);				//  4
        mbm_03(&usart5, 1, 0, 28, (unsigned short *)&MOPS_arr[1], 115200);
        //    stop_uart_tx();
        PORTGbits.RG7 = help_strobe;

        LED_8 = help_strobe;
    }
}
