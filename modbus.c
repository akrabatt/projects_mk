

#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../include/stdio.h"
#include "../include/string.h"

//#include "app.h"
//#include "system_definitions.h"
#include "define.h"
#include "extern.h"
//#include "mops_mups_str.h"  



extern void getcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len);
extern void putcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len);
extern void DMA1_init(void);

const char auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};
const char auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};

unsigned char uchCRCHi = 0xFF;
unsigned char uchCRCLo = 0xFF;
extern unsigned int CRC16_int;
extern unsigned char CRC16_Hi;
extern unsigned char CRC16_Lo;

void PIC_CRC16(unsigned char *puchMsg, unsigned short usDataLen)
//unsigned char PIC_CRC16(unsigned char *puchMsg, unsigned short usDataLen)
{
    unsigned char uIndex;
    uchCRCHi = 0xFF;
    uchCRCLo = 0xFF;
    while (usDataLen--) {
        uIndex = uchCRCLo ^ *puchMsg++;
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex];
    }

    //	return ((uchCRCHi * 0x100 )| uchCRCLo); 
    //	return (uintCRC); 
    //	return (uchCRCHi, uchCRCLo); 
}

static const unsigned int wCRCTable [] = {
    0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
    0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
    0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
    0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
    0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbC1, 0xda81, 0x1a40,
    0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
    0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
    0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
    0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
    0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
    0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
    0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
    0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
    0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
    0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
    0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
    0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
    0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
    0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
    0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
    0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
    0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
    0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
    0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
    0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
    0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
    0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
    0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
    0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
    0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
    0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
};

unsigned int MODBUS_CRC16_calculate(unsigned char *nData, unsigned char wLength) {

    unsigned char nTemp;
    unsigned int wCRCWord = 0xFFFF;
    while (wLength--) {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord ^= wCRCTable[nTemp];
    }
    return ( wCRCWord);
}

unsigned short swapshort(unsigned short data) {

    union {
        unsigned short sdata;
        unsigned char cdata [2];
    } conv, sconv;

    conv.sdata = data;
    sconv.cdata [1] = conv.cdata [0];
    sconv.cdata [0] = conv.cdata [1];
    return sconv.sdata;
}

float swapfloat(float data) {

    union {
        float fdata;
        unsigned short sdata [2];
        unsigned char cdata [4];
    } conv, sconv;

    conv.fdata = data;
    sconv.cdata [1] = conv.cdata [0];
    sconv.cdata [0] = conv.cdata [1];
    sconv.cdata [2] = conv.cdata [3];
    sconv.cdata [3] = conv.cdata [2];
    return sconv.fdata;
}

unsigned long swaplong(unsigned long data) {

    union {
        unsigned long ldata;
        unsigned short sdata [2];
    } conv, sconv;

    conv.ldata = _bswapw(data);
    sconv.sdata [1] = conv.sdata [0];
    sconv.sdata [0] = conv.sdata [1];
    return sconv.ldata;
}

void start_tx_usart(struct tag_usart * usart) {
    if (usart == &usart4) {
        IEC5bits.U4RXIE = 0; //disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        /*		if (usart->port_type==485){}*/
        ENAB_TX4;
        IEC5bits.U4TXIE = 1; //enable TX interrupt
    }

    if (usart == &usart5) {
        IEC5bits.U5RXIE = 0; //disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX5;
        IEC5bits.U5TXIE = 1; //enable TX interrupt
    }
    if (usart == &usart3) {
        IEC4bits.U3RXIE = 0; //disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX3;
        IEC4bits.U3TXIE = 1; //enable TX interrupt
    }
    if (usart == &usart2) {
        IEC4bits.U2RXIE = 0; //disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX2;
        IEC4bits.U2TXIE = 1; //enable TX interrupt
    }
    if (usart == &usart1) {
        IEC3bits.U1RXIE = 0; //disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX1;
        IEC3bits.U1TXIE = 1; //enable TX interrupt
    }
}

