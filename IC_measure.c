#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "define.h"
#include "extern.h"




extern void ignit_distributor_deep (void);


#define max_inactiv_1		12		// 1.2 sec
#define max_inactiv_2		12		// 1.2 sec



///////////////// InCap	///////////////////////



unsigned long ring_1[INCAP_VOLUME];
unsigned long ring_2[INCAP_VOLUME];

float 	phase_delta;				// 
float 	phase;      				// 
float   koeff;

void measuring ( struct tag_ch * ch, unsigned long * ring, unsigned short ring_count)
{
	unsigned short pseudo_teeth, temp_count;

	if (ch->ready==0) {return;}																// ??? ????? ????????? -  ??? ????????????? ????????
	pseudo_teeth = ch->teeth * ch->filter;
	if (ch->rotary==0) {if (ring_count >= (pseudo_teeth)) { ch->rotary = 1;} }		// ???????? ?????? ?? ???? ?????? ? ??????? ?????? ????????
	if (ch->activ==0)	{if (ring_count >= 4) { ch->activ = 1; } }						// ???????? ??????? 4 ????????? ????? ??????? ?????????

	koeff = ch->reductor * ch->filter;
///////////////////////////////////////////////?????? ?????????? ???????	//////////////////////////////////////////////////////
	if (ch->activ == 0) {	ch->ready = 0; return; }											// ?? ?????? 4 ????????? ????????? ?? ????????????

	if (ring_count != 0)	{ temp_count = ring_count - 1; }							// ???? ??????? ??????? ?? ????? 0 - ?????? ??e??????? ????????
	else 	{ temp_count = INCAP_VOLUME - 1; }										// ?????? ????????? ???????? ????????? ? ??????
	if (temp_count != 0)																// ????????? ??????????? ??????? ?????????
		{
		if (*(ring + temp_count) > *(ring + temp_count - 1))						// ??????????? ???????????? 32 ?????????? ???????? ???????
			{	ch->fast_delta = (float) (*(ring + temp_count) - *(ring + temp_count - 1));	}		// ??? ????????????
		else {	ch->fast_delta = (float) (*(ring + temp_count) - *(ring + temp_count - 1) + 0xFFFFFFFF + 1);	}		// ????????? ????????? ???????????? 32 ?????????? ????????
		}
	else
		{
		if (*(ring + 0) > *(ring + INCAP_VOLUME - 1))                                                   // ??????????? ???????????? 32 ?????????? ???????? ???????
			{	ch->fast_delta = (float)  (*(ring + 0) - *(ring + INCAP_VOLUME - 1));	}               	// ??? ????????????
		else { ch->fast_delta = (float) ((*(ring + 0)) - *(ring + INCAP_VOLUME-1) + 0xFFFFFFFF + 1 ); 	} 	// ????????? ????????? ???????????? 32 ?????????? ????????
		}

	ch->period = ch->fast_delta;


	if ((ch->ready) && (ch->fast_delta != 0))				// ???????? ?????????? ? ?????? ??????? ?? ????
		{
		ch->bbfast = ch->bfast;							// ?????????? ??????? ???????
		ch->bfast = ch->fast;							// ?????????? ??????? ???????
		ch->fast = PBCLK3_/ch->fast_delta / 32;              	// ?????? ?????????? ???????
		}

///////////////////////////////////////////////	?????? ?????????? ? ?????? ?????	//////////////////////////////////////////////////////
	if (ch->rotary==0) {	ch->ready = 0; return; }                                                                    // ?? ?????? ???????????? ? ?????? ???????????? ?????????? - ????????? ?? ????????????
	if (temp_count >= pseudo_teeth)                                                                                     // ?????? ????????? ?????. ????. ?????? ??? ???? * ??????????
		{
		if (*(ring + temp_count) > *(ring + temp_count - pseudo_teeth))                                                             // ???????? ???????????? 32 ?????????? ???????? 
			{ ch->delta = (float) (*(ring + temp_count) - *(ring + temp_count - pseudo_teeth));	}                                       // ???????????? 32 ?????????? ???????? ?? ????
		else { ch->delta = (float) ( *(ring + temp_count) - *(ring + temp_count - pseudo_teeth) + 0xFFFFFFFF + 1);	}                   // ???? ???????????? 32 ?????????? ????????		
		}
	else																			// ?????? ????????? ?????. ????. ?????? ??? ???? * ??????????
		{
		if (*(ring + temp_count) > *(ring + INCAP_VOLUME - pseudo_teeth + temp_count))                                              // ???????? ???????????? 32 ?????????? ???????? 
			{ ch->delta = (float) (*(ring + temp_count) - *(ring + INCAP_VOLUME - pseudo_teeth + temp_count));	}                       // ???????????? 32 ?????????? ???????? ?? ????
		else { ch->delta = (float) (*(ring + temp_count) - *(ring + INCAP_VOLUME - pseudo_teeth + temp_count) + 0xFFFFFFFF + 1);	}	// ???? ???????????? 32 ?????????? ????????
		}
	if ((ch->rotary!=0) && (ch->delta != 0))				// ???????? ?????? ?? ???????????? ? ?????? ??????? ?? ????
		{
		ch->bbrps = ch->brps;							// ?????????? ??????? ???????
		ch->bbrpm = ch->brpm;							// ?????????? ??????? ???????
		ch->brps = ch->rps;								// ?????????? ??????? ???????
		ch->brpm = ch->rpm;								// ?????????? ??????? ???????
		ch->rps = PBCLK3_ * ch->filter / ch->delta   ;									// ?????? ???????? ? ??????
		ch->rpm = ch->rps * 60 ;																// ?????? ???????? ? ???????
		}
	ch->ready = 0;
}

