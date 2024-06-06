
#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "system/common/../../define.h" // SYS function prototypes
#include "system/common/../../extern.h"
#include "ramtron_drv.h"

#if defined(__32MZ1024EFH100__)
#include <p32xxxx.h>
#include <sys/attribs.h>
//    #include <../framework/peripheral/spi/plib_spi.h>
//    #include "../framework/peripheral/int/plib_int.h"
// #include "../system_config.h"
// #include "../Common/system/clk/sys_clk.h"
#elif defined(__32MX795F512L__)
#include <p32xxxx.h>
//    #include <plib.h>
#include "../Common/peripheral/spi/plib_spi.h"
#elif defined(__dsPIC30F6010A__)
#include <p30f6010A.h>
#include <p30fxxxx.h>
#include <libpic30.h>
#include <spi.h>
#else
#include <p33EP512MU814.h>
#include <p33Exxxx.h>
#include <libpic30.h>
#include <spi.h>
#endif

#if defined(__FREERTOS__)
#include "FreeRTOSConfig.h"
#endif

#include <stdlib.h>
#include "ramtron_drv.h"

inline void SPI_BufferWrite(unsigned char a)
{
    while (SPI5STATbits.SPITBF)
        ;
    SPI5BUF = a;
} //
inline unsigned char SPI_BufferRead(void)
{
    while (SPI5STATbits.SPIRBE)
        ;
    return SPI5BUF;
} //

// inline void SPI_BufferWrite ()

#if defined(__32MZ1024EFH100__)
#define SPI_PUTC(a) SPI_BufferWrite(a)
#define SPI_GETC SPI_BufferRead()
// #define SPI_PUTC(a)                 SPI_BufferWrite(MEM_SPI_CHANNEL, a)
// #define SPI_GETC                    SPI_BufferRead(MEM_SPI_CHANNEL)

#define SPI_BUSY SPI5STATbits.SPIBUSY // PLIB_SPI_IsBusy(MEM_SPI_CHANNAL)
#define SPI_TRANS_BUF_FULL PLIB_SPI_TransmitBufferIsFull(MEMORY_BUS_SPEED)
#elif defined(__32MX795F512L__)

#ifdef __PLIB__
#define SPI_PUTC(a) SpiChnPutC(4, a)
#define SPI_GETC SpiChnGetC(4)
#define SPI_BUSY SpiChnIsBusy(4)
#else
#define SPI_PUTC(a) PLIB_SPI_BufferWrite(MEM_SPI_CHANNAL, a)
#define SPI_GETC SPI_BufferRead(MEM_SPI_CHANNAL);
#define SPI_BUSY PLIB_SPI_IsBusy(MEM_SPI_CHANNAL)
#endif
#else
#define SPI_PUTC WriteSPI1
#define SPI_GETC ReadSPI1()
#define SPI_BUSY !DataRdySPI1()
#endif

TMEMORY RAMTRON_RAM =
    {
        vMemoryInit,
        putc_FRAM,
        getc_FRAM,
        //    puts_FRAM,
        //    gets_FRAM,
        we_FRAM,
        wd_FRAM,
        erase_FRAM};

// void __ISR(_SPI5_RX_VECTOR, ipl0AUTO) vSPI5Interrupt( void );
// void __attribute__( (interrupt(ipl0), vector(_SPI5_RX_VECTOR))) vSPI5Interrupt( void );

unsigned char ucStoredData;
unsigned char ucAdressH;
unsigned char ucAdressL;

// functions prototypes
void vMemoryInit(void);
void getcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len);
void putcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len);
void getss_FRAM(unsigned short adress, unsigned short *pstr, unsigned short len);
void putss_FRAM(unsigned short adress, unsigned short *pstr, unsigned short len);
void getc_FRAM(unsigned short adress, unsigned char *pchr);
void putc_FRAM(unsigned short adress, unsigned char chr);
void we_FRAM(void);
void wd_FRAM(void);
void erase_FRAM(void);

extern unsigned char vMemTest();

void vMemDelay(unsigned short usDelay)
{
    static char dummy;

    while (usDelay--)
    {
        dummy = dummy;
    }
}

/*Init SPI*/
void vMemoryInit(void)
{
    //    return vSpiInit();
}

/*
void vMemorySetBitRate(void)
{
    vSpiSetBitRate();
}
*/

// unsigned char SPI_BufferRead(SPI_MODULE_ID index)
//{
//     unsigned long ulTime;
//     unsigned char ucError = 0;
//
//     _CP0_SET_COUNT(0);
//     ulTime = _CP0_GET_COUNT();
//
//     do {
//         if(( _CP0_GET_COUNT() - ulTime) > 221184) {  //5ms timeout
//             ucError = 1;
//             break;
//         }
//     } while(!PLIB_SPI_ReceiverBufferIsFull(index));
//
//     if(!ucError)
//         return SPI_BufferRead_Default(index);
//     else
//         return 0xff;
// }

volatile unsigned char iDta;
/*Get string*/
void getcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len)
{
    unsigned char ucData;
    ucAdressH = (adress >> 8) & 0xff;
    ucAdressL = adress & 0xff;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(READ);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressH);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressL);
    iDta = SPI_GETC;
    while (--len)
    {
        SPI_PUTC(0x00);
        ucData = SPI_GETC;
        *pstr++ = ucData;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
    }

    MEMORY_SET_CS;
}

