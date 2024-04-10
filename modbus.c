#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include <p32xxxx.h>
#include "def.h"
#include "str.h"

extern tag_usart usart5;

void stop_uart_tx(void)
{
    if (usart5.mb_status.tx_mode == INT_type ){
        if ((usart5.mb_status.modb_transmiting == 1)&&(U5STAbits.TRMT)&&(IEC5bits.U5TXIE == 0)) {
            usart5.mb_status.last_byte=0;
    		usart5.mb_status.modb_received=0;
        	usart5.mb_status.modb_receiving=0;
            usart5.in_buffer_count=0;
    		usart5.mb_status.modb_transmiting=0;
        	IFS5bits.U5RXIF = 0; 
            ENAB_RX5;
        	IEC5bits.U5RXIE = 1;			//disable RX interrupt
        }
        if (U5STAbits.OERR||U5STAbits.FERR)	{
			U5STAbits.OERR=0;
		}        
    }
	if (U4STAbits.OERR||U4STAbits.FERR)	{U4STAbits.OERR=0;}
}

void start_tx_usart (void)
{
	IEC3bits.U1RXIE = 0;			//disable RX interrupt
	usart5.mb_status.modb_transmiting=1;
	usart5.out_buffer_count=0;
	usart5.mb_status.last_byte=0;
	ENAB_TX5;
	IEC3bits.U1TXIE = 1;			//enable TX interrupt
}

void transmit (void) 
{
	usart5.out_buffer[0] = 11;
	usart5.out_buffer[1] = 22;
	usart5.out_buffer[2] = 33;
	usart5.number_send=3;
	start_tx_usart();
}