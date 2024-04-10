#define PBCLK2_      49766400    //perepheral boost cklock 2
#define U5_speed        57600  //speed bits
#define timeout1        55
#define frame_delay_1   PBCLK2_/115200*timeout1
#define OUT_SIZE    0x100   //for tag_usart - out_buffer
#define IN_SIZE     0x100   //for tag_usart - in_buffer
#define IN_SIZE1    0xF0
#define  INT_type	1
#define  ENAB_RX5		PORTFbits.RF2 = 0	
#define  ENAB_TX5		PORTFbits.RF2 = 1

/////////////////
#define SYS_PORT_A_ANSEL        0x0600
#define SYS_PORT_A_TRIS         0xc6e3
#define SYS_PORT_A_LAT          0x0
#define SYS_PORT_A_ODC          0x0
#define SYS_PORT_A_CNPU         0x0
#define SYS_PORT_A_CNPD         0x0
#define SYS_PORT_A_CNEN         0x0

#define SYS_PORT_B_ANSEL        0x8000
#define SYS_PORT_B_TRIS         0xe6ff
#define SYS_PORT_B_LAT          0x8000
#define SYS_PORT_B_ODC          0x0
#define SYS_PORT_B_CNPU         0x0
#define SYS_PORT_B_CNPD         0x0
#define SYS_PORT_B_CNEN         0x0

#define SYS_PORT_C_ANSEL        0x0
#define SYS_PORT_C_TRIS         0xd01e
#define SYS_PORT_C_LAT          0x0
#define SYS_PORT_C_ODC          0x0
#define SYS_PORT_C_CNPU         0x0
#define SYS_PORT_C_CNPD         0x0
#define SYS_PORT_C_CNEN         0x0

#define SYS_PORT_D_ANSEL        0x4000
#define SYS_PORT_D_TRIS         0x4000
#define SYS_PORT_D_LAT          0x0
#define SYS_PORT_D_ODC          0x0
#define SYS_PORT_D_CNPU         0x0
#define SYS_PORT_D_CNPD         0x0
#define SYS_PORT_D_CNEN         0x0

#define SYS_PORT_E_ANSEL        0x0
#define SYS_PORT_E_TRIS         0x3e0
#define SYS_PORT_E_LAT          0x10
#define SYS_PORT_E_ODC          0x0
#define SYS_PORT_E_CNPU         0x0
#define SYS_PORT_E_CNPD         0x0
#define SYS_PORT_E_CNEN         0x0

#define SYS_PORT_F_ANSEL        0x0
#define SYS_PORT_F_TRIS         0x313b
#define SYS_PORT_F_LAT          0x0
#define SYS_PORT_F_ODC          0x0
#define SYS_PORT_F_CNPU         0x0
#define SYS_PORT_F_CNPD         0x0
#define SYS_PORT_F_CNEN         0x0

#define SYS_PORT_G_ANSEL        0x0
#define SYS_PORT_G_TRIS         0x8343
#define SYS_PORT_G_LAT          0x0
#define SYS_PORT_G_ODC          0x0
#define SYS_PORT_G_CNPU         0x0
#define SYS_PORT_G_CNPD         0x0
#define SYS_PORT_G_CNEN         0x0