/*Put string*/
void putcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len)
{
    ucAdressH = (adress >> 8) & 0xff;
    ucAdressL = adress & 0xff;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WREN);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WRITE);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressH);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressL);
    iDta = SPI_GETC;
    while (len--)
    {
        SPI_PUTC(*pstr++);
        iDta = SPI_GETC;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
    }
    MEMORY_SET_CS;
}

void getss_FRAM(unsigned short adress, unsigned short *pstr, unsigned short len)
{
    unsigned char ucDataH, ucDataL;
    unsigned short usData;
    unsigned char ucData;
    ucAdressH = (adress >> 8) & 0xff;
    ucAdressL = adress & 0xff;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(READ);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressH);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressL);
    iDta = SPI_GETC;
    while (--len)
    {
        SPI_PUTC(0x01);
        ucData = SPI_GETC;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
        ucDataH = ucData;
        SPI_PUTC(0x01);
        ucData = SPI_GETC;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
        ucDataL = ucData;
        *pstr++ = (ucDataH << 8) | ucDataL;
    }
    MEMORY_SET_CS;
}

/*Put string*/
void putss_FRAM(unsigned short adress, unsigned short *pstr, unsigned short len)
{
    unsigned char ucDataH, ucDataL;

    ucAdressH = (adress >> 8) & 0xff;
    ucAdressL = adress & 0xff;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WREN);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //    while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WRITE);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressH);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressL);
    iDta = SPI_GETC;
    while (len--)
    {
        ucDataH = *pstr >> 8;
        ucDataL = *pstr & 0xff;

        SPI_PUTC(ucDataH);
        iDta = SPI_GETC;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
        SPI_PUTC(ucDataL);
        iDta = SPI_GETC;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
        *pstr++;
    }
    MEMORY_SET_CS;
}

/*Get char*/
void getc_FRAM(unsigned short adress, unsigned char *pchr)
{
    ucAdressH = (adress >> 8) & 0xff;
    ucAdressL = adress & 0xff;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(READ);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressH);
    iDta = SPI_GETC;
    SPI_PUTC(ucAdressL);
    iDta = SPI_GETC;
    SPI_PUTC(0x00);
    ucStoredData = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    *pchr = ucStoredData;

    MEMORY_SET_CS;
}

/*Put char*/
void putc_FRAM(unsigned short adress, unsigned char chr)
{
    ucAdressH = (adress >> 8) & 0xff;
    ucAdressL = adress & 0xff;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WREN);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //    while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WRITE);
    iDta = SPI_GETC;
    SPI_PUTC((adress >> 8) & 0xff);
    iDta = SPI_GETC;
    SPI_PUTC(adress & 0xff);
    iDta = SPI_GETC;
    SPI_PUTC(chr);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //    while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;
}

/*Wrote comand char*/
void put_cmd_FRAM(unsigned short adress, unsigned char chr)
{
    MEMORY_CLR_CS;
    SPI_PUTC(WRITE_PC);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    SPI_PUTC(adress);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    SPI_PUTC(chr);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;
}

/*Write enable*/
void we_FRAM(void)
{
    MEMORY_CLR_CS;
    SPI_PUTC(WREN);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;
}

/*Write disable*/
void wd_FRAM(void)
{
    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WRDI);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;
}

/*Erase*/
void erase_FRAM(void)
{
    static unsigned short len = MEMORY_SIZE;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WREN);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;

    MEMORY_CLR_CS;
    SPI_PUTC(WRITE);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    SPI_PUTC(0);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    SPI_PUTC(0);
    iDta = SPI_GETC;
    while (len--)
    {
        SPI_PUTC(0);
        iDta = SPI_GETC;
        while (SPI_BUSY)
            ;
        //        while(SPI5STATbits.SPIBUSY );
    }
    MEMORY_SET_CS;
}

/*Put/Get char*/
unsigned char pgetc_FRAM(unsigned short adress, unsigned char chr)
{
    static unsigned char data;

    MEMORY_SET_OTHER_CS;

    MEMORY_CLR_CS;
    SPI_PUTC((adress >> 8) & 0xff);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    SPI_PUTC(adress & 0xff);
    iDta = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    SPI_PUTC(chr);
    data = SPI_GETC;
    while (SPI_BUSY)
        ;
    //        while(SPI5STATbits.SPIBUSY );
    MEMORY_SET_CS;
    return data;
}

unsigned short usSpiBuf[5];
void vSPI5InterruptHandler(void)
{
    static unsigned char ucCnt = 0;
    if (ucCnt++ < 5)
        usSpiBuf[ucCnt] = SPI5BUF;
    IFS5bits.SPI5EIF = 0;
    IFS5bits.SPI5RXIF = 0;
    IFS5bits.SPI5TXIF = 0;
    //    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_SPI_5_RECEIVE);
}

void load_config(void)
{
    unsigned short iii;
    //	getcs_FRAM(RAMTRON_START_CONFIG, MB_conf.buf, 392);
    getcs_FRAM(RAMTRON_START_CONFIG, (unsigned char *)MB_conf.buf, 180);
    //	for (iii=0; iii<196; iii++) {		MB_sw_conf.buf  [iii] = swapshort(MB_conf.buf  [iii]);		}
    for (iii = 0; iii < 90; iii++)
    {
        MB_sw_conf.buf[iii] = swapshort(MB_conf.buf[iii]);
    }
}

/* *****************************************************************************
 End of File
 */
