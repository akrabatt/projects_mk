#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../include/string.h"
#include "define.h"
#include "extern.h"


unsigned long median_fiter (unsigned int* DataBuffer, unsigned char cntDat, unsigned char Wcount);
extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void* p) 
{ 
 return (int)p<0?((int)p&0x1fffffffL):(unsigned int)((unsigned char*)p+0x40000000L); 
}

#define ADCF_vol 256
unsigned int __attribute__((coherent)) adc1f [ADCF_vol /4], adc2f [ADCF_vol/4], adc3f [ADCF_vol/4], adc4f [ADCF_vol/4];

unsigned short OC_val ;
unsigned short filt_c [FILT_C] ;
unsigned short filt_i [FILT_I] ;
unsigned short count_c ;
unsigned short count_i ;


void middle_adc (void)
{

}


void pid_control(float Kp, float Kd, float Ki)
{
static float last_error;
static float DB[4];
static int d_count, ii;
static float d_buf [d_count_size];
static float d_middle;
float P;
float Prop;
float D;
static float I;
float PID;
float setpoint;
float currentpoint;
float MD;
unsigned short OC3_reg;

if (CV_regul_on == 0) { I = 0; return;}

setpoint = Modbus.CV_set;
currentpoint = Modbus.CV_pos;

P = setpoint - currentpoint;
if (((currentpoint - setpoint) >  INT_CLR) || ((setpoint - currentpoint) > INT_CLR)) { I = I + Ki * (setpoint - currentpoint) / OC_FREQ  ; }
if(I > 60.0) {I = 60.0;}
 if(I < 0.0) {I = 0.0;}

D = ((setpoint - currentpoint) - last_error) * (OC_FREQ);

d_buf [d_count++] = D;
if (d_count >= d_count_size) {d_count = 0;} 
d_middle = 0;
for (ii=0; ii<d_count_size; ii++) {d_middle += d_buf [ii];}
d_middle /= d_count_size;

last_error = setpoint - currentpoint;
//PID = (Kp * P) + I + (Kd * D);

Prop = Kp * P;
//if (Prop > 10) (Prop = 10);

PID = Prop + I + (Kd * d_middle); 

    MB.angle_5 = Kp * P;
//    MB.angle_6 = Kd * D;    
    MB.angle_6 = Kd * d_middle;        
    MB.angle_7 = I;    
    MB_swap.angle_5 = swapfloat (MB.angle_5);  
    MB_swap.angle_6 = swapfloat (MB.angle_6);     
    MB_swap.angle_7 = swapfloat (MB.angle_7);  
    
 if(PID > 99.9)  {PID = 99.9;}
 if(PID <= 0.001)  {PID = 0.001;}
 
    MB.angle_11 = PID;    
    MB_swap.angle_11 = swapfloat (MB.angle_11);     
    
 OC3_reg = PID / 100.0 * OC_MAX; 
 if (OC3_reg < 15) OC3_reg = 15;

 OC3RS = OC3_reg;
}

