

#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "define.h"
#include "extern.h"

unsigned short send_dma;


//void __ISR_AT_VECTOR (_ADC_VECTOR, IPL4SRS) ADCInterrupt(void)  {	LED_7_ON; ADC_interrupt_F ();  LED_7_OFF; IFS1bits.ADCIF = 0; ADCCON3bits.GSWTRG = 0; }  
//void __ISR_AT_VECTOR (_ADC_DATA10_VECTOR, IPL4SRS) ADC10Interrupt(void)  {	LED_8 = 1; ADC_interrupt_F (); IFS1bits.ADCIF = 0; LED_8 = 0; IFS2bits.ADCD10IF = 0; }  
//void __ISR_AT_VECTOR (_ADC_DATA32_VECTOR, IPL4SRS) ADC32Interrupt(void)  {	LED_8 = 1; ADC_interrupt_F (); IFS1bits.ADCIF = 0; LED_8 = 0; IFS2bits.ADCD32IF = 0; } 


/*timers interrupts*/
void __ISR_AT_VECTOR (_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void)   {T1CONbits.TON=0; TInterrupt_m(&usart1m); U1_LED_RX_OFF; IFS0bits.T1IF = 0;}
void __ISR_AT_VECTOR (_TIMER_2_VECTOR, IPL4SRS) T2Interrupt(void)   {T2CONbits.TON=0; TInterrupt_m(&usart2m); U2_LED_RX_OFF; IFS0bits.T2IF = 0;}
void __ISR_AT_VECTOR (_TIMER_3_VECTOR, IPL4SRS) T3Interrupt(void)   {T3CONbits.TON=0; /*U3_LED_RX_TOGGLE*/ U3_LED_RX_OFF; T3Interrupt_(&usart3); IFS0bits.T3IF = 0;}
void __ISR_AT_VECTOR (_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void)   {T4CONbits.TON=0; TInterrupt_m(&usart4m); IFS0bits.T4IF = 0;}
void __ISR_AT_VECTOR (_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void)   {T5CONbits.TON=0; TInterrupt_m(&usart5m); IFS0bits.T5IF = 0;}

//void __ISR_AT_VECTOR (_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void)   {Timer6Interrupt(); IFS0bits.T6IF = 0;}
//void __ISR_AT_VECTOR (_TIMER_7_VECTOR, IPL4SRS) T7Interrupt(void)   {Timer7Interrupt(); IFS1bits.T7IF = 0;}

void __ISR_AT_VECTOR (_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void)   
{     
    IFS1bits.T9IF = 0;
    
    // counter for modbus master start
    counters ();
    
    // up sync flag for main
    mbm_sync = 1;
    
    // starting 16 function u5-1
    if(++usart5m.mbm16_counter_start >= 100)
    {
        usart5m.mbm16_counter_start = 0;
        usart5m.mb_status.start16 = 1;
    }
    if(++usart4m.mbm16_counter_start >= 100)
    {
        usart4m.mbm16_counter_start = 0;
        usart4m.mb_status.start16 = 1;
    }
    if(++usart2m.mbm16_counter_start >= 100)
    {
        usart2m.mbm16_counter_start = 0;
        usart2m.mb_status.start16 = 1;
    }
    if(++usart1m.mbm16_counter_start >= 100)
    {
        usart1m.mbm16_counter_start = 0;
        usart1m.mb_status.start16 = 1;
    }
}    


/*interrupts tx-rx*/

