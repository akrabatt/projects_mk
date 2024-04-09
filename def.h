#define PBCLK2_      49766400    //perepheral boost cklock 2
#define U5_speed        115200  //speed bits
#define timeout1        55
#define frame_delay_1   PBCLK2_/115200*timeout1
#define OUT_SIZE    0x100   //for tag_usart - out_buffer
#define IN_SIZE     0x100   //for tag_usart - in_buffer
#define IN_SIZE1    0xF0
#define  INT_type	1
#define  ENAB_RX5		PORTFbits.RF2 = 0	
#define  ENAB_TX5		PORTFbits.RF2 = 1