void DRV_ADC_Initialize_F(void)
{
  /* initialize ADC calibration setting */
    ADC0CFG = DEVADC0;
    ADC1CFG = DEVADC1;
    ADC2CFG = DEVADC2;
    ADC3CFG = DEVADC3;
    ADC4CFG = DEVADC4;
    ADC7CFG = DEVADC7;    
    
/* Configure ADCCON1 */
ADCCON1 = 0; // No ADCCON1 features are enabled including: Stop-in-Idle, turbo,

/* Configure ADCCON2 */
ADCCON2 = 0; // Since, we are using only the Class 1 inputs, no setting is

/* Initialize warm up time register */
ADCANCON = 0;
ADCANCONbits.WKUPCLKCNT = 5; // Wake-up exponent = 32 * TADx
/* Clock setting */
ADCCON3 = 0;
ADCCON3bits.ADCSEL = 3;         // Select input clock source
ADCCON3bits.CONCLKDIV = 1;      // Control clock frequency is half of input clock
ADCCON3bits.VREFSEL = 0;        // Select (EXTVREF ==0) (VDD == 1) and AVSS as reference source
//ADC0TIMEbits.ADCDIV = 1;      // ADC0 clock frequency is half of control clock = TAD0
//ADC0TIMEbits.SAMC = 5;        // ADC0 sampling time = 5 * TAD0
//ADC0TIMEbits.SELRES = 3;      // ADC0 resolution is 12 bits

ADC1TIMEbits.ADCDIV = 1;        // ADC0 clock frequency is half of control clock = TAD0
ADC1TIMEbits.SAMC = 4;          // ADC0 sampling time = 5 * TAD0
ADC1TIMEbits.SELRES = 3;        // ADC0 resolution is 12 bits

ADC2TIMEbits.ADCDIV = 1;        // ADC0 clock frequency is half of control clock = TAD0
ADC2TIMEbits.SAMC = 4;          // ADC0 sampling time = 5 * TAD0
ADC2TIMEbits.SELRES = 3;        // ADC0 resolution is 12 bits

ADC3TIMEbits.ADCDIV = 1;        // ADC0 clock frequency is half of control clock = TAD0
ADC3TIMEbits.SAMC = 4;          // ADC0 sampling time = 5 * TAD0
ADC3TIMEbits.SELRES = 3;        // ADC0 resolution is 12 bits

ADC4TIMEbits.ADCDIV = 1;        // ADC0 clock frequency is half of control clock = TAD0
ADC4TIMEbits.SAMC = 4;          // ADC0 sampling time = 5 * TAD0
ADC4TIMEbits.SELRES = 3;        // ADC0 resolution is 12 bits

/* Select analog input for ADC modules, no presync trigger, not sync sampling */
ADCTRGMODEbits.SH0ALT = 0;      // ADC0 = AN0
/* Select ADC input mode */
ADCIMCON1bits.SIGN0 = 0;        // unsigned data format
ADCIMCON1bits.DIFF0 = 0;        // Single ended mode
/* Configure ADCGIRQENx */
ADCGIRQEN1 = 0;
ADCGIRQEN2 = 0;
ADCGIRQEN1bits.AGIEN10 = 1;     // No interrupts are used            добавлен 1 канал
ADCGIRQEN2bits.AGIEN32 = 1;     // No interrupts are used

/* Configure ADCCSSx */
ADCCSS1 = 0; // No scanning is used
ADCCSS2 = 0;

ADCCSS1bits.CSS10 = 1;
ADCCSS2bits.CSS32 = 1;
/* Configure ADCCMPCONx */

ADCCMPCON1 = 0; // No digital comparators are used. Setting the ADCCMPCONx
ADCCMPCON2 = 0; // register to '0' ensures that the comparator is disabled.
ADCCMPCON3 = 0; // Other registers are Сdon't careТ.
ADCCMPCON4 = 0;
ADCCMPCON5 = 0;
ADCCMPCON6 = 0;
/* Configure ADCFLTRx */
ADCFLTR1 = 0; // Clear all bits
ADCFLTR2 = 0; // Clear all bits
ADCFLTR3 = 0;
ADCFLTR4 = 0;
ADCFLTR5 = 0;
ADCFLTR6 = 0;
/* Set up the trigger sources */
ADCTRGSNSbits.LVL3 = 0; // Edge trigger
ADCTRG1bits.TRGSRC1 = 1; // Set AN1 to trigger from OC3. канал паразитный
ADCTRG1bits.TRGSRC2 = 1; // Set AN2 to trigger from OC3.
ADCTRG1bits.TRGSRC3 = 1; // Set AN3 to trigger from OC3.
ADCTRG2bits.TRGSRC4 = 1; // Set AN4 to trigger from OC3.

/* Turn the ADC on */
ADCCON1bits.ON = 1;
/* Wait for voltage reference to be stable */
while(!ADCCON2bits.BGVRRDY); // Wait until the reference voltage is ready
while(ADCCON2bits.REFFLT); // Wait if there is a fault with the reference voltage

ADCANCONbits.ANEN1 = 1; // Enable the clock to analog bias and digital control
/* Wait for ADC to be ready */
while(!ADCANCONbits.WKRDY1); // Wait until ADC1 is ready
ADCCON3bits.DIGEN1 = 1; // Enable ADC1

ADCANCONbits.ANEN2 = 1; // Enable the clock to analog bias and digital control
/* Wait for ADC to be ready */
while(!ADCANCONbits.WKRDY2); // Wait until ADC2 is ready
ADCCON3bits.DIGEN2 = 1; // Enable ADC2

/* Enable clock to analog circuit */
ADCANCONbits.ANEN3 = 1; // Enable the clock to analog bias and digital control
/* Wait for ADC to be ready */
while(!ADCANCONbits.WKRDY3); // Wait until ADC0 is ready
/* Enable the ADC module */
ADCCON3bits.DIGEN3 = 1; // Enable ADC3

ADCANCONbits.ANEN4 = 1; // Enable the clock to analog bias and digital control
/* Wait for ADC to be ready */
while(!ADCANCONbits.WKRDY4); // Wait until ADC0 is ready
ADCCON3bits.DIGEN4 = 1; // Enable ADC4

/* режим работы с прерывани€ми   
    IFS1bits.ADCIF = 0;
    IEC1bits.ADCIE = 1;
    IPC11bits.ADCIP = 3;
    IPC11bits.ADCIS = 0;    //прерывание отключить только дл€ DMA
       */
/* режим работы с DMA       */   
    IPC15bits.ADCD1IP = 1; //priority 1
    IPC15bits.ADCD1IS = 0; //sub-priority 0
    IFS1bits.ADCD1IF = 0; //clear flag    
    IPC15bits.ADCD2IP = 1; //priority 1
    IPC15bits.ADCD2IS = 0; //sub-priority 0    
    IFS1bits.ADCD2IF = 0; //clear flag 
    IPC15bits.ADCD3IP = 1; //priority 1
    IPC15bits.ADCD3IS = 0; //sub-priority 0
    IFS1bits.ADCD3IF = 0; //clear flag 
    IPC15bits.ADCD4IP = 1; //priority 1
    IPC15bits.ADCD4IS = 0; //sub-priority 0
    IFS1bits.ADCD4IF = 0; //clear flag 

    IEC1bits.ADCD1IE = 0; //enable interrupt    
    IEC1bits.ADCD2IE = 0; //enable interrupt
    IEC1bits.ADCD3IE = 0; //enable interrupt
    IEC1bits.ADCD4IE = 0; //enable interrupt 
/* режим работы с DMA  - конец  */    
}


    unsigned short temp_32, temp_10;
    unsigned short adc_count;
    unsigned short btemp_32 [FILTER], btemp_10 [FILTER];
    float f10, f32;
    
