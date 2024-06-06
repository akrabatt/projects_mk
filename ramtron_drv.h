#ifndef __RAMTRON_DRV_H__
#define __RAMTRON_DRV_H__

#define __FM33256__

#if defined(__FM33256__)
#define MEMORY_SIZE 0x7fff
#else
#define MEMORY_SIZE 0x3ff
#endif
#if defined(__32MZ1024EFH100__)
#include <proc/p32mz1024efh100.h>
// #include <../framework/peripheral/spi/processor/spi_p32mz1024efh100.h>
#elif defined(__32MX795F512L__)
#include "../Common/peripheral/spi/processor/spi_p32mx795f512l.h"
// #include <plib.h>

#endif

// #if 0
// #define MEMORY_BUS_SPEED    8000000
// #define MEM_SPI_CHANNAL     SPI_CHANNEL2
//
///*---------------------------------------------------------------*/
///*Defines for chip select*/
///*---------------------------------------------------------------*/
// #define MEMORY_TRIS         TRISG
// #define MEMORY_PORT         PORTG
// #define MEMORY_CS           (1 << 9)
//
// #define MEMORY_SET_CS        MEMORY_PORT |= MEMORY_CS;\
//                            Nop();\
//                            Nop();\
//                            Nop()
//
// #define MEMORY_CLR_CS        Nop();\
//                            Nop();\
//                            Nop();\
//                            MEMORY_PORT &= ~MEMORY_CS
// #else

#if defined(__32MZ1024EFH100__)

#define MEMORY_BUS_SPEED 8000000UL
#define MEM_SPI_CHANNAL SPI_ID_5
// #define MEM_SPI_CHANNAL     SPI_CHANNEL4

/*---------------------------------------------------------------*/
/*Defines for chip select*/
/*---------------------------------------------------------------*/
#define MEMORY_TRIS TRISB
#define MEMORY_PORT PORTB
#define MEMORY_LATCH LATB
#define MEMORY_CS (1 << 8)

#define MEMORY_SET_CS                       \
    MEMORY_PORT = MEMORY_LATCH | MEMORY_CS; \
    while ((MEMORY_PORT & MEMORY_CS) == 0)  \
        ;

#define MEMORY_CLR_CS                              \
    MEMORY_PORT = MEMORY_LATCH & ~MEMORY_CS;       \
    while ((MEMORY_PORT & MEMORY_CS) == MEMORY_CS) \
        ;

#define MEMORY_SET_OTHER_CS //PORTB = LATB | ((1 << 12) | (1 << 13));\
//                            while( (PORTB & (( 1<< 12) | ( 1<< 13))) == ((1 << 12) | (1 << 13)) )

#elif defined(__32MX795F512L__)
#define MEMORY_BUS_SPEED 8000000UL
#define MEM_SPI_CHANNAL SPI_ID_5
// #define MEM_SPI_CHANNAL     SPI_CHANNEL4

/*---------------------------------------------------------------*/
/*Defines for chip select*/
/*---------------------------------------------------------------*/
#define MEMORY_TRIS TRISB
#define MEMORY_PORT PORTB
#define MEMORY_LATCH LATB
#define MEMORY_CS (1 << 8)

#define MEMORY_SET_CS                       \
    MEMORY_PORT = MEMORY_LATCH | MEMORY_CS; \
    while ((MEMORY_PORT & MEMORY_CS) == 0)

#define MEMORY_CLR_CS                        \
    MEMORY_PORT = MEMORY_LATCH & ~MEMORY_CS; \
    while ((MEMORY_PORT & MEMORY_CS) == MEMORY_CS)

#define MEMORY_SET_OTHER_CS                 \
    PORTB = LATB | ((1 << 12) | (1 << 13)); \
    while ((PORTB & ((1 << 12) | (1 << 13))) == ((1 << 12) | (1 << 13)))
#endif
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/*Memory comands*/
/*---------------------------------------------------------------*/
#define WREN 0x06
#define WRDI 0b00000100
#define RDSR 0b00000101
#define WRSR 0b00000001
#define READ 0x03
#define WRITE 0x02
#define READ_PC 0x13
#define WRITE_PC 0x12
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
/* HAL Interface*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------*/
// ????????? ?????? ??? ?????????? ?????? ? FRAM
/*----------------------------------------------------------------------------------------*/
#define FRAM_F_WRIRE_KEY 0xb1

#define FRAM_SAVED_KZG_DATA 100
#define FRAM_CODE_CRC_KEY 400

// #define FRAM_DEV_SERIAL                     150

// #define FRAM_RESET_CNT                      400

#define FRAM_DEV_INFO 410

#define FRAM_TEST 510
#define FRAM_TEST2 509

#define FRAM_JOURNAL_CNT 730
#define FRAM_JOURNAL_ARRAY 731

typedef struct
{
    // init
    void (*minit)();
    // put char
    void (*mputc)(unsigned short adress, unsigned char chr);
    // grt char
    void (*mgetc)(unsigned short adress, unsigned char *pchr);
    // put string
    //    void (*mputs)(unsigned short adress, unsigned char *pchr, unsigned int len);
    //    //get string
    //    void (*mgets)(unsigned short adress, unsigned char *pchr, unsigned int len);
    // write enable
    void (*mwenable)();
    // write diaable
    void (*mwdisable)();
    // erase
    void (*merase)();
} TMEMORY;

extern TMEMORY RAMTRON_RAM;

// inline void SPI_BufferWrite(SPI_MODULE_ID MODULE_ID, unsigned char a);
extern void vMemoryInit(void);
extern void vMemorySetBitRate(void);
extern void getcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len);
extern void putcs_FRAM(unsigned short adress, unsigned char *pstr, unsigned short len);
extern void getss_FRAM(unsigned short adress, unsigned short *pstr, unsigned short len);
extern void putss_FRAM(unsigned short adress, unsigned short *pstr, unsigned short len);
extern void getc_FRAM(unsigned short adress, unsigned char *pchr);
extern void putc_FRAM(unsigned short adress, unsigned char chr);
extern void we_FRAM(void);
extern void wd_FRAM(void);
extern void erase_FRAM(void);
// unsigned char SPI_BufferRead(SPI_MODULE_ID index);
/*
inline void SPI_BufferWrite( unsigned char a)
{
    while (!SPI5STATbits.SPITBF) {SPI5BUF = a;}
}

*/

#endif
/* *****************************************************************************
 End of File
 */
