#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../include/stdio.h"
#include "../include/string.h"
#include "define.h"
#include "extern.h"

extern void stop_inactive(void);
extern void uart1_init(void);
extern void uart4_init(void);
extern void motor_regulator(float motor_Kp, float motor_Ki, float motor_Kd);
extern void motor_control(void);
extern void main_control(void);

extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void *p)
{
    return (int)p < 0 ? ((int)p & 0x1fffffffL) : (unsigned int)((unsigned char *)p + 0x40000000L);
}

void T1Interrupt_(struct tag_usart *usart)
{
    T1CONbits.TON = 0;
    IFS0bits.T1IF = 0;
    if (usart->mb_status.modb_receiving)
    {
        usart->mb_status.modb_received = 1;
        usart->mb_status.modb_receiving = 0;
    }
}

void T5Interrupt_(struct tag_usart *usart)
{
    T5CONbits.TON = 0;
    IFS0bits.T5IF = 0;
    if (usart->mb_status.modb_receiving)
    {
        usart->mb_status.modb_received = 1;
        usart->mb_status.modb_receiving = 0;
    }
}

void T9Interrupt_(struct tag_usart *usart)
{
    T9CONbits.TON = 0;
    IFS1bits.T9IF = 0;
    if (usart->mb_status.modb_receiving)
    {
        usart->mb_status.modb_received = 1;
        usart->mb_status.modb_receiving = 0;
    }
}

void DMA_uni(struct tag_usart *usart, unsigned short cnt, unsigned short on, unsigned short force)
{
    if (usart == &usart5)
    {
        DCH5SSA = _VirtToPhys(&buf_tx5); // transfer source physical address
        DCH5DSA = _VirtToPhys(&U5TXREG); // transfer destination physical address
        DCH5SSIZ = cnt;                  // source size at most 200 bytes
        DCH5DSIZ = 1;                    // dst size is 1 byte
        DCH5CSIZ = 1;                    // one byte per UART transfer request
        DCH5CONbits.CHEN = on;
        DCH5ECONbits.CFORCE = force;
    }
    if (usart == &usart4)
    {
        DCH4SSA = _VirtToPhys(&buf_tx4); // transfer source physical address
        DCH4DSA = _VirtToPhys(&U4TXREG); // transfer destination physical address
        DCH4SSIZ = cnt;                  // source size at most 200 bytes
        DCH4DSIZ = 1;                    // dst size is 1 byte
        DCH4CSIZ = 1;                    // one byte per UART transfer request
        DCH4CONbits.CHEN = on;
        DCH4ECONbits.CFORCE = force;
    }
}

void DMA5_init(void)
{
    DMACONSET = 0x00008000; // enable the DMA controller
    DCH5CON = 0x2;          // channel 1 off, priority 2
    DCH5ECONbits.CHSIRQ = _UART5_TX_VECTOR;
    DCH5ECONbits.SIRQEN = 1;
    DCH5SSA = _VirtToPhys(&buf_tx5); // transfer source physical address
    DCH5DSA = _VirtToPhys(&U5TXREG); // transfer destination physical address
    DCH5SSIZ = 38;                   // source size at most 200 bytes
    DCH5DSIZ = 1;                    // dst size is 1 byte
    DCH5CSIZ = 1;                    // one byte per UART transfer request
    DCH5INTCLR = 0x00ff00ff;         // DMA1: clear events, disable interrupts
    // DCH1INTbits.CHSDIF = 0;
    DCH5CONbits.CHEN = 0;
}
void DMA4_init(void)
{
    DMACONSET = 0x00008000; // enable the DMA controller
    DCH4CON = 0x2;          // channel 1 off, priority 2
    DCH4ECONbits.CHSIRQ = _UART4_TX_VECTOR;
    DCH4ECONbits.SIRQEN = 1;
    DCH4SSA = _VirtToPhys(&buf_tx4); // transfer source physical address
    DCH4DSA = _VirtToPhys(&U4TXREG); // transfer destination physical address
    DCH4SSIZ = 38;                   // source size at most 200 bytes
    DCH4DSIZ = 1;                    // dst size is 1 byte
    DCH4CSIZ = 1;                    // one byte per UART transfer request
    DCH4INTCLR = 0x00ff00ff;         // DMA1: clear events, disable interrupts
    // DCH4INTbits.CHSDIF = 0;
    DCH4CONbits.CHEN = 0;
}

void test_uart_dma(void)
{
    DMA5_init();
    ENAB_TX5;
    ENAB_TX5;
    DCH1CONbits.CHEN = 1;
    DCH1ECONbits.CFORCE = 1;
}

unsigned char conf, bconf;
unsigned char conf2, bconf2;

