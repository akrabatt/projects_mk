#include "extern.h"
#include <stdio.h>
#include <xc.h>
#include <string.h>

// таблица для функции CRC, эта используется для хранения старшего байта
const char auchCRCHi[] = { // Содержит предвычисленные значения старшего байта (Hi) для каждого возможного значения входного байта (0-255).
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
const char auchCRCLo[] = { // Содержит предвычисленные значения младшего байта (Lo) для каждого возможного значения входного байта (0-255).
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

/* Переменные auchCRCHi и auchCRCLo представляют собой таблицы предвычисленных значений для алгоритма вычисления CRC16.
Они используются для ускорения вычислений контрольной суммы путем обращения к этим таблицам, а не выполнения длительных
арифметических операций. */

unsigned char uchCRCHi = 0xFF; // переменная для хранения текущего значения старшего байта
unsigned char uchCRCLo = 0xFF; // младшего байта

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
        uIndex = uchCRCLo ^ *puchMsg++; // вычисляем индекс таблицы CRC

        // Обновление младшего байта CRC16 (uchCRCLo) путем выполнения операции XOR между текущим
        // значением старшего байта CRC (uchCRCHi) и значением из таблицы auchCRCHi по индексу uIndex.
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex]; // обновляем младший байт CRC

        // Обновление старшего байта CRC16 (uchCRCHi) новым значением из таблицы auchCRCLo по индексу uIndex.
        uchCRCHi = auchCRCLo[uIndex]; // обновляем старший байт CRC
    }
}
/* Функция PIC_CRC16 рассчитывает контрольную сумму CRC-16 для переданного сообщения. CRC (Cyclic Redundancy Check) используется
для проверки целостности данных. Алгоритм основан на побайтовой обработке входного сообщения и использовании предопределенных таблиц значений
для вычисления контрольной суммы.

Функция PIC_CRC16 необходима для вычисления CRC-16 контрольной суммы, которая используется в протоколах передачи данных, таких как Modbus.
Эта контрольная сумма добавляется к сообщению перед его отправкой и проверяется на принимающей стороне, чтобы убедиться, что данные не были
повреждены во время передачи.

Таким образом, вся функция PIC_CRC16 выполняет итеративное обновление старшего и младшего байтов контрольной суммы CRC16
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
    } conv, sconv;              // Объявление двух переменных типа union для конверсии данных

    conv.sdata = data; // Запись исходного значения в поле sdata объединения conv

    // Здесь происходит фактическая перестановка байтов. Мы присваиваем старшему байту (cdata[1] в sconv) младший байт
    // (cdata[0] в conv), а младшему байту (cdata[0] в sconv) — старший байт (cdata[1] в conv).
    sconv.cdata[1] = conv.cdata[0]; // Старший байт (второй по порядку) получает младший байт исходного числа
    sconv.cdata[0] = conv.cdata[1]; // Младший байт (первый по порядку) получает старший байт исходного числа
    return sconv.sdata;             // Возврат результата как беззнаковое короткое целое число с переставленными байтами
}

// для флота
// Функция swapshort предназначена для перестановки байтов 16-битного беззнакового целого числа. Это полезно в ситуациях,
// когда нужно преобразовать данные между различными форматами байтового порядка, например, между little-endian и big-endian.
// Вот как работает эта функция:

/* Функция swapshort используется для конвертации порядка байтов в 16-битном беззнаковом целочисленном значении. Это часто
необходимо при обмене данными между системами с разным порядком байтов (например, между устройствами с архитектурой little-endian и big-endian)
для обеспечения корректной интерпретации данных. */

float swapfloat(float data)
{
    // Объявление объединения (union) для работы с тремя форматами данных: float, unsigned short и unsigned char (байтовый массив)
    // Здесь объявляется объединение (union), которое позволяет интерпретировать одну и ту же область памяти как три различных типа
    // данных (float, unsigned short[2] и unsigned char[4]), что позволяет манипулировать отдельными байтами числа с плавающей запятой.

    union
    {
        float fdata;             // 32-битное число с плавающей запятой (исходный формат)
        unsigned short sdata[2]; // Массив из двух беззнаковых коротких целых чисел (для доступа к половинам float)
        unsigned char cdata[4];  // Байтовый массив из 4 элементов (для доступа к каждому байту)
    } conv, sconv;

    conv.fdata = data; // Запись исходного значения типа float в поле fdata объединения conv

    // Перестановка байтов:
    // Здесь происходит фактическая перестановка байтов. Мы присваиваем старшему байту (четвёртому по порядку)
    // в sconv младший байт (первый по порядку) первой половины числа с плавающей запятой, и так далее, чтобы
    // поменять местами байты в каждой половине числа.
    sconv.cdata[3] = conv.cdata[0]; // Старший байт (четвёртый по порядку) получает младший байт первой половины float
    sconv.cdata[2] = conv.cdata[1]; // Следующий байт (третий по порядку) получает следующий байт первой половины float
    sconv.cdata[1] = conv.cdata[2]; // Первый байт второй половины float получает младший байт второй половины float
    sconv.cdata[0] = conv.cdata[3]; // Младший байт второй половины float получает старший байт второй половины float

    // Возврат результата как float с переставленными байтами
    return sconv.fdata;
}

// для лонга

unsigned long swaplong(unsigned long data)
{
    // Объявление объединения (union) для удобства доступа к данным различных типов

    union
    {
        unsigned long ldata;     // Целое число беззнакового 32 бита
        unsigned short sdata[2]; // Массив из двух беззнаковых коротких целых чисел (16 бит)
    } conv, sconv;

    // Обмен местами байт в переданном числе с помощью встроенной функции _bswapw
    conv.ldata = _bswapw(data);

    // Перестановка байт между элементами массива sdata в объединении conv
    sconv.sdata[1] = conv.sdata[0]; // Младший байт идет в старший элемент массива
    sconv.sdata[0] = conv.sdata[1]; // Старший байт идет в младший элемент массива

    // Возврат числа после перестановки байт
    return sconv.ldata;
}
/* Эта функция, swaplong, предназначена для обмена местами байтов в беззнаковом 32-битном целом числе.  */

