#ifndef DEFINE_H
#define DEFINE_H

#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>

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


//ENAB_TX_RX
//u5
#define  ENAB_TX5		PORTFbits.RF2 = 1	
#define  ENAB_RX5		PORTFbits.RF2 = 0	
//u4
#define  ENAB_TX4		PORTBbits.RB12 = 1
#define  ENAB_RX4		PORTBbits.RB12 = 0 
//u3
#define  ENAB_TX3       PORTBbits.RB15 = 1
#define  ENAB_RX3       PORTBbits.RB15 = 0
//u2
#define  ENAB_TX2       PORTDbits.RD13 = 1
#define  ENAB_RX2       PORTDbits.RD13 = 0
//u1
#define  ENAB_TX1       PORTDbits.RD1 = 1
#define  ENAB_RX1       PORTDbits.RD1 = 0
//


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


/////////////////		leds for modbus 		    //////////////////////////
//uart3
#define U3_LED_TX_TOGGLE    PORTGbits.RG14 = LATGbits.LATG14 ^ 1;   // pin 95/RG14
#define U3_LED_RX_TOGGLE    PORTGbits.RG12 = LATGbits.LATG12 ^ 1;   // pin 96/RG12
#define U3_LED_TX_ON        PORTGbits.RG14 = 1;
#define U3_LED_TX_OFF       PORTGbits.RG14 = 0;
#define U3_LED_RX_ON        PORTGbits.RG12 = 1;
#define U3_LED_RX_OFF       PORTGbits.RG12 = 0;

//uart2
#define U2_LED_TX_TOGGLE    PORTGbits.RG13 = LATGbits.LATG13 ^ 1;   //pin 97/RG13
#define U2_LED_RX_TOGGLE    PORTEbits.RE2 = LATEbits.LATE2 ^ 1;     //pin 98/RE2
#define U2_LED_TX_ON        PORTGbits.RG13 = 1;
#define U2_LED_TX_OFF       PORTGbits.RG13 = 0;
#define U2_LED_RX_ON        PORTEbits.RE2 = 1;
#define U2_LED_RX_OFF       PORTEbits.RE2 = 0;

//uart1
#define U1_LED_TX_TOGGLE    PORTEbits.RE3 = LATEbits.LATE3 ^ 1;     //pin 99/RE3
#define U1_LED_RX_TOGGLE    PORTEbits.RE4 = LATEbits.LATE4 ^ 1;     //pin 100/RE4
#define U1_LED_TX_ON        PORTEbits.RE3 = 1;
#define U1_LED_TX_OFF       PORTEbits.RE3 = 0;
#define U1_LED_RX_ON        PORTEbits.RE4 = 1;
#define U1_LED_RX_OFF       PORTEbits.RE4 = 0;


// healp led toggle
#define LED_TOGGLE          PORTEbits.RE1 = LATEbits.LATE1 ^ 1;

/////////////////		const for 530 board MOPS		//////////////////////////

// attantion
#define ATTANTION_530_1             0x9249
#define ATTANTION_530_2             0x0024
// swapped attantion
#define SW_ATTANTION_530_1          0x4992
#define SW_ATTANTION_530_2          0x2400

// fire
#define FIRE_530_1                  0x2492
#define FIRE_530_2                  0x0049
// swapped fire
#define SW_FIRE_530_1               0x9224
#define SW_FIRE_530_2               0x4900

// short current
#define SHORT_CURRENT_530_1         0x4924
#define SHORT_CURRENT_530_2         0x0092
// swapped short current
#define SW_SHORT_CURRENT_530_1      0x2449
#define SW_SHORT_CURRENT_530_2      0x9200

// normal
#define NORMAL_530_1                0x0000
#define NORMAL_530_2                0x0000

// relay on start 4 reley
#define RELEY_ON_START_4_530_1      0xfff8
#define RELEY_ON_START_4_530_2      0x00ff
//swapped relay on start 4 reley
#define SW_RELEY_ON_START_4_530_1   0xf8ff
#define SW_RELEY_ON_START_4_530_2   0xff00

// reley on start 4 reley 001 18v
#define RELEY_ON_START_4_001_1      0xfff9
#define RELEY_ON_START_4_001_2      0x00ff
// swapped reley on start 4 reley 18v
#define SW_RELEY_ON_START_4_001_1   0xf9ff
#define SW_RELEY_ON_START_4_001_2   0xff00