void ADC_interrupt_F (void)
{
    unsigned short i;
    while (ADCDSTAT1bits.ARDY10 == 0);    btemp_10 [adc_count] = ADCDATA10;     // ток
    while (ADCDSTAT2bits.ARDY32 == 0);    btemp_32 [adc_count] = ADCDATA32;     // положение
    adc_count++;
    
    if (adc_count >= FILTER) {

        adc_count = 0;
//        Modbus.ADC_CV_curr = ADCDATA10;
//        Modbus.ADC_CV_pos = ADCDATA32;
        f10 = 0; f32 = 0;
        for (i=0; i<FILTER; i++) {
            f10 += btemp_10 [i]; f32 += btemp_32 [i]; 
            }
        f10 /= FILTER; f32 /= FILTER;        
        Modbus.ADC_CV_pos = f32;
        Modbus.ADC_CV_curr = f10;
        Modbus.CV_pos = (f32 - COORD_MIN) * 100 / (COORD_MAX - COORD_MIN);
        Modbus.CV_current = (f10 - CUR_MIN) * CUR_SCALE / (CUR_MAX - CUR_MIN);

        Modbus_sw.CV_current = swapfloat (Modbus.CV_current);
        Modbus_sw.CV_pos = swapfloat (Modbus.CV_pos);

        Modbus_sw.ADC_CV_curr = swapshort (Modbus.ADC_CV_curr);
        Modbus_sw.ADC_CV_pos = swapshort (Modbus.ADC_CV_pos);   
        }

}