// запуск передачи без DMA режим прерываний
// Этот код представляет собой функцию start_tx_usart, которая используется для начала передачи данных
// через USART (универсальный асинхронный приемопередатчик) на

void start_tx_usart(struct tag_usart *usart)
{
    // Проверяем, с каким USART мы работаем
    if (usart == &usart4)
    {
        // Если это USART4, отключаем прерывание RX
        IEC5bits.U4RXIE = 0; // disable RX interrupt

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Обнуляем счетчик буфера для передачи
        usart->out_buffer_count = 0;

        // Сбрасываем флаг последнего байта
        usart->mb_status.last_byte = 0;

        // Включаем передачу USART4
        ENAB_TX4;

        // Включаем прерывание TX для USART4
        IEC5bits.U4TXIE = 1; // enable TX interrupt
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart5)
    {
        // Если это USART5, отключаем прерывание RX
        IEC5bits.U5RXIE = 0; // disable RX interrupt

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Обнуляем счетчик буфера для передачи
        usart->out_buffer_count = 0;

        // Сбрасываем флаг последнего байта
        usart->mb_status.last_byte = 0;

        // Включаем передачу USART5
        ENAB_TX5;

        // Включаем прерывание TX для USART5
        IEC5bits.U5TXIE = 1; // enable TX interrupt
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart3)
    {
        // Если это USART3, отключаем прерывание RX
        IEC4bits.U3RXIE = 0; // disable RX interrupt

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Обнуляем счетчик буфера для передачи
        usart->out_buffer_count = 0;

        // Сбрасываем флаг последнего байта
        usart->mb_status.last_byte = 0;

        // Включаем передачу USART3
        ENAB_TX3;

        // Включаем прерывание TX для USART3
        IEC4bits.U3TXIE = 1; // enable TX interrupt
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart2)
    {
        // Если это USART2, отключаем прерывание RX
        IEC4bits.U2RXIE = 0; // disable RX interrupt

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Обнуляем счетчик буфера для передачи
        usart->out_buffer_count = 0;

        // Сбрасываем флаг последнего байта
        usart->mb_status.last_byte = 0;

        // Включаем передачу USART2
        ENAB_TX2;

        // Включаем прерывание TX для USART2
        IEC4bits.U2TXIE = 1; // enable TX interrupt
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart1)
    {
        // Если это USART1, отключаем прерывание RX
        IEC3bits.U1RXIE = 0; // disable RX interrupt

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Обнуляем счетчик буфера для передачи
        usart->out_buffer_count = 0;

        // Сбрасываем флаг последнего байта
        usart->mb_status.last_byte = 0;

        // Включаем передачу USART1
        ENAB_TX1;

        // Включаем прерывание TX для USART1
        IEC3bits.U1TXIE = 1; // enable TX interrupt
    }
}
/* Этот код запускает передачу данных через USART без использования режима прямого доступа к памяти
(DMA) и с использованием прерываний. */

// запуск передачи юсарт только с DMA без прерываний по передатчику
// Это объявление функции start_tx_usart_dma, которая принимает указатель usart на структуру
// tag_usart и количество данных count для передачи через DMA.

void start_tx_usart_dma(struct tag_usart *usart, unsigned short count)
{
    // Проверяем, с каким USART мы работаем
    if (usart == &usart4)
    {
        // Включаем передачу для USART4
        ENAB_TX4;

        // Копируем данные из буфера usart->out_buffer в буфер buf_tx4 через memcpy
        // Копирование данных из буфера usart->out_buffer в буфер передачи buf_txX через функцию memcpy. buf_txX
        // предположительно представляет собой буфер DMA для конкретного USART.
        memcpy((void *)(buf_tx4), (const void *)(usart->out_buffer), (count));

        // Отключаем прерывание RX для USART4
        IEC5bits.U4RXIE = 0;

        // Настраиваем DMA для передачи данных через USART4
        // Настройка и запуск DMA для передачи данных через конкретный USART
        // (X заменяется номером USART) с указанным количеством данных (count).
        DMA_uni(&usart4, count, 1, 1);

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Отключаем прерывание TX для USART4
        IEC5bits.U4TXIE = 0;
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart5)
    {
        // Включаем передачу для USART5
        ENAB_TX5;

        // Копируем данные из буфера usart->out_buffer в буфер buf_tx5 через memcpy
        memcpy((void *)(buf_tx5), (const void *)(usart->out_buffer), (count));

        // Отключаем прерывание RX для USART5
        IEC5bits.U5RXIE = 0;

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Настраиваем DMA для передачи данных через USART5
        DMA_uni(&usart5, count, 1, 1);

        // Отключаем прерывание TX для USART5
        IEC5bits.U5TXIE = 0;
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart3)
    {
        // Включаем передачу для USART3
        ENAB_TX3;

        // Копируем данные из буфера usart->out_buffer в буфер buf_tx3 через memcpy
        memcpy((void *)(buf_tx3), (const void *)(usart->out_buffer), (count));

        // Отключаем прерывание RX для USART3
        IEC4bits.U3RXIE = 0;

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Настраиваем DMA для передачи данных через USART3
        DMA_uni(&usart3, count, 1, 1);

        // Отключаем прерывание TX для USART3
        IEC4bits.U3TXIE = 0;
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart2)
    {
        // Включаем передачу для USART2
        ENAB_TX2;

        // Копируем данные из буфера usart->out_buffer в буфер buf_tx2 через memcpy
        memcpy((void *)(buf_tx2), (const void *)(usart->out_buffer), (count));

        // Отключаем прерывание RX для USART2
        IEC4bits.U2RXIE = 0;

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Настраиваем DMA для передачи данных через USART2
        DMA_uni(&usart2, count, 1, 1);

        // Отключаем прерывание TX для USART2
        IEC4bits.U2TXIE = 0;
    }

    // Проверяем, с каким USART мы работаем
    if (usart == &usart1)
    {
        // Включаем передачу для USART1
        ENAB_TX1;

        // Копируем данные из буфера usart->out_buffer в буфер buf_tx1 через memcpy
        memcpy((void *)(buf_tx1), (const void *)(usart->out_buffer), (count));

        // Отключаем прерывание RX для USART1
        IEC3bits.U1RXIE = 0;

        // Устанавливаем флаг, что начата передача по MODBUS
        usart->mb_status.modb_transmiting = 1;

        // Настраиваем DMA для передачи данных через USART1
        DMA_uni(&usart1, count, 1, 1);

        // Отключаем прерывание TX для USART1
        IEC3bits.U1TXIE = 0;
    }
}
/* Этот код представляет собой функцию для запуска передачи данных через USART только с использованием
DMA без использования прерываний по передатчику */

