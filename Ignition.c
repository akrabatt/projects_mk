#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "define.h"
#include "extern.h"


extern unsigned short rpm_compare(void);
extern void tmr_9_init(unsigned short T9_delay, unsigned short TMR9_IE, unsigned short TMR9_ON);
unsigned short ign_six;
unsigned short ign_seven;
unsigned short active_cylinder;
void ign_err_check(void);


unsigned short close_1;
unsigned short close_2;

unsigned short ign_wait;
unsigned short ign_IC3;
unsigned short ign_IC4;
unsigned short ign_IC7;
unsigned short ign_IC8;

void clr_charge_err(void) {
    close_1 = 0;
    close_2 = 0;
}

void ignit_start(unsigned short ch_num) {

    if (CTRL1 == 1) {
        close_1++;
    } else {
        close_1 = 0;
    }
    if (CTRL2 == 1) {
        close_2++;
    } else {
        close_2 = 0;
    }


    if (close_1 >= 10) {
        close_2 = 0;
        close_1 = 0;
        charge_fail = 1;
        Modbus.AO_cyl_num = 1;
        Modbus_sw.AO_cyl_num = swapshort(Modbus.AO_cyl_num);
        return;
    }

    if (close_2 >= 10) {
        close_2 = 0;
        close_1 = 0;
        charge_fail = 1;
        Modbus.AO_cyl_num = 2;
        Modbus_sw.AO_cyl_num = swapshort(Modbus.AO_cyl_num);
        return;
    }

    switch (ch_num) {
        case 1:
        {
            ON_IGN_1;
            ign_IC8 = 1;
            pulse_started1 = 1;
            ign_timer8 = TMR2;
            break;
        }
        case 2:
        {
            ON_IGN_2;
            ign_IC7 = 1;
            pulse_started2 = 1;
            ign_timer7 = TMR2;
            break;
        }
        case 3:
        {
            ON_IGN_3;
            ign_IC8 = 1;
            pulse_started1 = 1;
            ign_timer8 = TMR2;
            break;
        }
        case 4:
        {
            ON_IGN_4;
            ign_IC7 = 1;
            pulse_started2 = 1;
            ign_timer7 = TMR2;
            break;
        }
        case 5:
        {
            ON_IGN_5;
            ign_IC8 = 1;
            pulse_started1 = 1;
            ign_timer8 = TMR2;
            break;
        }
        case 6:
        {
            ON_IGN_6;
            ign_IC7 = 1;
            pulse_started2 = 1;
            ign_timer7 = TMR2;
            break;
        }
        case 7:
        {
            ON_IGN_7;
            ign_IC8 = 1;
            pulse_started1 = 1;
            ign_timer8 = TMR2;
            break;
        }
        case 8:
        {
            ON_IGN_8;
            ign_IC7 = 1;
            pulse_started2 = 1;
            ign_timer7 = TMR2;
            break;
        }
        case 9:
        {
            ON_IGN_9;
            ign_IC8 = 1;
            pulse_started1 = 1;
            ign_timer8 = TMR2;
            break;
        }
        case 10:
        {
            ON_IGN_10;
            ign_IC7 = 1;
            pulse_started2 = 1;
            ign_timer7 = TMR2;
            break;
        }
    }
    //    pulse_started = 1;
    ign_wait = 3;
    //    ign_timer8 = TMR2;               // holding TMR2 for control discharge time
    //    ign_timer7 = ign_timer8; 
}

float sc_low_lim;
float br_high_lim;

/*               каналы 2, 4, 6, 8, 10        */
void Timer6Interrupt(void) {
    ignit_start(ign_six);
    active_cylinder = ign_six - 1;
    T6CONbits.TON = 0;
    IFS0bits.T6IF = 0;
    ign_stat_even = 2;
}

void tmr_6_init(unsigned short T6_delay, unsigned short TMR6_IE, unsigned short TMR6_ON, unsigned short chan_num) {
    ign_six = chan_num;
    T6CONbits.ON = 0;
    TMR6 = 0x0;
    PR6 = T6_delay;
    IEC0bits.T6IE = TMR6_IE;
    T6CONbits.ON = TMR6_ON;
}

