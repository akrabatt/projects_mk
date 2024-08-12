#ifndef GLOBAL_H
#define GLOBAL_H

#include "define.h"

// buffers for uart
unsigned char __attribute__((coherent)) buf_tx5[300];
unsigned char __attribute__((coherent)) buf_tx4[300];
unsigned char __attribute__((coherent)) buf_tx3[300];
unsigned char __attribute__((coherent)) buf_tx2[300];
unsigned char __attribute__((coherent)) buf_tx1[300];

// speed for uart
unsigned short U1_speed;
unsigned short U2_speed;
unsigned short U3_speed;
unsigned short U4_speed;
unsigned short U5_speed;

// help vars
unsigned short help_strobe;
unsigned short help_reset;
unsigned short help_load;

union tag_direct
{

    struct
    {

        union
        {

            struct
            {
                unsigned short sensor1; // data channel 1
                unsigned short sensor2; // data channel 2
                unsigned short sensor3; // data channel 3
                unsigned short sensor4; // data channel 4
                unsigned short sensor5; // data channel 5
                unsigned short sensor6; // data channel 6
                unsigned short sensor7; //  7
                unsigned short sensor8; //  8
                float angle_1;          //  9
                float angle_2;          //  11
                float angle_3;          //  13
                float angle_4;          //  15
                float angle_5;          //  17
                float angle_6;          //  19
                float angle_7;          //  21
                float angle_8;          //  23
                float angle_9;          //  25
                float angle_10;         //  27
                float angle_11;         //  29
                float angle_12;         //  31
                unsigned long par1;     //  33
                unsigned long par2;     //  35
                unsigned long par3;     //  37
                unsigned long par4;     //  39
                unsigned long par5;     //  41
                unsigned long par6;     //  43
                unsigned long par7;     //  45
                unsigned long par8;     //  47
                unsigned long par9;     //  49
                unsigned long par10;    //  51

                struct
                {
                    unsigned break_sin1 : 1;      // Status DBSKT sin1 ch1: 0 - OK, 1 - NOK
                    unsigned break_cos1 : 1;      // Status DBSKT sos1 ch1: 0 - OK, 1 - NOK
                    unsigned break_sin2 : 1;      // Status DBSKT sin2 ch2: 0 - OK, 1 - NOK
                    unsigned break_cos2 : 1;      // Status DBSKT cos2 ch1: 0 - OK, 1 - NOK
                    unsigned break_sens1 : 1;     // Status DBSKT sensor ch1: 0 - OK, 1 - NOK
                    unsigned break_sens2 : 1;     // Status DBSKT sensor ch2: 0 - OK, 1 - NOK
                    unsigned coil_1_res_high : 1; // Coil 1 resistance: 0 - OK, 1 - too high resistance
                    unsigned coil_1_res_low : 1;  // Coil 1 resistance: 0 - OK, 1 - too low resistance
                    unsigned coil_2_res_high : 1; // Coil 2 resistance: 0 - OK, 1 - too high resistance
                    unsigned coil_2_res_low : 1;  // Coil 2 resistance: 0 - OK, 1 - too low resistance
                    unsigned I_1_fault : 1;       // analog out 1 fault: 0 - OK, 1 - fault
                    unsigned I_2_fault : 1;       // analog out 2 fault: 0 - OK, 1 - fault
                    unsigned I_in_fault : 1;      // analog out 2 fault: 0 - OK, 1 - fault
                    unsigned : 19;
                };
            };
            unsigned short output[54];
        };

        union
        {

            struct
            {
                float fl_1;              //  55
                float fl_2;              //  57
                float fl_3;              //  59
                float fl_4;              //  61
                float fl_5;              //  63
                float fl_6;              //  65
                float fl_7;              //  67
                unsigned short command1; //  69
                unsigned short command2; //  70
                unsigned short command3; //  71
                unsigned short command4; //  72
                unsigned short command5; //  73
                unsigned short command6; //  74
                unsigned short command7; //  75
                unsigned short command8; //  76