// остановки передачи данных через USART

void stop_uart_tx(void)
{
    if (usart4.mb_status.tx_mode == INT_type)
    {
        // Проверяем режим передачи (INT_type) для USART4
        if (usart4.mb_status.tx_mode == INT_type)
        {
            // Проверяем условие для остановки передачи
            if ((usart4.mb_status.modb_transmiting == 1) && (U4STAbits.TRMT) && (IEC5bits.U4TXIE == 0))
            // Это условие проверяет, можно ли остановить передачу данных через USART. Конкретные условия включают:
            // usartX.mb_status.modb_transmiting == 1: Проверяет, что передача MODBUS была начата.
            // UxSTAbits.TRMT: Проверяет, что буфер передатчика USART пуст (готов для новой передачи).
            // IECxbits.UXTXIE == 0: Проверяет, что прерывание передачи USART было выключено.
            {
                // Сбрасываем флаг последнего байта
                usart4.mb_status.last_byte = 0;

                // Сбрасываем флаги приема и передачи MODBUS
                usart4.mb_status.modb_received = 0;
                usart4.mb_status.modb_receiving = 0;

                // Обнуляем счетчик входного буфера
                usart4.in_buffer_count = 0;

                // Устанавливаем флаг, что передача MODBUS завершена
                usart4.mb_status.modb_transmiting = 0;

                // Сбрасываем флаг прерывания RX для USART4
                IFS5bits.U4RXIF = 0;

                // Включаем прием для USART4
                ENAB_RX4;

                // Включаем прерывание RX для USART4
                IEC5bits.U4RXIE = 1; // disable RX interrupt
            }

            // Проверяем наличие ошибок в USART4 (Overrun Error или Framing Error)
            if (U4STAbits.OERR || U4STAbits.FERR)
            {
                // Сбрасываем ошибку, если она есть
                U4STAbits.OERR = 0;
            }
        }

        // Проверяем режим передачи (INT_type) для USART5
        if (usart5.mb_status.tx_mode == INT_type)
        {
            // Проверяем условие для остановки передачи
            if ((usart5.mb_status.modb_transmiting == 1) && (U5STAbits.TRMT) && (IEC5bits.U5TXIE == 0))
            {
                // Сбрасываем флаг последнего байта
                usart5.mb_status.last_byte = 0;

                // Сбрасываем флаги приема и передачи MODBUS
                usart5.mb_status.modb_received = 0;
                usart5.mb_status.modb_receiving = 0;

                // Обнуляем счетчик входного буфера
                usart5.in_buffer_count = 0;

                // Устанавливаем флаг, что передача MODBUS завершена
                usart5.mb_status.modb_transmiting = 0;

                // Сбрасываем флаг прерывания RX для USART5
                IFS5bits.U5RXIF = 0;

                // Включаем прием для USART5
                ENAB_RX5;

                // Включаем прерывание RX для USART5
                IEC5bits.U5RXIE = 1; // disable RX interrupt
            }

            // Проверяем наличие ошибок в USART5 (Overrun Error или Framing Error)
            if (U5STAbits.OERR || U5STAbits.FERR)
            {
                // Сбрасываем ошибку, если она есть
                U5STAbits.OERR = 0;
            }
        }

        // Проверяем режим передачи (INT_type) для USART3 (аналогично для других USART)
        // Процесс повторяется для каждого USART (usart3, usart2, usart1)
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
}
// Эта функция выполняет остановку передачи данных через USART, проверяя условия для каждого USART (usartX) и
// выполняя соответствующие действия для каждого из них в зависимости от текущего состояния передачи и обнаруженных ошибок.

/**
 * @brief Остановка передачи данных через DMA для всех USART, использующих режим DMA передачи.
 *
 * Эта функция проверяет режим передачи (DMA_type) для каждого USART.
 * Если передача MODBUS через DMA была начата и буфер передатчика USART пуст (готов для новой передачи),
 * то передача останавливается и производится сброс соответствующих флагов и счетчика буфера.
 * Также проверяются наличие ошибок (Overrun Error или Framing Error) и при их обнаружении они сбрасываются.
 * Также полсле окончания передачи данных перстает моргать светодиод.
 *
 * @param void
 * @return void
 */
void stop_uart_tx_dma(void)
{
    // Проверяем режим передачи (DMA_type) для USART4
    if (usart4.mb_status.tx_mode == DMA_type)
    {
        // Проверяем условие для остановки передачи
        if ((usart4.mb_status.modb_transmiting == 1) && (U4STAbits.TRMT))
        // Это условие проверяет, можно ли остановить передачу данных через USART.Конкретные условия включают:
        // usartX.mb_status.modb_transmiting == 1: Проверяет, что передача MODBUS через DMA была начата.
        // UxSTAbits.TRMT: Проверяет, что буфер передатчика USART пуст (готов для новой передачи).
        {
            // Устанавливаем флаг, что передача MODBUS завершена
            usart4.mb_status.modb_transmiting = 0;

            // Останавливаем DMA для передачи данных через USART4
            DMA_uni(&usart4, 1, 0, 0);

            // Сбрасываем флаги приема и передачи MODBUS
            usart4.mb_status.modb_received = 0;
            usart4.mb_status.modb_receiving = 0;

            // Обнуляем счетчик входного буфера
            usart4.in_buffer_count = 0;

            // Сбрасываем флаг прерывания RX для USART4
            IFS5bits.U4RXIF = 0;

            // Включаем прием для USART4
            ENAB_RX4;

            // Включаем прерывание RX для USART4
            IEC5bits.U4RXIE = 1;
        }

        // Проверяем наличие ошибок в USART4 (Overrun Error или Framing Error)
        if (U4STAbits.OERR || U4STAbits.FERR)
        // Это условие проверяет наличие ошибок (Overrun Error или Framing Error) для каждого USART.
        // Если обнаружена ошибка, она сбрасывается (OERR = 0).
        {
            // Сбрасываем ошибку, если она есть
            U4STAbits.OERR = 0;
        }
    }

    // Проверяем режим передачи (DMA_type) для USART5 (аналогично для других USART)
    // Процесс повторяется для каждого USART (usart5, usart3, usart2, usart1)

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
            PORTGbits.RG14 = 0; // выключаем светодиод передачи данных
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
            PORTGbits.RG13 = 0; // отключаем светодиод который служит индикацией о передачи данных
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
            PORTEbits.RE3 = 0; // отключаем светодиод который служит индикацией о передачи данных
            IEC3bits.U1RXIE = 1;
        }
        if (U1STAbits.OERR || U1STAbits.FERR)
        {
            U1STAbits.OERR = 0;
        }
    }
}