/*              каналы 1, 3, 5, 7, 9         */
void Timer7Interrupt(void) {
    ignit_start(ign_seven);
    active_cylinder = ign_seven - 1;
    T7CONbits.TON = 0;
    IFS1bits.T7IF = 0;
    ign_stat_even = 2;
}

void tmr_7_init(unsigned short T7_delay, unsigned short TMR7_IE, unsigned short TMR7_ON, unsigned short chan_num) {
    ign_seven = chan_num;
    T7CONbits.ON = 0;
    TMR7 = 0x0;
    PR7 = T7_delay;
    IEC1bits.T7IE = TMR7_IE;
    T7CONbits.ON = TMR7_ON;
}

void ignit_stop(void) // выключение зажигания и контроль качества искрообразования
{
    unsigned short br_dir0, br_dir1;

    if ((pulse_started1 == 0) && (pulse_started2 == 0)) {
        return;
    }
    if (ign_wait != 0) {
        ign_wait--;
        return;
    }
    /* идет зажигание по цилиндрам  1-3-5-7-9 */
    if (pulse_started1 == 1) {
        br_dir0 = dir_br_low [ign_seven - 1];
        br_dir1 = dir_br_low [ign_seven - 1];
        if (ign_IC8 == 1) {
            MB_diagn.break_low [ign_seven - 1]++;
            br_dir1++;
            total_err_count1++;
        } else {
            br_dir1 = 0;
            total_err_count1 = 0;
        }
        if (br_dir1 > MB_conf.NUM_ERR_AO) {
            br_dir1 = MB_conf.NUM_ERR_AO;
        }
        dir_br_low [ign_seven - 1] = br_dir1;
        MB_diagn_sw.break_low [ign_seven - 1] = swapshort(MB_diagn.break_low [ign_seven - 1]);
        pulse_started1 = 0;
    }
    /* идет зажигание по цилиндрам  2-4-6-8-10 */
    if (pulse_started2 == 1) {
        br_dir0 = dir_br_low [ign_six - 1];
        br_dir1 = dir_br_low [ign_six - 1];
        if (ign_IC7 == 1) {
            MB_diagn.break_low [ign_six - 1]++;
            br_dir1++;
            total_err_count2++;
        } else {
            br_dir1 = 0;
            total_err_count2 = 0;
        }
        if (br_dir1 > MB_conf.NUM_ERR_AO) {
            br_dir1 = MB_conf.NUM_ERR_AO;
        }
        dir_br_low [ign_six - 1] = br_dir1;
        MB_diagn_sw.break_low [ign_six - 1] = swapshort(MB_diagn.break_low [ign_six - 1]);
        pulse_started2 = 0;
    }
    IGN_RESET;
}

void ignit_distributor(void) // режим работы по алгоритму от давления регулирования УОЗ
{
    unsigned short cylinder, tmr_set;

    float difference, sett_diff;
    if (sync_counter_11 == 0) {
        sync_counter_11++;
        if ((sync_status == 1) && (ch_1.rpm > 20.0) && (ch_2.rpm > 20.0)) {
            LED_SYNC = 1;
        } else {
            LED_SYNC = 0;
        }
        if (ch_2.rpm != 0) {
            difference = ch_1.rpm / ch_2.rpm;
        }
        return;
    }

    cylinder = cyl_order [sync_counter_11];
    sett_diff = RPM_UOZ_MAX - RPM_UOZ_MIN;
    if (sett_diff <= 0) {
        sett_diff = 1;
    }

    if (ch_1.rpm >= RPM_UOZ_MAX) {
        Modbus.actual_UOZ = NOM_UOZ;
    }// calculate UOZ depending of RPM 
    else {
        if (ch_1.rpm < RPM_UOZ_MIN) {
            Modbus.actual_UOZ = LOW_UOZ;
        }
        else {
            Modbus.actual_UOZ = (ch_1.rpm - RPM_UOZ_MIN) * NOM_UOZ / sett_diff;
        }
    }

    Modbus_sw.actual_UOZ = swapfloat(Modbus.actual_UOZ);
    tmr_set = ch_1.delta * (CONST_UOZ - Modbus.actual_UOZ - MB_conf.UOZ_shift_ind [cylinder - 1]) / 92160; //11520;

    if (tmr_set > 65535) {
        tmr_set = 65535;
    }
    if ((cylinder == 2) || (cylinder == 4) || (cylinder == 6) || (cylinder == 8) || (cylinder == 10)) {
        tmr_6_init(tmr_set, 1, 1, cylinder);
    }
    if ((cylinder == 1) || (cylinder == 3) || (cylinder == 5) || (cylinder == 7) || (cylinder == 9)) {
        tmr_7_init(tmr_set, 1, 1, cylinder);
    }

    sync_counter_11++;
    LED9 ^= 1;
}