void DMA0_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH0CON=0x2;                        // channel 1 off, priority 2
DCH0CONbits.CHAEN = 1;              //channel automatic enable
DCH0ECONbits.CHSIRQ = _ADC_DATA10_VECTOR;
DCH0ECONbits.SIRQEN = 1;
DCH0SSA = _VirtToPhys(&ADCDATA10);  // transfer source physical address
DCH0DSA = _VirtToPhys(&adc1f);      // transfer destination physical address
DCH0SSIZ=4;                         // source size at most 200 bytes
DCH0DSIZ=ADCF_vol;                  // dst size is 1 byte
DCH0CSIZ=4;                         // one byte per UART transfer request
DCH0DPTR = 0;
DCH0INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts

DCH0CONbits.CHEN = 1;

///////////////////////////////////////////////////////////

IEC4bits.DMA0IE = 0;                // disable DMA channel 0 interrupts
IFS4bits.DMA0IF = 0;                // clear any existing DMA channel 0 interrupt flag
DMACONbits.ON = 1;                  // enable the DMA controller
DCH0CON=0x03;                       // channel off, priority 3, no chaining
DCH0ECON=0;                         // no start or stop irqТs, no pattern match program the transfer

DCH0SSA=_VirtToPhys(&ADCDATA10);    // transfer source physical address
DCH0DSA=_VirtToPhys(&adc1f);        // transfer destination physical address
DCH0SSIZ=4;                         // source size 200 bytes
DCH0DSIZ=ADCF_vol;                  // destination size 200 bytes
DCH0CSIZ=4;                         // 200 bytes transferred per event
DCH0DPTR = 0;                       //
DCH0INTCLR=0x00ff00ff;              // clear existing events, disable all interrupts
DCH0INTSET=0x00090000;              // enable Block Complete and error interrupts

IPC33bits.DMA0IP = 0;               // clear the DMA channel 0 priority and sub-priority
IPC33bits.DMA0IS = 0;

IPC33bits.DMA0IP = 2;                // set IPL 5, sub-priority 2
IPC33bits.DMA0IS = 0;

IEC4bits.DMA0IE = 1;                // enable DMA channel 0 interrupt

DCH0CONbits.CHEN = 1;              // turn channel on
                                                // initiate a transfer
DCH0ECONSET=0x00000080;                         // set CFORCE to 1

}

void DMA2_init (void)
{
DMACONSET=0x00008000;               // enable the DMA controller
DCH2CON=0x2;                       // channel 1 off, priority 2
DCH2CONbits.CHAEN = 1; //channel automatic enable
DCH2ECONbits.CHSIRQ = _ADC_DATA32_VECTOR;
DCH2ECONbits.SIRQEN = 1;
DCH2SSA = _VirtToPhys(&ADCDATA32);      // transfer source physical address
DCH2DSA = _VirtToPhys(&adc2f);   // transfer destination physical address
DCH2SSIZ=4;                       // source size at most 200 bytes
DCH2DSIZ=ADCF_vol;                        // dst size is 1 byte
DCH2CSIZ=4;                       // one byte per UART transfer request
DCH2DPTR = 0;
DCH2INTCLR=0x00ff00ff;              // DMA1: clear events, disable interrupts

//DCH1INTbits.CHSDIF = 0; 
DCH2CONbits.CHEN = 1;
}