void conf_read(void)
{
    conf2 = 0;
    conf = 0;
    if (CONF1)
    {
        conf |= 0x01;
    }
    else
    {
        conf &= 0xFE;
    }
    if (CONF2)
    {
        conf |= 0x02;
    }
    else
    {
        conf &= 0xFD;
    }
    if (CONF3)
    {
        conf |= 0x04;
    }
    else
    {
        conf &= 0xFB;
    }
    if (CONF4)
    {
        conf |= 0x08;
    }
    else
    {
        conf &= 0xF7;
    }
    conf &= 0x0F;
    switch (conf)
    {
    case 7:
    {
        U4_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U4_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U4_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U4_speed = 19200;
        break;
    } // 19200
    default:
    {
        U4_speed = 19200;
        break;
    } // 19200
    }

    if (CONF5)
    {
        conf2 |= 0x01;
    }
    else
    {
        conf2 &= 0xFE;
    }
    if (CONF6)
    {
        conf2 |= 0x02;
    }
    else
    {
        conf2 &= 0xFD;
    }
    if (CONF7)
    {
        conf2 |= 0x04;
    }
    else
    {
        conf2 &= 0xFB;
    }
    if (CONF8)
    {
        conf2 |= 0x08;
    }
    else
    {
        conf2 &= 0xF7;
    }
    conf2 &= 0x0F;
    switch (conf2)
    {
    case 7:
    {
        U5_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U5_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U5_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U5_speed = 19200;
        break;
    } // 19200
    default:
    {
        U5_speed = 19200;
        break;
    } // 19200
    }
    //    U1_speed = 57600;
    help_reset = 1;
    bconf = conf;
    bconf2 = conf2;
}

void conf_check(void)
{
    if (CONF1)
    {
        conf |= 0x01;
    }
    else
    {
        conf &= 0xFE;
    }
    if (CONF2)
    {
        conf |= 0x02;
    }
    else
    {
        conf &= 0xFD;
    }
    if (CONF3)
    {
        conf |= 0x04;
    }
    else
    {
        conf &= 0xFB;
    }
    if (CONF4)
    {
        conf |= 0x08;
    }
    else
    {
        conf &= 0xF7;
    }
    conf &= 0x0F;
    switch (conf)
    {
    case 7:
    {
        U4_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U4_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U4_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U4_speed = 19200;
        break;
    } // 19200
    default:
    {
        U4_speed = 19200;
        break;
    } // 19200
    }

    if (CONF5)
    {
        conf2 |= 0x01;
    }
    else
    {
        conf2 &= 0xFE;
    }
    if (CONF6)
    {
        conf2 |= 0x02;
    }
    else
    {
        conf2 &= 0xFD;
    }
    if (CONF7)
    {
        conf2 |= 0x04;
    }
    else
    {
        conf2 &= 0xFB;
    }
    if (CONF8)
    {
        conf2 |= 0x08;
    }
    else
    {
        conf2 &= 0xF7;
    }
    conf2 &= 0x0F;
    switch (conf2)
    {
    case 7:
    {
        U5_speed = 115200;
        break;
    } // 115200
    case 6:
    {
        U5_speed = 57600;
        break;
    } // 57600
    case 5:
    {
        U5_speed = 38400;
        break;
    } // 38400
    case 4:
    {
        U5_speed = 19200;
        break;
    } // 19200
    default:
    {
        U5_speed = 19200;
        break;
    } // 19200
    }

    if (conf2 != bconf2)
    {
        uart5_init();
    }
    if (conf != bconf)
    {
        uart4_init();
    }
    bconf = conf;
    bconf2 = conf2;
}

unsigned int _1000msec;
unsigned int _100msec;
unsigned int _10msec;
unsigned int _divider;

unsigned int DI1_cnt;
unsigned int DI2_cnt;
unsigned int DI3_cnt;

void discret_ctrl(void)
{
    if (DINPUT1 != DI_1)
    {
        DI1_cnt += CYCLE;
        if (DI1_cnt >= FILT_DISCRET)
        {
            DINPUT1 = DI_1;
            DI1_cnt = 0;
        }
    }
    else
    {
        DI1_cnt = 0;
    }

    if (DINPUT2 != DI_2)
    {
        DI2_cnt += CYCLE;
        if (DI2_cnt >= FILT_DISCRET)
        {
            DINPUT2 = DI_2;
            DI2_cnt = 0;
        }
    }
    else
    {
        DI2_cnt = 0;
    }

    if (DINPUT3 != DI_3)
    {
        DI3_cnt += CYCLE;
        if (DI3_cnt >= FILT_DISCRET)
        {
            DINPUT3 = DI_3;
            DI3_cnt = 0;
        }
    }
    else
    {
        DI3_cnt = 0;
    }
}

void counters(void)
{
    if (_divider >= 25)
    {
        //        mpid_control(MB_conf.KP_mpid, MB_conf.KD_mpid, MB_conf.KI_mpid);
        _divider = 0;
        _100msec++;
        _1000msec++;
        discret_ctrl();
        start_ctrl = 1;
        //        main_control ();                                                        // ���������� ����������
        if (_100msec >= 10)
        {
            _100msec = 0;
            help_strobe ^= 1;
            stop_inactive();

            if ((MB_conf.max_RPM <= 350) || (MB_conf.max_RPM >= 390))
            {
                load_config();
            } // help_load =0;
        }     //
        if (_1000msec >= 100)
        {
            _1000msec = 0;
            conf_check();
        }
    }
    _divider++;
}

/* *****************************************************************************
 End of File
 */
