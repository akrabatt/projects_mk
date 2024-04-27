#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "define.h"
#include "extern.h"

enum {
    INIT = 0,
    STOP, //1
    STOP_READY,
    WAIT_SYNCHRO,
    VC_START_OPN,
    WAIT_IGNITION, //5
    INCREASE_TO_PID,
    SINCRONIZE_PID,
    WORK,
    AO,
    CYL_CONTROL, //10
    CV_CONTROL,
    PWM_CONTROL,
    IGN_CHECK
};


float timer_to_PID;
unsigned int timer_break;

unsigned int ign_delay;
unsigned int tmp_CV_val;
unsigned int cyl_timer;
unsigned int CV_blok_plus;
unsigned int CV_blok_minus;
unsigned short group_cyl_check;

static float M_Int;

void led_off(void) {
    PORTE = LATE & 0xfce0;
    PORTG = LATG & 0x8dff;
    PORTB = LATB & 0xffdf;
    PORTA = LATA & 0xffbe;
}

float mpid_control(float Kp, float Kd, float Ki, unsigned int clearI) {
    static float last_error;
    static float DB[4];
    static int d_count, ii;
    float P;
    float D;
    //static float I;
    static float backPID;
    float PID;
    float setpoint, plus_lim, minus_lim;
    float currentpoint;

    if (clearI == 0) {
        M_Int = 0;
    }

    setpoint = Modbus.RPM_set;
    currentpoint = Modbus.RPM40;
    plus_lim = MB_conf.KP_res_limit;
    minus_lim = MB_conf.KP_res_limit * (-1.0);

    P = setpoint - currentpoint;
    if (P > plus_lim) P = plus_lim;
    if (P < minus_lim) P = minus_lim;
    if (((currentpoint - setpoint) > INT_MCLR) || ((setpoint - currentpoint) > INT_MCLR)) {
        M_Int = M_Int + Ki * (setpoint - currentpoint) / MREG_FREQ;
    }
    if (M_Int > 100.0) {
        M_Int = 100.0;
    }
    if (M_Int < 0.1) {
        M_Int = 0.1;
    }

    D = ((setpoint - currentpoint) - last_error) * (MREG_FREQ);

    last_error = setpoint - currentpoint;
    PID = (Kp * P) + M_Int + (Kd * D);
    if (PID > 95.0) {
        PID = 95.0;
    }
    if (PID <= 0.01) {
        PID = 0.01;
    }

    if (CV_blok_regul == 1) {
        PID = backPID;
        return PID;
    } else {
        backPID = PID;
        return PID;
    }
}

unsigned int CV_pos_err;
unsigned int CV_curr_err;

void CV_err_ctrl(void) {
    if (Modbus.ADC_CV_pos < (COORD_MIN - 400)) {
        CV_pos_err = 1;
        Modbus.CV_sensor_err = 1;
    } else {
        CV_pos_err = 0;
        Modbus.CV_sensor_err = 0;
    }
    if (Modbus.CV_current < 0.08) {
        CV_curr_err = 1;
        Modbus.CV_magnet_brake = 1;
    } else {
        CV_curr_err = 0;
        Modbus.CV_magnet_brake = 0;
    }
}

void reset_cond(void) {
    Modbus.CV_set = 0;
    Modbus_sw.CV_set = 0;
    Modbus.RPM_set = 0;
    Modbus_sw.RPM_set = 0;
    ign_alowed = 0;
    sync_status = 0;
}

void reset_unlock(void) {
    unsigned int cc;
    IGN_ON = 1;
    Modbus.CV_set = 0;
    Modbus.RPM_set = 0;
    Modbus_sw.CV_set = 0;
    Modbus_sw.RPM_set = 0;
    Modbus.cmd1 = 0;
    Modbus_sw.cmd1 = 0;
    Modbus.statuses = 0;
    Modbus_sw.statuses = 0;
    TAP_OFF;
    ign_alowed = 0;
    led_off();

    Modbus.actual_UOZ = 0;
    Modbus_sw.actual_UOZ = 0;

    Modbus.AO_reason = 0;
    Modbus_sw.AO_reason = 0;
    Modbus.AO_cyl_num = 0;
    Modbus_sw.AO_cyl_num = 0;
    Modbus.num_check_cyl = 0;
    Modbus_sw.num_check_cyl = 0;
    Modbus.err_rpm = 0;
    Modbus_sw.err_rpm = 0;
    charge_fail = 0;
    total_err_count1 = 0;
    total_err_count2 = 0;
    //    clr_charge_err ();
    for (cc = 0; cc < CYLINDERS_NUM; cc++) {
        dir_sc_low[cc] = 0;
        dir_sc_low[cc] = 0;
        dir_br_low[cc] = 0;
        dir_br_low[cc] = 0;
        dir_br_high[cc] = 0;
        dir_br_high[cc] = 0;
    }
}

