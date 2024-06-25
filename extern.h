
#include "define.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    extern unsigned char __attribute__((coherent)) buf_tx5[300];
    extern unsigned char __attribute__((coherent)) buf_tx4[300];
    extern unsigned char __attribute__((coherent)) buf_tx3[300];
    extern unsigned char __attribute__((coherent)) buf_tx2[300];
    extern unsigned char __attribute__((coherent)) buf_tx1[300];

    extern float swapfloat(float data);
    extern unsigned long swaplong(unsigned long data);
    extern unsigned short swapshort(unsigned short data);

    extern unsigned long U4_speed;
    extern unsigned long U5_speed;

    extern unsigned short help_strobe;
    extern unsigned short help_reset;
    extern unsigned short help_load;

    extern union tag_direct
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
    } MB, MB_swap, calibr, calibr_swap; // ???????? ?????? 2000 - 2078 (READ / WRITE)

    extern struct tag_usart
    {
        unsigned char out_buffer[OUT_SIZE]; // ������ ������ ��� ��������� ������ (������������ ������).
        unsigned char in_buffer[IN_SIZE];   // ������ ������ ��� �������� ������ (����������� ������).
        unsigned short out_buffer_count;    // ������� ����� ���� � ������ ��������� ������.
        unsigned short in_buffer_count;     // ������� ����� ���� � ������ �������� ������.
        unsigned short in_buffer_count2;    // �������������� ������� ����� ���� � ������ �������� ������ (������ �������).
        unsigned short number_send;         // ���������� ���� ��� ��������.
        unsigned short port_type;           // ��� �����.
        unsigned short mbm_status;          // ������ MODBUS.
        unsigned short mbm_err;             // ������ MODBUS.
        unsigned short mbm_err16;           // ������ 16 �������
        unsigned short mbm_status_hl;       // ������ MODBUS �������� ������.
        unsigned short mbm_status16;        // ������ MODBUS 16 �������.
        unsigned short repeat_05;           // ������ MODBUS 05.
        unsigned short repeat_05_;          // ������ ������ MODBUS 05.
        unsigned short mbm_timeout_counter; // ����-��� ������� MODBUS. //
        unsigned short answer_count;        //

        struct tag_mb_statusBITS
        {
            unsigned modb_mode : 1;           // 1 ��� ��� ������ MODBUS
            unsigned term_mode : 1;           // 1 ��� ��� ������ ���������
            unsigned modb_received : 1;       // ���� ��������� MODBUS
            unsigned modb_transmited : 1;     // ���� �������� MODBUS
            unsigned modb_receiving : 1;      // ���� ������ MODBUS
            unsigned modb_transmiting : 1;    // ���� �������� MODBUS
            unsigned tx_mode : 1;             // ����� �������� (USART TX mode)
            unsigned mbm_data_rdy : 1;        // ���������� ������ � ��������
            unsigned master_error : 1;        // ������ �������
            unsigned bussy1 : 1;              // ��������� ����
            unsigned bussy2 : 1;              // ��������� ����
            unsigned last_byte : 1;           // ���� ���������� �����
            unsigned byte_missing : 1;        // ���������� �����
            unsigned coll_1 : 1;              // �������� 1
            unsigned coll_2 : 1;              // �������� 2
            unsigned coll_3 : 1;              // �������� 3
            unsigned start16 : 1;             // ������ ��������
            unsigned master_start : 1;        // ������ �������
            unsigned master_timeout_flag : 1; // ���� ������ ����-����
            unsigned tm_on : 1;               // ��������� �������
            unsigned device_error : 1;        // ������ ����������
            unsigned crc_error : 1;           // ������ CRC
            unsigned : 10;                    // ��������� ���� (19-32)
        } mb_status;
    } usart1, usart2, usart3, usart4, usart5;

    extern struct tag_usartm
    {
        unsigned char out_buffer[OUT_SIZE]; // ������ ������ ��� ��������� ������ (������������ ������).
        unsigned char in_buffer[IN_SIZE];   // ������ ������ ��� �������� ������ (����������� ������).
        unsigned short out_buffer_count;    // ������� ����� ���� � ������ ��������� ������.
        unsigned short in_buffer_count;     // ������� ����� ���� � ������ �������� ������.
        unsigned short in_buffer_count2;    // �������������� ������� ����� ���� � ������ �������� ������ (������ �������).
        unsigned short number_send;         // ���������� ���� ��� ��������.
        unsigned short mbm_status03;        // ������ MODBUS.
        unsigned short mbm_status16;        // ������ MODBUS 16 �������.
        unsigned short mbm03_tm_err;        // ������� ������ �������� ������� 3
        unsigned short mbm03_c01_err;       // ������� ������ �������� 1 ������� 3
        unsigned short mbm03_c02_err;       // ������� ������ �������� 2 ������� 3
        unsigned short mbm03_c03_err;       // ������� ������ �������� 3 ������� 3
        unsigned short mbm03_crc_err;       // ������� ������ CRC16 ������� 3
        unsigned short mbm16_tm_err;        // ������� ������ �������� ������� 16
        unsigned short mbm16_c01_err;       // ������� ������ �������� 1 ������� 16
        unsigned short mbm16_c02_err;       // ������� ������ �������� 2 ������� 16
        unsigned short mbm16_c03_err;       // ������� ������ �������� 3 ������� 16
        unsigned short mbm16_crc_err;       // ������� ������ CRC16 ������� 16
        unsigned short repeat_05;           // ������ MODBUS 05.
        unsigned short repeat_05_;          // ������ ������ MODBUS 05.
        unsigned short mbm_timeout_counter; // ����-��� ������� MODBUS. //
        unsigned short answer_count;        //

        struct stag_mb_statusBITS
        {
            unsigned modb_mode : 1;           // 1 ��� ��� ������ MODBUS
            unsigned term_mode : 1;           // 1 ��� ��� ������ ���������
            unsigned modb_received : 1;       // ���� ��������� MODBUS
            unsigned modb_transmited : 1;     // ���� �������� MODBUS
            unsigned modb_receiving : 1;      // ���� ������ MODBUS
            unsigned modb_transmiting : 1;    // ���� �������� MODBUS
            unsigned tx_mode : 1;             // ����� �������� (USART TX mode) ���������� ��� ���
            unsigned mbm_data_rdy : 1;        // ���������� ������ � ��������
            unsigned master_error : 1;        // ������ �������
            unsigned bussy1 : 1;              // ��������� ����
            unsigned bussy2 : 1;              // ��������� ����
            unsigned last_byte : 1;           // ���� ���������� �����
            unsigned byte_missing : 1;        // ���������� �����
            unsigned coll_1 : 1;              // �������� 1
            unsigned coll_2 : 1;              // �������� 2
            unsigned coll_3 : 1;              // �������� 3
            unsigned start16 : 1;             // ������ ��������
            unsigned master_start : 1;        // ������ �������
            unsigned master_timeout_flag : 1; // ���� ������ ����-����
            unsigned tm_on : 1;               // ��������� �������
            unsigned device_error : 1;        // ������ ����������
            unsigned crc_error : 1;           // ������ CRC
            unsigned : 10;                    // ��������� ���� (19-32)
        } mb_status;
    } usart1m, usart2m, usart3m, usart4m, usart5m;

    extern unsigned short mbm_sync;

    union tag_mops
    {
        struct
        {
            union
            {
                struct
                {
                    unsigned short info[3];                // ����������������� �������: ��� �������, ������ ��������, ������ �����
                    unsigned short status[num_zones];      // ������� ���
                    unsigned short hold_status[num_zones]; // ����������� ������� ���
                    unsigned short current[num_zones + 1]; // ���� ���
                };
                unsigned short read[num_zones * 3 + 4]; // ������� ������
            };
            union
            {
                struct
                {
                    unsigned short command[num_zones]; // ������� ���
                    unsigned short type[num_zones];    // ���� ���: �������, �������� � �� � ��� ��
                    unsigned short limit1[num_zones];  // ������ ���� - ����� ��� ���� ���
                    unsigned short limit2[num_zones];  // ������ ����� - �������� ��� ���� ���
                    unsigned short limit3[num_zones];  // ������ �������� - ����� ��� ���� ���
                    unsigned short limit4[num_zones];  // ������ ����� - �� ��� ���� ���
                    unsigned short timer1[num_zones];  // ������������� ������� ���� ���
                    unsigned short timer2[num_zones];
                    unsigned short timer3[num_zones];
                    unsigned short timer4[num_zones];
                    unsigned short stat_hysteresis;
                };
                unsigned short write[num_zones * 10 + 1];
            };
            unsigned short beak_err;
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

    extern union tag_mops MOPS_arr[10];
    extern union tag_mops MOPS_arr_sw[10];
    
    

    extern unsigned short mops_stat;
    extern unsigned short mups_stat;
    extern unsigned short mops_done;
    extern unsigned short mups_done;
    extern unsigned short mops_num;
    extern unsigned short mups_num;

    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************

    extern union tag_Modbus
    {
        struct
        {
            union
            {
                struct
                {
                    unsigned flap_On : 1;           // 1
                    unsigned start : 1;             // 2 ������� ����
                    unsigned ignit_allow : 1;       // 4 Comman ON current stabilization function
                    unsigned CV_dir_ctrl : 1;       // 8 ����� ������� ���������� ���
                    unsigned PWM_dir_ctrl : 1;      // 16 ����� ������� ���������� ���
                    unsigned ign_ctrl : 1;          // 32 ����� �������� ���������
                    unsigned unlock : 1;            // 64 ������������
                    unsigned AO : 1;                // 128 ������� ���������� ��������
                    unsigned clr_err_cnt : 1;       // 256 ������� ��������� ������
                    unsigned stop : 1;              // 512 ������� ���� - ����� �� ��������������� �������
                    unsigned press_mode_int : 1;    // 1024 �������� �� ����������
                    unsigned press_mode_analog : 1; // 2048 �������� �� �������
                    unsigned deep_on : 1;           // 4096 �������� ������������
                    unsigned NO : 1;                // 8192 ���������� �������
                    unsigned stop_pid_on : 1;       // 16384 ������������ ���-����������
                    unsigned stop_pid_off : 1;      // 32768 ��������� ���-����������
                    unsigned forced_pid_on : 1;     // 65536 ��������� �������������� ���-����������
                    unsigned forced_pid_off : 1;    // 131072 ���������� �������������� ���-����������
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
            unsigned short pulses_40;     // 28	���������� ��������� �� ������ �������� �� ���� ������ �� ������ �������������
            float err_rpm;                // 29
            union
            {
                struct
                {
                    unsigned CV_locked : 1;        // 1 "�����������" ���
                    unsigned press_via_analog : 1; // 2 1 - ������ �� ����������� �������; 0 - ������ �� ����������
                    unsigned CV_magnet_brake : 1;  // 4 ����� �������������� ���
                    unsigned CV_sensor_err : 1;    // 8 ��������������� ������� ��������� ���
                    unsigned deep_mode : 1;        // 16 Command ON
                    unsigned Protect_unswitch : 1; // 32 Command ON
                    unsigned DI1_ctrl : 1;         // 64 Command ON
                    unsigned CONTROL1 : 1;         // 128
                    unsigned CONTROL2 : 1;         // 256
                    unsigned CONTROL3 : 1;         // 512
                    unsigned CONTROL4 : 1;         // 1024
                    unsigned s12 : 1;              // 2048 �������� �� �������
                    unsigned deep_is_on : 1;       // 4096 �������� ������������
                    unsigned stop_pid : 1;         // 8192 �������� ���-���������
                    unsigned miss_sync : 1;        // 16384 �������� ������ �������������
                    unsigned miss_rpm : 1;         // 32768 �������� ������ ��������
                    unsigned forced_pid : 1;       // 65536 ������� ������������� ���
                    unsigned : 15;                 // Last 16 bits = byte for value of Kp regulator (current current stabilization function)
                };
                unsigned long statuses; // 31
            };
            float ign_err_num1; // 33
            float ign_err_num2; // 35
        };
        unsigned short buf[82]; // MB_READ_ MB_WRITE_  0 ... 80
    } Modbus, Modbus_sw;

    extern union tag_MB_diag
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

    extern union tag_diag
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
    } MB_diagn, MB_diagn_sw; // MB_DIAGN_READ_ MB_DIAGN_WRITE_  200 ... 270  ��������������� ������

    extern unsigned short dir_sc_low[CYLINDERS_NUM];
    extern unsigned short dir_br_low[CYLINDERS_NUM];
    extern unsigned short dir_br_high[CYLINDERS_NUM];
    extern unsigned short bit_sc_low;
    extern unsigned short bit_br_low;
    extern unsigned short bit_br_high;

    extern union tag_stand
    {
        struct
        {
            unsigned short active_mops[10];      // 1 ���������� �������� ����
            unsigned short active_mups[10];      // 11 ���������� �������� ����
            unsigned short mops_timeout_err[10]; // 21
            unsigned short mops_crc_err[10];     // 31 ���������� �������� ����
            unsigned short mops_coll_1_err[10];  // 41 ���������� �������� ����
            unsigned short mops_coll_2_err[10];  // 51 ���������� �������� ����
            unsigned short mops_coll_3_err[10];  // 61 ���������� �������� ����
            unsigned short mups_timeout_err[10]; // 71
            unsigned short mups_crc_err[10];     // 81 ���������� �������� ����
            unsigned short mups_coll_1_err[10];  // 91 ���������� �������� ����
            unsigned short mups_coll_2_err[10];  // 101 ���������� �������� ����
            unsigned short mups_coll_3_err[10];  // 111 ���������� �������� ����
            unsigned short beak_err[10];         // 121 ���������� �������� ����
            unsigned short norma_err[10];        // 131 ���������� �������� ����
            unsigned short att_err[10];          // 141 ���������� �������� ����
            unsigned short fire_err[10];         // 151 ���������� �������� ����
            unsigned short short_err[10];        // 161 ���������� �������� ����
            unsigned short current_err[10];      // 171 ���������� �������� ����
        };
        //    unsigned short buf [168];
        unsigned short buf[180];
    } Stand, Stand_sw;

    extern unsigned short DINPUT1;
    extern unsigned short DINPUT2;
    extern unsigned short DINPUT3;

    extern union tag_mups
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
                    unsigned short Ch_Current[4];   // 21
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
                    float AD_F_RES[4];              // 83 ... 86
                };
                unsigned short read[num_zones * 3 + 20];
            };
            union
            {
                //      struct {
                //        unsigned short command [num_zones];
                //        unsigned short type [num_zones];
                //                               };
                unsigned short write[num_zones * 26];
            };
        };

        unsigned short main_area[350];
    } uMBusWork, test_mups;
    
    extern union tag_mups MUPS_arr[10];
    extern union tag_mups MUPS_arr_sw[10];

#ifdef __cplusplus
}
#endif

/* *****************************************************************************
 End of File
 */
