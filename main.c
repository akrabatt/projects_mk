#include "define.h"
#include "global.h" 

extern void stop_uart_tx(void);
extern void stop_uart_tx_dma(void);
extern void mbs(struct tag_usart * usart, unsigned char mbs_addres);
extern void close_mb(struct tag_usart * usart);
extern void InitializeSystem(void);

int main(void) {
    InitializeSystem();

    help_reset = 1;
    ENAB_RX5; //����������� ��������� ����� � �� �����    == PORTFbits.RF2 = 0	
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

    while (1) {

        mbs(&usart5, 1); // ����� modbus slave usart5 �� 5�� ����� � 1-� �������� 
        stop_uart_tx_dma();
        mbs(&usart4, 1); 
        mbs(&usart3, 1); 
        mbs(&usart2, 1); 
        mbs(&usart1, 1); 
        //    stop_uart_tx();
    }
}