void ignit_check(unsigned short cyl_num) { //  ign_err_check ();                  // проверка зажигания
    if ((cyl_num == 1) || (cyl_num == 3) || (cyl_num == 5) || (cyl_num == 7) || (cyl_num == 9)) {
        tmr_7_init(150, 1, 1, cyl_num);
    }
    if ((cyl_num == 2) || (cyl_num == 4) || (cyl_num == 6) || (cyl_num == 8) || (cyl_num == 10)) {
        tmr_6_init(150, 1, 1, cyl_num);
    }
}

unsigned short bit_set(unsigned short cyl, unsigned short candle) {
    unsigned short bit_data;
    bit_data = 1 << (cyl - 1 + candle);
    return bit_data;
}

unsigned short bit_clr(unsigned short cyl, unsigned short candle) {
    unsigned short bit_data, tmp;
    bit_data = 1 << (cyl - 1 + candle);
    tmp = 0xFFFF ^ bit_data;
    return tmp;
}

void IC7_measure(void) // even cylinnders capture   2/4/6/8/10
{
    unsigned long IC_hold, IC_delta;
    float sc_limit, br_limit, discharge;
    unsigned short sc_count, br_count, sc_dir, br_dir;
    //    unsigned short oddeven;
    //    oddeven = 1;
    sc_dir = dir_sc_low [ign_six - 1];
    br_dir = dir_br_high [ign_six - 1];
    sc_count = MB_diagn.short_low [ign_six - 1];
    br_count = MB_diagn.break_high [ign_six - 1];
    sc_limit = MB_conf.discharge_sc_low;
    br_limit = MB_conf.discharge_br_high;

    while (IC7CONbits.ICBNE) {
        IC_hold = IC7BUF;
    }
    if (pulse_started2 == 1) {
        if (IC_hold > ign_timer7) {
            IC_delta = IC_hold - ign_timer7;
        } else {
            IC_delta = (0xFFFFFFFF - ign_timer7) + IC_hold + 1;
        }
        //            discharge = (float) IC_delta / 49.7664;
        discharge = (float) IC_delta * 0.02009388;
        MB.fl_2 = discharge;
        if (discharge < sc_limit) {
            sc_count++;
            sc_dir++;
            total_err_count2++;
        } else {
            sc_dir = 0;
            total_err_count2 = 0;
        } //контроль на короткое замыкание низковольтой части
        if (discharge > br_limit) {
            br_count++;
            br_dir++;
        } else {
            br_dir = 0;
        } //контроль на обрыв высоковольтой части
        if (sc_dir > MB_conf.NUM_ERR_AO) {
            sc_dir = MB_conf.NUM_ERR_AO;
        }
        if (br_dir > MB_conf.NUM_ERR_AO) {
            br_dir = MB_conf.NUM_ERR_AO;
        }
        dir_sc_low [ign_six - 1] = sc_dir;
        dir_br_high [ign_six - 1] = br_dir;
        MB_swap.fl_2 = swapfloat(MB.fl_2);
        MB_diagn.discharge_hold [ign_six - 1] = discharge;
        MB_diagn_sw.discharge_hold [ign_six - 1] = swapfloat(discharge);
        MB_diagn.short_low [ign_six - 1] = sc_count;
        MB_diagn.break_high [ign_six - 1] = br_count;
        MB_diagn_sw.short_low [ign_six - 1] = swapshort(MB_diagn.short_low [ign_six - 1]);
        MB_diagn_sw.break_high [ign_six - 1] = swapshort(MB_diagn.break_high [ign_six - 1]);
    }
}