// just turne on 18v
#define JUST_TURNE_ON_18V_1         0x0001
#define JUST_TURNE_ON_18V_2         0x0000

// swapped just turne on 18v
#define SW_JUST_TURNE_ON_18V_1      0x0100
#define SW_JUST_TURNE_ON_18V_2      0x0000

// just turne on 24v
#define JUST_TURNE_ON_24V_1         0x0003
#define JUST_TURNE_ON_24V_2         0x0000

// swapped just turne on 24v
#define SW_JUST_TURNE_ON_24V_1      0x0300
#define SW_JUST_TURNE_ON_24V_2      0x0000

// just turne on 28v
#define JUST_TURNE_ON_28V_1         0x0007
#define JUST_TURNE_ON_28V_2         0x0000

// swapped just turne on 28v
#define SW_JUST_TURNE_ON_28V_1      0x0700
#define SW_JUST_TURNE_ON_28V_2      0x0000

// reley on start 4 reley 011 24v
#define RELEY_ON_START_4_011_1      0xfffb
#define RELEY_ON_START_4_011_2      0x00ff
// swapped reley on start 4 reley 24v
#define SW_RELEY_ON_START_4_011_1   0xfbff
#define SW_RELEY_ON_START_4_011_2   0xff00

//reley on start 4 reley 111 28v
#define RELEY_ON_START_4_111_1      0xffff
#define RELEY_ON_START_4_111_2      0x00ff
// swapped reley on start 4 reley 28v
#define SW_RELEY_ON_START_4_111_1   0xffff
#define SW_RELEY_ON_START_4_111_2   0xff00

// relay on end 83 reley
#define RELEY_ON_END_84_530_1       0x07ff
#define RELEY_ON_END_84_530_2       0x0000
// swapped reley oh end 83 reley
#define SW_RELEY_ON_END_84_530_1    0xff07
#define SW_RELEY_ON_END_84_530_2    0x0000

//reley on
#define RELEY_ON_530_1              0xffff
#define RELEY_ON_530_2              0x00ff
//swapped reley on 
#define SW_RELEY_ON_530_1           0xffff
#define SW_RELEY_ON_530_2           0xff00

// reley off
#define RELEY_OFF_530_1             0x0000
#define RELEY_OFF_530_2             0x0000

// mups 88-91-94... reley on norm
#define MUPS_88_91_94_RELEY_ON_1        0x9249
#define MUPS_88_91_94_RELEY_ON_2        0x0024

// swapped mups 88_91_94... reley on norm
#define SW_MUPS_88_91_94_RELEY_ON_1     0x4992
#define SW_MUPS_88_91_94_RELEY_ON_2     0x2400

// mups 89-92-95... reley on 
#define MUPS_89_92_95_RELEY_ON_1        0x2492    
#define MUPS_89_92_95_RELEY_ON_2        0x0049 

// swapped mups 89-92-95... reley on 
#define SW_MUPS_89_92_95_RELEY_ON_1     0x9224    
#define SW_MUPS_89_92_95_RELEY_ON_2     0x4900 

// mups 88 89 - 91 92 - 94 95 - 97 98...
#define MUPS_88_89_SC_RELEY_ON_1        0xb6db
#define MUPS_88_89_SC_RELEY_ON_2        0x006d

// swapped mups 88 89 - 91 92 - 94 95 - 97 98...
#define SW_MUPS_88_89_SC_RELEY_ON_1     0xdbb6
#define SW_MUPS_88_89_SC_RELEY_ON_2     0x6d00

// high current
#define HIGH_CURRENT                    0x7800
#define SW_HIGH_CURRENT                 0x0078

// mups1 norm load
#define MUPS_1_NORM_LOAD                0x0b6d      // 0000 1011 0110 1101
// swapped mups1 norm load
#define SW_MUPS_1_NORM_LOAD             0x6d0b

// mups2 norm load
#define MUPS_2_NORM_LOAD_1              0xd000      // 1101 0000 0000 0000 
#define MUPS_2_NORM_LOAD_2              0x00b6      // 0000 0000 1011 0110       
// swapped mups2 norm load
#define SW_MUPS_2_NORM_LOAD_1           0x00d0      // 1101 0000 0000 0000 
#define SW_MUPS_2_NORM_LOAD_2           0xb600      // 0000 0000 1011 0110 

