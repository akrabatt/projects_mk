#include <xc.h>
#include <sys/attribs.h>    
#include "str.h"
#include "def.h"

tag_usart usart5;

extern int count1, count2;
extern void tmr_1_init();
extern void transmit(void);


void __ISR_AT_VECTOR (_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void) {
    
    if(count1++ == 100){
        PORTAbits.RA1 = LATAbits.LATA1 ^ 1;
        transmit();
        count1 = 0;
    }
    IFS0bits.T1IF = 0; // delete interrupt flag !!!!!
}

void __ISR_AT_VECTOR (_TIMER_2_VECTOR, IPL5SRS) T2Interrupt(void) {
    if(count2++ == 100) {
        PORTBbits.RB11 = LATBbits.LATB11 ^ 1;
        count2 = 0;
    }
    IFS0bits.T2IF = 0;
}

void __ISR_AT_VECTOR (_UART5_RX_VECTOR, IPL4SRS) U5RXInterrupt(void)  {		
    IFS5bits.U5RXIF = 0;    
	usart5.mb_status.modb_receiving = 1;	    	
	while (U5STAbits.URXDA)	{ 
        usart5.in_buffer[usart5.in_buffer_count++] = U5RXREG; 
    }
	if (usart5.in_buffer_count>=IN_SIZE1) {
        usart5.mb_status.modb_received = 1;
        usart5.mb_status.modb_receiving = 0;
    }
	// tmr_1_init(frame_delay_1, 1, 1);
    // void timer_1_init(void);
	IFS5bits.U5RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART5_TX_VECTOR, IPL4SRS) U5TXInterrupt(void)  {	
	IFS5bits.U5TXIF=0; 	
	while ((!U5STAbits.UTXBF)&&(!usart5.mb_status.last_byte)) {		//copy if buff  isn't full and byte is not last
		U5TXREG = usart5.out_buffer[usart5.out_buffer_count++];
		if (usart5.out_buffer_count >= (usart5.number_send)) {
            usart5.mb_status.last_byte = 1;
            IEC5bits.U5TXIE = 0;
        }
	}
	IFS5bits.U5TXIF=0;
}