                struct
                {
                    unsigned command_On : 1;       //  Command ON! "Semicrone" unit
                    unsigned command_Off : 1;      //  Command OFF! "Semicrone" unit
                    unsigned command_Istab_On : 1; // Comman ON current stabilization function
                    unsigned command_Integ_ON : 1; // Comman ON I-unit into the PI-regulator (current current stabilization function)
                    unsigned : 28;                 // Last 12 bits = byte for value of Kp regulator (current current stabilization function)
                };
            };
            unsigned short input[24];
        };
    };
    unsigned short buf[78];
} MB, MB_swap, calibr, calibr_swap; // MODBUS_READ_ = 2000 ... 2078   MODBUS_WRITE = 0 ... 8

// struct full usart
struct tag_usart
{
    unsigned char out_buffer[OUT_SIZE]; //
    unsigned char in_buffer[IN_SIZE];   //
    unsigned short out_buffer_count;    //
    unsigned short in_buffer_count;     //
    unsigned short in_buffer_count2;    //
    unsigned short number_send;         //
    unsigned short port_type;           //
    unsigned short mbm_status;          //
    unsigned short mbm_err;             //
    unsigned short mbm_err16;           //
    unsigned short mbm_status_hl;       //
    unsigned short mbm_status16;        //
    unsigned short repeat_05;           //
    unsigned short repeat_05_;          //
    unsigned short mbm_timeout_counter; //
    unsigned short answer_count;        //

    struct tag_mb_statusBITS
    {
        unsigned modb_mode : 1;           //
        unsigned term_mode : 1;           //
        unsigned modb_received : 1;       //
        unsigned modb_transmited : 1;     //
        unsigned modb_receiving : 1;      //
        unsigned modb_transmiting : 1;    //
        unsigned tx_mode : 1;             //
        unsigned mbm_data_rdy : 1;        //
        unsigned master_error : 1;        //
        unsigned bussy1 : 1;              //
        unsigned bussy2 : 1;              //
        unsigned last_byte : 1;           //
        unsigned byte_missing : 1;        //
        unsigned coll_1 : 1;              //
        unsigned coll_2 : 1;              //
        unsigned coll_3 : 1;              //
        unsigned start16 : 1;             //
        unsigned master_start : 1;        //
        unsigned master_timeout_flag : 1; //
        unsigned tm_on : 1;               //
        unsigned device_error : 1;        //
        unsigned crc_error : 1;           //
        unsigned : 10;                    //
    } mb_status;
} usart1, usart2, usart3, usart4, usart5;

// struct full usart master
struct tag_usartm
{
    unsigned char out_buffer[OUT_SIZE]; //
    unsigned char in_buffer[IN_SIZE];   //
    unsigned short out_buffer_count;    //
    unsigned short in_buffer_count;     //
    unsigned short in_buffer_count2;    //
    unsigned short number_send;         //
    unsigned short mbm_status03;        //
    unsigned short mbm_status16;        //
    unsigned short mbm03_tm_err;        //
    unsigned short mbm03_c01_err;       //
    unsigned short mbm03_c02_err;       //
    unsigned short mbm03_c03_err;       //
    unsigned short mbm03_crc_err;       //
    unsigned short mbm16_tm_err;        //
    unsigned short mbm16_c01_err;       //
    unsigned short mbm16_c02_err;       //
    unsigned short mbm16_c03_err;       //
    unsigned short mbm16_crc_err;       //
    unsigned short repeat_05;           //
    unsigned short repeat_05_;          //
    unsigned short mbm_timeout_counter; //
    unsigned short answer_count;        //
    unsigned short mbm16_counter_start; //