void start_tx_usart_dma(struct tag_usart * usart, unsigned short count) {
    if (usart == &usart4) {
        ENAB_TX4;
        memcpy((void*) (buf_tx4), (const void*) (usart->out_buffer), (count));
        IEC5bits.U4RXIE = 0;
        DMA_uni(&usart4, count, 1, 1);
        usart->mb_status.modb_transmiting = 1;
        IEC5bits.U4TXIE = 0; //enable TX interrupt
    }
    if (usart == &usart5) {
        ENAB_TX5;
        memcpy((void*) (buf_tx5), (const void*) (usart->out_buffer), (count));
        IEC5bits.U5RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart5, count, 1, 1);
        IEC5bits.U5TXIE = 0;
    }
    if (usart == &usart3) {
        ENAB_TX3;
        memcpy((void*) (buf_tx3), (const void*) (usart->out_buffer), (count));
        IEC4bits.U3RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart3, count, 1, 1);
        IEC4bits.U3TXIE = 0;
    }
    if (usart == &usart2) {
        ENAB_TX2;
        memcpy((void*) (buf_tx2), (const void*) (usart->out_buffer), (count));
        IEC4bits.U2RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart2, count, 1, 1);
        IEC4bits.U2TXIE = 0;
    }
    if (usart == &usart1) {
        ENAB_TX1;
        memcpy((void*) (buf_tx1), (const void*) (usart->out_buffer), (count));
        IEC3bits.U1RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart1, count, 1, 1);
        IEC3bits.U1TXIE = 0;
    }
}

void stop_uart_tx(void) {
    if (usart4.mb_status.tx_mode == INT_type) {
        if ((usart4.mb_status.modb_transmiting == 1)&&(U4STAbits.TRMT)&&(IEC5bits.U4TXIE == 0)) {
            usart4.mb_status.last_byte = 0;
            usart4.mb_status.modb_received = 0;
            usart4.mb_status.modb_receiving = 0;
            usart4.in_buffer_count = 0;
            usart4.mb_status.modb_transmiting = 0;
            IFS5bits.U4RXIF = 0;
            ENAB_RX4;
            IEC5bits.U4RXIE = 1; //disable RX interrupt
        }
        if (U4STAbits.OERR || U4STAbits.FERR) {
            U4STAbits.OERR = 0;
        }
    }

    if (usart5.mb_status.tx_mode == INT_type) {
        if ((usart5.mb_status.modb_transmiting == 1)&&(U5STAbits.TRMT)&&(IEC5bits.U5TXIE == 0)) {
            usart5.mb_status.last_byte = 0;
            usart5.mb_status.modb_received = 0;
            usart5.mb_status.modb_receiving = 0;
            usart5.in_buffer_count = 0;
            usart5.mb_status.modb_transmiting = 0;
            IFS5bits.U5RXIF = 0;
            ENAB_RX5;
            IEC5bits.U5RXIE = 1; //disable RX interrupt
        }
        if (U5STAbits.OERR || U5STAbits.FERR) {
            U5STAbits.OERR = 0;
        }
    }
    if (usart3.mb_status.tx_mode == INT_type) {
        if ((usart3.mb_status.modb_transmiting == 1)&&(U3STAbits.TRMT)&&(IEC4bits.U3TXIE == 0)) {
            usart3.mb_status.last_byte = 0;
            usart3.mb_status.modb_received = 0;
            usart3.mb_status.modb_receiving = 0;
            usart3.in_buffer_count = 0;
            usart3.mb_status.modb_transmiting = 0;
            IFS4bits.U3RXIF = 0;
            ENAB_RX3;
            IEC4bits.U3RXIE = 1; //disable RX interrupt
        }
        if (U3STAbits.OERR || U3STAbits.FERR) {
            U3STAbits.OERR = 0;
        }
    }
    if (usart2.mb_status.tx_mode == INT_type) {
        if ((usart2.mb_status.modb_transmiting == 1)&&(U2STAbits.TRMT)&&(IEC4bits.U2TXIE == 0)) {
            usart2.mb_status.last_byte = 0;
            usart2.mb_status.modb_received = 0;
            usart2.mb_status.modb_receiving = 0;
            usart2.in_buffer_count = 0;
            usart2.mb_status.modb_transmiting = 0;
            IFS4bits.U2RXIF = 0;
            ENAB_RX2;
            IEC4bits.U2RXIE = 1; //disable RX interrupt
        }
        if (U2STAbits.OERR || U2STAbits.FERR) {
            U2STAbits.OERR = 0;
        }
    }
    if (usart1.mb_status.tx_mode == INT_type) {
        if ((usart1.mb_status.modb_transmiting == 1)&&(U1STAbits.TRMT)&&(IEC3bits.U1TXIE == 0)) {
            usart1.mb_status.last_byte = 0;
            usart1.mb_status.modb_received = 0;
            usart1.mb_status.modb_receiving = 0;
            usart1.in_buffer_count = 0;
            usart1.mb_status.modb_transmiting = 0;
            IFS3bits.U1RXIF = 0;
            ENAB_RX1;
            IEC3bits.U1RXIE = 1; //disable RX interrupt
        }
        if (U1STAbits.OERR || U1STAbits.FERR) {
            U1STAbits.OERR = 0;
        }
    }
}