//5
void __ISR_AT_VECTOR (_UART5_RX_VECTOR, IPL4SRS) U5RXInterrupt(void)  
{		
    IFS5bits.U5RXIF = 0;    
	usart5m.mb_status.modb_receiving = 1;	    	
	while (U5STAbits.URXDA)	{ usart5m.in_buffer[usart5m.in_buffer_count++] = U5RXREG; }
	if (usart5m.in_buffer_count>=IN_SIZE1) {usart5m.mb_status.modb_received = 1; usart5m.mb_status.modb_receiving = 0;}
	tmr_5_init( frame_delay_1, 1, 1);
	IFS5bits.U5RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART5_TX_VECTOR, IPL4SRS) U5TXInterrupt(void)  
{	
	IFS5bits.U5TXIF=0; 	
	while ((!U5STAbits.UTXBF)&&(!usart5m.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
	{
		U5TXREG = usart5m.out_buffer[usart5m.out_buffer_count++];
		if (usart5m.out_buffer_count >= (usart5m.number_send)) {usart5m.mb_status.last_byte = 1;	IEC5bits.U5TXIE = 0;}
	}
	IFS5bits.U5TXIF=0;
}

//4
void __ISR_AT_VECTOR (_UART4_RX_VECTOR, IPL4SRS) U4RXInterrupt(void)  
{		
    IFS5bits.U4RXIF = 0;    
	usart4m.mb_status.modb_receiving = 1;	    	
	while (U4STAbits.URXDA)	{ usart4m.in_buffer[usart4m.in_buffer_count++] = U4RXREG; }
	if (usart4m.in_buffer_count>=IN_SIZE1) { usart4m.mb_status.modb_received = 1; usart4m.mb_status.modb_receiving = 0;}
	tmr_4_init( frame_delay_1, 1, 1);
	IFS5bits.U4RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART4_TX_VECTOR, IPL4SRS) U4TXInterrupt(void)  
{	
	IFS5bits.U4TXIF=0; 	
	while ((!U4STAbits.UTXBF)&&(!usart4m.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
	{
		U4TXREG = usart4m.out_buffer[usart4m.out_buffer_count++];
		if (usart4m.out_buffer_count >= (usart4m.number_send)) {usart4m.mb_status.last_byte = 1;	IEC5bits.U4TXIE = 0;}
	}
	IFS5bits.U4TXIF=0;
}

//3
void __ISR_AT_VECTOR (_UART3_RX_VECTOR, IPL4SRS) U3RXInterrupt(void)  
{		
    IFS4bits.U3RXIF = 0;
    U3_LED_RX_ON;
	usart3.mb_status.modb_receiving = 1;	    	
	while (U3STAbits.URXDA)	{ usart3.in_buffer[usart3.in_buffer_count++] = U3RXREG; }
	if (usart3.in_buffer_count>=IN_SIZE1) { usart3.mb_status.modb_received = 1; usart3.mb_status.modb_receiving = 0;}
	tmr_3_init( frame_delay_1, 1, 1);
	IFS4bits.U3RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART3_TX_VECTOR, IPL4SRS) U3TXInterrupt(void)  
{	
	IFS4bits.U3TXIF=0; 	
	while ((!U3STAbits.UTXBF)&&(!usart3.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
	{
		U3TXREG = usart3.out_buffer[usart3.out_buffer_count++];
		if (usart3.out_buffer_count >= (usart3.number_send)) {usart3.mb_status.last_byte = 1;	IEC4bits.U3TXIE = 0;}
	}
	IFS4bits.U3TXIF=0;
}
 
//2
void __ISR_AT_VECTOR (_UART2_RX_VECTOR, IPL4SRS) U2RXInterrupt(void)  
{		
    IFS4bits.U2RXIF = 0;  
    U2_LED_RX_ON;
	usart2m.mb_status.modb_receiving = 1;	    	
	while (U2STAbits.URXDA)	{ usart2m.in_buffer[usart2m.in_buffer_count++] = U2RXREG; /*U2_LED_RX_TOGGLE*/;}
	if (usart2m.in_buffer_count>=IN_SIZE1) { usart2m.mb_status.modb_received = 1; usart2m.mb_status.modb_receiving = 0;}
	tmr_2_init( frame_delay_1, 1, 1);
	IFS4bits.U2RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART2_TX_VECTOR, IPL4SRS) U2TXInterrupt(void)  
{	
	IFS4bits.U2TXIF=0; 
    U2_LED_TX_TOGGLE;
	while ((!U2STAbits.UTXBF)&&(!usart2m.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
	{
		U2TXREG = usart2m.out_buffer[usart2m.out_buffer_count++];
		if (usart2m.out_buffer_count >= (usart2m.number_send)) {usart2m.mb_status.last_byte = 1;	IEC4bits.U2TXIE = 0;}
	}
	IFS4bits.U2TXIF=0;
}

//1
void __ISR_AT_VECTOR (_UART1_RX_VECTOR, IPL4SRS) U1RXInterrupt(void)  
{		
    IFS3bits.U1RXIF = 0;  
    U1_LED_RX_ON;
	usart1m.mb_status.modb_receiving = 1;	    	
	while (U1STAbits.URXDA)	{ usart1m.in_buffer[usart1m.in_buffer_count++] = U1RXREG; /*U1_LED_RX_TOGGLE*/;}
	if (usart1m.in_buffer_count>=IN_SIZE1) { usart1m.mb_status.modb_received = 1; usart1m.mb_status.modb_receiving = 0;}
	tmr_1_init( frame_delay_1, 1, 1);
	IFS3bits.U1RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART1_TX_VECTOR, IPL4SRS) U1TXInterrupt(void)  
{	
	IFS3bits.U1TXIF=0; 
    U1_LED_TX_TOGGLE;
	while ((!U1STAbits.UTXBF)&&(!usart1m.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
	{
		U1TXREG = usart1m.out_buffer[usart1m.out_buffer_count++];
		if (usart1m.out_buffer_count >= (usart1m.number_send)) {usart1m.mb_status.last_byte = 1;	IEC3bits.U1TXIE = 0;}
	}
	IFS3bits.U1TXIF=0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void)
{
int dmaFlags=DCH0INT&0xff; // read the interrupt flags

//perform application specific operations in response to any interrupt flag set

DCH0INTCLR=0x000000ff;      // clear the DMA channel interrupt flags
IFS4bits.DMA0IF = 0;        // Be sure to clear the DMA0 interrupt flags
// before exiting the service routine.
}