// none
#define NONE_530                    0x0000

/////////////////		Modbus alowed areas 		//////////////////////////
/*stand configuration area*/
#define START_READ_STAND_CONF_AREA     9000
#define END_READ_STAND_CONF_AREA       9900
#define START_WRITE_STAND_CONF_AREA    9000
#define END_WRITE_STAND_CONF_AREA      9900
#define READ_STAND_CONF_AREA           ((start_reg>=START_READ_STAND_CONF_AREA)&&(last_reg<=END_READ_STAND_CONF_AREA))
#define WRITE_STAND_CONF_AREA          ((start_reg>=START_WRITE_STAND_CONF_AREA)&&(last_reg<=END_WRITE_STAND_CONF_AREA))

/*stand read mops area 18v*/
#define START_READ_STAND_MOPS_AREA_18V  10000
#define END_READ_STAND_MOPS_AREA_18V    10900
#define READ_STAND_MOPS_AREA_18V        ((start_reg>=START_READ_STAND_MOPS_AREA_18V)&&(last_reg<=END_READ_STAND_MOPS_AREA_18V))

/*stand read mups area 18v*/
#define START_READ_STAND_MUPS_AREA_18V  11000
#define END_READ_STAND_MUPS_AREA_18V    11900
#define READ_STAND_MUPS_AREA_18V        ((start_reg>=START_READ_STAND_MUPS_AREA_18V)&&(last_reg<=END_READ_STAND_MUPS_AREA_18V)) 
    
/*stand read mops area 24v*/
#define START_READ_STAND_MOPS_AREA_24V  12000
#define END_READ_STAND_MOPS_AREA_24V    12900
#define READ_STAND_MOPS_AREA_24V        ((start_reg>=START_READ_STAND_MOPS_AREA_24V)&&(last_reg<=END_READ_STAND_MOPS_AREA_24V))

/*stand read mups area 24v*/
#define START_READ_STAND_MUPS_AREA_24V  13000
#define END_READ_STAND_MUPS_AREA_24V    13900
#define READ_STAND_MUPS_AREA_24V        ((start_reg>=START_READ_STAND_MUPS_AREA_24V)&&(last_reg<=END_READ_STAND_MUPS_AREA_24V)) 
    
/*stand read mops area 28v*/
#define START_READ_STAND_MOPS_AREA_28V  14000
#define END_READ_STAND_MOPS_AREA_28V    14900
#define READ_STAND_MOPS_AREA_28V        ((start_reg>=START_READ_STAND_MOPS_AREA_28V)&&(last_reg<=END_READ_STAND_MOPS_AREA_28V))

/*stand read mups area 28v*/
#define START_READ_STAND_MUPS_AREA_28V  15000
#define END_READ_STAND_MUPS_AREA_28V    15900
#define READ_STAND_MUPS_AREA_28V        ((start_reg>=START_READ_STAND_MUPS_AREA_28V)&&(last_reg<=END_READ_STAND_MUPS_AREA_28V)) 
    
/*read MOPS*/
#define START_READ_MUPS     5000
#define END_READ_MUPS       6200
#define START_WRITE_MUPS    5000
#define END_WRITE_MUPS      6200
#define  READ_MUPS			((start_reg>=START_READ_MUPS)&&(last_reg<=END_READ_MUPS))			
#define  WRITE_MUPS		    ((start_reg>=START_WRITE_MUPS)&&(last_reg<=END_WRITE_MUPS))		

/*read MUPS_short*/
#define START_READ_MUPS_SHORT   7000
#define END_READ_MUPS_SHORT     7900
#define START_WRITE_MUPS_SHORT  7000
#define END_WRITE_MUPS_SHORT    7900
#define READ_MUPS_SHORT			((start_reg>=START_READ_MUPS_SHORT)&&(last_reg<=END_READ_MUPS_SHORT))			
#define WRITE_MUPS_SHORT		((start_reg>=START_WRITE_MUPS_SHORT)&&(last_reg<=END_WRITE_MUPS_SHORT))