void stop_uart_tx_dma(void) {
    if (usart4.mb_status.tx_mode == DMA_type) {
        if ((usart4.mb_status.modb_transmiting == 1)&&(U4STAbits.TRMT)) {
            usart4.mb_status.modb_transmiting = 0;
            DMA_uni(&usart4, 1, 0, 0);
            usart4.mb_status.modb_received = 0;
            usart4.mb_status.modb_receiving = 0;
            usart4.in_buffer_count = 0;
            IFS5bits.U4RXIF = 0;
            ENAB_RX4;
            IEC5bits.U4RXIE = 1;
        }
        if (U4STAbits.OERR || U4STAbits.FERR) {
            U4STAbits.OERR = 0;
        }
    }

    if (usart5.mb_status.tx_mode == DMA_type) {
        if ((usart5.mb_status.modb_transmiting == 1)&&(U5STAbits.TRMT)) {
            usart5.mb_status.modb_transmiting = 0;
            DMA_uni(&usart5, 1, 0, 0);
            usart5.mb_status.modb_received = 0;
            usart5.mb_status.modb_receiving = 0;
            usart5.in_buffer_count = 0;
            IFS5bits.U5RXIF = 0;
            ENAB_RX5;
            IEC5bits.U5RXIE = 1;
        }
        if (U5STAbits.OERR || U5STAbits.FERR) {
            U5STAbits.OERR = 0;
        }
    }
    if (usart3.mb_status.tx_mode == DMA_type) {
        if ((usart3.mb_status.modb_transmiting == 1)&&(U3STAbits.TRMT)) {
            usart3.mb_status.modb_transmiting = 0;
            DMA_uni(&usart3, 1, 0, 0);
            usart3.mb_status.modb_received = 0;
            usart3.mb_status.modb_receiving = 0;
            usart3.in_buffer_count = 0;
            IFS4bits.U3RXIF;
            ENAB_RX3;
            IEC4bits.U3RXIE = 1;
        }
        if (U3STAbits.OERR || U3STAbits.FERR) {
            U3STAbits.OERR = 0;
        }
    }
    if (usart2.mb_status.tx_mode == DMA_type) {
        if ((usart2.mb_status.modb_transmiting == 1)&&(U2STAbits.TRMT)) {
            usart2.mb_status.modb_transmiting = 0;
            DMA_uni(&usart2, 1, 0, 0);
            usart2.mb_status.modb_received = 0;
            usart2.mb_status.modb_receiving = 0;
            usart2.in_buffer_count = 0;
            IFS4bits.U2RXIF;
            ENAB_RX2;
            IEC4bits.U2RXIE = 1;
        }
        if (U2STAbits.OERR || U2STAbits.FERR) {
            U2STAbits.OERR = 0;
        }
    }
    if (usart1.mb_status.tx_mode == DMA_type) {
        if ((usart1.mb_status.modb_transmiting == 1)&&(U1STAbits.TRMT)) {
            usart1.mb_status.modb_transmiting = 0;
            DMA_uni(&usart1, 1, 0, 0);
            usart1.mb_status.modb_received = 0;
            usart1.mb_status.modb_receiving = 0;
            usart1.in_buffer_count = 0;
            IFS3bits.U1RXIF;
            ENAB_RX1;
            IEC3bits.U1RXIE = 1;
        }
        if (U1STAbits.OERR || U1STAbits.FERR) {
            U1STAbits.OERR = 0;
        }
    }
}

void close_mb(struct tag_usart * usart) {
    usart->mb_status.modb_received = 0;
    usart->mb_status.modb_receiving = 0;
    usart->in_buffer_count = 0;
}

void answer_illegal(struct tag_usart * usart, unsigned char illegal) {
    usart->out_buffer[0x00] = usart->in_buffer[0];
    usart->out_buffer[0x01] = usart->in_buffer[1] | 0x80;
    usart->out_buffer [0x02] = illegal;
    PIC_CRC16(usart->out_buffer, 0x03);
    usart->out_buffer [0x03] = uchCRCLo;
    usart->out_buffer [0x04] = uchCRCHi;
    usart->number_send = 5;
}

