#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "define.h"
#include "extern.h"




extern void ignit_check (unsigned short cyl_num) ;
extern unsigned short count_sc_low [10];
extern unsigned short count_br_low [10];
extern unsigned short count_br_high [10];
extern void clr_charge_err (void);


float motor_P_routine (float motor_InputErr, float motor_Kp)
{
float motor_P_Result;

motor_P_Result = motor_Kp * motor_InputErr;
return motor_P_Result;
}

//D-regulator    D_Result = (Td/T)*(InputErr-InputErr_prev);  
float motor_D_routine ( float motor_InputErr, float motor_Coeff_Td)
{
// ? ???? ??????? Coeff_Td = Td/T_discr ? ?????? ??????? ?????????????
static float motor_InputErr_prev; //previous Input error (n-1)
float motor_D_Result;

motor_D_Result = motor_Coeff_Td*(motor_InputErr - motor_InputErr_prev);
motor_InputErr_prev = motor_InputErr;

return motor_D_Result;
}

float motor_I_Result;

float motor_I_routine (float motor_InputErr, float motor_Ti, float motor_Ki)
{
float motor_coeff;
if (motor_Ki) {motor_coeff = motor_Ti / motor_Ki;}
motor_I_Result = motor_I_Result + (motor_coeff * motor_InputErr);
if (motor_I_Result >= 100.0) {motor_I_Result = 100.0;}
if (motor_I_Result <= -100.0) {motor_I_Result = -100.0;}
return motor_I_Result;
}

float motor_regulator (float motor_Kp, float motor_Ki, float motor_Kd)
{
float motor_P_Result;
float motor_D_Result;
float motor_Clearance_Error;
float motor_Coeff_D_Reg;
float CV_task;
float Set;
float Pos;
unsigned short cc;

    motor_Coeff_D_Reg = motor_Kd / 100.0;
    
    Set = Modbus.RPM_set;
//    Pos = (Modbus.RPM40 + Modbus.RPM11) / 2;    
//    middle_40 = 0;
//    for (cc = 0; cc < (FILT_CRPM * 40); cc++)  
//        {
//        middle_40 += middle_buf40 [cc];
//        }
//    middle_40 /= (FILT_CRPM * 40);
//    Pos = Modbus.RPM40 ;    
    Pos = middle_40 ;    
    
    motor_Clearance_Error = Set - Pos;
    
    if ((motor_Clearance_Error < MB_conf.PID_deadband) ||(motor_Clearance_Error > (MB_conf.PID_deadband * (-1.0)))) {motor_P_Result = motor_P_routine (motor_Clearance_Error , motor_Kp);}
    if ((motor_Clearance_Error < -3.0) ||(motor_Clearance_Error > 3)) 
        {
        motor_I_Result = motor_I_routine (motor_Clearance_Error, 10, motor_Ki);
        }  

    motor_D_Result = motor_D_routine ((motor_Kd * motor_Clearance_Error ), (motor_Coeff_D_Reg)); 
    if (motor_P_Result > MB_conf.KP_res_limit) {motor_P_Result = MB_conf.KP_res_limit;}
    if (motor_P_Result < ((-1.0) * MB_conf.KP_res_limit)) {motor_P_Result = (-1.0) * MB_conf.KP_res_limit;}
    CV_task = motor_P_Result + motor_I_Result + motor_D_Result; 
    
    if(CV_task > 99.0)		{CV_task = 99.0;}
	if(CV_task < 0.0)		{CV_task = 0.0;}

    return CV_task;

}
/*
enum 
{
	START = 0,

	STOP,
    STOP_READY,
    WAIT_SYNCHRO,
    VC_START_OPN,
	WAIT_IGNITION,
    INCREASE_TO_PID,
    SINCRONIZE_PID,
	WORK,
	AO,
    CV_START_CHECK,
	CYL_CONTROL,
	CV_CONTROL,
	PWM_CONTROL,
    IGN_CHECK
};
*/





void reset_condition_ (void) 
{
    unsigned int cc;
    IGN_ON = 1;
    Modbus.CV_set = 0;
    Modbus.RPM_set = 0;
    Modbus_sw.CV_set = 0;
    Modbus_sw.RPM_set = 0;
    AO_ignit_error = 0;
    middle_40 = 0;
    motor_I_Result = 0;
    Modbus.cmd1 = 0;
    Modbus_sw.cmd1 = 0;
    TAP_OFF;
    ign_alowed = 0;
    led_off () ;
    Modbus.AO_reason = 0; Modbus_sw.AO_reason = 0;
    Modbus.AO_cyl_num = 0; Modbus_sw.AO_cyl_num = 0;
    Modbus.num_check_cyl = 0; Modbus_sw.num_check_cyl = 0;
    Modbus.err_rpm = 0; Modbus_sw.err_rpm = 0;
    AO_ignit_error = 0;
    charge_fail = 0;
    clr_charge_err ();
    for (cc = 0; cc < (FILT_CRPM * 40); cc++)  
        {
        middle_buf40 [cc] = 0;
        }

}