    struct stag_mb_statusBITS
    {
        unsigned modb_mode : 1;           // 1
        unsigned term_mode : 1;           // 2
        unsigned modb_received : 1;       // 3
        unsigned modb_transmited : 1;     // 4
        unsigned modb_receiving : 1;      // 5
        unsigned modb_transmiting : 1;    // 6
        unsigned tx_mode : 1;             // 7
        unsigned mbm_data_rdy : 1;        // 8
        unsigned master_error : 1;        // 9
        unsigned bussy1 : 1;              // 10
        unsigned bussy2 : 1;              // 11
        unsigned last_byte : 1;           // 12
        unsigned byte_missing : 1;        // 13
        unsigned coll_1 : 1;              // 14
        unsigned coll_2 : 1;              // 15
        unsigned coll_3 : 1;              // 16
        unsigned start16 : 1;             // 17
        unsigned master_start : 1;        // 18
        unsigned master_timeout_flag : 1; // 19
        unsigned tm_on : 1;               // 20
        unsigned device_error : 1;        // 21
        unsigned crc_error : 1;           // 22
        unsigned : 10;                    // (23-32)
    } mb_status;
} usart1m, usart2m, usart3m, usart4m, usart5m;

// help var for strob and sync
unsigned short mbm_sync;

// struct full mops
union tag_mops
{

    struct
    {

        union
        {

            struct
            {
                unsigned short info[3];                //
                unsigned short status[num_zones];      //
                unsigned short hold_status[num_zones]; //
                unsigned short current[num_zones + 1]; //
            };
            unsigned short read[num_zones * 3 + 4]; //
        };

        union
        {

            struct
            {
                unsigned short command[num_zones]; //
                unsigned short type[num_zones];    //
                unsigned short limit1[num_zones];  //
                unsigned short limit2[num_zones];  //
                unsigned short limit3[num_zones];  //
                unsigned short limit4[num_zones];  //
                unsigned short timer1[num_zones];  //
                unsigned short timer2[num_zones];
                unsigned short timer3[num_zones];
                unsigned short timer4[num_zones];
                unsigned short stat_hysteresis;
            };
            unsigned short write[num_zones * 10 + 1];
        };
        unsigned short break_err;
        unsigned short norma_err;
        unsigned short att_err;
        unsigned short fire_err;
        unsigned short short_err;
        unsigned short current_err;
        unsigned short timeout_err;
        unsigned short crc_err;
        unsigned short coll_1_err;
        unsigned short coll_2_err;
        unsigned short coll_3_err;
    };
    unsigned short main_area[num_zones * 13 + 16];
};

// short struct mops
union tag_mops_short
{
    struct
    {
        union
        {
            struct
            {
                unsigned short info[3];                //
                unsigned short status[num_zones];      //
                unsigned short hold_status[num_zones]; //
                unsigned short current[num_zones + 1]; //
            };
            unsigned short read[num_zones * 3 + 4]; //
        };
        union
        {
            struct
            {
                unsigned short command[num_zones];
                unsigned short type[num_zones]; //
            };
            unsigned short write[num_zones * 2];
        };
        unsigned short break_err;
        unsigned short norma_err;
        unsigned short att_err;
        unsigned short fire_err;
        unsigned short short_err;
        unsigned short current_err;
        unsigned short timeout_err;
        unsigned short crc_err;
        unsigned short coll_1_err;
        unsigned short coll_2_err;
        unsigned short coll_3_err;
    };
    unsigned short main_area[num_zones * 6 + 15];
};

// full arrs for mops
union tag_mops MOPS_arr[10];
union tag_mops MOPS_arr_sw[10];

// short arrs for mops
union tag_mops_short MOPS_S_arr[10];
union tag_mops_short MOPS_S_arr_sw[10];

// full struct for mups
union tag_mups
{

    struct
    {

        union
        {

