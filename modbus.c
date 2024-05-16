#include "extern.h"

// таблица для функции CRC, эта используется для хранения старшего байта
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
    0x40};
// эта используется для хранения младшего байта
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
    0x40};

unsigned char uchCRCHi = 0xFF;
unsigned char uchCRCLo = 0xFF;

// эта функция реализует расчет CRC16 для переданного массива данных puchMsg, длинной usDataLen
// Внутри цикла вычисляются новые значения uchCRCLo и uchCRCHi на основе текущего байта
// сообщения и значений из таблицы auchCRCHi и auchCRCLo.
void PIC_CRC16(unsigned char *puchMsg, unsigned short usDataLen)
{
    unsigned char uIndex; // переменная будет использоваться для индексации в таблицах CRC
    uchCRCHi = 0xFF;      // старший байт
    uchCRCLo = 0xFF;      // младший байт
    while (usDataLen--)   // начало цикла который будет выполняться usDataLen-раз для каждого байта в сообщении
    {
        // Используется текущий байт сообщения (*puchMsg) для вычисления индекса uIndex,
        // который используется для доступа к соответствующим значениям из таблицы CRC.
        uIndex = uchCRCLo ^ *puchMsg++;

        // Обновление младшего байта CRC16 (uchCRCLo) путем выполнения операции XOR между текущим
        // значением старшего байта CRC (uchCRCHi) и значением из таблицы auchCRCHi по индексу uIndex.
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];

        // Обновление старшего байта CRC16 (uchCRCHi) новым значением из таблицы auchCRCLo по индексу uIndex.
        uchCRCHi = auchCRCLo[uIndex];
    }
}
/* Таким образом, вся функция PIC_CRC16 выполняет итеративное обновление старшего и младшего байтов контрольной суммы CRC16
для массива данных (puchMsg) заданной длины (usDataLen). Каждый байт данных используется для обновления текущего состояния CRC16,
используя таблицы предварительно вычисленных значений (auchCRCHi и auchCRCLo). */

/* В контексте вычисления циклической избыточности (CRC) обновление старшего и младшего байта означает изменение значений, используемых для
вычисления контрольной суммы CRC16. В приведенной функции PIC_CRC16, старший байт обозначается как uchCRCHi, а младший байт — как uchCRCLo.

Когда вы вычисляете CRC16 для некоторых данных (например, сообщения или пакета данных), вы начинаете с начальных значений uchCRCHi = 0xFF и
uchCRCLo = 0xFF. Затем для каждого байта данных вы выполняете следующие шаги:

Обновление uchCRCLo:

Сначала uchCRCLo (младший байт CRC16) изменяется путем выполнения операции XOR между текущим значением uchCRCHi (старший байт) и
определенным байтом данных. Это обновление помогает учесть новые данные в контрольной сумме. Обновление uchCRCHi:

Затем uchCRCHi (старший байт CRC16) изменяется на основе нового значения uchCRCLo (младшего байта CRC16), используя значение из
таблицы auchCRCLo. Это также влияет на состояние CRC16 и учитывает предыдущие данные.
Эти шаги выполняются для каждого байта данных в цикле while (usDataLen--), где usDataLen уменьшается с каждой итерацией. В результате
выполнения всех итераций старший и младший байты uchCRCHi и uchCRCLo будут содержать окончательное значение CRC16 для всего сообщения или пакета
данных. */

// таблица предварительно вычеслинных значений для быстрого вычисления CRC16
// она используется для оптимизации расчета контрольной суммы
static const unsigned int wCRCTable[] = {
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
    0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040};

// перстановка байтов