extern unsigned int work_status;
extern unsigned int tmp_CV_val;
extern float timer_to_PID;
extern unsigned int cyl_timer;
extern unsigned int ign_delay;
float middle_current;
unsigned int middle_count;
float middle_curr [50];
unsigned int CV_err_count;
/*
void motor_control (void)
{
    float tmp_CV;
    if (work_status != AO) {Modbus.unlock = 0; Modbus_sw.cmd1 = swaplong (Modbus.cmd1);}
    switch (work_status)
    {
    case START : { reset_condition (); work_status = STOP; 	break;	}
    case STOP :
        {
        led_off ();  LED_STOP = 1;
        if (Modbus.start == 1) {work_status = CV_START_CHECK; timer_to_PID = 0; Modbus.start = 0;  break;}
        if (Modbus.PWM_dir_ctrl == 1) {work_status = PWM_CONTROL; Modbus.PWM_dir_ctrl = 0; Modbus_sw.cmd1 = swaplong (Modbus.cmd1); break;} // go to direct PWM control procedure 
        if (Modbus.CV_dir_ctrl == 1) {work_status = CV_CONTROL; break;} // go to direct valve control procedure
        if (Modbus.ign_ctrl == 1) {work_status = CYL_CONTROL; Modbus.ign_ctrl = 0; Modbus_sw.cmd1 = swaplong (Modbus.cmd1); break;} // go to direct valve control procedure
        break;	
        }
    
     case WAIT_SYNCHRO :
        {
        led_off ();
        if ((ch_1.rpm > MB_conf.Ignit_spd) && (ch_2.rpm > MB_conf.Ignit_spd) && (sync_status == 1)) {work_status = VC_START_OPN; LED_SYNC = 1;}
        break;	
        }
    
    case VC_START_OPN :
        {
        Modbus.CV_set += MB_conf.CV_start_spd / 100;
        Modbus_sw.CV_set = swapfloat (Modbus.CV_set);
        if (Modbus.CV_set >= MB_conf.CV_start_val) {work_status = WAIT_IGNITION; ign_delay = 0;}
        break;	
        }

    case WAIT_IGNITION :
        {
        LED_WIGN = 1;
        if (Modbus.ignit_allow || (DINPUT1 == 1)) {ign_alowed = 1;  Modbus.RPM_set = MB_conf.PID_spd; timer_to_PID = 0; LED_WIGN = 0; ign_delay ++; IGN_ON = 0;}
        if (ign_delay >=100) 
            {
            if((CTRL1 == 0) && (CTRL2 == 0))
                {
                work_status = INCREASE_TO_PID; ign_delay = 0;
                }
            else {Modbus.AO_reason = AO_NO_CHARGE; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason); work_status = AO; }
            }
        break;	
        }    
    
    case INCREASE_TO_PID :
        {
        LED_IGN = 1; timer_to_PID += 0.01; LED_WIGN = 0;
//        tmp_CV = motor_regulator (0, 50000, 0);
//        if (tmp_CV < MB_conf.CV_start_val)    {Modbus.CV_set = MB_conf.CV_start_val;}
//        else {Modbus.CV_set = tmp_CV;}
//        Modbus_sw.CV_set = swapfloat (Modbus.CV_set);
        if (DINPUT1 == 0) {Modbus.AO_reason = AO_MISS_IGN_SIGN; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason); work_status = AO; }
        if (Modbus.RPM40 < (MB_conf.PID_spd - 30.0)) {Modbus.CV_set += MB_conf.CV_open_spd / 100.0;}
        else { tmp_CV_val = Modbus.CV_set; work_status = SINCRONIZE_PID; }
        Modbus_sw.CV_set = swapfloat (Modbus.CV_set);
        Modbus_sw.RPM_set = swapfloat (Modbus.RPM_set);
        if ( timer_to_PID >= MB_conf.Timer_to_PID) 
        {
            Modbus.AO_reason = AO_START_ERROR; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
            work_status = AO; 
        }
        break;	
        }      

    case SINCRONIZE_PID :
        {
        if (DINPUT1 == 0) {Modbus.AO_reason = AO_MISS_IGN_SIGN; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason); work_status = AO; }
        LED_IGN = 1; timer_to_PID += 0.01;
        tmp_CV = motor_regulator (0, 10000.0, 0);
        if (tmp_CV_val < tmp_CV) {tmp_CV_val = tmp_CV; Modbus.CV_set = tmp_CV; }
        Modbus_sw.CV_set = swapfloat (Modbus.CV_set);
        if (Modbus.RPM40 >= (MB_conf.PID_spd -1.0)) {work_status = WORK;}
        if ( timer_to_PID >= MB_conf.Timer_to_PID) 
        {
            Modbus.AO_reason = AO_START_ERROR; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
            work_status = AO;
        }
        break;	
        }      
    
    case WORK :
        {
        if (DINPUT1 == 0) {Modbus.AO_reason = AO_MISS_IGN_SIGN; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason); work_status = AO; }
        LED_IGN = 1;
        tmp_CV = motor_regulator (MB_conf.KP_mpid, MB_conf.KI_mpid, MB_conf.KD_mpid);
        Modbus.CV_set = tmp_CV;
        Modbus_sw.CV_set = swapfloat (Modbus.CV_set);
        if ((Modbus.RPM40 < MB_conf.min_RPM) || (Modbus.RPM11 < MB_conf.min_RPM)) 
            {
            led_off();
            work_status = AO;         
            if (Modbus.RPM40 < Modbus.RPM11) {Modbus.err_rpm = Modbus.RPM40; Modbus_sw.err_rpm = swapfloat (Modbus.err_rpm);}
            else {Modbus.err_rpm = Modbus.RPM11; Modbus_sw.err_rpm = swapfloat (Modbus.err_rpm);}
            Modbus.AO_reason = AO_TOO_LOW_RPM; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
            }
        break;	
        }     

    case AO :
        {
        led_off();
        Modbus.CV_set = 0;
        LED_AO = 1; 
        Modbus_sw.CV_set = 0;

        TAP_OFF;
        IGN_ON = 1;
        ign_alowed = 0;
        Modbus.ignit_allow = 0; Modbus_sw.cmd1 = swaplong (Modbus.cmd1);
        if (Modbus.unlock == 1) {reset_condition (); Modbus.unlock = 0; work_status = START; LED_AO = 0; }
        break;	
        }    
    
    case CV_START_CHECK :                      // check valve withou PID regulator for direct measure end CV positions and current measuring
        {
        OC3RS = MB_conf.CV_check_level / 100 * (PBCLK3_ / OC_FREQ -1);
        timer_to_PID += 0.01;
        if (middle_count < 40){ middle_curr [middle_count] = Modbus.CV_current; middle_count ++;}
        else { middle_count = 0;}
        if (timer_to_PID >= 2 ) 
        {
            for (middle_count = 0; middle_count < 40; middle_count ++) {middle_current += middle_curr [middle_count];}
            middle_current /= 40; 
            if ((middle_current > 0.2) && (middle_current < 0.4)) {OC3RS = 100; work_status = WAIT_SYNCHRO; Modbus.start = 0;  break;}
//            if ((Modbus.CV_current > 0.2) && (Modbus.CV_current < 0.5)) {OC3RS = 100; work_status = WAIT_SYNCHRO; Modbus.start = 0;  break;}
            else {OC3RS = 100; work_status = AO;  Modbus.AO_reason = AO_CV_CURR_ERROR; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);   break;}
            timer_to_PID = 0; 
        }
        break;
        }     
    
    case CYL_CONTROL :                      // check valve withou PID regulator for direct measure end CV positions and current measuring
        {
        if (cyl_timer >= 20) 
            {
            cyl_timer = 0;
            LED_IGN ^= 1;
            if (Modbus.num_check_cyl != 0) {ignit_check (Modbus.num_check_cyl) ; }
            }

        cyl_timer++;
        break;
        }      
    
        case CV_CONTROL :                       // check valve with PID regulator
        {
        if (Modbus.CV_dir_ctrl == 0) {work_status = START;}
        if (Modbus.CV_dir_set == 0) {Modbus.CV_dir_set = 1;}

        Modbus.CV_set = Modbus.CV_dir_set;
        Modbus_sw.CV_set = swapfloat (Modbus.CV_set);
        break;
        }
    
    case PWM_CONTROL :                      // check valve withou PID regulator for direct measure end CV positions and current measuring
        {
        if (Modbus.CV_dir_set == 0) {Modbus.CV_dir_set = 1;}

        OC3RS = Modbus.CV_dir_set / 100.0 * (PBCLK3_ / OC_FREQ -1);
        break;
        }
  
    
    default :  {work_status = START;}
    }
    if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID) || (work_status == WORK) || (work_status == CYL_CONTROL)) 
        {IGN_ON = 0; DO_1 = 1;}
    else {DO_1 = 0;}

    if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID) || (work_status == WORK) ||
        (work_status == WAIT_SYNCHRO) || (work_status == VC_START_OPN) || (work_status == WAIT_IGNITION) || 
        (work_status == CV_CONTROL) || (work_status == PWM_CONTROL) || (work_status == CV_START_CHECK )) 
        {TAP_ON;}
    if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID) || (work_status == WORK) || (work_status == CYL_CONTROL) ||
        (work_status == WAIT_SYNCHRO) || (work_status == VC_START_OPN) || (work_status == WAIT_IGNITION) || 
        (work_status == CV_CONTROL))     {CV_regul_on = 1;}   
    else {CV_regul_on = 0;}

     if (charge_fail == 1)                   // AO if caps are no charged
        {
         charge_fail = 0; 
         Modbus.AO_reason = AO_NO_CHARGE; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason); work_status = AO; 
        }
    
    if (Modbus.AO == 1) 
        {
        led_off(); work_status = AO; 
        Modbus.AO = 0; Modbus_sw.cmd1 = swaplong (Modbus.cmd1); 
        Modbus.AO_reason = AO_SAU_COMMAND; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
        }
//    if ((Modbus.RPM40 > MB_conf.max_RPM))                   // AO if RPM is too high
    if ((middle_40 > MB_conf.max_RPM))          
        {
        led_off(); work_status = AO; 
//        if (Modbus.RPM40 > Modbus.RPM11) {Modbus.err_rpm = Modbus.RPM40; Modbus_sw.err_rpm = swapfloat (Modbus.err_rpm);}
        Modbus.err_rpm = middle_40; Modbus_sw.err_rpm = swapfloat (Modbus.err_rpm);
//        else {Modbus.err_rpm = Modbus.RPM11; Modbus_sw.err_rpm = swapfloat (Modbus.err_rpm);}
        Modbus.AO_reason = AO_TOO_HIGH_RPM; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
        }
    if (Modbus.clr_err_cnt){ Modbus.clr_err_cnt = 0; Modbus_sw.cmd1 = swaplong (Modbus.cmd1); clear_err_cnt ();}
    if (AO_ignit_br_low == 1) 
        {
        AO_ignit_br_low = 0;
        Modbus.AO_reason = AO_CYL_BR_LOW; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
        work_status = AO; 
        }
        if (AO_ignit_sc_low == 1) 
        {
        AO_ignit_sc_low = 0;
        Modbus.AO_reason = AO_CYL_SC_LOW; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
        work_status = AO; 
        }
        if (AO_ignit_br_high == 1) 
        {
        AO_ignit_br_high = 0;
        Modbus.AO_reason = AO_CYL_BR_HIGH; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
        work_status = AO; 
        }
    if (unsync_error == 1)                                                                      // AO if not syncronised RPM measured via two channels
        {
        unsync_error = 0;
        Modbus.AO_reason = AO_UNSYNC; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
        work_status = AO; 
        }    
    if (((Modbus.CV_set - Modbus.CV_pos) > 20) || ((Modbus.CV_pos - Modbus.CV_set) > 20))       //CV trouble condition when set is not equivalent to pos more than 20 %
        {
        CV_err_count++;
        if (work_status == PWM_CONTROL) {CV_err_count = 0;}
        if (CV_err_count >= 20)                                                                 //AO delay for 200 ms
            {
            work_status = AO; 
            Modbus.AO_reason = AO_CV_ERROR; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
            }  
        }
    else {CV_err_count = 0;}
    if (Modbus.ADC_CV_pos < (MB_conf.CV_pos_min - 4000))    {work_status = AO; Modbus.AO_reason = CV_SENSOR_BRAKE; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);}   
    
    if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID))
        {
        if ((Modbus.RPM40 < 20) || (Modbus.RPM11 < 20))
            {
            //led_off();
            work_status = AO;         
            Modbus.AO_reason = AO_TOO_LOW_RPM; Modbus_sw.AO_reason = swapshort (Modbus.AO_reason);
            }
        }
    
    Modbus.work_status = work_status; Modbus_sw.work_status = swapfloat (Modbus.work_status);
    if (DINPUT1 == 1) {LED9 = 1;} else  {LED9 = 0;} 
}

*/

/* *****************************************************************************
 End of File
 */