/*read MOPS short*/
#define START_READ_MOPS_SHORT   8000    
#define END_READ_MOPS_SHORT     8900
//#define START_WRITE_MOPS_SHORT  8000
//#define END_WRITE_MOPS_SHORT    8900
#define READ_MOPS_SHORT			((start_reg>=START_READ_MOPS_SHORT)&&(last_reg<=END_READ_MOPS_SHORT))			
//#define WRITE_MOPS_SHORT		((start_reg>=START_WRITE_MOPS_SHORT)&&(last_reg<=END_WRITE_MOPS_SHORT))

/*read*/
#define  START_READ					2000			// 
#define  END_READ					2078			// 
#define  START_WRITE				2054			// 
#define  END_WRITE					2078			// 
#define  READ_			((start_reg>=START_READ)&&(last_reg<=END_READ))			// 
#define  WRITE_			((start_reg>=START_WRITE)&&(last_reg<=END_WRITE))		// 


#define  START_WORK_READ				800			// 
#define  END_WORK_READ					812			// 
#define  START_WORK_WRITE				806			// 
#define  END_WORK_WRITE					812			// 
#define  WORK_READ_         ((start_reg >= START_WORK_READ) && (last_reg <= END_WORK_READ))	
#define  WORK_WRITE_		((start_reg >= START_WORK_WRITE) && (last_reg <= END_WORK_WRITE))


#define  START_CALIBR_READ				1000			// 
#define  END_CALIBR_READ				1034			// 
#define  START_CALIBR_WRITE				1000			// 
#define  END_CALIBR_WRITE				1034			// 
#define  CALIBR_READ_		((start_reg >= START_CALIBR_READ) && (last_reg <= END_CALIBR_READ))	
#define  CALIBR_WRITE_		((start_reg >= START_CALIBR_WRITE) && (last_reg <= END_CALIBR_WRITE))

/*read&write conf*/
#define  START_CONF_READ				500			// config area - setting of engine parameters
#define  END_CONF_READ  				696			// 
#define  START_CONF_WRITE				500			//
#define  END_CONF_WRITE					540			// 
#define  CONF_READ_             ((start_reg >= START_CONF_READ) && (last_reg <= END_CONF_READ))	
#define  CONF_WRITE_            ((start_reg >= START_CONF_WRITE) && (last_reg <= END_CONF_WRITE))

/*read&write modbus*/
#define  START_MODBUS_READ				0			// working area of engine control and statuses
#define  END_MODBUS_READ  				82			// 
#define  START_MODBUS_WRITE				20			//
#define  END_MODBUS_WRITE				82			// 
#define  MODBUS_READ_           ((start_reg >= START_MODBUS_READ) && (last_reg <= END_MODBUS_READ))	
#define  MODBUS_WRITE_          ((start_reg >= START_MODBUS_WRITE) && (last_reg <= END_MODBUS_WRITE))


#define  START_MB_DIAGN_READ				3000			// config area - setting of engine parameters
#define  END_MB_DIAGN_READ  				4200			// 
#define  START_MB_DIAGN_WRITE				3000			//
#define  END_MB_DIAGN_WRITE                 4200			// 
#define  MB_DIAGN_READ_           ((start_reg >= START_MB_DIAGN_READ) && (last_reg <= END_MB_DIAGN_READ))	
#define  MB_DIAGN_WRITE_          ((start_reg >= START_MB_DIAGN_WRITE) && (last_reg <= END_MB_DIAGN_WRITE))    
    
#define  RAMTRON_START              64
#define  RAMTRON_START_CONFIG		1024    // for Stand_sw
#define  RAMTRON_STEND_CONFIG_AREA  2000    //for conf_stand_sw

//////////////////////////////////////////////////////////////////////////////////////////////////////////
    
#define  COORD_MAX			MB_conf.CV_pos_max
#define  COORD_MIN			MB_conf.CV_pos_min
#define  CUR_MAX			MB_conf.CV_curr_max
#define  CUR_MIN			MB_conf.CV_curr_min
#define  CUR_SCALE			MB_conf.CV_curr_scale

#define  CUR_CTRL_VAL		10
//#define  CUR_CTRL_VAL			MB_conf.CV_check_level  

#define  INT_CLR			0.0  
#define  INT_MCLR			1.0  
#define  MREG_FREQ			100    
    