// Функция swapshort предназначена для перестановки байтов в 16-битном беззнаковом коротком целом числе (unsigned short).
// Это может быть полезно, если порядок байтов в числе нужно изменить для совместимости с форматом,
// принятым на другой платформе или устройстве.
// unsigned short swapshort(unsigned short data): Это объявление функции swapshort, которая принимает беззнаковое короткое целое число 
// (unsigned short) в качестве аргумента и возвращает также беззнаковое короткое целое число после перестановки байтов.
unsigned short swapshort(unsigned short data)
{
    // Объявление объединения (union) для работы с двумя форматами данных: short и char (байтовый массив)
    // union {...} conv, sconv;: Здесь объявляется объединение (union), позволяющее интерпретировать одну и ту же 
    // область памяти как два различных типа данных (unsigned short и unsigned char[2]), что позволяет нам 
    // манипулировать отдельными байтами числа.
    union
    {
        unsigned short sdata;   // 16-битное беззнаковое целое число (исходный формат)
        unsigned char cdata[2]; // Байтовый массив из 2 элементов (для доступа к каждому байту)
    } conv, sconv;

    conv.sdata = data;              // Запись исходного значения в поле sdata объединения conv

    // Здесь происходит фактическая перестановка байтов. Мы присваиваем старшему байту (cdata[1] в sconv) младший байт 
    // (cdata[0] в conv), а младшему байту (cdata[0] в sconv) — старший байт (cdata[1] в conv).
    sconv.cdata[1] = conv.cdata[0]; // Старший байт (второй по порядку) получает младший байт исходного числа
    sconv.cdata[0] = conv.cdata[1]; // Младший байт (первый по порядку) получает старший байт исходного числа
    return sconv.sdata;             // Возврат результата как беззнаковое короткое целое число с переставленными байтами
}

// для флота
// Эта функция переставляет байты младшего и старшего порядка в представлении числа с плавающей точкой (float).

float swapfloat(float data)
{
    // Также используется объединение union, но здесь float разбивается на два 16-битных значения sdata,
    // которые затем переставляются в массиве cdata.
    union
    {
        float fdata;
        unsigned short sdata[2];
        unsigned char cdata[4];
    } conv, sconv;

    conv.fdata = data;
    sconv.cdata[1] = conv.cdata[0];
    sconv.cdata[0] = conv.cdata[1];
    sconv.cdata[2] = conv.cdata[3];
    sconv.cdata[3] = conv.cdata[2];
    return sconv.fdata;
}

// для лонга

unsigned long swaplong(unsigned long data)
{

    union
    {
        unsigned long ldata;
        unsigned short sdata[2];
    } conv, sconv;

    conv.ldata = _bswapw(data);
    sconv.sdata[1] = conv.sdata[0];
    sconv.sdata[0] = conv.sdata[1];
    return sconv.ldata;
}

// запуск передачи без DMA режим прерываний

void start_tx_usart(struct tag_usart *usart)
{
    if (usart == &usart4)
    {
        IEC5bits.U4RXIE = 0; // disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        /*		if (usart->port_type==485){}*/
        ENAB_TX4;
        IEC5bits.U4TXIE = 1; // enable TX interrupt
    }

    if (usart == &usart5)
    {
        IEC5bits.U5RXIE = 0; // disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX5;
        IEC5bits.U5TXIE = 1; // enable TX interrupt
    }
    if (usart == &usart3)
    {
        IEC4bits.U3RXIE = 0; // disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX3;
        IEC4bits.U3TXIE = 1; // enable TX interrupt
    }
    if (usart == &usart2)
    {
        IEC4bits.U2RXIE = 0; // disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX2;
        IEC4bits.U2TXIE = 1; // enable TX interrupt
    }
    if (usart == &usart1)
    {
        IEC3bits.U1RXIE = 0; // disable RX interrupt
        usart->mb_status.modb_transmiting = 1;
        usart->out_buffer_count = 0;
        usart->mb_status.last_byte = 0;
        ENAB_TX1;
        IEC3bits.U1TXIE = 1; // enable TX interrupt
    }
}

// запуск передачи юсарт только с DMA без прерываний по передатчику

void start_tx_usart_dma(struct tag_usart *usart, unsigned short count)
{
    if (usart == &usart4)
    {
        ENAB_TX4;
        memcpy((void *)(buf_tx4), (const void *)(usart->out_buffer), (count));
        IEC5bits.U4RXIE = 0;
        DMA_uni(&usart4, count, 1, 1);
        usart->mb_status.modb_transmiting = 1;
        IEC5bits.U4TXIE = 0; // enable TX interrupt
    }
    if (usart == &usart5)
    {
        ENAB_TX5;
        memcpy((void *)(buf_tx5), (const void *)(usart->out_buffer), (count));
        IEC5bits.U5RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart5, count, 1, 1);
        IEC5bits.U5TXIE = 0;
    }
    if (usart == &usart3)
    {
        ENAB_TX3;
        memcpy((void *)(buf_tx3), (const void *)(usart->out_buffer), (count));
        IEC4bits.U3RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart3, count, 1, 1);
        IEC4bits.U3TXIE = 0;
    }
    if (usart == &usart2)
    {
        ENAB_TX2;
        memcpy((void *)(buf_tx2), (const void *)(usart->out_buffer), (count));
        IEC4bits.U2RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart2, count, 1, 1);
        IEC4bits.U2TXIE = 0;
    }
    if (usart == &usart1)
    {
        ENAB_TX1;
        memcpy((void *)(buf_tx1), (const void *)(usart->out_buffer), (count));
        IEC3bits.U1RXIE = 0;
        usart->mb_status.modb_transmiting = 1;
        DMA_uni(&usart1, count, 1, 1);
        IEC3bits.U1TXIE = 0;
    }
}

