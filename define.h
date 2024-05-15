#include <xc.h>
#include <sys/attribs.h>


#define num_zone_mops   8

#define SYS_CLK_FREQUENCY  (199065600ull)       // Fsys = 200 MHz
#define CPU_CLK_FREQUENCY  SYS_CLK_FREQUENCY/2  // Fcpu = 200 MHz
#define PB3_CLK_FREQUENCY SYS_CLK_FREQUENCY/27   // Fpb3 = 2 MHz

#define  PBCLK2_    49766400

#define  DMA_type	0
#define  INT_type	1

#define  ENAB_TX5   PORTFbits.RF2 = 1	
#define  ENAB_RX5   PORTFbits.RF2 = 0	
#define  ENAB_TX4   PORTBbits.RB12 = 1
#define  ENAB_RX4   PORTBbits.RB12 = 0 
#define  ENAB_TX3   PORTBbits.RB15 = 1
#define  ENAB_RX3   PORTBbits.RB15 = 0 
#define  ENAB_TX2   PORTDbits.RD13 = 1
#define  ENAB_RX2   PORTDbits.RD13 = 0 
#define  ENAB_TX1   PORTDbits.RD1 = 1
#define  ENAB_RX1   PORTDbits.RD1 = 0 

//?
#define  t9_del_1	timer9_bits.t_del_1		//		:1;		// 12

#define  OUT_SIZE		0x100
#define  IN_SIZE		0x100
#define  IN_SIZE1		0xF0

#define  timeout1       55
#define  frame_delay_1  PBCLK2_/115200*timeout1

/////////////////		Modbus alowed areas 		//////////////////////////

#define  START_READ     2000			// MB_swap 
#define  END_READ       2078			// 

#define  START_WRITE    2054			
#define  END_WRITE      2078			// 

#define  READ_			((start_reg>=START_READ)&&(last_reg<=END_READ))			
#define  WRITE_			((start_reg>=START_WRITE)&&(last_reg<=END_WRITE))		

#define  START_CONF_READ				500			// config area - setting of engine parameters
#define  END_CONF_READ  				696			// 
#define  START_CONF_WRITE				500			//
#define  END_CONF_WRITE					696			// 

#define  CONF_READ_             ((start_reg >= START_CONF_READ) && (last_reg <= END_CONF_READ))	
#define  CONF_WRITE_            ((start_reg >= START_CONF_WRITE) && (last_reg <= END_CONF_WRITE))

#define  START_MODBUS_READ				0			// working area of engine control and statuses
#define  END_MODBUS_READ  				82			// 
#define  START_MODBUS_WRITE				0			//
#define  END_MODBUS_WRITE				12			// 

#define  MODBUS_READ_       ((start_reg >= START_MODBUS_READ) && (last_reg <= END_MODBUS_READ))	
#define  MODBUS_WRITE_		((start_reg >= START_MODBUS_WRITE) && (last_reg <= END_MODBUS_WRITE))

#define  START_MB_DIAGN_READ            200			// config area - setting of engine parameters
#define  END_MB_DIAGN_READ              312			// 
#define  START_MB_DIAGN_WRITE           200			//
#define  END_MB_DIAGN_WRITE				312			// 

#define  MB_DIAGN_READ_           ((start_reg >= START_MB_DIAGN_READ) && (last_reg <= END_MB_DIAGN_READ))	
#define  MB_DIAGN_WRITE_          ((start_reg >= START_MB_DIAGN_WRITE) && (last_reg <= END_MB_DIAGN_WRITE))    

#define  RAMTRON_START              64
#define  RAMTRON_START_CONFIG		512

#define  CUR_CTRL_VAL       10

#define  TMR4CLK	    49776400

#define  OC_FREQ            3000    

#define  FILT_DISCRET       500
#define  CYCLE              10

////////////////	End Modbus alowed area 	/////////////////////

#define  CONF1		PORTCbits.RC2			
#define  CONF2		PORTCbits.RC3			
#define  CONF3		PORTCbits.RC4			
#define  CONF4		PORTGbits.RG6			 
#define  CONF5		PORTEbits.RE5			
#define  CONF6		PORTEbits.RE6			
#define  CONF7		PORTEbits.RE7			
#define  CONF8		PORTCbits.RC1			

#define  DI_1		PORTAbits.RA5 			
#define  DI_2		PORTGbits.RG15			
#define  DI_3		PORTFbits.RF4 			

//  Modbus data define
#define CYLINDERS_NUM	        10

// for UARTx_init
#define URXISEL1	U1STAbits.URXISEL
#define URXISEL2	U2STAbits.URXISEL
#define URXISEL4	U4STAbits.URXISEL
#define URXISEL5	U5STAbits.URXISEL

#define PDSEL1		U1MODEbits.PDSEL
#define STSEL1		U1MODEbits.STSEL
#define PDSEL2		U2MODEbits.PDSEL
#define STSEL2		U2MODEbits.STSEL
#define PDSEL4		U4MODEbits.PDSEL
#define STSEL4		U4MODEbits.STSEL
#define PDSEL5		U5MODEbits.PDSEL
#define STSEL5		U5MODEbits.STSEL

#define UARTEN1		U1MODEbits.UARTEN
#define UTXEN1		U1STAbits.UTXEN
#define UARTEN2		U2MODEbits.UARTEN
#define UTXEN2		U2STAbits.UTXEN
#define UARTEN4		U4MODEbits.UARTEN
#define UTXEN4		U4STAbits.UTXEN
#define UARTEN5		U5MODEbits.UARTEN
#define UTXEN5		U5STAbits.UTXEN

#define  FOSC		9216000					//0x8CA000
#define  PLL_rate		4
#define  Fcy			((FOSC*PLL_rate)/4)
#define rx_timeout1			35
#define  receive	0