#define  TMR4CLK            49776400
//#define  TMR4CLK	    24883200
#define  OC_FREQ            3000    
#define  OC_MAX             TMR4CLK / OC_FREQ -1
#define  OC_MIN             1500
#define  FILTER             20    
#define	 d_count_size	    4
#define  FILT_CRPM          4
#define  FILT_C             10
#define  FILT_I             10
#define  FILT_DISCRET       500
#define  CYCLE              10
#define  TMAXUOZ            58320                  
    
    ////////////////	End Modbus alowed area 	/////////////////////

#define  STROBE		PORTGbits.RG7			
    
#define  LED_AO		PORTGbits.RG12			
#define  LED_AO_ON	PORTG = LATG | 0x1000		
#define  LED_AO_OFF	PORTG = LATG & 0xEFFF		
    
#define  LED_IGN	PORTGbits.RG13			
#define  LED_IGN_ON	PORTG = LATG | 0x2000		
#define  LED_IGN_OFF	PORTG = LATG & 0xDFFF		
     
#define  LED_STOP	PORTEbits.RE4			
#define  LED_STOP_ON	PORTE = LATE | 0x0010		
#define  LED_STOP_OFF	PORTE = LATE & 0xFFEF		

#define  LED_SYNC	PORTEbits.RE3			
#define  LED_SYNC_ON	PORTE = LATE | 0x0008		
#define  LED_SYNC_OFF	PORTE = LATE & 0xFFF7		

#define  LED_WIGN	PORTEbits.RE2			
#define  LED_WIGN_ON	PORTG = LATG | 0x0004		
#define  LED_WIGN_OFF	PORTG = LATG & 0xFFFB		

#define  LED_8		PORTEbits.RE0			
#define  LED_8_ON	PORTE = LATE | 0x0001		
#define  LED_8_OFF	PORTE = LATE & 0xFFFE		
 
#define  LED_7		PORTEbits.RE1			
#define  LED_7_ON	PORTE = LATE | 0x0002		
#define  LED_7_OFF	PORTE = LATE & 0xFFFD		
    
    
#define  LED9		PORTDbits.RD15			
#define  LED9_ON	PORTD = LATD | 0x8000		
#define  LED9_OFF	PORTD = LATD & 0x7FFF		
    
#define  LED10		PORTAbits.RA2			
#define  LED10_ON	PORTA = LATA | 0x0004		
#define  LED10_OFF	PORTA = LATA & 0xFFFB		

#define  DO_2		PORTAbits.RA3			
#define  DO_2_ON	PORTA = LATA | 0x0008		
#define  DO_2_OFF	PORTA = LATA & 0xFFF7		       

#define  DO_1		PORTAbits.RA4			//  pin 61
#define  DO_1_ON	PORTA = LATA | 0x0010		//    
#define  DO_1_OFF	PORTA = LATA & 0xFFEF		

#define  IGN_ON		PORTDbits.RD5			//  pin 82

#define  TAP_ON		PORTC = LATC | 0x2000		//  pin 72
#define  TAP_OFF	PORTC = LATC & 0xDFFF		//  pin 72

#define  IGN_1		PORTDbits.RD9			//  pin 68
#define  IGN_2		PORTDbits.RD2			//  pin 77
#define  IGN_3		PORTDbits.RD10			//  pin 69
#define  IGN_4		PORTDbits.RD3			//  pin 78
#define  IGN_5		PORTDbits.RD11			//  pin 70
#define  IGN_6		PORTDbits.RD12			//  pin 79
#define  IGN_7		PORTDbits.RD0			//  pin 71
#define  IGN_8		PORTDbits.RD13			//  pin 80
#define  IGN_9		PORTDbits.RD1			//  pin 76
#define  IGN_10		PORTDbits.RD4			//  pin 81

#define  ON_IGN_1       PORTD = LATD | 0x0200		//  pin 68
#define  ON_IGN_2       PORTD = LATD | 0x0004		//  pin 77
#define  ON_IGN_3       PORTD = LATD | 0x0400		//  pin 69
#define  ON_IGN_4       PORTD = LATD | 0x0008		//  pin 78
#define  ON_IGN_5       PORTD = LATD | 0x0800		//  pin 70
#define  ON_IGN_6       PORTD = LATD | 0x1000		//  pin 79
#define  ON_IGN_7       PORTD = LATD | 0x0001		//  pin 71
#define  ON_IGN_8       PORTD = LATD | 0x2000		//  pin 80
#define  ON_IGN_9       PORTD = LATD | 0x0002		//  pin 76
#define  ON_IGN_10      PORTD = LATD | 0x0010		//  pin 81
    