// остоновка передачи юсарт с прерыванием

void stop_uart_tx(void)
{
    if (usart4.mb_status.tx_mode == INT_type)
    {
        if ((usart4.mb_status.modb_transmiting == 1) && (U4STAbits.TRMT) && (IEC5bits.U4TXIE == 0))
        {
            usart4.mb_status.last_byte = 0;
            usart4.mb_status.modb_received = 0;
            usart4.mb_status.modb_receiving = 0;
            usart4.in_buffer_count = 0;
            usart4.mb_status.modb_transmiting = 0;
            IFS5bits.U4RXIF = 0;
            ENAB_RX4;
            IEC5bits.U4RXIE = 1; // disable RX interrupt
        }
        if (U4STAbits.OERR || U4STAbits.FERR)
        {
            U4STAbits.OERR = 0;
        }
    }

    if (usart5.mb_status.tx_mode == INT_type)
    {
        if ((usart5.mb_status.modb_transmiting == 1) && (U5STAbits.TRMT) && (IEC5bits.U5TXIE == 0))
        {
            usart5.mb_status.last_byte = 0;
            usart5.mb_status.modb_received = 0;
            usart5.mb_status.modb_receiving = 0;
            usart5.in_buffer_count = 0;
            usart5.mb_status.modb_transmiting = 0;
            IFS5bits.U5RXIF = 0;
            ENAB_RX5;
            IEC5bits.U5RXIE = 1; // disable RX interrupt
        }
        if (U5STAbits.OERR || U5STAbits.FERR)
        {
            U5STAbits.OERR = 0;
        }
    }
    if (usart3.mb_status.tx_mode == INT_type)
    {
        if ((usart3.mb_status.modb_transmiting == 1) && (U3STAbits.TRMT) && (IEC4bits.U3TXIE == 0))
        {
            usart3.mb_status.last_byte = 0;
            usart3.mb_status.modb_received = 0;
            usart3.mb_status.modb_receiving = 0;
            usart3.in_buffer_count = 0;
            usart3.mb_status.modb_transmiting = 0;
            IFS4bits.U3RXIF = 0;
            ENAB_RX3;
            IEC4bits.U3RXIE = 1; // disable RX interrupt
        }
        if (U3STAbits.OERR || U3STAbits.FERR)
        {
            U3STAbits.OERR = 0;
        }
    }
    if (usart2.mb_status.tx_mode == INT_type)
    {
        if ((usart2.mb_status.modb_transmiting == 1) && (U2STAbits.TRMT) && (IEC4bits.U2TXIE == 0))
        {
            usart2.mb_status.last_byte = 0;
            usart2.mb_status.modb_received = 0;
            usart2.mb_status.modb_receiving = 0;
            usart2.in_buffer_count = 0;
            usart2.mb_status.modb_transmiting = 0;
            IFS4bits.U2RXIF = 0;
            ENAB_RX2;
            IEC4bits.U2RXIE = 1; // disable RX interrupt
        }
        if (U2STAbits.OERR || U2STAbits.FERR)
        {
            U2STAbits.OERR = 0;
        }
    }
    if (usart1.mb_status.tx_mode == INT_type)
    {
        if ((usart1.mb_status.modb_transmiting == 1) && (U1STAbits.TRMT) && (IEC3bits.U1TXIE == 0))
        {
            usart1.mb_status.last_byte = 0;
            usart1.mb_status.modb_received = 0;
            usart1.mb_status.modb_receiving = 0;
            usart1.in_buffer_count = 0;
            usart1.mb_status.modb_transmiting = 0;
            IFS3bits.U1RXIF = 0;
            ENAB_RX1;
            IEC3bits.U1RXIE = 1; // disable RX interrupt
        }
        if (U1STAbits.OERR || U1STAbits.FERR)
        {
            U1STAbits.OERR = 0;
        }
    }
}