void IC8_measure(void) // odd cylinnders capture 1/3/3/5/7/9
{
    unsigned long IC_hold, IC_delta;
    float sc_limit, br_limit, discharge;
    unsigned short sc_count, br_count, sc_dir, br_dir;
    //    unsigned short oddeven;
    //    oddeven = 0;
    sc_dir = dir_sc_low [ign_seven - 1];
    br_dir = dir_br_high [ign_seven - 1];
    sc_count = MB_diagn.short_low [ign_seven - 1];
    br_count = MB_diagn.break_high [ign_seven - 1];
    sc_limit = MB_conf.discharge_sc_low;
    br_limit = MB_conf.discharge_br_high;

    while (IC8CONbits.ICBNE) {
        IC_hold = IC8BUF;
    }
    if (pulse_started1 == 1) {
        if (IC_hold > ign_timer8) {
            IC_delta = IC_hold - ign_timer8;
        } else {
            IC_delta = (0xFFFFFFFF - ign_timer8) + IC_hold + 1;
        }
        //            discharge = (float) IC_delta / 49.7664;
        discharge = (float) IC_delta * 0.02009388;
        MB.fl_2 = discharge;
        if (discharge < sc_limit) {
            sc_count++;
            sc_dir++;
            total_err_count1++;
        } else {
            sc_dir = 0;
            total_err_count1 = 0;
        } //контроль на короткое замыкание низковольтой части
        if (discharge > br_limit) {
            br_count++;
            br_dir++;
        } else {
            br_dir = 0;
        } //контроль на обрыв высоковольтой части
        if (sc_dir > MB_conf.NUM_ERR_AO) {
            sc_dir = MB_conf.NUM_ERR_AO;
        }
        if (br_dir > MB_conf.NUM_ERR_AO) {
            br_dir = MB_conf.NUM_ERR_AO;
        }
        dir_sc_low [ign_seven - 1] = sc_dir;
        dir_br_high [ign_seven - 1] = br_dir;
        MB_swap.fl_2 = swapfloat(MB.fl_2);
        MB_diagn.discharge_hold [ign_seven - 1] = discharge;
        MB_diagn_sw.discharge_hold [ign_seven - 1] = swapfloat(discharge);
        MB_diagn.short_low [ign_seven - 1] = sc_count;
        MB_diagn.break_high [ign_seven - 1] = br_count;
        MB_diagn_sw.short_low [ign_seven - 1] = swapshort(MB_diagn.short_low [ign_seven - 1]);
        MB_diagn_sw.break_high [ign_seven - 1] = swapshort(MB_diagn.break_high [ign_seven - 1]);
    }
}

void IC7Int(void) {
    ign_IC7 = 0;
    IGN_RESET;
    pulse_started2 = 0;
    //    if ((ign_IC7 == 0) && (ign_IC8 == 0)) {      //        ignit_stop () ;
    //        }
}

void IC8Int(void) {
    ign_IC8 = 0;
    IGN_RESET;
    pulse_started1 = 0;
    //    if ((ign_IC7 == 0) && (ign_IC8 == 0)) {     //        ignit_stop () ;
    //        }    
}

/*    
    
    void IC4Int3527 (void)  {   ign_IC4 = 0; 
    if ((ign_IC3 == 0) && (ign_IC4 == 0)) { IGN_RESET;  pulse_started2 = 0;     //        ignit_stop () ;
        }    
    }
 */

