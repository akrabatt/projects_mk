

#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "define.h"
#include "extern.h"



extern void tmr_1_init(unsigned short T1_delay, unsigned short TMR1_IE, unsigned short TMR1_ON);
extern void T1Interrupt_(struct tag_usart * usart);
extern void T5Interrupt_(struct tag_usart * usart);
extern void T9Interrupt_(struct tag_usart * usart);
extern void mbs(struct tag_usart * usart, unsigned char mbs_addres, union tag_direct * dir);
extern void DMA_uni(struct tag_usart * usart, unsigned short cnt, unsigned short on, unsigned short force);
extern void test_uart_dma(void);
extern void counters(void);
extern void motor_control(void);
extern void pid_control(float Kp, float Kd, float Ki);
extern void ADC_data_store(void);

extern void ADC_interrupt_F(void);
extern void ADC_dma_store(void);
extern void IC1Interrupt_(void);
extern void IC6Interrupt_(void);
extern void Timer6Interrupt(void);
extern void Timer7Interrupt(void);
extern void ignit_stop(void);
extern void IC3Int3527(void);
extern void IC4Int3527(void);
extern void IC7Int(void);
extern void IC8Int(void);
extern void IC7_measure(void);
extern void IC8_measure(void);
extern void IC3_measure(void);
extern void IC4_measure(void);

unsigned short send_dma;

void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void) {
    T5CONbits.TON = 0;
    T5Interrupt_(&usart5);
    IFS0bits.T5IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void) { 
    T1CONbits.TON = 0;
    
    IFS0bits.T1IF = 0;
}


void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void) {
    T9CONbits.TON = 0;
    T9Interrupt_(&usart4);
    IFS1bits.T9IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void) {
    Timer6Interrupt();
    IFS0bits.T6IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_7_VECTOR, IPL4SRS) T7Interrupt(void) {
    Timer7Interrupt();
    IFS1bits.T7IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void) {
    ignit_stop();
    ADCCON3bits.GSWTRG = 1;
    IFS0bits.T4IF = 0;
    counters();
    start_pid_reg = 1; //pid_control(MB_conf.CV_KP, MB_conf.CV_KD, MB_conf.CV_KI);
}

void __ISR_AT_VECTOR(_UART5_RX_VECTOR, IPL4SRS) U5RXInterrupt(void) {
    IFS5bits.U5RXIF = 0;
    usart5.mb_status.modb_receiving = 1;
    while (U5STAbits.URXDA) {
        usart5.in_buffer[usart5.in_buffer_count++] = U5RXREG;
    }
    if (usart5.in_buffer_count >= IN_SIZE1) {
        usart5.mb_status.modb_received = 1;
        usart5.mb_status.modb_receiving = 0;
    }
    tmr_5_init(frame_delay_1, 1, 1);
    IFS5bits.U5RXIF = 0;
}

void __ISR_AT_VECTOR(_UART5_TX_VECTOR, IPL4SRS) U5TXInterrupt(void) {
    IFS5bits.U5TXIF = 0;
    while ((!U5STAbits.UTXBF)&&(!usart5.mb_status.last_byte)) //copy if buff  isn't full and byte is not last
    {
        U5TXREG = usart5.out_buffer[usart5.out_buffer_count++];
        if (usart5.out_buffer_count >= (usart5.number_send)) {
            usart5.mb_status.last_byte = 1;
            IEC5bits.U5TXIE = 0;
        }
    }
    IFS5bits.U5TXIF = 0;
}

void __ISR_AT_VECTOR(_UART4_RX_VECTOR, IPL4SRS) U4RXInterrupt(void) {
    IFS5bits.U4RXIF = 0;
    usart4.mb_status.modb_receiving = 1;
    while (U4STAbits.URXDA) {
        usart4.in_buffer[usart4.in_buffer_count++] = U4RXREG;
    }
    if (usart4.in_buffer_count >= IN_SIZE1) {
        usart4.mb_status.modb_received = 1;
        usart4.mb_status.modb_receiving = 0;
    }
    tmr_9_init(frame_delay_1, 1, 1);
    IFS5bits.U4RXIF = 0;
}