// остановка передачи без прерываний DMA

void stop_uart_tx_dma(void)
{
    if (usart4.mb_status.tx_mode == DMA_type)
    {
        if ((usart4.mb_status.modb_transmiting == 1) && (U4STAbits.TRMT))
        {
            usart4.mb_status.modb_transmiting = 0;
            DMA_uni(&usart4, 1, 0, 0);
            usart4.mb_status.modb_received = 0;
            usart4.mb_status.modb_receiving = 0;
            usart4.in_buffer_count = 0;
            IFS5bits.U4RXIF = 0;
            ENAB_RX4;
            IEC5bits.U4RXIE = 1;
        }
        if (U4STAbits.OERR || U4STAbits.FERR)
        {
            U4STAbits.OERR = 0;
        }
    }

    if (usart5.mb_status.tx_mode == DMA_type)
    {
        if ((usart5.mb_status.modb_transmiting == 1) && (U5STAbits.TRMT))
        {
            usart5.mb_status.modb_transmiting = 0;
            DMA_uni(&usart5, 1, 0, 0);
            usart5.mb_status.modb_received = 0;
            usart5.mb_status.modb_receiving = 0;
            usart5.in_buffer_count = 0;
            IFS5bits.U5RXIF = 0;
            ENAB_RX5;
            IEC5bits.U5RXIE = 1;
        }
        if (U5STAbits.OERR || U5STAbits.FERR)
        {
            U5STAbits.OERR = 0;
        }
    }
    if (usart3.mb_status.tx_mode == DMA_type)
    {
        if ((usart3.mb_status.modb_transmiting == 1) && (U3STAbits.TRMT))
        {
            usart3.mb_status.modb_transmiting = 0;
            DMA_uni(&usart3, 1, 0, 0);
            usart3.mb_status.modb_received = 0;
            usart3.mb_status.modb_receiving = 0;
            usart3.in_buffer_count = 0;
            IFS4bits.U3RXIF;
            ENAB_RX3;
            IEC4bits.U3RXIE = 1;
        }
        if (U3STAbits.OERR || U3STAbits.FERR)
        {
            U3STAbits.OERR = 0;
        }
    }
    if (usart2.mb_status.tx_mode == DMA_type)
    {
        if ((usart2.mb_status.modb_transmiting == 1) && (U2STAbits.TRMT))
        {
            usart2.mb_status.modb_transmiting = 0;
            DMA_uni(&usart2, 1, 0, 0);
            usart2.mb_status.modb_received = 0;
            usart2.mb_status.modb_receiving = 0;
            usart2.in_buffer_count = 0;
            IFS4bits.U2RXIF;
            ENAB_RX2;
            IEC4bits.U2RXIE = 1;
        }
        if (U2STAbits.OERR || U2STAbits.FERR)
        {
            U2STAbits.OERR = 0;
        }
    }
    if (usart1.mb_status.tx_mode == DMA_type)
    {
        if ((usart1.mb_status.modb_transmiting == 1) && (U1STAbits.TRMT))
        {
            usart1.mb_status.modb_transmiting = 0;
            DMA_uni(&usart1, 1, 0, 0);
            usart1.mb_status.modb_received = 0;
            usart1.mb_status.modb_receiving = 0;
            usart1.in_buffer_count = 0;
            IFS3bits.U1RXIF;
            ENAB_RX1;
            IEC3bits.U1RXIE = 1;
        }
        if (U1STAbits.OERR || U1STAbits.FERR)
        {
            U1STAbits.OERR = 0;
        }
    }
}

// сброс модбаса по приему по COM порту

void close_mb(struct tag_usart *usart)
{
    usart->mb_status.modb_received = 0;
    usart->mb_status.modb_receiving = 0;
    usart->in_buffer_count = 0;
}

// формирование ответа на ошибочное обращение