/**
 * @brief Сбрасывает состояние протокола MODBUS для конкретного USART.
 *
 * Эта функция позволяет сбросить состояние протокола MODBUS для конкретного USART, устанавливая соответствующие
 * флаги в 0 и обнуляя счетчик буфера, что полезно при завершении или сбросе процесса передачи или приема данных
 * через USART с применением протокола MODBUS.
 *
 * @param usart Указатель на структуру usart, содержащую информацию о состоянии протокола MODBUS.
 * @return void
 */
void close_mb(struct tag_usart *usart)
{
    // Сбрасываем флаги приема и передачи MODBUS
    usart->mb_status.modb_received = 0;  // Эта строка устанавливает флаг modb_received в 0, что указывает на то, что передача MODBUS не была завершена.
    usart->mb_status.modb_receiving = 0; // Эта строка также устанавливает флаг modb_receiving в 0, что указывает на то, что процесс приема MODBUS не активен.

    // Обнуляем счетчик входного буфера
    usart->in_buffer_count = 0; // Эта строка обнуляет счетчик in_buffer_count, который отслеживает количество байт, находящихся во входном буфере USART.
}

/**
 * @brief Управление таймаутом Modbus Master.
 *
 * Эта функция осуществляет контроль за таймаутом Modbus Master. Если таймер включен, то каждый раз,
 * когда функция вызывается, счетчик таймаута уменьшается. Если счетчик таймаута достигает нуля,
 * устанавливается флаг таймаута мастера и таймер выключается.
 *
 * @param usart Указатель на структуру usart, содержащую информацию о статусе и счетчике таймаута.
 * @return void
 */
void mbm_timeout_control(struct tag_usart *usart)
{
    if (usart->mb_status.tm_on)
    {
        if (usart->mbm_timeout_counter - TICK)
        {
            usart->mb_status.tm_on = 0;
            usart->mb_status.master_timeout_flag = 1;
        }
    }
}

// формирование ответа на недопустимый запрос протокола
// Эта функция answer_illegal формирует ответ на недопустимый запрос протокола MODBUS,
// включая первые два байта из входного запроса, устанавливая старший бит во втором байте для обозначения ошибки,
// добавляя недопустимый код запроса и вычисляя CRC16 для данных ответа, чтобы обеспечить его целостность при передаче

void answer_illegal(struct tag_usart *usart, unsigned char illegal)
{
    // Копируем первые два байта из входного буфера в выходной буфер
    usart->out_buffer[0x00] = usart->in_buffer[0]; // Здесь копируется первый байт из входного буфера (usart->in_buffer[0]) в
    // первый байт выходного буфера (usart->out_buffer[0x00]).

    usart->out_buffer[0x01] = usart->in_buffer[1] | 0x80; // Здесь копируется второй байт из входного буфера (usart->in_buffer[1])
    // во второй байт выходного буфера (usart->out_buffer[0x01]), причем копируемое
    // значение OR'ится с 0x80, чтобы установить старший бит (бит 7) в единицу, что указывает на
    // ошибку (недопустимый запрос).

    // Записываем недопустимый код запроса в третий байт выходного буфера
    usart->out_buffer[0x02] = illegal; // Здесь записывается переданный недопустимый код запроса (illegal) в третий байт выходного буфера.

    // Вычисляем CRC16 для первых трех байтов выходного буфера
    PIC_CRC16(usart->out_buffer, 0x03);

    // Записываем младший байт CRC16 в четвертый байт выходного буфера
    usart->out_buffer[0x03] = uchCRCLo; // Здесь вычисляется контрольная сумма CRC16 для первых трех байтов выходного буфера (usart->out_buffer)
    // с использованием функции PIC_CRC16.

    // Записываем старший байт CRC16 в пятый байт выходного буфера
    usart->out_buffer[0x04] = uchCRCHi; // Здесь записывается младший байт CRC16 (uchCRCLo) в четвертый байт выходного буфера.

    // Устанавливаем количество байт для отправки (размер ответа)
    usart->number_send = 5; // Здесь устанавливается количество байт для отправки (usart->number_send), которое равно 5, так как формируется ответ
    //  из 5 байтов (2 байта из входного буфера + 1 байт недопустимого
    //  кода запроса + 2 байта CRC16).
}
/* Эта функция позволяет сформировать ответ о недопустимом запросе в соответствии с протоколом MODBUS,
включая в него необходимые байты данных и CRC16. */

// вариант ответа на неправильную функцию
// Функция answer_illegal_func управляет формированием ответа на недопустимый запрос и выбором метода
// передачи этого ответа в зависимости от режима передачи USART (INT_type или DMA_type).

void answer_illegal_func(struct tag_usart *usart)
{
    // Формируем ответ на недопустимый запрос (недопустимая функция с кодом 0x01)
    answer_illegal(usart, 0x01); // Здесь вызывается функция answer_illegal для формирования ответа на недопустимый запрос.
    //  Передается указатель usart на структуру tag_usart и код недопустимой функции (в данном случае 0x01).

    // Проверяем режим передачи USART
    if (usart->mb_status.tx_mode == INT_type) // Здесь происходит проверка режима передачи USART (tx_mode).
                                              //  Если режим передачи равен INT_type, то используется прямая передача через
                                              //  USART без использования DMA.
    {
        // Если режим передачи - INT_type, запускаем передачу через USART без использования DMA
        start_tx_usart(usart);
    }
    else
    {
        // Если режим передачи - DMA_type, запускаем передачу через USART с использованием DMA
        start_tx_usart_dma(usart, 5); // Здесь 5 - количество байт для передачи (размер ответа)
    }
}