            struct
            {
                unsigned short info[3];         // 1
                unsigned short Int_Voltage;     // 4
                unsigned short Ch_State[4];     // 5
                unsigned short Ch_Cmd[4];       // 9
                unsigned short Ch_Strategy[4];  // 13
                unsigned short Ch_Res[4];       // 17
                unsigned short Ch_Current[4];   // 21 //
                unsigned short Ch_P1[4];        // 25
                unsigned short Ch_P2[4];        // 29
                unsigned short Ch_P3[4];        // 33
                unsigned short Ch_P4[4];        // 37
                unsigned short Blinc_param1[2]; // 41
                unsigned short Blinc_param2[2]; // 43
                unsigned short Blinc_param3[2]; // 45
                unsigned short Blinc_param4[2]; // 47
                signed short Res_Coef[4];       // 49
                signed short Cur_ZCoef[4];      // 53
                signed short Cur_MaxCoef[4];    // 57
                unsigned short LineChDelay;     // 61
                unsigned short ADC[16];         // 62
                unsigned short relay;           // 78
                unsigned short AD_RES[4];       // 79
                float AD_F_RES[4];              // 83 ... 90    //
                unsigned short timeout_err;     // 91
                unsigned short crc_err;         // 92
                unsigned short coll_1_err;      // 93
                unsigned short coll_2_err;      // 94
                unsigned short coll_3_err;      // 95
            };
            unsigned short read[96];
        };
    };
};

// short struct for mups
union tag_mups_short
{

    union
    {

        struct
        {
            unsigned short info[3];        // 1
            unsigned short Int_Voltage;    // 4
            unsigned short Ch_State[4];    // 5
            unsigned short Ch_Cmd[4];      // 9
            unsigned short Ch_Strategy[4]; // 13
            unsigned short Ch_Res[4];      // 17
            unsigned short Ch_Current[4];  // 21
            unsigned short timeout_err;    // 25
            unsigned short crc_err;        // 26
            unsigned short coll_1_err;     // 27
            unsigned short coll_2_err;     // 28
            unsigned short coll_3_err;     // 29
        };
        unsigned short read[29]; // выровнять
    };
    unsigned short main_area[29];
} mups_short;

// full arrs for mups
union tag_mups MUPS_arr[10];
union tag_mups MUPS_arr_sw[10];

// short arrs for mups
union tag_mups_short MUPS_S_arr[10];
union tag_mups_short MUPS_S_arr_sw[10];

// mups strategy for all chanels
unsigned short mups_strategy[4];
unsigned short mups_1_strategy[4] = {0x0100, 0x0100, 0x0100, 0x0100};
unsigned short mups_2_strategy[4] = {0x0200, 0x0200, 0x0200, 0x0200};
unsigned short mups_3_strategy[4] = {0x0300, 0x0300, 0x0300, 0x0300};

// strategy buffer
unsigned short mups_strategy_sep[4];

// relay buffer
// relay buffer
unsigned short relay_toggle[4];

// flag for a low-level function mbm_16
unsigned short mbm_16_end_flag;

// flag for the order of high-level functions
unsigned short mbm_fun_in_work = 0;

// help vars for mops&mups
unsigned short mops_stat;
unsigned short mups_stat;
unsigned short mops_done;
unsigned short mups_done;
unsigned short mops_num;
unsigned short mups_num;

// modbus struct
// modbus struct
union tag_Modbus
{

    struct
    {

        union
        {