void answer_illegal(struct tag_usart *usart, unsigned char illegal)
{
    usart->out_buffer[0x00] = usart->in_buffer[0];
    usart->out_buffer[0x01] = usart->in_buffer[1] | 0x80;
    usart->out_buffer[0x02] = illegal;
    PIC_CRC16(usart->out_buffer, 0x03);
    usart->out_buffer[0x03] = uchCRCLo;
    usart->out_buffer[0x04] = uchCRCHi;
    usart->number_send = 5;
}

// вариант ответа на неправильную функцию

void answer_illegal_func(struct tag_usart *usart)
{
    answer_illegal(usart, 0x01);
    if (usart->mb_status.tx_mode == INT_type)
    {
        start_tx_usart(usart);
    }
    else
    {
        start_tx_usart_dma(usart, 5);
    }
}

// вариант ответа на неправильную адресацию

void answer_illegal_data_addr(struct tag_usart *usart)
{
    answer_illegal(usart, 0x02);
    if (usart->mb_status.tx_mode == INT_type)
    {
        start_tx_usart(usart);
    }
    else
    {
        start_tx_usart_dma(usart, 5);
    }
}

// вариант ответа на неправильные данные

void answer_illegal_data_val(struct tag_usart *usart)
{
    answer_illegal(usart, 0x03);
    if (usart->mb_status.tx_mode == INT_type)
    {
        start_tx_usart(usart);
    }
    else
    {
        start_tx_usart_dma(usart, 5);
    }
}

unsigned short num3;
// 3-я фукнкия модбас slave должна отвечать на mbm_03

void mbs_03(struct tag_usart *_usart, unsigned short *source, unsigned short shift, unsigned short num)
{
    num3 = num;
    memcpy((void *)(_usart->out_buffer + 0x03), (const void *)(source + shift), (num3 * 2));
    num3 *= 2;
    _usart->out_buffer[0] = _usart->in_buffer[0];
    _usart->out_buffer[1] = _usart->in_buffer[1];
    _usart->out_buffer[0x02] = num3;
    num3 += 0x03;
    PIC_CRC16(_usart->out_buffer, (num3));
    _usart->out_buffer[num3++] = uchCRCLo;
    _usart->out_buffer[num3++] = uchCRCHi;
    _usart->number_send = num3;
    if (_usart->mb_status.tx_mode == DMA_type)
    {
        start_tx_usart_dma(_usart, num3);
    }
    else
    {
        start_tx_usart(_usart);
    }
}

// 16-я функция модбас слэйв, отвечает на mbm_10 записывает данные и кратко отвечает что все ок

void mbs_10(struct tag_usart *_usart, unsigned short *source, unsigned short shift_uni, unsigned short num_uni)
{
    //	unsigned int help_store [10];
    unsigned short ii, upd;

    upd = 0;

    // Проверяем, является ли указатель source указателем на массив MB_swap.input
    if (source == MB_swap.input)
    {
        // Копируем данные из буфера _usart->in_buffer в MB_swap.input с учетом смещения shift_uni и количества элементов num_uni
        memcpy((void *)(MB_swap.input + shift_uni), (const void *)(_usart->in_buffer + 0x07), (num_uni * 2));
        // Проходим по элементам исходного массива MB_swap.input, меняем порядок байт с помощью функций swapshort и _bswapw
        for (ii = 0; ii < num_uni; ii++)
        {
            MB.input[ii + shift_uni] = swapshort(MB_swap.input[ii + shift_uni]);
            MB.input[ii + shift_uni] = _bswapw(MB.input[ii + shift_uni]);
        }
    }
    // Проверяем, является ли указатель source указателем на массив MB_sw_conf.buf
    if (source == MB_sw_conf.buf)
    {
        // Копируем данные из буфера _usart->in_buffer в MB_sw_conf.buf с учетом смещения shift_uni и количества элементов num_uni
        memcpy((void *)(MB_sw_conf.buf + shift_uni), (const void *)(_usart->in_buffer + 0x07), (num_uni * 2));

        // Проходим по элементам исходного массива MB_sw_conf.buf, меняем порядок байт с помощью функции swapshort
        for (ii = 0; ii < num_uni; ii++)
        {
            MB_conf.buf[ii + shift_uni] = swapshort(MB_sw_conf.buf[ii + shift_uni]);
        }
        // Записываем данные во внешнюю память и выполняем другие действия
        putcs_FRAM(RAMTRON_START_CONFIG, MB_conf.buf, 180);
        getcs_FRAM(RAMTRON_START_CONFIG, MB_conf.buf, 180);
        load_config();
    }
    // Проверяем, является ли указатель source указателем на массив Modbus_sw.buf
    if (source == Modbus_sw.buf)
    {
        // Копируем данные из буфера _usart->in_buffer в Modbus_sw.buf с учетом смещения shift_uni и количества элементов num_uni
        memcpy((void *)(Modbus_sw.buf + shift_uni), (const void *)(_usart->in_buffer + 0x07), (num_uni * 2));
        // Проходим по элементам исходного массива Modbus_sw.buf, меняем порядок байт с помощью функции swapshort
        for (ii = 0; ii < num_uni; ii++)
        {
            Modbus.buf[ii + shift_uni] = swapshort(Modbus_sw.buf[ii + shift_uni]);
        }
    }

    // Копируем первые 8 байт из _usart->in_buffer в _usart->out_buffer
    _usart->out_buffer[0x00] = _usart->in_buffer[0x00];
    _usart->out_buffer[0x01] = _usart->in_buffer[0x01];
    _usart->out_buffer[0x02] = _usart->in_buffer[0x02];
    _usart->out_buffer[0x03] = _usart->in_buffer[0x03];
    _usart->out_buffer[0x04] = _usart->in_buffer[0x04];
    _usart->out_buffer[0x05] = _usart->in_buffer[0x05];
    // Вычисляем CRC16 для первых 6 байт из _usart->out_buffer и записываем его в буфер
    PIC_CRC16(_usart->out_buffer, (0x06));
    _usart->out_buffer[0x06] = uchCRCLo;
    _usart->out_buffer[0x07] = uchCRCHi;
    _usart->number_send = 0x08;
    // Проверяем режим передачи данных и вызываем соответствующую функцию
    if (_usart->mb_status.tx_mode == DMA_type)
    {
        start_tx_usart_dma(_usart, _usart->number_send);
    }
    else
    {
        start_tx_usart(_usart);
    }
}