void answer_illegal_func(struct tag_usart * usart) {
    answer_illegal(usart, 0x01);
    if (usart->mb_status.tx_mode == INT_type) {
        start_tx_usart(usart);
    } else {
        start_tx_usart_dma(usart, 5);
    }
}

void answer_illegal_data_addr(struct tag_usart * usart) {
    answer_illegal(usart, 0x02);
    if (usart->mb_status.tx_mode == INT_type) {
        start_tx_usart(usart);
    } else {
        start_tx_usart_dma(usart, 5);
    }
}

void answer_illegal_data_val(struct tag_usart * usart) {
    answer_illegal(usart, 0x03);
    if (usart->mb_status.tx_mode == INT_type) {
        start_tx_usart(usart);
    } else {
        start_tx_usart_dma(usart, 5);
    }
}

unsigned short num3;

void mbs_03(struct tag_usart * _usart, unsigned short * source, unsigned short shift, unsigned short num) {
    num3 = num;
    memcpy((void*) (_usart->out_buffer + 0x03), (const void*) (source + shift), (num3 * 2));
    num3 *= 2;
    _usart->out_buffer[0] = _usart->in_buffer[0];
    _usart->out_buffer[1] = _usart->in_buffer[1];
    _usart->out_buffer [0x02] = num3;
    num3 += 0x03;
    PIC_CRC16(_usart->out_buffer, (num3));
    _usart->out_buffer [num3++] = uchCRCLo;
    _usart->out_buffer [num3++] = uchCRCHi;
    _usart->number_send = num3;
    if (_usart->mb_status.tx_mode == DMA_type) {
        start_tx_usart_dma(_usart, num3);
    } else {
        start_tx_usart(_usart);
    }
}

void mbs_10(struct tag_usart * _usart, unsigned short * source, unsigned short shift_uni, unsigned short num_uni) {
    //	unsigned int help_store [10];
    unsigned short ii, upd;

    upd = 0;

    if (source == MB_swap.input) {
        memcpy((void *) (MB_swap.input + shift_uni), (const void *) (_usart->in_buffer + 0x07), (num_uni * 2));
        for (ii = 0; ii < num_uni; ii++) {
            MB.input [ii + shift_uni] = swapshort(MB_swap.input [ii + shift_uni]);
            MB.input [ii + shift_uni] = _bswapw(MB.input [ii + shift_uni]);
        }
    }

    if (source == MB_sw_conf.buf) {
        memcpy((void *) (MB_sw_conf.buf + shift_uni), (const void *) (_usart->in_buffer + 0x07), (num_uni * 2));

        for (ii = 0; ii < num_uni; ii++) {
            MB_conf.buf [ii + shift_uni] = swapshort(MB_sw_conf.buf [ii + shift_uni]);
        }
        putcs_FRAM(RAMTRON_START_CONFIG, MB_conf.buf, 180);
        getcs_FRAM(RAMTRON_START_CONFIG, MB_conf.buf, 180);
        load_config();
    }
    if (source == Modbus_sw.buf) {
        memcpy((void *) (Modbus_sw.buf + shift_uni), (const void *) (_usart->in_buffer + 0x07), (num_uni * 2));
        for (ii = 0; ii < num_uni; ii++) {
            Modbus.buf [ii + shift_uni] = swapshort(Modbus_sw.buf [ii + shift_uni]);
        }
        //		if ((MB_work_tmp.SET >= 0.0) && (MB_work_tmp.SET <= 100.0)) {FLAP_SET = MB_work_tmp.SET; }
        //		else {
        //			MB_work_tmp.SET = FLAP_SET; 
        //			MB_work_swap.SET = FLAP_SET; 
        //            MB_work_swap.buf  [6] = swapshort(MB_work_swap.buf  [6]);
        //            MB_work_swap.buf  [7] = swapshort(MB_work_swap.buf  [7]);
        //			answer_illegal_data_val (_usart); 
        //			return;
        //			}
        //		MB_work.cmd1 = MB_work_tmp.cmd1;
        //		MB_work.cmd2 = MB_work_tmp.cmd2;
    }


    _usart->out_buffer [0x00] = _usart->in_buffer[0x00];
    _usart->out_buffer [0x01] = _usart->in_buffer[0x01];
    _usart->out_buffer [0x02] = _usart->in_buffer[0x02];
    _usart->out_buffer [0x03] = _usart->in_buffer[0x03];
    _usart->out_buffer [0x04] = _usart->in_buffer[0x04];
    _usart->out_buffer [0x05] = _usart->in_buffer[0x05];
    PIC_CRC16(_usart->out_buffer, (0x06));
    _usart->out_buffer [0x06] = uchCRCLo;
    _usart->out_buffer [0x07] = uchCRCHi;
    _usart->number_send = 0x08;
    if (_usart->mb_status.tx_mode == DMA_type) {
        start_tx_usart_dma(_usart, _usart->number_send);
    } else {
        start_tx_usart(_usart);
    }
}