void reset_AO(void) {
    Modbus.CV_set = 0;
    Modbus.RPM_set = 0;
    Modbus_sw.CV_set = 0;
    Modbus_sw.RPM_set = 0;
    ign_alowed = 0;
    charge_fail = 0;
    //    clr_charge_err ();
}

void chek_CV_block(void) {
    if ((Modbus.CV_set - Modbus.CV_pos) > 5.0) {
        CV_blok_plus++;
    }
    if ((Modbus.CV_pos - Modbus.CV_set) > 5.0) {
        CV_blok_minus++;
    }
    if (((Modbus.CV_pos - Modbus.CV_set) < 1.0) && ((Modbus.CV_set - Modbus.CV_pos) < 1.0)) {
        CV_blok_minus = 0;
        CV_blok_plus = 0;
    }
    if ((CV_blok_minus > 100) || (CV_blok_plus > 100)) {
        CV_blok_regul = 1;
        Modbus.CV_locked = 1;
    } else {
        CV_blok_regul = 0;
        Modbus.CV_locked = 0;
    }
    Modbus_sw.statuses = swaplong(Modbus.statuses);
}

void clear_err_cnt(void) {
    unsigned short cc;
    for (cc = 0; cc < 10; cc++) {
        MB_diagn.short_low [cc] = 0;
        MB_diagn_sw.short_low [cc] = 0;
        dir_sc_low[cc] = 0;
        MB_diagn.short_low [cc] = 0;
        MB_diagn_sw.short_low [cc] = 0;
        dir_sc_low[cc] = 0;
        MB_diagn.break_low [cc] = 0;
        MB_diagn_sw.break_low [cc] = 0;
        dir_br_low[cc] = 0;
        MB_diagn.break_low [cc] = 0;
        MB_diagn_sw.break_low [cc] = 0;
        dir_br_low[cc] = 0;
        MB_diagn.break_high [cc] = 0;
        MB_diagn_sw.break_high [cc] = 0;
        dir_br_high[cc] = 0;
        MB_diagn.break_high [cc] = 0;
        MB_diagn_sw.break_high [cc] = 0;
        dir_br_high[cc] = 0;
    }
}

void output_reason(unsigned short reason) {
    Modbus.AO_reason = reason;
    Modbus_sw.AO_reason = swapshort(Modbus.AO_reason);
}

void clr_command(void) {
    Modbus.cmd1 ^= Modbus.cmd1;
    Modbus_sw.cmd1 = swaplong(Modbus.cmd1);
}