//void ignit_distributor_ext (void)                           // режим работы при задании коррекции УОЗ от САУ
//{
//    unsigned short cylinder, tmr_set;
//    float difference, pressure;
//    pressure = Modbus.Pressure_set;
//    if (sync_counter_11 == 0)   { 
//        sync_counter_11++; 
//        if ((sync_status == 1)  && (ch_1.rpm > 20.0) && (ch_2.rpm > 20.0)) {LED_SYNC = 1;}     else {LED_SYNC = 0;}
//        if  (ch_2.rpm != 0)  { difference = ch_1.rpm / ch_2.rpm; } 
//        return;   }
//    
//    cylinder = cyl_order [sync_counter_11];
//    Modbus.actual_UOZ = Modbus.UOZ_corr_deep;
//    
//    Modbus_sw.actual_UOZ = swapfloat (Modbus.actual_UOZ);
//    tmr_set = ch_1.delta * (CONST_UOZ - Modbus.actual_UOZ - MB_conf.UOZ_shift_ind [cylinder - 1]) / 92160;  //11520;
//
//    if (tmr_set > 65535) {tmr_set = 65535;}
//    if ((cylinder == 1) ||(cylinder == 3) ||(cylinder == 5) ||(cylinder == 7) ||(cylinder == 9))        {   tmr_6_init (tmr_set, 1, 1, cylinder);  }
//    if ((cylinder == 2) ||(cylinder == 4) ||(cylinder == 6) ||(cylinder == 8) ||(cylinder == 10))       {   tmr_7_init (tmr_set, 1, 1, cylinder);  }
//
//    sync_counter_11 ++;     LED9 ^=1;
//}

/*
void ign_err_check (void)
{
    unsigned short ii;
    unsigned short err_limit;
    unsigned short tmp_buf1 [CYLINDERS_NUM *2], tmp_buf2 [CYLINDERS_NUM *2], tmp_buf3 [CYLINDERS_NUM *2];

    err_limit = MB_conf.NUM_ERR_AO;

    memcpy ((void*) (tmp_buf1), (const void*) ( dir_br_low), (CYLINDERS_NUM * 4));
    memcpy ((void*) (tmp_buf2), (const void*) ( dir_sc_low), (CYLINDERS_NUM * 4));
    memcpy ((void*) (tmp_buf3), (const void*) ( dir_br_high), (CYLINDERS_NUM * 4));
    
    for (ii=0; ii < 16; ii++) 
        {
        if (tmp_buf1 [ii] >= err_limit)       {
            if (!(Modbus.cyl_mask & (1 <<ii)))       {
//                AO_ignit_br_low = 1; 
//                Modbus.AO_cyl_num = ii + 1; 
//                Modbus_sw.AO_cyl_num = swapshort (Modbus.AO_cyl_num);
//                Modbus.AO_reason = AO_CYL_BR_LOW; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
//                work_status = 10; 
                }
            }
        if (tmp_buf2 [ii] >= err_limit)       {
            if (!(Modbus.cyl_mask & (1 <<ii)))       {
//                AO_ignit_br_low = 1; 
//                Modbus.AO_cyl_num = ii + 1; 
//                Modbus_sw.AO_cyl_num = swapshort (Modbus.AO_cyl_num);
//                Modbus.AO_reason = AO_CYL_SC_LOW; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
//                work_status = 10; 
                }
            }
        if (tmp_buf3 [ii] >= err_limit)       {
            if (!(Modbus.cyl_mask & (1 <<ii)))       {
//                AO_ignit_br_low = 1; 
//                Modbus.AO_cyl_num = ii + 1; 
//                Modbus_sw.AO_cyl_num = swapshort (Modbus.AO_cyl_num);
//                Modbus.AO_reason = AO_CYL_BR_HIGH; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
//                work_status = 10; 
                }
            }
    }
}
 */


