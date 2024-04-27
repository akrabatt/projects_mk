#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "../include/string.h"
#include "define.h"
#include "extern.h"


unsigned long median_fiter(unsigned int* DataBuffer, unsigned char cntDat, unsigned char Wcount);

extern __inline__ unsigned int __attribute__((always_inline)) _VirtToPhys(const void* p) {
    return (int) p < 0 ? ((int) p & 0x1fffffffL) : (unsigned int) ((unsigned char*) p + 0x40000000L);
}

#define ADCF_vol 256
unsigned int __attribute__((coherent)) adc1f [ADCF_vol / 4], adc2f [ADCF_vol / 4], adc3f [ADCF_vol / 4], adc4f [ADCF_vol / 4];

unsigned short OC_val;
unsigned short filt_c [FILT_C];
unsigned short filt_i [FILT_I];
unsigned short count_c;
unsigned short count_i;

void pid_control(float Kp, float Kd, float Ki) {
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

    if (CV_regul_on == 0) {
        I = 0;
        return;
    }

    setpoint = Modbus.CV_set;
    currentpoint = Modbus.CV_pos;

    P = setpoint - currentpoint;
    if (((currentpoint - setpoint) > INT_CLR) || ((setpoint - currentpoint) > INT_CLR)) {
        I = I + Ki * (setpoint - currentpoint) / OC_FREQ;
    }
    if (I > 60.0) {
        I = 60.0;
    }
    if (I < 0.0) {
        I = 0.0;
    }

    D = ((setpoint - currentpoint) - last_error) * (OC_FREQ);

    d_buf [d_count++] = D;
    if (d_count >= d_count_size) {
        d_count = 0;
    }
    d_middle = 0;
    for (ii = 0; ii < d_count_size; ii++) {
        d_middle += d_buf [ii];
    }
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
    MB_swap.angle_5 = swapfloat(MB.angle_5);
    MB_swap.angle_6 = swapfloat(MB.angle_6);
    MB_swap.angle_7 = swapfloat(MB.angle_7);

    if (PID > 99.9) {
        PID = 99.9;
    }
    if (PID <= 0.001) {
        PID = 0.001;
    }

    MB.angle_11 = PID;
    MB_swap.angle_11 = swapfloat(MB.angle_11);

    OC3_reg = PID / 100.0 * OC_MAX;
    if (OC3_reg < 15) OC3_reg = 15;

    OC3RS = OC3_reg;
}

unsigned short temp_32, temp_10;
unsigned short adc_count;
unsigned short btemp_32 [FILTER], btemp_10 [FILTER];
float f10, f32;

void DMA2_init(void) {
    DMACONSET = 0x00008000; // enable the DMA controller
    DCH2CON = 0x2; // channel 1 off, priority 2
    DCH2CONbits.CHAEN = 1; //channel automatic enable
    DCH2ECONbits.CHSIRQ = _ADC_DATA32_VECTOR;
    DCH2ECONbits.SIRQEN = 1;
    DCH2SSA = _VirtToPhys(&ADCDATA32); // transfer source physical address
    DCH2DSA = _VirtToPhys(&adc2f); // transfer destination physical address
    DCH2SSIZ = 4; // source size at most 200 bytes
    DCH2DSIZ = ADCF_vol; // dst size is 1 byte
    DCH2CSIZ = 4; // one byte per UART transfer request
    DCH2DPTR = 0;
    DCH2INTCLR = 0x00ff00ff; // DMA1: clear events, disable interrupts

    //DCH1INTbits.CHSDIF = 0; 
    DCH2CONbits.CHEN = 1;
}