void ADC_init_scan (void)
{
/* Configure ADCCON1 */
ADCCON1 = 0; // No ADCCON1 features are enabled including: Stop-in-Idle, turbo,
// CVD mode, Fractional mode and scan trigger source.
ADCCON1bits.SELRES = 3; // ADC7 resolution is 12 bits
ADCCON1bits.STRGSRC = 7; // Select scan trigger.
/* Configure ADCCON2 */
ADCCON2bits.SAMC = 5; // ADC7 sampling time = 5 * TAD7
ADCCON2bits.ADCDIV = 1; // ADC7 clock freq is half of control clock = TAD7
/* Initialize warm up time register */
ADCANCON = 0;
ADCANCONbits.WKUPCLKCNT = 5; // Wakeup exponent = 32 * TADx
/* Clock setting */
ADCCON3bits.ADCSEL = 0; // Select input clock source
ADCCON3bits.CONCLKDIV = 1; // Control clock frequency is half of input clock
ADCCON3bits.VREFSEL = 0; // Select AVDD and AVSS as reference source
ADC0TIMEbits.ADCDIV = 1; // ADC0 clock frequency is half of control clock = TAD0
ADC0TIMEbits.SAMC = 5; // ADC0 sampling time = 5 * TAD0
ADC0TIMEbits.SELRES = 3; // ADC0 resolution is 12 bits
/* Select analog input for ADC modules, no presync trigger, not sync sampling */
ADCTRGMODEbits.SH0ALT = 0; // ADC0 = AN0
/* Select ADC input mode */
ADCIMCON1bits.SIGN10 = 0; // unsigned data format
ADCIMCON1bits.DIFF10 = 0; // Single ended mode
ADCIMCON3bits.SIGN32 = 0; // unsigned data format
ADCIMCON3bits.DIFF32 = 0; // Single ended mode
/* Configure ADCGIRQENx */
ADCGIRQEN1 = 0; // No interrupts are used.
ADCGIRQEN2 = 0;

ADCGIRQEN1bits.AGIEN10 = 1;
ADCGIRQEN2bits.AGIEN32 = 1;

/* Configure ADCCSSx */
ADCCSS1 = 0; // Clear all bits
ADCCSS2 = 0;
ADCCSS1bits.CSS10 = 1; // AN10 (Class 2) set for scan
ADCCSS2bits.CSS32 = 1; // AN32 (Class 3) set for scan
/* Configure ADCCMPCONx */
ADCCMPCON1 = 0; // No digital comparators are used. Setting the ADCCMPCONx
ADCCMPCON2 = 0; // register to '0' ensures that the comparator is disabled.
ADCCMPCON3 = 0; // Other registers are Сdon't careТ.
ADCCMPCON4 = 0;
ADCCMPCON5 = 0;
ADCCMPCON6 = 0;
/* Configure ADCFLTRx */
ADCFLTR1 = 0; // No oversampling filters are used.
ADCFLTR2 = 0;
ADCFLTR3 = 0;
ADCFLTR4 = 0;
ADCFLTR5 = 0;
ADCFLTR6 = 0;    
    
/* Set up the trigger sources */
ADCTRG3bits.TRGSRC10 = 3; // Set AN0 (Class 1) to trigger from scan source
//ADCTRG2bits.TRGSRC7 = 3; // Set AN8 (Class 2) to trigger from scan source
// AN40 (Class 3) always uses scan trigger source
/* Early interrupt */
ADCEIEN1 = 0; // No early interrupt
ADCEIEN2 = 0;
/* Turn the ADC on */
ADCCON1bits.ON = 1;
/* Wait for voltage reference to be stable */
while(!ADCCON2bits.BGVRRDY); // Wait until the reference voltage is ready
while(ADCCON2bits.REFFLT); // Wait if there is a fault with the reference voltage
/* Enable clock to analog circuit */
ADCANCONbits.ANEN0 = 1; // Enable the clock to analog bias ADC0
ADCANCONbits.ANEN7 = 1; // Enable, ADC7
/* Wait for ADC to be ready */
while(!ADCANCONbits.WKRDY0); // Wait until ADC0 is ready
while(!ADCANCONbits.WKRDY7); // Wait until ADC7 is ready
/* Enable the ADC module */
ADCCON3bits.DIGEN0 = 1; // Enable ADC0
ADCCON3bits.DIGEN7 = 1; // Enable ADC7

    IFS1bits.ADCIF = 0;
    IEC1bits.ADCIE = 1;
    IPC11bits.ADCIP = 3;
    IPC11bits.ADCIS = 0;
}



/* *****************************************************************************
 End of File
 */