unsigned short num_reg;
unsigned short start_reg;
unsigned short last_reg;
unsigned short length_err;

void mbs_uni(struct tag_usart * usart, unsigned char mbs_addres) {
    if (usart->mb_status.modb_received) {
        PIC_CRC16(usart->in_buffer, (usart->in_buffer_count)); // wrong CRC 
        if (uchCRCLo | uchCRCHi) {
            close_mb(usart);
            return;
        } // no actions

        start_reg = usart->in_buffer[0x02]*0x100;
        start_reg += usart->in_buffer[0x03];
        num_reg = usart->in_buffer[0x04]*0x100;
        num_reg += usart->in_buffer[0x05];

        last_reg = start_reg + num_reg;

        if (((usart->in_buffer_count - 9) != usart->in_buffer[0x06])&&(usart->in_buffer[1] == 0x10)) // quantity must be equal to
        { // number received bytes - 9 bytes
            length_err = 1;
        } else {
            length_err = 0;
        }
        if (((usart->in_buffer_count - 9) != (num_reg * 2))&&(usart->in_buffer[1] == 0x10)) // num reg*2 must be equal to
        {
            length_err = 1;
        } else {
            length_err = 0;
        }

        switch (length_err) {
            case 1:
            {
                answer_illegal_data_addr(usart);
                break;
            } // ?????? ??? ????????? ????? ??????? ? ????????? ?????????? ??????
            default:
            {
                switch (usart->in_buffer[1]) {
                    case 0x03:
                    {
                        if (READ_) {
                            mbs_03(usart, MB_swap.buf, (start_reg - START_READ), num_reg);
                            break;
                        } // 2000 ... 2078
                        if (CONF_READ_) {
                            mbs_03(usart, MB_sw_conf.buf, (start_reg - START_CONF_READ), num_reg);
                            break;
                        } // 500 ... 680
                        if (MODBUS_READ_) {
                            mbs_03(usart, Modbus_sw.buf, (start_reg - START_MODBUS_READ), num_reg);
                            break;
                        } // 0 ... 80
                        if (MB_DIAGN_READ_) {
                            mbs_03(usart, MB_diagn_sw.buf, (start_reg - START_MB_DIAGN_READ), num_reg);
                            break;
                        } // 200 ... 312
                        answer_illegal_data_addr(usart);
                        break;
                    }

                    case 0x10:
                    {
                        if (WRITE_) {
                            mbs_10(usart, MB_swap.input, (start_reg - START_WRITE), num_reg);
                            break;
                        }
                        if (CONF_WRITE_) {
                            mbs_10(usart, MB_sw_conf.buf, (start_reg - START_CONF_WRITE), num_reg);
                            break;
                        }
                        if (MODBUS_WRITE_) {
                            mbs_10(usart, Modbus_sw.buf, (start_reg - START_MODBUS_WRITE), num_reg);
                            break;
                        }
                        answer_illegal_data_addr(usart);
                        break;
                    }

                    default:
                    {
                        answer_illegal_func(usart);
                        break;
                    }
                }
            }
        }
    }
    close_mb(usart);
}

void mbs(struct tag_usart * usart, unsigned char mbs_addres) {
    if (!usart->mb_status.modb_received) {
        return; //return if nothing received
    }

    if (usart->in_buffer[0] == mbs_addres) {
        mbs_uni(usart, mbs_addres);
        return;
    } else {
        close_mb(usart);
        return;
    }

}

