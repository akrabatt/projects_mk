#include <xc.h>
#include <sys/attribs.h>    /* contains __ISR() Macros */
#include "define.h"
#include "extern.h"


//extern void tmr_1_init(unsigned short T1_delay, unsigned short TMR1_IE, unsigned short TMR1_ON);
extern void T1Interrupt_(struct tag_usart * usart);
extern void T2Interrupt_(struct tag_usart * usart);
extern void T5Interrupt_(struct tag_usart * usart);
extern void T9Interrupt_(struct tag_usart * usart);
extern void mbs(struct tag_usart * usart, unsigned char mbs_addres, union tag_direct * dir);
extern void DMA_uni(struct tag_usart * usart, unsigned short cnt, unsigned short on, unsigned short force);
extern void test_uart_dma(void);
extern void IC8Int(void);
extern void IC7_measure(void);
extern void IC8_measure(void);
extern void IC3_measure(void);
extern void IC4_measure(void);
unsigned short send_dma;
extern void fun_blink_counter(void);


//TIMERS

void __ISR_AT_VECTOR(_TIMER_1_VECTOR, IPL4SRS) T1Interrupt(void) {
    T1CONbits.TON = 0;
    T1Interrupt_(&usart1);
    PORTEbits.RE3 = LATEbits.LATE3 ^ 1;
    IFS0bits.T1IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_2_VECTOR, IPL4SRS) T2Interrupt(void) {
    T2CONbits.TON = 0;
    T2Interrupt_(&usart2);
//    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;
    PORTGbits.RG13 = LATGbits.LATG13 ^ 1;
    IFS0bits.T2IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_4_VECTOR, IPL4SRS) T4Interrupt(void) {
    T4CONbits.TON = 0;
    IFS0bits.T4IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_5_VECTOR, IPL4SRS) T5Interrupt(void) {
    T5CONbits.TON = 0;
    T5Interrupt_(&usart5);
    IFS0bits.T5IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_6_VECTOR, IPL4SRS) T6Interrupt(void) {
    T6CONbits.TON = 0;
    T6Interrupt_(&usart4);
    IFS0bits.T6IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_7_VECTOR, IPL4SRS) T7Interrupt(void) {
    T7CONbits.TON = 0;
    T4Interrupt_(&usart3);
    PORTGbits.RG14 = LATGbits.LATG14 ^ 1;
    IFS1bits.T7IF = 0;
}

void __ISR_AT_VECTOR(_TIMER_9_VECTOR, IPL4SRS) T9Interrupt(void) {
    
    fun_blink_counter();
    IFS1bits.T9IF = 0;
}


//TX/RX

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
    tmr_6_init(frame_delay_1, 1, 1);
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

void __ISR_AT_VECTOR(_UART1_RX_VECTOR, IPL4SRS) U1RXInterrupt(void) {
    IFS3bits.U1RXIF = 0;
    usart1.mb_status.modb_receiving = 1;
    while (U1STAbits.URXDA) {
        usart1.in_buffer[usart1.in_buffer_count++] = U1RXREG;
    }
    if (usart1.in_buffer_count >= IN_SIZE1) {
        usart1.mb_status.modb_received = 1;
        usart1.mb_status.modb_receiving = 0;
    }
    tmr_1_init(frame_delay_1, 1, 1);


    IFS3bits.U1RXIF = 0;

}

void __ISR_AT_VECTOR(_UART1_TX_VECTOR, IPL1SRS) U1TXInterrupt(void) {
    IFS3bits.U1TXIF = 0;
    while ((!U1STAbits.UTXBF)&&(!usart1.mb_status.last_byte)) //copy if buff  isn't full and byte is not last
    {
        U1TXREG = usart1.out_buffer[usart1.out_buffer_count++];
        if (usart1.out_buffer_count >= (usart1.number_send)) {
            usart1.mb_status.last_byte = 1;
            IEC3bits.U1TXIE = 0;
        }
    }
    IFS3bits.U1TXIF = 0;
}
void __ISR_AT_VECTOR(_UART2_RX_VECTOR, IPL4SRS) U2RXInterrupt(void) {
    IFS4bits.U2RXIF = 0;
    usart2.mb_status.modb_receiving = 1;
    while (U2STAbits.URXDA) {
        usart2.in_buffer[usart2.in_buffer_count++] = U2RXREG;
    }
    if (usart2.in_buffer_count >= IN_SIZE1) {
        usart2.mb_status.modb_received = 1;
        usart2.mb_status.modb_receiving = 0;
    }
    tmr_2_init(frame_delay_1, 1, 1);


    IFS4bits.U2RXIF = 0;
//    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;

}

void __ISR_AT_VECTOR(_UART2_TX_VECTOR, IPL1SRS) U2TXInterrupt(void) {
    IFS4bits.U2TXIF = 0;
    while ((!U2STAbits.UTXBF)&&(!usart2.mb_status.last_byte)) //copy if buff  isn't full and byte is not last
    {
        U2TXREG = usart2.out_buffer[usart2.out_buffer_count++];
        if (usart2.out_buffer_count >= (usart2.number_send)) {
            usart2.mb_status.last_byte = 1;
            IEC4bits.U2TXIE = 0;
        }
    }
    IFS4bits.U2TXIF = 0;
}
void __ISR_AT_VECTOR(_UART3_RX_VECTOR, IPL4SRS) U3RXInterrupt(void) {
    IFS4bits.U3RXIF = 0;
    usart3.mb_status.modb_receiving = 1;
    while (U3STAbits.URXDA) {
        usart3.in_buffer[usart3.in_buffer_count++] = U3RXREG;
    }
    if (usart3.in_buffer_count >= IN_SIZE1) {
        usart3.mb_status.modb_received = 1;
        usart3.mb_status.modb_receiving = 0;
    }
    tmr_7_init(frame_delay_1, 1, 1);


    IFS4bits.U3RXIF = 0;
//    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;

}

void __ISR_AT_VECTOR(_UART3_TX_VECTOR, IPL1SRS) U3TXInterrupt(void) {
    IFS4bits.U3TXIF = 0;
    while ((!U3STAbits.UTXBF)&&(!usart3.mb_status.last_byte)) //copy if buff  isn't full and byte is not last
    {
        U3TXREG = usart3.out_buffer[usart3.out_buffer_count++];
        if (usart3.out_buffer_count >= (usart3.number_send)) {
            usart3.mb_status.last_byte = 1;
            IEC4bits.U3TXIE = 0;
        }
    }
    IFS4bits.U3TXIF = 0;
}

void __ISR_AT_VECTOR(_DMA0_VECTOR, IPL4SRS) __DMA0Interrupt(void) {
    int dmaFlags = DCH0INT & 0xff; // read the interrupt flags

    //perform application specific operations in response to any interrupt flag set

    DCH0INTCLR = 0x000000ff; // clear the DMA channel interrupt flags
    IFS4bits.DMA0IF = 0; // Be sure to clear the DMA0 interrupt flags
    // before exiting the service routine.
}