// вариант ответа на неправильную адресацию
// Функция answer_illegal_data_addr управляет формированием ответа на недопустимый запрос (недопустимый адрес данных)
// и выбором метода передачи этого ответа в зависимости от режима передачи USART (INT_type или DMA_type).

void answer_illegal_data_addr(struct tag_usart *usart)
{
    // Формируем ответ на недопустимый запрос (недопустимый адрес данных с кодом 0x02)
    answer_illegal(usart, 0x02);

    // Проверяем режим передачи USART
    if (usart->mb_status.tx_mode == INT_type)
    {
        // Если режим передачи - INT_type, запускаем передачу через USART без использования DMA
        start_tx_usart(usart);
    }
    else
    {
        // Если режим передачи - DMA_type, запускаем передачу через USART с использованием DMA
        start_tx_usart_dma(usart, 5); // Здесь 5 - количество байт для передачи (размер ответа)
    }
}

// вариант ответа на неправильные данные
// Функция answer_illegal_data_val управляет формированием ответа на недопустимый запрос
// (недопустимое значение данных) и выбором метода передачи этого ответа в зависимости от
// режима передачи USART (INT_type или DMA_type).

void answer_illegal_data_val(struct tag_usart *usart)
{
    // Формируем ответ на недопустимый запрос (недопустимое значение данных с кодом 0x03)
    answer_illegal(usart, 0x03);

    // Проверяем режим передачи USART
    if (usart->mb_status.tx_mode == INT_type)
    {
        // Если режим передачи - INT_type, запускаем передачу через USART без использования DMA
        start_tx_usart(usart);
    }
    else
    {
        // Если режим передачи - DMA_type, запускаем передачу через USART с использованием DMA
        start_tx_usart_dma(usart, 5); // Здесь 5 - количество байт для передачи (размер ответа)
    }
}

unsigned short num3;
// Функция mbs_03 формирует ответный пакет Modbus, который включает в себя заголовок, данные и
// контрольную сумму CRC16. После формирования пакета функция запускает передачу данных либо через DMA,
// либо через USART, в зависимости от текущего режима передачи, указанного в структуре _usart->mb_status.
// 3-я фукнкия модбас slave должна отвечать на mbm_03

void mbs_03(struct tag_usart *_usart, unsigned short *source, unsigned short shift, unsigned short num)
{
    num3 = num; // Инициализация переменной num3 значением аргумента num

    // Копирование данных из массива source в буфер исходящих данных _usart->out_buffer,
    // начиная с позиции сдвига (shift) и до количества элементов num3 (в байтах).
    memcpy((void *)(_usart->out_buffer + 0x03), (const void *)(source + shift), (num3 * 2));

    num3 *= 2; // Умножение num3 на 2 (для получения общего количества байт в буфере исходящих данных)

    // Копирование первых двух байт из буфера входящих данных _usart->in_buffer в буфер исходящих данных _usart->out_buffer.
    _usart->out_buffer[0] = _usart->in_buffer[0];
    _usart->out_buffer[1] = _usart->in_buffer[1];

    // Запись значения num3 (общее количество байт в передаваемых данных) в третий байт буфера исходящих данных.
    _usart->out_buffer[0x02] = num3;

    num3 += 0x03; // Увеличение num3 на 3 (для учета первых трех байт буфера исходящих данных)

    // Вычисление CRC16 для буфера исходящих данных _usart->out_buffer с учетом num3 байт.
    PIC_CRC16(_usart->out_buffer, num3);

    // Запись младшего байта CRC16 в следующий байт буфера исходящих данных.
    _usart->out_buffer[num3++] = uchCRCLo;

    // Запись старшего байта CRC16 в последующий байт буфера исходящих данных.
    _usart->out_buffer[num3++] = uchCRCHi;

    _usart->number_send = num3; // Запись количества байт для передачи в переменную number_send в структуре _usart.

    // Проверка режима передачи (tx_mode) в структуре _usart.
    if (_usart->mb_status.tx_mode == DMA_type)
    {
        // Если режим передачи DMA, вызываем функцию передачи через DMA.
        start_tx_usart_dma(_usart, num3);
    }
    else
    {
        // Иначе вызываем функцию передачи через USART.
        start_tx_usart(_usart);
    }
}
/* Эта функция mbs_03 предназначена для формирования и отправки ответного пакета в рамках протокола Modbus. Давайте рассмотрим шаги, которые выполняет эта функция:

Копирование данных из source в буфер исходящих данных:

Функция начинается с копирования данных из массива source в буфер исходящих данных _usart->out_buffer.
Копирование происходит с учетом сдвига (shift) и количества элементов (num), которые указываются в 16-битных словах.
Копирование части входящего буфера в исходящий:

Первые два байта из входящего буфера _usart->in_buffer копируются в начало исходящего буфера _usart->out_buffer.
Это может быть часть заголовка или иной информации, которая должна быть включена в ответный пакет.
Запись длины данных в исходящий буфер:

В третий байт исходящего буфера _usart->out_buffer записывается длина данных, которые будут передаваться (в байтах).
Вычисление контрольной суммы (CRC16):

Функция PIC_CRC16 вызывается для вычисления CRC16 для всего содержимого исходящего буфера.
Результат CRC16 записывается в последние два байта исходящего буфера.
Установка количества байт для передачи:

Значение переменной num3, которая представляет общее количество байт для передачи (включая заголовок, данные и CRC), записывается в переменную _usart->number_send.
Выбор метода передачи данных (DMA или USART):

Проверяется режим передачи в структуре _usart->mb_status.
Если режим DMA (DMA_type), вызывается функция start_tx_usart_dma для запуска передачи данных через DMA с указанием количества байт для отправки.
Если режим USART (INT_type), вызывается функция start_tx_usart для запуска передачи данных через USART. */