/*
void IC3_measure_(void)                     // even cylinnders capture 
    {
    unsigned long IC_hold, IC_delta;
    float sc_limit, br_limit, discharge;
    unsigned short sc_count, br_count, sc_dir, br_dir;
    unsigned short oddeven;
    oddeven = 1;
    sc_dir = dir_sc_low [ign_seven-1];
    br_dir = dir_br_high [ign_seven-1];
    sc_count = MB_diagn.short_low [ign_seven-1];     br_count = MB_diagn.break_high [ign_seven-1];
    sc_limit = MB_conf.discharge_sc_low;    br_limit = MB_conf.discharge_br_high;
    
    while (IC3CONbits.ICBNE)	{IC_hold = IC3BUF;	}
    if (pulse_started2 == 1){
            if (IC_hold  > ign_timer) {IC_delta = IC_hold  - ign_timer;}
            else {IC_delta = (0xFFFFFFFF - ign_timer) + IC_hold  +1;}
            discharge = (float) IC_delta / 49.7664;
            if (discharge < sc_limit) { sc_count++; sc_dir++;  total_err_count ++;} else {sc_dir = 0;  total_err_count = 0;}    //контроль на короткое замыкание низковольтой части
            if (discharge > br_limit) { br_count++; br_dir++; } else {br_dir = 0;}                                              //контроль на обрыв высоковольтой части
            if (sc_dir > MB_conf.NUM_ERR_AO) {sc_dir = MB_conf.NUM_ERR_AO; }
            if (br_dir > MB_conf.NUM_ERR_AO) {br_dir = MB_conf.NUM_ERR_AO; }
            dir_sc_low [ign_seven-1] = sc_dir;
            dir_br_high [ign_seven-1] = br_dir;      
            MB_swap.fl_2 = swapfloat (MB.fl_2);
            MB_diagn.discharge_hold [ign_seven-1] = discharge;    
            MB_diagn_sw.discharge_hold [ign_seven-1] = swapfloat (discharge);
            MB_diagn.short_low [ign_seven-1] =   sc_count;   
            MB_diagn.break_high [ign_seven-1] =  br_count; 
            MB_diagn_sw.short_low [ign_seven-1] = swapshort (MB_diagn.short_low [ign_seven-1]);            
            MB_diagn_sw.break_high [ign_seven-1] = swapshort (MB_diagn.break_high [ign_seven-1]);            
        }
    }

void IC4_measure_(void)                     // even cylinnders capture 
    {
    unsigned long IC_hold, IC_delta;
    float sc_limit, br_limit, discharge;
    unsigned short sc_count, br_count, sc_dir, br_dir;
    unsigned short oddeven;
    oddeven = 0;
    sc_dir = dir_sc_low [ign_seven-1];
    br_dir = dir_br_high [ign_seven-1];
    sc_count = MB_diagn.short_low [ign_seven-1];     br_count = MB_diagn.break_high [ign_seven-1];
    sc_limit = MB_conf.discharge_sc_low;    br_limit = MB_conf.discharge_br_high;
    
    while (IC4CONbits.ICBNE)	{IC_hold = IC4BUF;	}
    if (pulse_started2 == 1){
            if (IC_hold  > ign_timer) {IC_delta = IC_hold  - ign_timer;}
            else {IC_delta = (0xFFFFFFFF - ign_timer) + IC_hold  +1;}
            discharge = (float) IC_delta / 49.7664;
            if (discharge < sc_limit) { sc_count++; sc_dir++;  total_err_count ++;} else {sc_dir = 0;  total_err_count = 0;}    //контроль на короткое замыкание низковольтой части
            if (discharge > br_limit) { br_count++; br_dir++; } else {br_dir = 0;}                                              //контроль на обрыв высоковольтой части
            if (sc_dir > MB_conf.NUM_ERR_AO) {sc_dir = MB_conf.NUM_ERR_AO; }
            if (br_dir > MB_conf.NUM_ERR_AO) {br_dir = MB_conf.NUM_ERR_AO; }
            dir_sc_low [ign_seven-1] = sc_dir;
            dir_br_high [ign_seven-1] = br_dir;   
            MB_swap.fl_2 = swapfloat (MB.fl_2);
            MB_diagn.discharge_hold [ign_seven-1] = discharge;    
            MB_diagn_sw.discharge_hold [ign_seven-1] = swapfloat (discharge);
            MB_diagn.short_low [ign_seven-1] =  sc_count;   
            MB_diagn.break_high [ign_seven-1] =  br_count; 
            MB_diagn_sw.short_low [ign_seven-1] = swapshort (MB_diagn.short_low [ign_seven-1]);            
            MB_diagn_sw.break_high [ign_seven-1] = swapshort (MB_diagn.break_high [ign_seven-1]);            
        }
    }
                                            //discharge_capt [sync_counter_11 - 1]
    void IC3Int3527 (void)  {   ign_IC3 = 0; 
    if ((ign_IC3 == 0) && (ign_IC4 == 0)) { IGN_RESET;   pulse_started2 = 0;    //        ignit_stop () ;
        }
    }
 */



/* *****************************************************************************
 End of File
 */