            struct
            {
                unsigned flap_On : 1;           // 1
                unsigned start : 1;             // 2
                unsigned ignit_allow : 1;       // 4
                unsigned CV_dir_ctrl : 1;       // 8
                unsigned PWM_dir_ctrl : 1;      // 16
                unsigned ign_ctrl : 1;          // 32
                unsigned unlock : 1;            // 64
                unsigned AO : 1;                // 128
                unsigned clr_err_cnt : 1;       // 256
                unsigned stop : 1;              // 512
                unsigned press_mode_int : 1;    // 1024
                unsigned press_mode_analog : 1; // 2048
                unsigned deep_on : 1;           // 4096
                unsigned NO : 1;                // 8192
                unsigned stop_pid_on : 1;       // 16384
                unsigned stop_pid_off : 1;      // 32768
                unsigned forced_pid_on : 1;     // 65536
                unsigned forced_pid_off : 1;    // 131072
                unsigned : 14;                  // Last 8 bits = byte for value of Kp regulator (current current stabilization function)
            };
            unsigned long cmd1; // 1
        };
        unsigned short num_check_cyl; // 3
        unsigned short cyl_mask;      // 4
        float RPM_set;                // 5      setting the ngine speed
        float CV_dir_set;             // 7      setting the ngine speed
        float work_status;            // 9      status BUD
        float RPM11;                  // 11      rpm, measured via sinchro 11-teeth-channel
        float RPM40;                  // 13      rpm, measured via rpm 40-teeth-channel
        float CV_set;                 // 15      fuel valve setting
        float CV_pos;                 // 17      actual fuel valve position
        float CV_current;             // 19      actual valve currrent
        float actual_UOZ;             // 21      ignition angle
        unsigned short AO_reason;     // 23
        unsigned short AO_cyl_num;    // 24
        unsigned short ADC_CV_pos;    // 25
        unsigned short ADC_CV_curr;   // 26
        unsigned short pulses_11;     // 27
        unsigned short pulses_40;     // 28
        float err_rpm;                // 29

        union
        {

            struct
            {
                unsigned CV_locked : 1;        // 1
                unsigned press_via_analog : 1; // 2
                unsigned CV_magnet_brake : 1;  // 4
                unsigned CV_sensor_err : 1;    // 8
                unsigned deep_mode : 1;        // 16 Command ON
                unsigned Protect_unswitch : 1; // 32 Command ON
                unsigned DI1_ctrl : 1;         // 64 Command ON
                unsigned CONTROL1 : 1;         // 128
                unsigned CONTROL2 : 1;         // 256
                unsigned CONTROL3 : 1;         // 512
                unsigned CONTROL4 : 1;         // 1024
                unsigned s12 : 1;              // 2048
                unsigned deep_is_on : 1;       // 4096
                unsigned stop_pid : 1;         // 8192
                unsigned miss_sync : 1;        // 16384
                unsigned miss_rpm : 1;         // 32768
                unsigned forced_pid : 1;       // 65536
                unsigned : 15;                 // Last 16 bits = byte for value of Kp regulator (current current stabilization function)
            };
            unsigned long statuses; // 31
        };
        float ign_err_num1; // 33
        float ign_err_num2; // 35
    };
    unsigned short buf[82]; // MB_READ_ MB_WRITE_  0 ... 80
} Modbus, Modbus_sw;

//
union tag_MB_diag
{

    struct
    {
        unsigned short break_low[10];  //      event counter of break low voltage wire for every of 10 cylinders
        unsigned short short_low[10];  //      event counter of short circuit low voltage wire for every of 10 cylinders
        unsigned short break_high[10]; //      event counter of break high voltage wire for every of 10 cylinders
        float discharge_hold[10];      //  -   momental discharge time captured for 10 cylinders
        float discharge_middle[10];    //  -   middle discharge time capture for 10 cylinders
    };
    unsigned short buf[70];
} MB_diag, MB_diag_sw; // MB_DIAGN_READ_ MB_DIAGN_WRITE_  200 ... 270

//
union tag_diag
{

    struct
    {
        unsigned short break_low[CYLINDERS_NUM];  //      event counter of break low voltage wire for every of 10 cylinders
        unsigned short short_low[CYLINDERS_NUM];  //      event counter of short circuit low voltage wire for every of 10 cylinders
        unsigned short break_high[CYLINDERS_NUM]; //      event counter of break high voltage wire for every of 10 cylinders
        float discharge_hold[CYLINDERS_NUM];      //  -   momental discharge time captured for 10 cylinders
        float charge_hold[CYLINDERS_NUM];         //  -   middle discharge time capture for 10 cylinders
    };
    unsigned short buf[112];
} MB_diagn, MB_diagn_sw; // MB_DIAGN_READ_ MB_DIAGN_WRITE_  200 ... 270