#define  IGN_RESET      PORTD = LATD & 0xC1E0		
#define  MAX_CYL_NUM    10				

#define  CTRL1      PORTGbits.RG0			//  pin 88
#define  CTRL2      PORTGbits.RG1			//  pin 87

#define  CONF1		PORTCbits.RC2			//  pin 7 
#define  CONF2		PORTCbits.RC3			//  pin 8
#define  CONF3		PORTCbits.RC4			//  pin 9
#define  CONF4		PORTGbits.RG6			//  pin 10 
#define  CONF5		PORTEbits.RE5			//  pin 3
#define  CONF6		PORTEbits.RE6			//  pin 4 
#define  CONF7		PORTEbits.RE7			//  pin 5
#define  CONF8		PORTCbits.RC1			//  pin 6

#define  DI_1		PORTAbits.RA5 			//  pin 2
#define  DI_2		PORTGbits.RG15			//  pin 1
    
#define  FLAP_SET	Modbus.CV_set
#define  FLAP_POS	Modbus.CV_pos
#define  FLAP_CURR	Modbus.CV_current    

#define  RPM_UOZ_MAX    MB_conf.UOZ_RPM_max
#define  RPM_UOZ_MIN	MB_conf.UOZ_RPM_min

#define  NOM_UOZ        MB_conf.UOZ_high
#define  LOW_UOZ        MB_conf.UOZ_low
#define  CONST_UOZ      MB_conf.constructive_UOZ
    
#define CYLINDERS_NUM	        10
#define CANDLES_NUM             1

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
#define AO_5CYL_ERROR_EVEN      14
#define AO_5CYL_ERROR_ODD       15

    

// MACROS MOPS

/**
 * @brief macros to set mops statment
 */
#define MACRO_SET_MOPS_STATMENT(mops, online, online_err, offline, not_operable, operable) \
    do { \
        (mops).mops_online = (online); \
        (mops).mops_online_err = (online_err); \
        (mops).mops_offline = (offline); \
        (mops).mops_not_operable = (not_operable); \
        (mops).mops_operable = (operable); \
    } while(0)


/**
 * @brief macros to set mops arr
 */
#define MACRO_SELECT_MOPS_STATMENT(power_cycle_mops) \
    ((power_cycle_mops) == 0 ? MOPS_statment_18v :   \
     (power_cycle_mops) == 1 ? MOPS_statment_24v :   \
                               MOPS_statment_28v)


/**
 * @brief macros to set mops arr swapped
 */
#define MACRO_SELECT_MOPS_STATMENT_SW(power_cycle_mops) \
    ((power_cycle_mops) == 0 ? MOPS_statment_sw_18v :   \
     (power_cycle_mops) == 1 ? MOPS_statment_sw_24v :   \
                               MOPS_statment_sw_28v)


/**
 * @brief macros to select powersupply
 */
#define MACRO_SELECT_SW_RELEY_ON_START_4(power_cycle) \
    ((power_cycle) == 0 ? SW_RELEY_ON_START_4_001_1 : \
     (power_cycle) == 1 ? SW_RELEY_ON_START_4_011_1 : \
                          SW_RELEY_ON_START_4_111_1)  \
                          

/**
 * @brief macros to select vars 3id 530 board
 */
#define MACRO_SELECT_VAR_3ID_530(power_cycle) \
    ((power_cycle) == 0 ? 0x0100 : \
     (power_cycle) == 1 ? 0x0300 : \
                          0x0700)  \
    

/**
 * @brief macros if mbm send
 */
#define MACRO_MBM_END_SEND(a, b, c, d) ((a) > 0 && (b) > 0 && (c) > 0 && (d) > 0)


/**
 * @brief macros reset flags
 */
#define MACRO_MBM_RESET_FLAGS(a, b, c, d) \
    do {                                  \
        (a) = 0;                          \
        (b) = 0;                          \
        (c) = 0;                          \
        (d) = 0;                          \
    } while(0)


/**
 * @brief Select 18v, 24v, or 28v error field
 * @param power_cycle - Select between 18v, 24v, 28v error fields
 * @param statment - the mops_statment structure to access the error field
 */
