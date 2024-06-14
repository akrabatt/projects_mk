/* ************************************************************************** */
/***************************************************************** */
#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>

//#include "global.h"    /* contains __ISR() Macros */
//#include "extern.h"

#ifdef __cplusplus
extern "C" {
#endif
#define EXAMPLE_CONSTANT 0


#define SYS_CLK_FREQUENCY  (199065600ull)       // Fsys = 200 MHz
#define CPU_CLK_FREQUENCY  SYS_CLK_FREQUENCY/2  // Fcpu = 200 MHz
#define PB3_CLK_FREQUENCY SYS_CLK_FREQUENCY/27   // Fpb3 = 2 MHz

#define  PBCLK3_		49766400
#define  PBCLK2_		49766400
    
// LED_LD1 (RG6)
#define LED_LD1       	LATBbits.LATB6
#define TRIS_LED_LD1  	TRISBbits.TRISB6
#define LED_LD1_SET()   LATBSET = _LATB_LATB6_MASK;
#define LED_LD1_CLR()   LATBCLR = _LATB_LATB6_MASK;
#define LED_LD1_INV()   LATBINV = _LATB_LATB6_MASK;

#define  DMA_type	0
#define  INT_type	1

#define  ENAB_TX5		PORTFbits.RF2 = 1	
#define  ENAB_RX5		PORTFbits.RF2 = 0	
#define  ENAB_TX4		PORTBbits.RB12 = 1
#define  ENAB_RX4		PORTBbits.RB12 = 0 

#define  OUT_SIZE		0x100
#define  IN_SIZE		0x100
#define  OUT_SIZE2		0xF0
#define  IN_SIZE1		0xF0
#define  INCAP_VOLUME	380    
    
#define  timeout1       55
#define  timeout4       55    
#define  TICK           1 
#define  MASTER_TICK    1 
#define  num_zones      8    
    
 
#define  frame_delay_1          PBCLK2_/115200*timeout1
#define  frame_delay_4          PBCLK2_/115200*timeout4
    
/////////////////		Modbus alowed areas 		//////////////////////////

#define  START_READ					2000			// отладочгая область чтение
#define  END_READ					2078			// 

#define  START_WRITE				2054			// отладочгая область запись
#define  END_WRITE					2078			// 

#define  READ_			((start_reg>=START_READ)&&(last_reg<=END_READ))			// ??????? ?????? ????????? ?????
#define  WRITE_			((start_reg>=START_WRITE)&&(last_reg<=END_WRITE))		// ??????? ?????? ????????????

#define  START_WORK_READ				800			// ??????? ?????? ??????? ??????
#define  END_WORK_READ					812			// 
#define  START_WORK_WRITE				806			// ??????? ?????? ??????? ??????
#define  END_WORK_WRITE					812			// 

#define  WORK_READ_		((start_reg >= START_WORK_READ) && (last_reg <= END_WORK_READ))	
#define  WORK_WRITE_		((start_reg >= START_WORK_WRITE) && (last_reg <= END_WORK_WRITE))

#define  START_CALIBR_READ				1000			// ??????? ?????? ??????? ??????
#define  END_CALIBR_READ				1034			// 
#define  START_CALIBR_WRITE				1000			// ??????? ?????? ??????? ??????
#define  END_CALIBR_WRITE				1034			// 

#define  CALIBR_READ_		((start_reg >= START_CALIBR_READ) && (last_reg <= END_CALIBR_READ))	
#define  CALIBR_WRITE_		((start_reg >= START_CALIBR_WRITE) && (last_reg <= END_CALIBR_WRITE))

#define  START_CONF_READ				500			// config area - setting of engine parameters
#define  END_CONF_READ  				696			// 
#define  START_CONF_WRITE				500			//
#define  END_CONF_WRITE					520			// 

#define  CONF_READ_             ((start_reg >= START_CONF_READ) && (last_reg <= END_CONF_READ))	
#define  CONF_WRITE_            ((start_reg >= START_CONF_WRITE) && (last_reg <= END_CONF_WRITE))

#define  START_MODBUS_READ				0			// working area of engine control and statuses
#define  END_MODBUS_READ  				82			// 
#define  START_MODBUS_WRITE				0			//
#define  END_MODBUS_WRITE				12			// 

#define  MODBUS_READ_           ((start_reg >= START_MODBUS_READ) && (last_reg <= END_MODBUS_READ))	
#define  MODBUS_WRITE_		((start_reg >= START_MODBUS_WRITE) && (last_reg <= END_MODBUS_WRITE))
    
#define  START_MB_DIAGN_READ				3000			// config area - setting of engine parameters
#define  END_MB_DIAGN_READ  				4200			// 
#define  START_MB_DIAGN_WRITE				3000			//
#define  END_MB_DIAGN_WRITE                 4200			// 

#define  MB_DIAGN_READ_           ((start_reg >= START_MB_DIAGN_READ) && (last_reg <= END_MB_DIAGN_READ))	
#define  MB_DIAGN_WRITE_          ((start_reg >= START_MB_DIAGN_WRITE) && (last_reg <= END_MB_DIAGN_WRITE))    
    
#define  RAMTRON_START              64
#define  RAMTRON_START_CONFIG		1024
    
#define  COORD_MAX			MB_conf.CV_pos_max
#define  COORD_MIN			MB_conf.CV_pos_min
#define  CUR_MAX			MB_conf.CV_curr_max
#define  CUR_MIN			MB_conf.CV_curr_min
#define  CUR_SCALE			MB_conf.CV_curr_scale

#define  CUR_CTRL_VAL			10
//#define  CUR_CTRL_VAL			MB_conf.CV_check_level  

#define  INT_CLR			0.0  
#define  INT_MCLR			1.0  
#define  MREG_FREQ			100    
    
#define  TMR4CLK	    49776400
//#define  TMR4CLK	    24883200
#define  OC_FREQ            3000    
#define  OC_MAX             TMR4CLK / OC_FREQ -1
#define  OC_MIN             1500
#define   FILTER	    20    
#define	  d_count_size	    4
    
#define  FILT_CRPM          4
    
#define  FILT_C             10
#define  FILT_I             10
#define  FILT_DISCRET       500
#define  CYCLE              10
    
#define  TMAXUOZ            58320                  
    
    ////////////////	End Modbus alowed area 	/////////////////////

#define  STROBE		PORTGbits.RG7			// изменено для платы 586-хх
    
#define  LED_AO		PORTGbits.RG12			// изменено для платы 586-хх pin 96
#define  LED_AO_ON	PORTG = LATG | 0x1000		// изменено для платы 586-хх
#define  LED_AO_OFF	PORTG = LATG & 0xEFFF		// изменено для платы 586-хх
    
#define  LED_IGN	PORTGbits.RG13			// изменено для платы 586-хх pin 97
#define  LED_IGN_ON	PORTG = LATG | 0x2000		// изменено для платы 586-хх
#define  LED_IGN_OFF	PORTG = LATG & 0xDFFF		// изменено для платы 586-хх
     
#define  LED_STOP	PORTEbits.RE4			// изменено для платы 586-хх pin 100
#define  LED_STOP_ON	PORTE = LATE | 0x0010		// изменено для платы 586-хх
#define  LED_STOP_OFF	PORTE = LATE & 0xFFEF		// изменено для платы 586-хх    

#define  LED_SYNC	PORTEbits.RE3			// изменено для платы 586-хх pin 99
#define  LED_SYNC_ON	PORTE = LATE | 0x0008		// изменено для платы 586-хх
#define  LED_SYNC_OFF	PORTE = LATE & 0xFFF7		// изменено для платы 586-хх    

#define  LED_WIGN	PORTEbits.RE2			// изменено для платы 586-хх pin 98
#define  LED_WIGN_ON	PORTG = LATG | 0x0004		// изменено для платы 586-хх   
#define  LED_WIGN_OFF	PORTG = LATG & 0xFFFB		// изменено для платы 586-хх   

#define  LED_8		PORTEbits.RE0			// изменено для платы 586-хх pin 91
#define  LED_8_ON	PORTE = LATE | 0x0001		// изменено для платы 586-хх
#define  LED_8_OFF	PORTE = LATE & 0xFFFE		// изменено для платы 586-хх        
 
#define  LED_7		PORTEbits.RE1			// изменено для платы 586-хх pin 94
#define  LED_7_ON	PORTE = LATE | 0x0002		// изменено для платы 586-хх   
#define  LED_7_OFF	PORTE = LATE & 0xFFFD		// изменено для платы 586-хх   
    
    
#define  LED9		PORTDbits.RD15			// изменено для платы 586-хх pin 48
#define  LED9_ON	PORTD = LATD | 0x8000		// изменено для платы 586-хх   
#define  LED9_OFF	PORTD = LATD & 0x7FFF		// изменено для платы 586-хх       
    
#define  LED10		PORTAbits.RA2			// изменено для платы 586-хх pin 59
#define  LED10_ON	PORTA = LATA | 0x0004		// изменено для платы 586-хх   
#define  LED10_OFF	PORTA = LATA & 0xFFFB		// изменено для платы 586-хх       

#define  DO_2		PORTAbits.RA3			// изменено для платы 606-хх pin 60
#define  DO_2_ON	PORTA = LATA | 0x0008		// изменено для платы 606-хх   
#define  DO_2_OFF	PORTA = LATA & 0xFFF7		// изменено для платы 606-хх       

#define  DO_1		PORTAbits.RA4			// изменено для платы 606-хх pin 61
#define  DO_1_ON	PORTA = LATA | 0x0010		// изменено для платы 606-хх   
#define  DO_1_OFF	PORTA = LATA & 0xFFEF		// изменено для платы 606-хх   

#define  IGN_ON		PORTDbits.RD5			// изменено для платы 606-хх pin 82

#define  TAP_ON		PORTC = LATC | 0x2000		// изменено для платы 586-хх pin 72
#define  TAP_OFF	PORTC = LATC & 0xDFFF		// изменено для платы 586-хх pin 72

#define  IGN_1		PORTDbits.RD9			// изменено для платы 586-хх pin 68
#define  IGN_2		PORTDbits.RD2			// изменено для платы 586-хх pin 77
#define  IGN_3		PORTDbits.RD10			// изменено для платы 586-хх pin 69
#define  IGN_4		PORTDbits.RD3			// изменено для платы 586-хх pin 78
#define  IGN_5		PORTDbits.RD11			// изменено для платы 586-хх pin 70
#define  IGN_6		PORTDbits.RD12			// изменено для платы 586-хх pin 79
#define  IGN_7		PORTDbits.RD0			// изменено для платы 586-хх pin 71
#define  IGN_8		PORTDbits.RD13			// изменено для платы 586-хх pin 80
#define  IGN_9		PORTDbits.RD1			// изменено для платы 586-хх pin 76
#define  IGN_10		PORTDbits.RD4			// изменено для платы 586-хх pin 81

#define  ON_IGN_1       PORTD = LATD | 0x0200		// изменено для платы 586-хх pin 68
#define  ON_IGN_2       PORTD = LATD | 0x0004		// изменено для платы 586-хх pin 77
#define  ON_IGN_3       PORTD = LATD | 0x0400		// изменено для платы 586-хх pin 69
#define  ON_IGN_4       PORTD = LATD | 0x0008		// изменено для платы 586-хх pin 78
#define  ON_IGN_5       PORTD = LATD | 0x0800		// изменено для платы 586-хх pin 70
#define  ON_IGN_6       PORTD = LATD | 0x1000		// изменено для платы 586-хх pin 79
#define  ON_IGN_7       PORTD = LATD | 0x0001		// изменено для платы 586-хх pin 71
#define  ON_IGN_8       PORTD = LATD | 0x2000		// изменено для платы 586-хх pin 80
#define  ON_IGN_9       PORTD = LATD | 0x0002		// изменено для платы 586-хх pin 76
#define  ON_IGN_10      PORTD = LATD | 0x0010		// изменено для платы 586-хх pin 81
    
#define  IGN_RESET      PORTD = LATD & 0xC1E0		// изменено для платы 586-хх
#define  MAX_CYL_NUM    10				// изменено для платы 586-хх

#define  CTRL1      PORTGbits.RG0			// изменено для платы 586-хх pin 88
#define  CTRL2      PORTGbits.RG1			// изменено для платы 586-хх pin 87

#define  CONF1		PORTCbits.RC2			// изменено для платы 606-хх pin 7 
#define  CONF2		PORTCbits.RC3			// изменено для платы 606-хх pin 8
#define  CONF3		PORTCbits.RC4			// изменено для платы 606-хх pin 9
#define  CONF4		PORTGbits.RG6			// изменено для платы 606-хх pin 10 
#define  CONF5		PORTEbits.RE5			// изменено для платы 586-хх pin 3
#define  CONF6		PORTEbits.RE6			// изменено для платы 586-хх pin 4 
#define  CONF7		PORTEbits.RE7			// изменено для платы 586-хх pin 5
#define  CONF8		PORTCbits.RC1			// изменено для платы 586-хх pin 6

#define  DI_1		PORTAbits.RA5 			// изменено для платы 606-хх pin 2
#define  DI_2		PORTGbits.RG15			// изменено для платы 606-хх pin 1
    
//  Modbus data define
/*    */
#define  FLAP_SET	Modbus.CV_set
#define  FLAP_POS	Modbus.CV_pos
#define  FLAP_CURR	Modbus.CV_current    

#define  RPM_UOZ_MAX    MB_conf.UOZ_RPM_max
#define  RPM_UOZ_MIN	MB_conf.UOZ_RPM_min

#define  NOM_UOZ        MB_conf.UOZ_high
#define  LOW_UOZ        MB_conf.UOZ_low
#define  CONST_UOZ      MB_conf.constructive_UOZ
    
#define CYLINDERS_NUM	        10
#define CANDLES_NUM	        1

#define AO_MISS_IGN_SIGN        1
#define AO_SAU_COMMAND          2
#define AO_TOO_LOW_RPM          3
#define AO_TOO_HIGH_RPM         4
#define AO_CV_ERROR             5
#define AO_UNSYNC               6
#define AO_CYL_BR_LOW           7
#define AO_CYL_SC_LOW           8
#define AO_CYL_BR_HIGH          9
#define AO_START_ERROR          10
#define AO_CV_CURR_ERROR        11
#define AO_NO_CHARGE            12
#define CV_SENSOR_BRAKE         13
#define AO_5CYL_ERROR_EVEN	14
#define AO_5CYL_ERROR_ODD	15

    
    
 
    
    
    
    
    
/* *****************************************************************************
 End of File
 */