void __ISR_AT_VECTOR(_UART4_TX_VECTOR, IPL4SRS) U4TXInterrupt(void) {
    IFS5bits.U4TXIF = 0;
    while ((!U4STAbits.UTXBF)&&(!usart4.mb_status.last_byte)) //copy if buff  isn't full and byte is not last
    {
        U4TXREG = usart4.out_buffer[usart4.out_buffer_count++];
        if (usart4.out_buffer_count >= (usart4.number_send)) {
            usart4.mb_status.last_byte = 1;
            IEC5bits.U4TXIE = 0;
        }
    }
    IFS5bits.U4TXIF = 0;
}

//void __ISR_AT_VECTOR (_INPUT_CAPTURE_1_VECTOR, IPL4SRS) IC1Interrupt(void)   {IC1Interrupt_(); IFS0bits.IC1IF = 0; }

//void __ISR_AT_VECTOR (_INPUT_CAPTURE_6_VECTOR, IPL4SRS) IC6Interrupt(void)   {IC6Interrupt_();  IFS0bits.IC6IF = 0; }

void __ISR_AT_VECTOR(_INPUT_CAPTURE_3_VECTOR, IPL4SRS) IC3Interrupt(void) {
    IC3Interrupt_();
    measure_sync();
    IFS0bits.IC3IF = 0;
} //IC3Int3527 ();

void __ISR_AT_VECTOR(_INPUT_CAPTURE_4_VECTOR, IPL4SRS) IC4Interrupt(void) {
    IC4Interrupt_();
    measure_rpm();
    IFS0bits.IC4IF = 0;
} //IC4Int3527 ();

void __ISR_AT_VECTOR(_INPUT_CAPTURE_7_VECTOR, IPL4SRS) IC7Interrupt(void) {
    IC7_measure();
    IC7Int();
    IFS1bits.IC7IF = 0;
}

void __ISR_AT_VECTOR(_INPUT_CAPTURE_8_VECTOR, IPL4SRS) IC8Interrupt(void) {
    IC8_measure();
    IC8Int();
    IFS1bits.IC8IF = 0;
}

void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void) {
    int dmaFlags = DCH0INT & 0xff; // read the interrupt flags

    //perform application specific operations in response to any interrupt flag set

    DCH0INTCLR = 0x000000ff; // clear the DMA channel interrupt flags
    IFS4bits.DMA0IF = 0; // Be sure to clear the DMA0 interrupt flags
    // before exiting the service routine.
}
/*     */

/*
  

 
void __ISR_AT_VECTOR (_TIMER_2_VECTOR, ipl2AUTO) T2Interrupt(void)   {		IFS0bits.T2IF = 0; }  
 
void __ISR(_ADC_DF1_VECTOR , IPL1AUTO) ADC_DF1_ISR(void) { resss = ADCFLTR1bits.FLTRDATA; IFS1bits.ADCDF1IF = 0; } //clear flag
void __ISR(_ADC_DF2_VECTOR , IPL1AUTO) ADC_DF2_ISR(void) { fpres = ADCFLTR2bits.FLTRDATA; IFS1bits.ADCDF2IF = 0; } //clear flag
void __ISR(_ADC_DF3_VECTOR , IPL1AUTO) ADC_DF3_ISR(void) { fcurr = ADCFLTR3bits.FLTRDATA; IFS1bits.ADCDF3IF = 0; } //clear flag
void __ISR(_ADC_DF4_VECTOR , IPL1AUTO) ADC_DF4_ISR(void) { fpos = ADCFLTR4bits.FLTRDATA; IFS1bits.ADCDF4IF = 0; } //clear flag
void __ISR(_ADC_DATA1_VECTOR, IPL1AUTO) ADC_DATA1_ISR(void) { IFS1bits.ADCD1IF = 0; }//clear flag
void __ISR(_ADC_DATA2_VECTOR, IPL1AUTO) ADC_DATA2_ISR(void) { IFS1bits.ADCD2IF = 0; }//clear flag
void __ISR(_ADC_DATA3_VECTOR, IPL1AUTO) ADC_DATA3_ISR(void) { IFS1bits.ADCD1IF = 0; }//clear flag
void __ISR(_ADC_DATA4_VECTOR, IPL1AUTO) ADC_DATA4_ISR(void) { IFS1bits.ADCD1IF = 0; } //clear flag

 */

/* *****************************************************************************
 End of File
 */