#define MACRO_SELECT_SUPPLY(statment, power_cycle)    \
    (((power_cycle) == 0) ? (statment).mops_power_supply_error.mops_18v_error :    \
     ((power_cycle) == 1) ? (statment).mops_power_supply_error.mops_24v_error :    \
                            (statment).mops_power_supply_error.mops_28v_error)



 

/**
 * @brief Set mops supply error flag up or down
 * @param statment - mops buffer structure (union tag_mops_stand_statment)
 * @param power_cycle - Select between 18v, 24v, or 28v error field
 * @param value - Set error flag up (1) or down (0)
 */
#define MACRO_SET_SUPPLY_FLAG(statment, power_cycle, value)  \
     do {                                                       \
        if ((power_cycle) == 0)                                \
            (statment).mops_power_supply_error.mops_18v_error = (value); \
        else if ((power_cycle) == 1)                           \
            (statment).mops_power_supply_error.mops_24v_error = (value); \
        else                                                   \
            (statment).mops_power_supply_error.mops_28v_error = (value); \
    } while (0)



// MACROS MUPS

/**
 * @brief macros to set mops statment
 */
#define MACRO_SET_MUPS_STATMENT(mups, online, online_err, offline, not_operable, operable) \
    do { \
        (mups).mups_statment.mups_online = (online); \
        (mups).mups_statment.mups_online_err = (online_err); \
        (mups).mups_statment.mups_offline = (offline); \
        (mups).mups_statment.mups_not_operable = (not_operable); \
        (mups).mups_statment.mups_operable = (operable); \
    } while(0)



/**
 * @brief macros to set mups arr
 */
#define MACRO_SELECT_MUPS_STATMENT(power_cycle_mups) \
    ((power_cycle_mups) == 0 ? MUPS_statment_18v :   \
     (power_cycle_mups) == 1 ? MUPS_statment_24v :   \
                               MUPS_statment_28v)

/**
 * @brief macros to set mups arr swapped
 */
#define MACRO_SELECT_MUPS_STATMENT_SW(power_cycle_mups) \
    ((power_cycle_mups) == 0 ? MUPS_statment_sw_18v :   \
     (power_cycle_mups) == 1 ? MUPS_statment_sw_24v :   \
                               MUPS_statment_sw_28v)


/**
 * @brief macros return 530 board mups supply
 */
#define MACRO_530_SUPPLY(power_cycle_mups) \
    ((power_cycle_mups) == 0 ? _530_board_just_18v :   \
     (power_cycle_mups) == 1 ? _530_board_just_24v :   \
                               _530_board_just_28v)


/**
 * @brief macros to set error flag in channel
 * @param mups MACRO_SELECT_MUPS_STATMENT
 * @param ch_statment current ch statment 
 * @param id_mups current mups address
 * @param ch_num current ch num
 */
#define MACRO_SET_ERR_CH_FLAG(mups, ch_statment, id_mups, ch_num_)                              \
do                                                                                              \
{                                                                                               \
    switch((ch_statment))                                                                       \
    {                                                                                           \
        case 1:                                                                                 \
            (mups)[(id_mups)].mups_ch_statement.mups_ch_err_break_ch_off[(ch_num_)] = 1;        \
            break;                                                                              \
        case 2:                                                                                 \
            (mups)[(id_mups)].mups_ch_statement.mups_ch_err_norm_ch_off[(ch_num_)] = 1;         \
            break;                                                                              \
        case 3:                                                                                 \
            (mups)[(id_mups)].mups_ch_statement.mups_ch_err_sc_ch_off[(ch_num_)] = 1;           \
            break;                                                                              \
        case 4:                                                                                 \
            (mups)[(id_mups)].mups_ch_statement.mups_ch_err_norm_ch_on[(ch_num_)] = 1;          \
            break;                                                                              \
        case 5:                                                                                 \
            (mups)[(id_mups)].mups_ch_statement.mups_ch_err_cur_up_ch_off_force[(ch_num_)] = 1; \
            break;                                                                              \
        case 6:                                                                                 \
            (mups)[(id_mups)].mups_ch_statement.mups_ch_err_break_ch_on[(ch_num_)] = 1;         \
            break;                                                                              \
    }                                                                                           \
    (mups)[(id_mups)].mups_statment.mups_not_operable = 1;                                      \
}                                                                                               \
while(0)                                                                                        



/**
 * @param macros return _*_mups_on_cab_load_norm_xp_*
 */

#endif //DEFINE_H