unsigned short rpm_compare (void)
{
    unsigned short compare_result;
    float delta_rpm;
    compare_result = 0;
    delta_rpm = ch_1.rpm - ch_2.rpm;
    if (((ch_1.rpm - ch_2.rpm ) < 0.5) || ((ch_2.rpm - ch_1.rpm)) < 0.5) {compare_result = 1;}
    return compare_result;
}

float hold;
float holdb;
float holdbb;

void tmr_8_init(unsigned short T8_delay, unsigned short TMR8_IE, unsigned short TMR8_ON)
	{
	TMR8 = 0x0000;
	PR8 = T8_delay;					//
	IEC1bits.T8IE = TMR8_IE;
	T8CONbits.TCKPS = 0b11;				//T1 prescaler 1:8
	T8CONbits.TON = TMR8_ON;
	}

void sync_control (void)
{
    Modbus.pulses_11 = sync_counter_11;
    Modbus.pulses_40 = rpm_count;
    Modbus_sw.pulses_40 = swapshort (rpm_count);
    Modbus_sw.pulses_11 = swapshort (sync_counter_11);    
    if (rpm_count > 40) {Modbus.miss_sync = 1;}
    if (rpm_count < 40) {Modbus.miss_rpm = 1;}
    if (rpm_count == 40) {Modbus.miss_rpm = 0; Modbus.miss_sync = 0;}

    
    Modbus_sw.statuses = swaplong (Modbus.statuses );
    rpm_count = 0;
}

void measure_sync (void)
{
    ch_1.teeth = 11;
    ch_1.filter = 1;
	measuring (&ch_1, ring_1, ch_1.ring_count);		// 
    
    holdbb = holdb;
    holdb = hold;
    hold = ch_1.fast_delta;
//    if ((sync_counter_11 == 11) && (sync_status == 1)) { sync_counter_11 = 0; sync_status = 1; }
    if ((holdbb > holdb) && (holdb > hold)) {sync_status = 1; sync_control (); sync_counter_11 = 0; }
    if (ign_alowed == 1) {ignit_distributor (); }        // ����� ������ �� ��������� ������������� ���


    MB_swap.angle_3 = swapfloat (ch_1.delta);    
  
    Modbus.RPM11 = ch_1.rpm;
    Modbus_sw.RPM11 = swapfloat (ch_1.rpm);
    middle_buf11 [middle_count11] = ch_1.rpm;
    middle_count11 ++;
    if (middle_count11 >= (FILT_CRPM * 11)) {middle_count11 = 0;}
    phase_delta = ch_1.fast_delta  * 360 / ch_1.delta;	
    ch_1.angle = phase_delta;
    MB_swap.angle_4 = swapfloat (phase_delta);
}