// 16-я функция модбас слэйв, отвечает на mbm_10 записывает данные и кратко отвечает что все ок
// функция mbs_10 обрабатывает запросы на запись нескольких регистров, копирует данные в соответствующие массивы,
// меняет порядок байтов, записывает данные во внешнюю память и отправляет ответный пакет с вычисленным CRC16.

void mbs_10(struct tag_usart *_usart, unsigned short *source, unsigned short shift_uni, unsigned short num_uni)
{
    unsigned short ii;

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
        putcs_FRAM(RAMTRON_START_CONFIG,(unsigned char *) MB_conf.buf, 180);
        getcs_FRAM(RAMTRON_START_CONFIG, (unsigned char *) MB_conf.buf, 180);
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
// Итак, функция mbs_uni осуществляет полный цикл обработки запросов Modbus, включая проверку данных,
// расчет CRC16, проверку длины пакета и количества регистров, а также вызов соответствующих функций для чтения
// или записи регистров, после чего завершает соединение Modbus.
short buf_[100];
void mbs_uni(struct tag_usart *usart, unsigned char mbs_addres)
{
    if (usart->mb_status.modb_received)
    {
        // Проверка флага modb_received, указывающего на наличие принятых данных Modbus
        PIC_CRC16(usart->in_buffer, (usart->in_buffer_count));
        // Вычисление CRC16 для принятых данных
        if (uchCRCLo | uchCRCHi)
        {
            // Проверка некорректности CRC16 (неравенство нулю)
            close_mb(usart);
            // Закрытие соединения Modbus в случае ошибки CRC16
            return;
            // Выход из функции
        }

        start_reg = usart->in_buffer[0x02] * 0x100;
        // Извлечение стартового регистра (старший байт)
        start_reg += usart->in_buffer[0x03];
        // Добавление младшего байта к стартовому регистру
        num_reg = usart->in_buffer[0x04] * 0x100;
        // Извлечение количества регистров (старший байт)
        num_reg += usart->in_buffer[0x05];
        // Добавление младшего байта к количеству регистров
        last_reg = start_reg + num_reg;
        // Вычисление номера последнего регистра

        if (((usart->in_buffer_count - 9) != usart->in_buffer[0x06]) && (usart->in_buffer[1] == 0x10))
        {
            // Проверка длины пакета данных и типа функции (0x10 - запись нескольких регистров)
            length_err = 1;
            // Установка флага ошибки длины пакета
        }
        else
        {
            length_err = 0;
            // Сброс флага ошибки длины пакета
        }

        if (((usart->in_buffer_count - 9) != (num_reg * 2)) && (usart->in_buffer[1] == 0x10))
        {
            // Проверка количества регистров в пакете данных
            length_err = 1;
            // Установка флага ошибки количества регистров
        }
        else
        {
            length_err = 0;
            // Сброс флага ошибки количества регистров
        }

        switch (length_err)
        {
        case 1:
            // Обработка ошибки длины пакета или количества регистров
            answer_illegal_data_addr(usart);
            // Генерация ответа о неправильном адресе
            break;

        default:
            switch (usart->in_buffer[1])
            {
            case 0x03:
                if (READ_MOPS)
                {
                    mbs_03(usart,(unsigned short *) MOPS_arr, (start_reg - START_READ_MOPS), num_reg);
                    break;
                }
                // Обработка функции чтения нескольких регистров (0x03)
                if (READ_)
                {
                    mbs_03(usart, MB_swap.buf, (start_reg - START_READ), num_reg);
                    // Выполнение функции чтения с массивом MB_swap.buf
                    break;
                }
                if (CONF_READ_)
                {
                    mbs_03(usart, MB_sw_conf.buf, (start_reg - START_CONF_READ), num_reg);
                    // Выполнение функции чтения с массивом MB_sw_conf.buf
                    break;
                }
                if (MODBUS_READ_)
                {
                    mbs_03(usart, Modbus_sw.buf, (start_reg - START_MODBUS_READ), num_reg);
                    // Выполнение функции чтения с массивом Modbus_sw.buf
                    break;
                }
                // if (MB_DIAGN_READ_)
                // {
                //     mbs_03(usart, MB_diagn_sw.buf, (start_reg - START_MB_DIAGN_READ), num_reg);
                //     // Выполнение функции чтения с массивом MB_diagn_sw.buf
                //     break;
                // }
                
                answer_illegal_data_addr(usart);
                // Генерация ответа о неправильном адресе в случае неизвестной функции
                break;

            case 0x10:
                // Обработка функции записи нескольких регистров (0x10)
                if (WRITE_)
                {
                    mbs_10(usart, MB_swap.input, (start_reg - START_WRITE), num_reg);
                    // Выполнение функции записи с массивом MB_swap.input
                    break;
                }
                if (CONF_WRITE_)
                {
                    mbs_10(usart, MB_sw_conf.buf, (start_reg - START_CONF_WRITE), num_reg);
                    // Выполнение функции записи с массивом MB_sw_conf.buf
                    break;
                }
                if (MODBUS_WRITE_)
                {
                    mbs_10(usart, Modbus_sw.buf, (start_reg - START_MODBUS_WRITE), num_reg);
                    // Выполнение функции записи с массивом Modbus_sw.buf
                    break;
                }
                answer_illegal_data_addr(usart);
                // Генерация ответа о неправильном адресе в случае неизвестной функции
                break;

            default:
                // Обработка неизвестной функции
                answer_illegal_func(usart);
                // Генерация ответа о неправильной функции
                break;
            }
        }
    }
    // Закрытие соединения Modbus
    close_mb(usart);
}
/* Эта функция mbs_uni является обработчиком универсальных запросов в протоколе Modbus. Ее основное назначение - принимать
запросы от ведущего устройства (master), проверять их корректность, извлекать информацию о регистрах и значениях, выполнять
соответствующие действия (чтение или запись), и отправлять ответные пакеты.
Основные шаги, выполняемые функцией mbs_uni:

1. Проверка флага modb_received, который указывает на то, что данные Modbus были приняты.
2. Расчет и проверка CRC16 для данных, принятых через USART.
3. Извлечение информации о начальном и конечном регистрах из полученного запроса.
4. Проверка длины пакета данных и количества регистров.
5. Обработка ошибок в зависимости от результатов проверок:
    - Если обнаружена ошибка CRC16, соединение Modbus закрывается.
    - Если есть ошибки в длине пакета данных или количестве регистров, генерируется ответ о неправильном адресе.
    - В зависимости от типа запроса (функции Modbus), вызывается соответствующая функция для чтения или записи нескольких регистров.
6. В конце функции всегда происходит закрытие соединения Modbus, независимо от результатов обработки запроса. */

// проверяет адрес
// Функция mbs реализует простую логику обработки принятых данных в протоколе Modbus.

/* Эта функция mbs является обработчиком запросов в протоколе Modbus. Ее основное назначение -
проверять принятые данные Modbus и, если они соответствуют ожидаемому адресу Modbus, передавать
управление функции mbs_uni для дальнейшей обработки запроса. Если адрес не совпадает, соединение
закрывается. */
void mbs(struct tag_usart *usart, unsigned char mbs_addres)
{
    if (!usart->mb_status.modb_received)
    {
        // Проверка: если нет принятых данных Modbus
        return;
        // Возврат из функции, если ничего не принято
    }

    if (usart->in_buffer[0] == mbs_addres)
    {
        // Проверка: если принятый адрес соответствует ожидаемому адресу Modbus
        mbs_uni(usart, mbs_addres);
        // Вызов функции обработки запроса Modbus, если адрес соответствует
        return;
        // Возврат из функции после обработки запроса
    }
    else
    {
        close_mb(usart);
        // Закрытие соединения Modbus в случае неверного адреса
        return;
        // Возврат из функции после закрытия соединения
    }
}
/* Функция mbs реализует простую логику обработки принятых данных в протоколе Modbus. Вот подробное описание того, что делает эта функция:

Проверка наличия принятых данных:

Функция начинает с проверки флага modb_received в структуре mb_status устройства usart.
Если флаг указывает на отсутствие принятых данных (modb_received == 0), то функция просто завершает свою работу, не выполняя никаких дополнительных действий.
Проверка адреса Modbus:

Если в принятых данных (in_buffer[0]) содержится адрес, который совпадает с ожидаемым адресом Modbus (mbs_addres), то функция переходит к обработке этого запроса.
Если адрес не совпадает, функция вызывает close_mb(usart), что предположительно сбрасывает текущее состояние Modbus и готовит устройство к новому запросу.
Вызов обработки запроса Modbus:

Если адрес совпадает, функция вызывает функцию mbs_uni(usart, mbs_addres), передавая ей указатель на структуру usart и ожидаемый адрес Modbus.
Эта функция mbs_uni будет отвечать за обработку запроса в зависимости от типа запроса и адреса.
Закрытие соединения:

Если адрес не совпадает, то вызывается close_mb(usart), что, вероятно, означает завершение текущего запроса и готовность к новому запросу.
Итак, функция mbs является основной точкой входа для обработки принятых данных Modbus. Она анализирует принятые данные, определяет адрес и осуществляет соответствующие действия в зависимости от адреса запроса. */

// 3-я фукнция мастер запрос данных

/* Эта функция mbm_03 служит для выполнения операции чтения нескольких регистров устройства по протоколу Modbus.
Она обеспечивает инициализацию передачи данных, формирование запроса, отправку запроса по USART, прием ответа, а
также обработку полученных данных и ошибок. */
void mbm_03(struct tag_usart *usart, unsigned short mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short *dest, unsigned short speed)
{

    unsigned int cc;                      // Объявление переменной cc типа unsigned int для использования в цикле
    unsigned short lockal_buff_swap[109]; // локальный буффер для данных которые надо просвапитьы
    unsigned short lockal_buff[109];      // локальный буффер для просвапленных данных
    if (!usart->mb_status.master_start)   // Если флаг master_start не установлен, функция завершает выполнение
    {
        return;
    }
    switch (usart->mbm_status) // Начало блока switch для обработки разлкичных состояний master-устройства
    {
    case 0: // Состояние 0: инициализация
    {
        if (usart == &usart1) // Если usart указывает на usart1
        {
            UART1_init(speed); // Инициализация UART1 с указанной скоростью
        }
        if (usart == &usart2) // Если usart указывает на usart2
        {
            UART2_init(speed); // Инициализация UART2 с указанной скоростью
        }
        if (usart == &usart4) // Если usart указывает на usart4
        {
            UART4_init(speed); // Инициализация UART4 с указанной скоростью
        }
        if (usart == &usart5) // Если usart указывает на usart5
        {
            UART5_init(speed); // Инициализация UART5 с указанной скоростью
        }
//        usart->mbm_timeout_counter = 500; // Установка таймаута в 500
        usart->mbm_timeout_counter = 1000; // Установка таймаута в 500
    }
    case 1: // формирование запроса
    {
        // Формирование заголовка запроса Modbus
        usart->out_buffer[0x00] = mbm_adres;
        usart->out_buffer[0x01] = 0x03;
        usart->out_buffer[0x03] = shift_03 & 0x00FF;
        usart->out_buffer[0x02] = (shift_03 >> 8) & 0x00FF;
        usart->out_buffer[0x05] = quant_03 & 0x00FF;
        usart->out_buffer[0x04] = (quant_03 >> 8) & 0x00FF;
        PIC_CRC16(usart->out_buffer, 0x06); // Вычисление CRC16 для запроса
        usart->out_buffer[0x06] = uchCRCLo;
        usart->out_buffer[0x07] = uchCRCHi;
        usart->number_send = 0x08;        // Установка числа отправляемых байт
//        usart->mbm_timeout_counter = 100; // Установка счетчика таймера
        usart->mb_status.tm_on = 1;       // Установка флага TM_ON
        // Инкремент счетчика ошибок
        usart->mb_status.master_timeout_flag = 0; // Сброс
        usart->mb_status.modb_received = 0;       // Сброс флага modb_received
        // И так далее для всех флагов и переменных
        usart->mb_status.byte_missing = 0;
        usart->mb_status.crc_error = 0;
        usart->mb_status.device_error = 0;
        usart->mb_status.coll_1 = 0;
        usart->mb_status.coll_2 = 0;
        usart->mb_status.coll_3 = 0;
        start_tx_usart_dma(usart, 8); // Начало передачи данных через USART
        usart->mbm_status = 2;        // Установка состояния master-устройства в 2
        if (usart == &usart2)
        {
            LED3_TOGGLE;
        }
        break;
    }
    case 2: // Состояние 2: ожидание ответа и обработка результата
    {
        if (!usart->mb_status.master_timeout_flag && !usart->mb_status.modb_received) // если нет ответа и не сработал таймаут, то выходим
            return;
        if (usart->mb_status.master_timeout_flag) // Если есть таймаут, инкрементируем счетчик ошибок и закрываем все
        {                                         // если есть таймаут, инкрем. счетчик ошибок и закрываем все
            usart->mbm_err++;                     // Увеличиваем счетчик ошибок
            usart->mbm_status = 0;                // Сброс состояния master-устройства
            usart->mb_status.master_start = 0;    // Сброс флага master_start
            break;
        }

        if (usart->in_buffer[1] == 0x83) // Если получен ответ о неправильном обращении
        {
            // Проверяем, на какую коллизию указывает ответ
            if (usart->in_buffer[2] == 0x01)
            {
                usart->mb_status.coll_1 = 1;       // Устанавливаем флаг коллизии 1
                usart->mbm_err++;                  // Увеличиваем счетчик ошибок
                usart->mb_status.master_start = 0; // Сброс флага master_start
                usart->mbm_status = 0;             // Сброс состояния master-устройства
                break;
            }
            if (usart->in_buffer[2] == 0x02)
            {
                usart->mb_status.coll_2 = 1;       // Устанавливаем флаг коллизии 1
                usart->mbm_err++;                  // Увеличиваем счетчик ошибок
                usart->mb_status.master_start = 0; // Сброс флага master_start
                usart->mbm_status = 0;             // Сброс состояния master-устройства
                break;
            }
            if (usart->in_buffer[2] == 0x03)
            {
                usart->mb_status.coll_3 = 1;       // Устанавливаем флаг коллизии 1
                usart->mbm_err++;                  // Увеличиваем счетчик ошибок
                usart->mb_status.master_start = 0; // Сброс флага master_start
                usart->mbm_status = 0;             // Сброс состояния master-устройства
                break;
            }
        }
        //			if (usart->in_buffer_count!=(quant_03*2+5))									//byte missing
        //				{usart->mbm_status=0; usart->mb_status.byte_missing=1; usart->mbm_err++; usart->mb_status.master_start=0; break;}
        if (usart->in_buffer[0] != usart->out_buffer[0]) // Проверяем соответствие принятого адреса ожидаемому адресу
        {
            usart->mbm_status = 0;             // Сброс состояния master-устройства
            usart->mb_status.device_error = 1; // Установка флага ошибки устройства
            usart->mbm_err++;                  // Увеличиваем счетчик ошибок
            usart->mb_status.master_start = 0; // Сброс флага master_start
            break;
        }
        // проверяем CRC ответ
        PIC_CRC16(usart->in_buffer, (usart->in_buffer_count)); // // Вычисляем CRC16 для принятых данных
        if (uchCRCLo | uchCRCHi)                               // Если CRC неверен
        {
            usart->mbm_status = 0;             // Сброс состояния master-устройства
            usart->mb_status.crc_error = 1;    // Установка флага ошибки CRC
            usart->mbm_err++;                  // Увеличиваем счетчик ошибок
            usart->mb_status.master_start = 0; // Сброс флага master_start
            break;
        } // wrong crc

        // Копируем данные в целевой массив и выполняем необходимые действия
        usart -> in_buffer[4] = 4;
        memcpy((void *)(lockal_buff_swap), (const void *)(usart->in_buffer + 0x03), usart->in_buffer[2]); // если все нормально, то начинаем
        for (cc = 0; cc < quant_03; cc++)
        {
            lockal_buff[cc + shift_03] = swapshort(lockal_buff_swap[cc + shift_03]);
        }
        memcpy((void *)(dest), (const void *)(lockal_buff), lockal_buff[2]); // если все нормально, то начинаем

        // Обновляем счетчик ответов и сбрасываем флаги ошибок
        usart->answer_count++;             // Увеличиваем счетчик ответов
        usart->mb_status.master_error = 0; // Сброс флага ошибки master-устройства
        usart->mb_status.master_start = 0; // Сброс флага master_start
        usart->mbm_status = 0;             // Сброс состояния master-устройства
        break;
    }
    default: // Состояние по умолчанию: сброс состояния
    {
        usart->mbm_status = 0;             // Сброс состояния master-устройства
        usart->mb_status.master_start = 0; // Сброс флага master_start
        break;
    }
    }
}

/* Эта функция mbm_03 выполняет чтение нескольких регистров по протоколу Modbus. Вот пошаговый комментарий:

Объявление функции с параметрами: указатель на структуру tag_usart, адрес Modbus, смещение, количество регистров,
указатель на целевой массив и скорость передачи.

Объявление локальной переменной cc для использования в циклах.

Проверка флага master_start в структуре mb_status. Если флаг сброшен (равен 0), функция завершается.

Выполнение операций в зависимости от текущего состояния mbm_status:

Состояние 0: Начальная инициализация устройства. Выбор и инициализация USART в зависимости от переданной скорости.
    Установка таймаута в соответствии с переданной скоростью. Установка mbm_status в 1.
Состояние 1: Формирование запроса для чтения нескольких регистров. Заполнение выходного буфера Modbus данными
    для запроса: адрес, функция чтения, стартовый регистр, количество регистров и CRC16. Установка таймаута, включение таймера, сброс флагов ошибок и статусов. Запуск передачи данных через USART. Установка mbm_status в 2.
Состояние 2: Ожидание ответа и обработка результата. Проверка таймаута и приема данных. Обработка различных
    ситуаций ответа (коллизии, неверный CRC и т. д.). Копирование данных ответа в целевой массив. Увеличение счетчика ответов и сброс
    флагов ошибок. Возврат к состоянию 0 для нового запроса.
Состояние по умолчанию: Сброс состояний и флагов при неожиданном состоянии.

Эта функция обеспечивает обмен данными с устройствами по протоколу Modbus, осуществляя чтение нескольких регистров и обработку ответов. */