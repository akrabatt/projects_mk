#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../include/stdio.h"
#include "../include/string.h"
#include "define.h"
#include "extern.h"




extern void stop_inactive (void);
extern void uart1_init(void);
extern void uart2_init(void);
extern void uart3_init(void);
extern void uart4_init(void);
extern void uart5_init(void);
extern void motor_regulator (float motor_Kp, float motor_Ki, float motor_Kd);
extern void motor_control (void);
extern void main_control (void);

//extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void* p)
extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void* p) 
{ 
 return (int)p<0?((int)p&0x1fffffffL):(unsigned int)((unsigned char*)p+0x40000000L); 
}

void TInterrupt_(struct tag_usart * usart)
	{
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void T1Interrupt_(struct tag_usart * usart)
	{
	T1CONbits.TON=0;	IFS0bits.T1IF=0;
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void T2Interrupt_(struct tag_usart * usart)
	{
	T2CONbits.TON=0;	IFS0bits.T2IF=0;
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void T3Interrupt_(struct tag_usart * usart)
	{
	T3CONbits.TON=0;	IFS0bits.T3IF=0;
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void T4Interrupt_(struct tag_usart * usart)
	{
	T4CONbits.TON=0;	IFS0bits.T4IF=0;
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void T5Interrupt_(struct tag_usart * usart)
	{
	T5CONbits.TON=0;	IFS0bits.T5IF=0;
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void T9Interrupt_(struct tag_usart * usart)
	{
	T9CONbits.TON=0;	IFS1bits.T9IF=0;
	if (usart->mb_status.modb_receiving)    {usart->mb_status.modb_received = 1;    usart->mb_status.modb_receiving = 0;}
	}

void DMA_uni ( struct tag_usart * usart, unsigned short cnt, unsigned short on, unsigned short force)
{
    if (usart == &usart1)
        {
        DCH1SSA = _VirtToPhys(&buf_tx1);      // transfer source physical address
        DCH1DSA = _VirtToPhys((const void*) &U1TXREG);   // transfer destination physical address
        DCH1SSIZ = cnt;                       // source size at most 200 bytes
        DCH1DSIZ = 1;                        // dst size is 1 byte
        DCH1CSIZ = 1;                       // one byte per UART transfer request
        DCH1CONbits.CHEN = on;
        DCH1ECONbits.CFORCE = force;
        }        
    if (usart == &usart2)
        {
        DCH2SSA = _VirtToPhys(&buf_tx2);      // transfer source physical address
        DCH2DSA = _VirtToPhys((const void*) &U2TXREG);   // transfer destination physical address
        DCH2SSIZ = cnt;                       // source size at most 200 bytes
        DCH2DSIZ = 1;                        // dst size is 1 byte
        DCH2CSIZ = 1;                       // one byte per UART transfer request
        DCH2CONbits.CHEN = on;
        DCH2ECONbits.CFORCE = force;
        }    
    if (usart == &usart3)
        {
        DCH3SSA = _VirtToPhys(&buf_tx3);      // transfer source physical address
        DCH3DSA = _VirtToPhys((const void*) &U3TXREG);   // transfer destination physical address
        DCH3SSIZ = cnt;                       // source size at most 200 bytes
        DCH3DSIZ = 1;                        // dst size is 1 byte
        DCH3CSIZ = 1;                       // one byte per UART transfer request
        DCH3CONbits.CHEN = on;
        DCH3ECONbits.CFORCE = force;
        }    
    if (usart == &usart4)
        {
        DCH4SSA = _VirtToPhys(&buf_tx4);      // transfer source physical address
        DCH4DSA = _VirtToPhys((const void*) &U4TXREG);   // transfer destination physical address
        DCH4SSIZ = cnt;                       // source size at most 200 bytes
        DCH4DSIZ = 1;                        // dst size is 1 byte
        DCH4CSIZ = 1;                       // one byte per UART transfer request
        DCH4CONbits.CHEN = on;
        DCH4ECONbits.CFORCE = force;
        }
    if (usart == &usart5)
        {
        DCH5SSA = _VirtToPhys(&buf_tx5 );      // transfer source physical address
        DCH5DSA = _VirtToPhys((const void*) &U5TXREG);   // transfer destination physical address
        DCH5SSIZ = cnt;                       // source size at most 200 bytes
        DCH5DSIZ = 1;                        // dst size is 1 byte
        DCH5CSIZ = 1;                       // one byte per UART transfer request
        DCH5CONbits.CHEN = on;
        DCH5ECONbits.CFORCE = force;
        }
}

void DMA1_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH1CON=0x2;                       // channel 1 off, priority 2
DCH1ECONbits.CHSIRQ = _UART1_TX_VECTOR;
DCH1ECONbits.SIRQEN = 1;
DCH1SSA = _VirtToPhys(&buf_tx1);      // transfer source physical address
DCH1DSA = _VirtToPhys((const void*) &U1TXREG);   // transfer destination physical address
DCH1SSIZ=38;                       // source size at most 200 bytes
DCH1DSIZ=1;                        // dst size is 1 byte
DCH1CSIZ=1;                       // one byte per UART transfer request
DCH1INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts
//DCH1INTbits.CHSDIF = 0; 
DCH1CONbits.CHEN = 0;
}

void DMA2_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH2CON=0x2;                       // channel 1 off, priority 2
DCH2ECONbits.CHSIRQ = _UART2_TX_VECTOR;
DCH2ECONbits.SIRQEN = 1;
DCH2SSA = _VirtToPhys(&buf_tx2);      // transfer source physical address
DCH2DSA = _VirtToPhys((const void*) &U2TXREG);   // transfer destination physical address
DCH2SSIZ=38;                       // source size at most 200 bytes
DCH2DSIZ=1;                        // dst size is 1 byte
DCH2CSIZ=1;                       // one byte per UART transfer request
DCH2INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts
//DCH4INTbits.CHSDIF = 0; 
DCH2CONbits.CHEN = 0;
}

void DMA3_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH3CON=0x2;                       // channel 1 off, priority 2
DCH3ECONbits.CHSIRQ = _UART3_TX_VECTOR;
DCH3ECONbits.SIRQEN = 1;
DCH3SSA = _VirtToPhys(&buf_tx3);      // transfer source physical address
DCH3DSA = _VirtToPhys((const void*) &U3TXREG);   // transfer destination physical address
DCH3SSIZ=38;                       // source size at most 200 bytes
DCH3DSIZ=1;                        // dst size is 1 byte
DCH3CSIZ=1;                       // one byte per UART transfer request
DCH3INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts
//DCH4INTbits.CHSDIF = 0; 
DCH3CONbits.CHEN = 0;
}

void DMA4_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH4CON=0x2;                       // channel 1 off, priority 2
DCH4ECONbits.CHSIRQ = _UART4_TX_VECTOR;
DCH4ECONbits.SIRQEN = 1;
DCH4SSA = _VirtToPhys(&buf_tx4);      // transfer source physical address
DCH4DSA = _VirtToPhys((const void*) &U4TXREG);   // transfer destination physical address
DCH4SSIZ=38;                       // source size at most 200 bytes
DCH4DSIZ=1;                        // dst size is 1 byte
DCH4CSIZ=1;                       // one byte per UART transfer request
DCH4INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts
//DCH4INTbits.CHSDIF = 0; 
DCH4CONbits.CHEN = 0;
}

void DMA5_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH5CON=0x2;                       // channel 1 off, priority 2
DCH5ECONbits.CHSIRQ = _UART5_TX_VECTOR;
DCH5ECONbits.SIRQEN = 1;
DCH5SSA = _VirtToPhys(&buf_tx5);      // transfer source physical address
DCH5DSA = _VirtToPhys((const void*) &U5TXREG);   // transfer destination physical address
DCH5SSIZ=38;                       // source size at most 200 bytes
DCH5DSIZ=1;                        // dst size is 1 byte
DCH5CSIZ=1;                       // one byte per UART transfer request
DCH5INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts
//DCH1INTbits.CHSDIF = 0; 
DCH5CONbits.CHEN = 0;
}


//void test_uart_dma(void)    { DMA1_init (); ENAB_TX5; ENAB_TX5; DCH1CONbits.CHEN = 1; DCH1ECONbits.CFORCE = 1; }

unsigned char conf, bconf;
unsigned char conf2, bconf2;

void conf_read (void)
{
    conf2 = 0;
    conf = 0;
    if (CONF1) {conf |= 0x01;} else {conf &= 0xFE;}
    if (CONF2) {conf |= 0x02;} else {conf &= 0xFD;}
    if (CONF3) {conf |= 0x04;} else {conf &= 0xFB;}
    if (CONF4) {conf |= 0x08;} else {conf &= 0xF7;}
    conf &= 0x0F;
    switch (conf)
    {
        case 7: { U4_speed = 115200; break;}               //115200
        case 6: { U4_speed = 57600;  break;}               //57600
        case 5: { U4_speed = 38400; break;}               //38400
        case 4: { U4_speed = 19200; break;}               //19200
        default: { U4_speed = 19200; break;}                     //19200
    }

    if (CONF5) {conf2 |= 0x01;} else {conf2 &= 0xFE;}
    if (CONF6) {conf2 |= 0x02;} else {conf2 &= 0xFD;}
    if (CONF7) {conf2 |= 0x04;} else {conf2 &= 0xFB;}
    if (CONF8) {conf2 |= 0x08;} else {conf2 &= 0xF7;}
    conf2 &= 0x0F;
    switch (conf2)
    {
        case 7: { U5_speed = 115200; break;}               //115200
        case 6: { U5_speed = 57600;  break;}               //57600
        case 5: { U5_speed = 38400; break;}               //38400
        case 4: { U5_speed = 19200; break;}               //19200
        default: { U5_speed = 19200; break;}                     //19200
   }
//    U1_speed = 57600; 
    help_reset = 1;
    bconf = conf;
    bconf2 = conf2;    
}

void conf_check (void)
{
    if (CONF1) {conf |= 0x01;} else {conf &= 0xFE;}
    if (CONF2) {conf |= 0x02;} else {conf &= 0xFD;}
    if (CONF3) {conf |= 0x04;} else {conf &= 0xFB;}
    if (CONF4) {conf |= 0x08;} else {conf &= 0xF7;}
    conf &= 0x0F;
    switch (conf)
    {
        case 7: { U4_speed = 115200; break;}               //115200
        case 6: { U4_speed = 57600;  break;}               //57600
        case 5: { U4_speed = 38400; break;}               //38400
        case 4: { U4_speed = 19200; break;}               //19200
        default: { U4_speed = 19200; break;}                     //19200
    }
    
    if (CONF5) {conf2 |= 0x01;} else {conf2 &= 0xFE;}
    if (CONF6) {conf2 |= 0x02;} else {conf2 &= 0xFD;}
    if (CONF7) {conf2 |= 0x04;} else {conf2 &= 0xFB;}
    if (CONF8) {conf2 |= 0x08;} else {conf2 &= 0xF7;}
    conf2 &= 0x0F;
    switch (conf2)
    {
        case 7: { U5_speed = 115200; break;}               //115200
        case 6: { U5_speed = 57600;  break;}               //57600
        case 5: { U5_speed = 38400; break;}               //38400
        case 4: { U5_speed = 19200; break;}               //19200
        default: { U5_speed = 19200; break;}                     //19200
    }

    if (conf2 != bconf2) {  uart5_init();     }    
    if (conf != bconf )  {   uart4_init();   }    
    bconf = conf;
    bconf2 = conf2;
}


unsigned short _1000msec;
unsigned short _100msec;
unsigned short _10msec;
unsigned short _divider;

unsigned short DI1_cnt;
unsigned short DI2_cnt;
unsigned short DI3_cnt;

void discret_ctrl (void)
{
    if (DINPUT1 != DI_1) {  DI1_cnt += CYCLE; 
        if (DI1_cnt >= FILT_DISCRET) { DINPUT1 = DI_1 ; DI1_cnt = 0; } 
        }
    else { DI1_cnt = 0;}

    if (DINPUT2 != DI_2) {  DI2_cnt += CYCLE; 
        if (DI2_cnt >= FILT_DISCRET) { DINPUT2 = DI_2 ; DI2_cnt = 0; } 
        }
    else { DI2_cnt = 0;}
 }

void counters (void)
{
    if (_divider >= 10)
        {
        _divider = 0;
        _100msec ++;
        _1000msec ++;

        Modbus.buf [0]++; 
        Modbus.buf [1] = usart5.mbm_status;
        Modbus.buf [2] = usart5.mbm_err;        
        Modbus.buf [3] = usart5.mbm_timeout_counter;
        Modbus.buf [4] = usart5.mb_status.master_start;
        Modbus.buf [5] = usart5.mb_status.tm_on;
        Modbus.buf [6] = usart5.mb_status.master_timeout_flag;
        Modbus.buf [7] = usart5.in_buffer_count;
        Modbus.buf [8] = usart5.mb_status.modb_received;     
        
        Modbus.buf [10] = MOPS_arr[1].status[4];
        Modbus.buf [11] = MOPS_arr[1].status[5];      
        Modbus.buf [12] = MOPS_arr[1].status[6];      
        
        Modbus_sw.buf [0] = swapshort (Modbus.buf [0]);
        Modbus_sw.buf [1] = swapshort (Modbus.buf [1]);
        Modbus_sw.buf [2] = swapshort (Modbus.buf [2]);
        Modbus_sw.buf [3] = swapshort (Modbus.buf [3]);
        Modbus_sw.buf [4] = swapshort (Modbus.buf [4]);
        Modbus_sw.buf [5] = swapshort (Modbus.buf [5]);       
        Modbus_sw.buf [6] = swapshort (Modbus.buf [6]);     
        Modbus_sw.buf [7] = swapshort (Modbus.buf [7]); 
        Modbus_sw.buf [8] = swapshort (Modbus.buf [8]); 
        Modbus_sw.buf [9] = swapshort (Modbus.buf [9]); 
        Modbus_sw.buf [10] = swapshort (Modbus.buf [10]); 
        Modbus_sw.buf [11] = swapshort (Modbus.buf [11]); 
        Modbus_sw.buf [12] = swapshort (Modbus.buf [12]); 
        Modbus_sw.buf [13] = swapshort (Modbus.buf [13]); 
        
                
        if (_100msec >= 3) {
            _100msec = 0; 
            help_strobe  ^= 1; 
            usart5.mb_status.master_start = 1;
            }   

        if (_1000msec >= 100) {
            _1000msec = 0;  
            conf_check ();

            }
    }
    _divider++;
}

/* *****************************************************************************
 End of File
 */