void measure_rpm (void)
{
    ch_2.teeth = 40;
    ch_2.filter = 5;
    rpm_count ++;
	measuring (&ch_2, ring_2, ch_2.ring_count);		// 
    Modbus_sw.RPM40 = swapfloat (ch_2.rpm);
    Modbus.RPM40 = ch_2.rpm;
    MB_swap.angle_2 = swapfloat (ch_2.rpm);  
}

void IC1Interrupt_(void)	{
    while (IC1CONbits.ICBNE)	{ ring_1[ch_1.ring_count++]  = IC1BUF;	}		//fixing the value during IC ()
	if (ch_1.ring_count >= INCAP_VOLUME) ch_1.ring_count = 0;
	ch_1.ready = 1;
	ch_1.wait = max_inactiv_1;		//start delay for inactivity    
    MB_swap.par1 = swaplong (ring_1[ch_1.ring_count]);
    }

void IC3Interrupt_(void)	{
    while (IC3CONbits.ICBNE)	{ ring_1[ch_1.ring_count++]  = IC3BUF;	}		//fixing the value during IC ()
	if (ch_1.ring_count >= INCAP_VOLUME) ch_1.ring_count = 0;
	ch_1.ready = 1;
	ch_1.wait = max_inactiv_1;		//start delay for inactivity    
    MB_swap.par1 = swaplong (ring_1[ch_1.ring_count]);
    }

void IC6Interrupt_(void)
	{
	while (IC6CONbits.ICBNE)	{ ring_2[ch_2.ring_count++]  = IC6BUF;	}//ring_2[ch_2.ring_count++] = IC6BUF;    /* reads the input capture buffer */
	if (ch_2.ring_count >= INCAP_VOLUME) ch_2.ring_count = 0;
	ch_2.ready = 1;
	ch_2.wait = max_inactiv_2;	//start delay for inactivity
	}


void IC4Interrupt_(void)
	{
	while (IC4CONbits.ICBNE)	{ ring_2[ch_2.ring_count++]  = IC4BUF;	}//ring_2[ch_2.ring_count++] = IC4BUF;    /* reads the input capture buffer */
	if (ch_2.ring_count >= INCAP_VOLUME) ch_2.ring_count = 0;
	ch_2.ready = 1;
	ch_2.wait = max_inactiv_2;	//start delay for inactivity
	}

void stop_inactive (void)
{
	if (ch_1.activ)							//channel is active
		{
		if (!(--ch_1.wait))						//waiting for inactivity interval
			{
			ch_1.activ=0;
			ch_1.rotary=0;
			ch_1.ring_count=0;
			ch_1.fast=0;
			ch_1.rpm=0;
			ch_1.rps=0;
            Modbus_sw.RPM11 = swapfloat (ch_1.rpm);
            Modbus.RPM11 = ch_1.rpm;
			}
		}
	if (ch_2.activ)
		{
		if (!(--ch_2.wait))
			{
			ch_2.activ=0;
			ch_2.rotary=0;
			ch_2.ring_count = 0;
			ch_2.fast=0;
			ch_2.rpm=0;
			ch_2.rps=0;
            Modbus_sw.RPM40 = swapfloat (ch_2.rpm);
            Modbus.RPM40 = ch_2.rpm;
			}
		}
}



/* *****************************************************************************
 End of File
 */
