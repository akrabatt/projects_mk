#include <xc.h>
#include <sys/attribs.h> /* contains __ISR() Macros */
// #include "extern.h"
#include "global.h"
#include "define.h"

// ��������� ������� �������
extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs(struct tag_usart *usart, unsigned char mbs_addres);
extern void mbm_03(struct tag_usart *usart, unsigned char mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short *dest, unsigned long speed);
extern void InitializeSystem(void);

int main(void)
{
    InitializeSystem(); // �������������� �������
    ENAB_RX5;
    ENAB_RX4;
    usart4.mb_status.tx_mode = DMA_type; // ���� 4 �����, ������ ����� ���
    usart5.mb_status.tx_mode = INT_type; // ���� 5 ������, ������ ����� ����������
    while (1)
    {
        mbs(&usart4, 1);    // ��������� ���� 4 �����
        stop_uart_tx_dma(); // ����� ���� ��� �������� ���������, �������� �� �����

        mbm_03(&usart5, 1, 0, 28, (unsigned short *)&MOPS_arr[1], 115200); // ��������� �� 5 ����� ������� 3-� �������
        stop_uart_tx();                                                    // ���������� ��� � ��������� �� �����

        // ��� ��������
        // PORTGbits.RG7 = help_strobe;

        // �������
        LED_8 = help_strobe;
    }
}