unsigned short num_reg;
unsigned short start_reg;
unsigned short last_reg;
unsigned short length_err;

// функция которая смотрит какая функция ей прилетела

void mbs_uni(struct tag_usart *usart, unsigned char mbs_addres)
{
    if (usart->mb_status.modb_received)
    {                                                          // повторно смотрит приняты ли данные проверка CRC
        PIC_CRC16(usart->in_buffer, (usart->in_buffer_count)); // расчет CRC
        if (uchCRCLo | uchCRCHi)
        { // логическо или ели оба равны нулю
            close_mb(usart);
            return;
        } // no actions

        start_reg = usart->in_buffer[0x02] * 0x100;
        start_reg += usart->in_buffer[0x03];
        num_reg = usart->in_buffer[0x04] * 0x100;
        num_reg += usart->in_buffer[0x05];

        last_reg = start_reg + num_reg;

        if (((usart->in_buffer_count - 9) != usart->in_buffer[0x06]) && (usart->in_buffer[1] == 0x10)) // проверяет длинну
        {                                                                                              // number received bytes - 9 bytes
            length_err = 1;
        }
        else
        {
            length_err = 0;
        }
        if (((usart->in_buffer_count - 9) != (num_reg * 2)) && (usart->in_buffer[1] == 0x10)) // num reg*2 must be equal to
        {
            length_err = 1;
        }
        else
        {
            length_err = 0;
        }

        switch (length_err)
        {
        case 1:
        {
            answer_illegal_data_addr(usart); // неправильный адрес
            break;
        } // ?????? ??? ????????? ????? ??????? ? ????????? ?????????? ??????
        default:
        {
            switch (usart->in_buffer[1])
            {
            case 0x03: // 3-я функция
            {
                if (READ_)
                {
                    mbs_03(usart, MB_swap.buf, (start_reg - START_READ), num_reg);
                    break;
                } // 2000 ... 2078
                if (CONF_READ_)
                {
                    mbs_03(usart, MB_sw_conf.buf, (start_reg - START_CONF_READ), num_reg);
                    break;
                } // 500 ... 680
                if (MODBUS_READ_)
                {
                    mbs_03(usart, Modbus_sw.buf, (start_reg - START_MODBUS_READ), num_reg);
                    break;
                } // 0 ... 80
                if (MB_DIAGN_READ_)
                {
                    mbs_03(usart, MB_diagn_sw.buf, (start_reg - START_MB_DIAGN_READ), num_reg);
                    break;
                } // 200 ... 312
                answer_illegal_data_addr(usart);
                break;
            }

            case 0x10: // 16-я функция
            {
                if (WRITE_)
                {
                    mbs_10(usart, MB_swap.input, (start_reg - START_WRITE), num_reg);
                    break;
                }
                if (CONF_WRITE_)
                {
                    mbs_10(usart, MB_sw_conf.buf, (start_reg - START_CONF_WRITE), num_reg);
                    break;
                }
                if (MODBUS_WRITE_)
                {
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

// проверяет адрес

void mbs(struct tag_usart *usart, unsigned char mbs_addres)
{
    if (!usart->mb_status.modb_received)
    {           // смотри есть ли принятые данные
        return; // return if nothing received
    }

    if (usart->in_buffer[0] == mbs_addres)
    {                               // если принято, то смотрит адрес к нем обратились или не к нему
        mbs_uni(usart, mbs_addres); // вызывает функцию выше, то отвечает
        return;
    }
    else
    {
        close_mb(usart); // сбрасывает модбас в 0
        return;
    }
}

// 3-я фукнция мастер запрос данных

void mbm_03(struct tag_usart *usart, unsigned char mbm_adres, unsigned int shift_03, unsigned int quant_03, unsigned int *dest, unsigned int speed)
{

    unsigned int cc;
    if (!usart->mb_status.master_start)
    {
        return;
    }
    switch (usart->mbm_status)
    {
    case 0:
    {
        if (usart == &usart1)
        {
            UART1_init(speed);
        }
        if (usart == &usart2)
        {
            UART2_init(speed);
        }
        if (usart == &usart4)
        {
            UART4_init(speed);
        }
        if (usart == &usart5)
        {
            UART5_init(speed);
        }
        switch (speed)
        {
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
    case 1: // формирование запроса
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
        if (!usart->mb_status.master_timeout && !usart->mb_status.modb_received) // если нет ответа и не сработал таймаут, то выходим
            return;
        if (usart->mb_status.master_timeout)
        { // если есть таймаут, инкрем. счетчик ошибок и закрываем все
            usart->mbm_err++;
            usart->mbm_status = 0;
            usart->mb_status.master_start = 0;
            break;
        }

        if (usart->in_buffer[1] == 0x83) // ответ на неправильное обращение
        {
            // смотрит какая коллизия
            if (usart->in_buffer[2] == 0x01)
            {
                usart->mb_status.coll_1 = 1;
                usart->mbm_err++;
                usart->mb_status.master_start = 0;
                usart->mbm_status = 0;
                break;
            }
            if (usart->in_buffer[2] == 0x02)
            {
                usart->mb_status.coll_2 = 1;
                usart->mbm_err++;
                usart->mb_status.master_start = 0;
                usart->mbm_status = 0;
                break;
            }
            if (usart->in_buffer[2] == 0x03)
            {
                usart->mb_status.coll_3 = 1;
                usart->mbm_err++;
                usart->mb_status.master_start = 0;
                usart->mbm_status = 0;
                break;
            }
        }
        //			if (usart->in_buffer_count!=(quant_03*2+5))									//byte missing
        //				{usart->mbm_status=0; usart->mb_status.byte_missing=1; usart->mbm_err++; usart->mb_status.master_start=0; break;}
        if (usart->in_buffer[0] != usart->out_buffer[0]) // если ответил другой модуль
        {
            usart->mbm_status = 0;
            usart->mb_status.device_error = 1;
            usart->mbm_err++;
            usart->mb_status.master_start = 0;
            break;
        }
        PIC_CRC16(usart->in_buffer, (usart->in_buffer_count)); // проверяем CRC ответ
        if (uchCRCLo | uchCRCHi)
        { // если неправильно
            usart->mbm_status = 0;
            usart->mb_status.crc_error = 1;
            usart->mbm_err++;
            usart->mb_status.master_start = 0;
            break;
        } // wrong crc

        memcpy((void *)(dest), (const void *)(usart->in_buffer + 0x03), usart->in_buffer[2]); // если все нормально, то начинаем
        for (cc = 0; cc < quant_03; cc++)
        {
            //                MOPS.main_area[cc + shift_03] = swapshort(MOPS_swap.main_area[cc + shift_03]);
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