//
unsigned short dir_sc_low[CYLINDERS_NUM];
unsigned short dir_br_low[CYLINDERS_NUM];
unsigned short dir_br_high[CYLINDERS_NUM];
unsigned short bit_sc_low;
unsigned short bit_br_low;
unsigned short bit_br_high;

// struct for stand
union tag_stand
{

    struct
    {
        unsigned short active_mops[10];      // 1
        unsigned short active_mups[10];      // 11
        unsigned short mops_timeout_err[10]; // 21
        unsigned short mops_crc_err[10];     // 31
        unsigned short mops_coll_1_err[10];  // 41
        unsigned short mops_coll_2_err[10];  // 51
        unsigned short mops_coll_3_err[10];  // 61
        unsigned short mups_timeout_err[10]; // 71
        unsigned short mups_crc_err[10];     // 81
        unsigned short mups_coll_1_err[10];  // 91
        unsigned short mups_coll_2_err[10];  // 101
        unsigned short mups_coll_3_err[10];  // 111
        unsigned short break_err[10];         // 121
        unsigned short norma_err[10];        // 131
        unsigned short att_err[10];          // 141
        unsigned short fire_err[10];         // 151
        unsigned short short_err[10];        // 161
        unsigned short current_err[10];      // 171
    };
    //    unsigned short buf [168];
    unsigned short buf[180];
} Stand, Stand_sw;

// help vars
unsigned short DINPUT1;
unsigned short DINPUT2;
unsigned short DINPUT3;

//530 board arr for mods

                                            //===normal===//
// 1-4 normal
unsigned short _530_board_normal_mops[8] = {NORMAL_530_1, NORMAL_530_2, NORMAL_530_1, NORMAL_530_2, 
                                            NORMAL_530_1, NORMAL_530_2, NORMAL_530_1, NORMAL_530_2};
// 1 - normal, 2 - normal, 3 - reley on starting from 4th, 4 - reley on
unsigned short _530_board_normal_start_reley_4_mops[8] = {NORMAL_530_1, NORMAL_530_2, NORMAL_530_1, NORMAL_530_2,
                                                          SW_RELEY_ON_START_4_530_1, SW_RELEY_ON_START_4_530_2, SW_RELEY_ON_530_1, SW_RELEY_ON_530_2};

                                            //===short current===//
//1-4 short current
unsigned short _530_board_short_current_mops[8] = {SW_SHORT_CURRENT_530_1, SW_SHORT_CURRENT_530_2, SW_SHORT_CURRENT_530_1, SW_SHORT_CURRENT_530_2, 
                                                   SW_SHORT_CURRENT_530_1, SW_SHORT_CURRENT_530_2, SW_SHORT_CURRENT_530_1, SW_SHORT_CURRENT_530_2};
// 1 - sc, 2 - sc, 3 - reley on starting from 4th, 4 - reley on
unsigned short _530_board_short_current_start_reley_4_mops[8] = {SW_SHORT_CURRENT_530_1, SW_SHORT_CURRENT_530_2, SW_SHORT_CURRENT_530_1, SW_SHORT_CURRENT_530_2,
                                                                 SW_RELEY_ON_START_4_530_1, SW_RELEY_ON_START_4_530_2, SW_RELEY_ON_530_1, SW_RELEY_ON_530_2};

                                                //===fire===//
// 1-4 fire
unsigned short _530_board_fire_mops[8] = {SW_FIRE_530_1, SW_FIRE_530_2, SW_FIRE_530_1, SW_FIRE_530_2, 
                                          SW_FIRE_530_1, SW_FIRE_530_2, SW_FIRE_530_1, SW_FIRE_530_2};