void mbm_03(struct tag_usart *usart, unsigned char mbm_adres, unsigned int shift_03, unsigned int quant_03, unsigned int *dest, unsigned int speed) {

    unsigned int cc;
    if (!usart->mb_status.master_start) {
        return;
    }
    switch (usart->mbm_status) {
        case 0:
        {
            if (usart == &usart1) {
                UART1_init(speed);
            }
            //            if (usart == &usart2) {
            //                UART2_init(speed, 4);
            //            }
            switch (speed) {
                case 1:
                {
                    usart->mbm_timeout = 240;
                    break;
                }
                case 2:
                {
                    usart->mbm_timeout = 120;
                    break;
                }
                case 3:
                {
                    usart->mbm_timeout = 80;
                    break;
                }
                case 4:
                {
                    usart->mbm_timeout = 40;
                    break;
                }
                case 5:
                {
                    usart->mbm_timeout = 20;
                    break;
                }
                case 6:
                {
                    usart->mbm_timeout = 12;
                    break;
                }
                case 7:
                {
                    usart->mbm_timeout = 5;
                    break;
                }
                case 8:
                {
                    usart->mbm_timeout = 4;
                    break;
                }
            }
            usart->mbm_status = 1;
            break;
        }
        case 1:
        {
            usart->out_buffer[0x00] = mbm_adres;
            usart->out_buffer[0x01] = 0x03;
            usart->out_buffer[0x03] = shift_03 & 0x00FF;
            usart->out_buffer[0x02] = (shift_03 >> 8) & 0x00FF;
            usart->out_buffer[0x05] = quant_03 & 0x00FF;
            usart->out_buffer[0x04] = (quant_03 >> 8) & 0x00FF;
            PIC_CRC16(usart->out_buffer, 0x06);
            usart->out_buffer[0x06] = uchCRCLo;
            usart->out_buffer[0x07] = uchCRCHi;
            usart->number_send = 0x08;
            usart->mbm_timeout = 10;
            usart->mb_status.tm_on = 1;
            //            if (usart == &usart2) {
            //                T4_delay_5 = mbm_timeout;
            //                t4_del_5 = 1;
            //            }
            usart->mb_status.master_timeout = 0;
            usart->mb_status.modb_received = 0;
            usart->mb_status.byte_missing = 0;
            usart->mb_status.crc_error = 0;
            usart->mb_status.device_error = 0;
            usart->mb_status.coll_1 = 0;
            usart->mb_status.coll_2 = 0;
            usart->mb_status.coll_3 = 0;
            start_tx_usart(usart);
            usart->mbm_status = 2;
            break;
        }
        case 2:
        {
            if (!usart->mb_status.master_timeout && !usart->mb_status.modb_received)
                return;
            if (usart->mb_status.master_timeout) {
                usart->mbm_err++;
                usart->mbm_status = 0;
                usart->mb_status.master_start = 0;
                break;
            }

            if (usart->in_buffer[1] == 0x83) // modbus collisions
            {
                if (usart->in_buffer[2] == 0x01) {
                    usart->mb_status.coll_1 = 1;
                    usart->mbm_err++;
                    usart->mb_status.master_start = 0;
                    usart->mbm_status = 0;
                    break;
                }
                if (usart->in_buffer[2] == 0x02) {
                    usart->mb_status.coll_2 = 1;
                    usart->mbm_err++;
                    usart->mb_status.master_start = 0;
                    usart->mbm_status = 0;
                    break;
                }
                if (usart->in_buffer[2] == 0x03) {
                    usart->mb_status.coll_3 = 1;
                    usart->mbm_err++;
                    usart->mb_status.master_start = 0;
                    usart->mbm_status = 0;
                    break;
                }
            }
            //			if (usart->in_buffer_count!=(quant_03*2+5))									//byte missing
            //				{usart->mbm_status=0; usart->mb_status.byte_missing=1; usart->mbm_err++; usart->mb_status.master_start=0; break;}
            if (usart->in_buffer[0] != usart->out_buffer[0]) // wrong device address
            {
                usart->mbm_status = 0;
                usart->mb_status.device_error = 1;
                usart->mbm_err++;
                usart->mb_status.master_start = 0;
                break;
            }
            PIC_CRC16(usart->in_buffer, (usart->in_buffer_count));
            if (uchCRCLo | uchCRCHi) {
                usart->mbm_status = 0;
                usart->mb_status.crc_error = 1;
                usart->mbm_err++;
                usart->mb_status.master_start = 0;
                break;
            } // wrong crc

            memcpy((void *) (dest), (const void *) (usart->in_buffer + 0x03), usart->in_buffer[2]);
            for (cc = 0; cc < quant_03; cc++) {
                //              MOPS.main_area[cc + shift_03] = swapshort(MOPS_swap.main_area[cc + shift_03]);
            }
            usart->answer_count++;
            usart->mb_status.master_error = 0;
            usart->mb_status.master_start = 0;
            usart->mbm_status = 0;
            break;
        }
        default:
        {
            usart->mb_status.master_start = 0;
            usart->mbm_status = 0;
            break;
        }
    }
}




