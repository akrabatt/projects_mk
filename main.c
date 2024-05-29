#include "define.h"
#include "global.h"

extern void stop_uart_tx(void);                                     // ���� �����
extern void stop_uart_tx_dma(void);                                 // ���� ����� ���
extern void mbs(struct tag_usart *usart, unsigned char mbs_addres); // ������ �����
extern void close_mb(struct tag_usart *usart);                      // ��������� ������
extern void InitializeSystem(void);                                 // ������������� �������
extern unsigned short swapshort(unsigned short data);               // ����

/* ��������� ������ ����������� ����������� ��� ����� */
union tag_MOPS MOPS_arr[10]; // �������� ������ ��������

int main(void)
{
    InitializeSystem(); // �������������� �������

    help_reset = 1;
    ENAB_RX5; // ����������� ��������� ����� � �� �����    == PORTFbits.RF2 = 0
    ENAB_RX4; // ���� ����� �� ��� ������� ����������
    ENAB_RX3; // ���� ����� �� ��� ������� ����������
    ENAB_RX2; // ���� ����� �� ��� ������� ����������
    ENAB_RX1; // ���� ����� �� ��� ������� ����������

    /* ����� ������ usart  �� ��� */
    usart5.mb_status.tx_mode = DMA_type;
    usart4.mb_status.tx_mode = DMA_type;
    usart3.mb_status.tx_mode = DMA_type;
    usart2.mb_status.tx_mode = DMA_type;
    usart1.mb_status.tx_mode = DMA_type;
    /* ����� ������ �� ����������� */
    // usart1.mb_status.tx_mode = INT_type;
    // usart4.mb_status.tx_mode = INT_type;

    while (1)
    {

        mbm_03(&usart1, 1, 0, 28, &MOPS_arr[0], 5); // ������ ������
        mbm_03(&usart2, 2, 0, 28, &MOPS_arr[1], 5); // ������ ������
        mbm_03(&usart4, 4, 0, 28, &MOPS_arr[2], 5); // ������ ������
        mbm_03(&usart5, 5, 0, 28, &MOPS_arr[3], 5); // ������ ������
        mbs(&usart3, 1);
        stop_uart_tx_dma();
        //    stop_uart_tx();
        Modbus.Modbus_data.cyl_mask = 50;
        Modbus_sw.Modbus_data.cyl_mask = swapshort(Modbus.Modbus_data.cyl_mask);
        //        LED3_TOGGLE;
    }
}