void main_control(void) {
    float CV_set_back;
    float CV_check_curr;
    static float tmp_CV, ttt;
    unsigned short PWM;
    float KP_reg, KD_reg, KI_reg;

    if (delay_before_start < 150) {
        delay_before_start++;
        return;
    }

    KP_reg = MB_conf.KP_mpid;
    KD_reg = MB_conf.KD_mpid;
    KI_reg = MB_conf.KI_mpid;

    led_off();
    CV_check_curr = MB_conf.CV_check_level;
    PWM = CV_check_curr / 100.0 * OC_MAX;
    if (PWM == 0) {
        PWM = 100;
    }
    if (PWM >= (OC_MAX + 1)) {
        PWM = 100;
    }

    if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID) || (work_status == WORK) || (work_status == IGN_CHECK)) {
        IGN_ON = 0;
        DO_1 = 1;
        ign_alowed = 1;
    } else {
        DO_1 = 0;
        IGN_ON = 1;
    }
    CV_err_ctrl();
    switch (work_status) {
        case INIT:
        {
            work_status = STOP;
            reset_unlock();
            break;
        }

        case STOP:
        {
            OC3RS = PWM;
            if ((CV_pos_err == 0) && (CV_curr_err == 0)) {
                work_status = STOP_READY;
            }
            reset_cond();
            LED_STOP_ON;
            if ((Modbus.CV_sensor_err == 1) || (Modbus.CV_magnet_brake == 1)) //LED_FAIL_ON;  
                break;
        }

        case STOP_READY:
        {
            OC3RS = PWM;
            CV_err_ctrl();
            if ((CV_pos_err == 1) || (CV_curr_err == 1)) {
                work_status = STOP;
            } // контроль тестового тока ТРК
            if (Modbus.CV_dir_ctrl == 1) {
                work_status = CV_CONTROL;
                clr_command();
            } // режим проверки ТРК
            if (Modbus.PWM_dir_ctrl == 1) {
                work_status = PWM_CONTROL;
                clr_command();
            } // режим проверки ШИМ
            if (Modbus.ign_ctrl == 1) {
                work_status = IGN_CHECK;
                clr_command();
            } // режим прверки цепей искрообразования
            if (Modbus.start == 1) {
                work_status = WAIT_SYNCHRO;
                clr_command();
            }
            LED_STOP_ON; //LED_READY_ON;   LAMP_READY_ON; 
            break;
        }

        case WAIT_SYNCHRO:
        {
            if (Modbus.NO == 1) {
                work_status = STOP;
                clr_command();
            }
            if ((ch_1.rpm > MB_conf.Ignit_spd) && (sync_status == 1)) {
                work_status = VC_START_OPN;
            }
            break;
        }

        case VC_START_OPN:
        {
            if (Modbus.NO == 1) {
                work_status = STOP;
                clr_command();
            }
            Modbus.CV_set += MB_conf.CV_start_spd / 100;
            Modbus_sw.CV_set = swapfloat(Modbus.CV_set);
            if ((Modbus.CV_set >= MB_conf.CV_start_val) || (Modbus.CV_pos >= MB_conf.CV_start_val)) {
                work_status = WAIT_IGNITION;
                ign_delay = 0;
            }
            Modbus.RPM_set = MB_conf.PID_spd;
            Modbus_sw.RPM_set = swapfloat(Modbus.RPM_set);
            timer_break = 0;
            LED_SYNC_ON;
            break;
        }

        case WAIT_IGNITION:
        {
            LED_WIGN_ON;
            if (Modbus.NO == 1) {
                work_status = STOP;
                clr_command();
            }
            if (DINPUT1 == 1) {
                IGN_ON = 0;
                ign_alowed = 1;
                timer_to_PID = 0;
                ign_delay++;
            }
            if (ign_delay >= 200) {
                if ((CTRL1 == 0) && (CTRL2 == 0)) {
                    work_status = INCREASE_TO_PID;
                    ign_delay = 0;
                    M_Int = Modbus.CV_set;
                } else {
                    output_reason(AO_NO_CHARGE);
                    work_status = AO;
                }
            }
            if ((Modbus.RPM40 == 0) || (Modbus.RPM11 == 0)) {
                timer_break += 10;
                if (timer_break >= 10000) {
                    timer_break = 0;
                    work_status = STOP;
                }
            }
            break;
        }

        case INCREASE_TO_PID:
        {
            if (Modbus.NO == 1) {
                work_status = STOP;
                clr_command();
            }
            if (DINPUT1 == 0) {
                output_reason(AO_MISS_IGN_SIGN);
                work_status = AO;
            } // снят сигнал разрешение зажигания
            if (Modbus.RPM40 < (MB_conf.PID_spd - 5.0)) {
                if (Modbus.CV_set < 50.0) {
                    Modbus.CV_set += MB_conf.CV_open_spd / 100.0;
                } // ограничение линейного открытия ТРК до уровня 50%
            } else {
                M_Int = Modbus.CV_set;
                tmp_CV_val = Modbus.CV_set;
                work_status = SINCRONIZE_PID;
                ttt = mpid_control(0, 0, 0.12, 0);
            }
            Modbus_sw.CV_set = swapfloat(Modbus.CV_set);
            if (timer_to_PID >= MB_conf.Timer_to_PID) {
                output_reason(AO_START_ERROR);
                work_status = AO;
            }
            LED_IGN_ON;
            break;
        }

        case SINCRONIZE_PID:
        {
            if (Modbus.NO == 1) {
                work_status = STOP;
                clr_command();
            }
            if (DINPUT1 == 0) {
                output_reason(AO_MISS_IGN_SIGN);
                work_status = AO;
            }
            timer_to_PID += 0.01;
            tmp_CV = mpid_control(0, 0, 0.12, 1);
            if (tmp_CV_val < tmp_CV) {
                tmp_CV_val = tmp_CV;
                Modbus.CV_set = tmp_CV;
            }
            Modbus_sw.CV_set = swapfloat(Modbus.CV_set);
            if (Modbus.RPM40 >= (MB_conf.PID_spd - 5.0)) {
                M_Int = Modbus.CV_set;
                work_status = WORK;
            }
            if (timer_to_PID >= MB_conf.Timer_to_PID) {
                output_reason(AO_START_ERROR);
                work_status = AO;
            }
            LED_IGN_ON;
            break;
        }

        case WORK:
        {
            if (Modbus.NO == 1) {
                work_status = STOP;
                clr_command();
            }
            if (DINPUT1 == 0) {
                output_reason(AO_MISS_IGN_SIGN);
                work_status = AO;
            } // снят сигнал разрешение зажигания
            if (Modbus.stop_pid == 0) {
                tmp_CV = mpid_control(KP_reg, KD_reg, KI_reg, 1);
            }
            Modbus.CV_set = tmp_CV;
            Modbus_sw.CV_set = swapfloat(Modbus.CV_set);
            if ((Modbus.RPM40 < MB_conf.min_RPM) || (Modbus.RPM11 < MB_conf.min_RPM)) {
                work_status = AO;
                if (Modbus.RPM40 < Modbus.RPM11) {
                    Modbus.err_rpm = Modbus.RPM40;
                    Modbus_sw.err_rpm = swapfloat(Modbus.err_rpm);
                } else {
                    Modbus.err_rpm = Modbus.RPM11;
                    Modbus_sw.err_rpm = swapfloat(Modbus.err_rpm);
                }
                output_reason(AO_TOO_LOW_RPM);
            }
            Modbus.deep_mode = 0;
            LED_IGN = 1;
            break;
        }

        case AO:
        {
            if (Modbus.unlock == 1) {
                work_status = STOP;
                clr_command();
                reset_unlock();
            }
            reset_AO(); //сброс заданий оборотов и полжения ТРК
            LED_AO_ON;
            break;
        }

        case CV_CONTROL:
        {
            if (Modbus.stop == 1) {
                work_status = STOP;
                clr_command();
            }
            if (Modbus.CV_dir_set == 0) {
                Modbus.CV_dir_set = 1;
            }
            Modbus.CV_set = Modbus.CV_dir_set;
            Modbus_sw.CV_set = swapfloat(Modbus.CV_set);
            break;
        }

        case PWM_CONTROL:
        {
            if (Modbus.stop == 1) {
                work_status = STOP;
                clr_command();
            }
            if (Modbus.CV_dir_set == 0) {
                Modbus.CV_dir_set = 1;
            }
            OC3RS = Modbus.CV_dir_set / 100.0 * OC_MAX;
            break;
        }

        case IGN_CHECK:
        {
            if (Modbus.stop == 1) {
                work_status = STOP;
                clr_command();
            }
            unsigned int ct;
            if (Modbus.num_check_cyl == 11) {
                ct = 5;
            } else {
                ct = 10;
            }
            if (cyl_timer >= ct) {
                cyl_timer = 0;
                LED_IGN ^= 1;
                //            if ((Modbus.num_check_cyl > 0) && (Modbus.num_check_cyl < 11)) {ignit_check (Modbus.num_check_cyl) ; }     // выборочная проверка цилиндров цилиндр выбирается по модбасу
                if (Modbus.num_check_cyl == 11) // групповая проверка цилиндров - ключается командой "9" в качестве номера цилиндра
                    //                { ignit_check (group_cyl_check ) ; group_cyl_check +=1; if (group_cyl_check > 10) {group_cyl_check =1;} }   
                    //            }
                    cyl_timer++;
                break;
            }

            default:
            {
                work_status = INIT;
            }
        }

            if (charge_fail == 1) {
                charge_fail = 0;
                output_reason(AO_NO_CHARGE);
                work_status = AO;
            } // нет заряда конденсаторов, номер цепи контроля - в регистре номера цилиндра

            if (hold_current >= 3000) { // превышение тока электромагнита ТРК
                work_status = AO;
                output_reason(AO_CV_CURR_ERROR);
                Modbus.AO_cyl_num = hold_current;
                Modbus_sw.AO_cyl_num = swapshort(Modbus.AO_cyl_num);
                hold_current = 0;
            }

            if (Modbus.AO == 1) {
                work_status = AO;
                clr_command();
                output_reason(AO_SAU_COMMAND);
            } // команда АО от САУ

            if (Modbus.stop_pid_on == 1) {
                Modbus.stop_pid = 1;
                clr_command();
            } //включение блокировки ПИД
            if (Modbus.stop_pid_off == 1) {
                Modbus.stop_pid = 0;
                clr_command();
            } //выключение блокировки ПИД

            if (Modbus.forced_pid_on == 1) {
                Modbus.forced_pid = 1;
                clr_command();
            } //включение форсирования ПИД
            if (Modbus.forced_pid_off == 1) {
                Modbus.forced_pid = 0;
                clr_command();
            } //выключение форсирования ПИД

            if ((Modbus.RPM40 > MB_conf.max_RPM) || (Modbus.RPM11 > MB_conf.max_RPM)) //превышение частоты вращения 
            {
                work_status = AO;
                if (Modbus.RPM40 > Modbus.RPM11) {
                    Modbus.err_rpm = Modbus.RPM40;
                    Modbus_sw.err_rpm = swapfloat(Modbus.err_rpm);
                } else {
                    Modbus.err_rpm = Modbus.RPM11;
                    Modbus_sw.err_rpm = swapfloat(Modbus.err_rpm);
                }
                output_reason(AO_TOO_HIGH_RPM);
            }

            if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID) || (work_status == WORK) ||
                    (work_status == WAIT_SYNCHRO) || (work_status == VC_START_OPN) || (work_status == WAIT_IGNITION)) {
                if ((CV_pos_err == 1)) {
                    work_status = AO;
                    output_reason(CV_SENSOR_BRAKE);
                } // обрыв датчика положения ТРК
            }

            if (DINPUT2 == 0) {
                Modbus.Protect_unswitch = 0;
            } else {
                Modbus.Protect_unswitch = 1;
            } // отображение вх дискрет по модбасу
            if (DINPUT1 == 1) {
                Modbus.DI1_ctrl = 1;
                LED10_ON;
            } else {
                Modbus.DI1_ctrl = 0;
                LED10_OFF;
            } // отображение вх дискрет по модбасу

            if (CTRL1 == 0) {
                Modbus.CONTROL1 = 1;
            } else {
                Modbus.CONTROL1 = 0;
            } // отображение заряда конденсаторов по модбасу
            if (CTRL2 == 0) {
                Modbus.CONTROL2 = 1;
            } else {
                Modbus.CONTROL2 = 0;
            } // отображение заряда конденсаторов по модбасу 

            if (total_err_count2 > (MB_conf.NUM_ERR_AO + 1)) {
                work_status = AO;
                output_reason(AO_5CYL_ERROR_EVEN);
            } // ошибка зажигания в 5 цилиндрах подряд четная группа
            if (total_err_count1 > (MB_conf.NUM_ERR_AO + 1)) {
                work_status = AO;
                output_reason(AO_5CYL_ERROR_ODD);
            } // ошибка зажигания в 5 цилиндрах подряд нечетная группа

            //    if (total_err_count2 >= 5) {work_status = AO;  output_reason (AO_5CYL_ERROR_EVEN);}               // ошибка зажигания в 5 цилиндрах подряд четная группа
            //  if (total_err_count1 >= 5) {work_status = AO;  output_reason (AO_5CYL_ERROR_ODD);}                  // ошибка зажигания в 5 цилиндрах подряд нечетная группа


            if (Modbus.clr_err_cnt) {
                clear_err_cnt();
                clr_command();
            } // очистка счетчиков ошибок

            if ((work_status == INIT) || (work_status == AO)) {
                OC3RS = 2;
                TAP_OFF;
            } else {
                TAP_ON;
            } // отклюение  реле питания электромагнита при АО и инициализации

            if ((work_status == INCREASE_TO_PID) || (work_status == SINCRONIZE_PID) || (work_status == WORK) ||
                    (work_status == WAIT_SYNCHRO) || (work_status == VC_START_OPN) || (work_status == WAIT_IGNITION) ||
                    (work_status == CV_CONTROL)) {
                CV_regul_on = 1;
            }
            else {
                CV_regul_on = 0;
            }

            chek_CV_block();

            Modbus.ign_err_num1 = total_err_count1;
            Modbus_sw.ign_err_num1 = swapfloat(Modbus.ign_err_num1);
            Modbus.ign_err_num2 = total_err_count2;
            Modbus_sw.ign_err_num2 = swapfloat(Modbus.ign_err_num2);
            Modbus.work_status = work_status;
            Modbus_sw.work_status = swapfloat(Modbus.work_status);
            Modbus_sw.statuses = swaplong(Modbus.statuses);
            clr_command(); // добавлено 7.06.2021
    }





    /* *****************************************************************************
     End of File
     */