// 1 - fire, 2 - fire, 3 - reley on starting from 4th, 4 - reley on
unsigned short _530_board_fire_start_reley_4_mops[8] = {SW_FIRE_530_1, SW_FIRE_530_2, SW_FIRE_530_1, SW_FIRE_530_2, 
                                                        SW_RELEY_ON_START_4_530_1, SW_RELEY_ON_START_4_530_2, SW_RELEY_ON_530_1, SW_RELEY_ON_530_2};

                                            //===attantion===//
// 1-4 attantion
unsigned short _530_board_attantion_mops[8] = {SW_ATTANTION_530_1, SW_ATTANTION_530_2, SW_ATTANTION_530_1, SW_ATTANTION_530_2, 
                                               SW_ATTANTION_530_1, SW_ATTANTION_530_2, SW_ATTANTION_530_1, SW_ATTANTION_530_2};
// 1 - attantion, 2 - attantion, 3 - reley on starting from 4th, 4 - reley on
unsigned short _530_board_attantion_start_reley_4_mops[8] = {SW_ATTANTION_530_1, SW_ATTANTION_530_2, SW_ATTANTION_530_1, SW_ATTANTION_530_2, 
                                                             SW_RELEY_ON_START_4_530_1, SW_RELEY_ON_START_4_530_2, SW_RELEY_ON_530_1, SW_RELEY_ON_530_2};

                                        //===end on with 84 reley===//
// 1 - reley on, 2 - end 84 reley on, 3 - none, 4 - none
unsigned short _530_board_84_reley_on_mops[8] = {SW_RELEY_ON_530_1, SW_RELEY_ON_530_2, SW_RELEY_ON_END_84_530_1, SW_RELEY_ON_END_84_530_2,
                                                 NONE_530, NONE_530, NONE_530, NONE_530};

                                    //===just reley on without strategy===//
// 1 - none, 2 - none, 3 - reley on starting from 4th, 4 - reley on
unsigned short _530_board_only_reley_on_start_4_mops[8] = {NONE_530, NONE_530, NONE_530, NONE_530,
                                                           SW_RELEY_ON_START_4_530_1, SW_RELEY_ON_START_4_530_2, SW_RELEY_ON_530_1, SW_RELEY_ON_530_2};


                                            //===main array===//
unsigned short _530_board_mode_mops[8];


//var for function _1_sec
unsigned short _1_sec_counter;
short start_1_sec_timer; 

// var for function _var_sec
unsigned short _var_sec_conunter;
short start_var_sec_timer;

//var for function _500_msec
unsigned short _500_msec_counter;


// mops statement struct, show mops statements
struct tag_mops_stand_statment
{
    struct 
    {
        unsigned short mops_online       : 1;            // is there connection with module
        unsigned short mops_online_err   : 1;            // connection error
        unsigned short mops_offline      : 1;            // mops not connected special
        unsigned short mops_operable     : 1;            // is the module working properly or not
        unsigned short mops_not_operable : 1;            // the module is not working properly
        unsigned short : 11;
    }mops_statment;
    unsigned short mops_current_ch_status[8];                   // buffer for the value of the states
    struct
    {
        unsigned short mops_ch_err_break[8];                   // break(1)
        unsigned short mops_ch_err_normal[8];                  // normal(2)
        unsigned short mops_ch_err_attantion[8];               // attantion(4)
        unsigned short mops_ch_err_fire[8];                    // fire(5)
        unsigned short mops_ch_err_sc[8];                      // short current(6)
    }mops_ch_statement;
}mops_stand_statment;

//struct mups array
struct tag_mops_stand_statment MOPS_statment[10];

//union for configuration stand
union tag_conf_stand
{
    struct
    {
       unsigned short start_check_mops;
       unsigned short not_usable[99];
    }stand_commands;
    unsigned short comm_buff[100];
}conf_stand, conf_stand_sw;     // conf_stand - normal data

#endif // GLOBAL_H