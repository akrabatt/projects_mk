

#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "define.h"
#include "extern.h"
//#include "global.h"
//#include "global.h"



extern void tmr_1_init(unsigned short T1_delay, unsigned short TMR1_IE, unsigned  short  TMR1_ON);
extern void T1Interrupt_(struct tag_usart * usart);
extern void T5Interrupt_(struct tag_usart * usart);
extern void T4Interrupt_(struct tag_usart * usart);
extern void TInterrupt_(struct tag_usart * usart);
extern void TInterrupt_m(struct tag_usartm * usart);

extern void mbs (struct tag_usart * usart, unsigned char mbs_addres, union tag_direct * dir);
extern void DMA_uni ( struct tag_usart * usart, unsigned short cnt, unsigned short on, unsigned short force);
extern void test_uart_dma(void);
extern void counters (void);
extern void motor_control (void);
extern void pid_control(float Kp, float Kd, float Ki);
extern void ADC_data_store (void);

extern void ADC_interrupt_F (void);
extern void ADC_dma_store (void);
extern void IC1Interrupt_(void);
extern void IC6Interrupt_(void);
extern void Timer6Interrupt(void);
extern void Timer7Interrupt(void);
extern void ignit_stop (void) ;
extern void IC3Int3527 (void) ;
extern void IC4Int3527 (void) ;  
extern void IC7Int (void) ;
extern void IC8Int (void) ;
extern void IC7_measure(void);  
extern void IC8_measure(void);  
extern void IC3_measure(void);  
extern void mbm_timeout_control(struct tag_usart *usart);  

unsigned short send_dma;


//void __ISR_AT_VECTOR (_ADC_VECTOR, IPL4SRS) ADCInterrupt(void)  {	LED_7_ON; ADC_interrupt_F ();  LED_7_OFF; IFS1bits.ADCIF = 0; ADCCON3bits.GSWTRG = 0; }  

//void __ISR_AT_VECTOR (_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void)   {  IFS0bits.T5IF = 0; }

//void __ISR_AT_VECTOR (_ADC_DATA10_VECTOR, IPL4SRS) ADC10Interrupt(void)  {	LED_8 = 1; ADC_interrupt_F (); IFS1bits.ADCIF = 0; LED_8 = 0; IFS2bits.ADCD10IF = 0; }  

//void __ISR_AT_VECTOR (_ADC_DATA32_VECTOR, IPL4SRS) ADC32Interrupt(void)  {	LED_8 = 1; ADC_interrupt_F (); IFS1bits.ADCIF = 0; LED_8 = 0; IFS2bits.ADCD32IF = 0; } 

void __ISR_AT_VECTOR (_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void)   {T1CONbits.TON=0; T1Interrupt_(&usart1); IFS0bits.T1IF = 0;}
void __ISR_AT_VECTOR (_TIMER_2_VECTOR, IPL4SRS) T2Interrupt(void)   {T2CONbits.TON=0; T2Interrupt_(&usart2); IFS0bits.T2IF = 0;}
void __ISR_AT_VECTOR (_TIMER_3_VECTOR, IPL4SRS) T3Interrupt(void)   {T3CONbits.TON=0; T3Interrupt_(&usart3); IFS0bits.T3IF = 0;}
void __ISR_AT_VECTOR (_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void)   {T4CONbits.TON=0; TInterrupt_(&usart4); IFS0bits.T4IF = 0;}
void __ISR_AT_VECTOR (_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void)   {T5CONbits.TON=0; TInterrupt_m(&usart5m); IFS0bits.T5IF = 0;}

//void __ISR_AT_VECTOR (_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void)   {Timer6Interrupt(); IFS0bits.T6IF = 0;}

//void __ISR_AT_VECTOR (_TIMER_7_VECTOR, IPL4SRS) T7Interrupt(void)   {Timer7Interrupt(); IFS1bits.T7IF = 0;}

void __ISR_AT_VECTOR (_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void)   {     
    IFS1bits.T9IF = 0;
    counters ();  
    mbm_sync = 1;
    
    if(++usart5m.mbm16_counter_start >= 100)
    {
        usart5m.mbm16_counter_start = 0;
        usart5m.mb_status.start16 = 1;
    }
//    mbm_timeout_control(&usart4);
//    mbm_timeout_control(&usart5);
    }    


void __ISR_AT_VECTOR (_UART5_RX_VECTOR, IPL4SRS) U5RXInterrupt(void)  {		IFS5bits.U5RXIF = 0;    
	usart5m.mb_status.modb_receiving = 1;	    	
	while (U5STAbits.URXDA)	{ usart5m.in_buffer[usart5m.in_buffer_count++] = U5RXREG; }
	if (usart5m.in_buffer_count>=IN_SIZE1) { usart5m.mb_status.modb_received = 1; usart5m.mb_status.modb_receiving = 0;}
	tmr_5_init( frame_delay_1, 1, 1);
	IFS5bits.U5RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART5_TX_VECTOR, IPL4SRS) U5TXInterrupt(void)  {	
	IFS5bits.U5TXIF=0; 	
	while ((!U5STAbits.UTXBF)&&(!usart5m.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
		{
		U5TXREG = usart5m.out_buffer[usart5m.out_buffer_count++];
		if (usart5m.out_buffer_count >= (usart5m.number_send))	{	usart5m.mb_status.last_byte = 1;	IEC5bits.U5TXIE = 0;	}
		}
	IFS5bits.U5TXIF=0;
}

void __ISR_AT_VECTOR (_UART4_RX_VECTOR, IPL4SRS) U4RXInterrupt(void)  {		IFS5bits.U4RXIF = 0;    
	usart4.mb_status.modb_receiving = 1;	    	
	while (U4STAbits.URXDA)	{ usart4.in_buffer[usart4.in_buffer_count++] = U4RXREG; }
	if (usart4.in_buffer_count>=IN_SIZE1) { usart4.mb_status.modb_received = 1; usart4.mb_status.modb_receiving = 0;}
	tmr_4_init( frame_delay_1, 1, 1);
	IFS5bits.U4RXIF = 0;     
}

void __ISR_AT_VECTOR (_UART4_TX_VECTOR, IPL4SRS) U4TXInterrupt(void)  {	
	IFS5bits.U4TXIF=0; 	
	while ((!U4STAbits.UTXBF)&&(!usart4.mb_status.last_byte))		//copy if buff  isn't full and byte is not last
		{
		U4TXREG = usart4.out_buffer[usart4.out_buffer_count++];
		if (usart4.out_buffer_count >= (usart4.number_send))	{	usart4.mb_status.last_byte = 1;	IEC5bits.U4TXIE = 0;	}
		}
	IFS5bits.U4TXIF=0;
}


 
void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void)
{
int dmaFlags=DCH0INT&0xff; // read the interrupt flags

//perform application specific operations in response to any interrupt flag set

DCH0INTCLR=0x000000ff;      // clear the DMA channel interrupt flags
IFS4bits.DMA0IF = 0;        // Be sure to clear the DMA0 interrupt flags
// before exiting the service routine.
}


/* *****************************************************************************
 End of File
 */
