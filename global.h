#include "define.h"

// ����� ������� �� ��� ����� ��� ������ dma
unsigned char __attribute__((coherent)) buf_tx5[300];
unsigned char __attribute__((coherent)) buf_tx4[300];
unsigned char __attribute__((coherent)) buf_tx3[300];
unsigned char __attribute__((coherent)) buf_tx2[300];
unsigned char __attribute__((coherent)) buf_tx1[300];

// �������
int blink_counter = 0;

// �������� ������ ������
unsigned int U4_speed;
unsigned int U5_speed;
unsigned int U3_speed;
unsigned int U2_speed;
unsigned int U1_speed;

// ���������� �������� ������
unsigned int frame_delay;

// ����� ������� ��� ������� �������
unsigned short help_reset;

// ���� �� ��� ������ ��������
unsigned short help_load;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
union tag_direct
{
    struct
    {
        union
        {
            struct
            {
                unsigned short sensor1; // ������ ������ 1
                unsigned short sensor2; // ������ ������ 2
                unsigned short sensor3; // ������ ������ 3
                unsigned short sensor4; // ������ ������ 4
                unsigned short sensor5; // ������ ������ 5
                unsigned short sensor6; // ������ ������ 6
                unsigned short sensor7; // ������ ������ 7
                unsigned short sensor8; // ������ ������ 8
                float angle_1;          // ���� 1
                float angle_2;          // ���� 2
                float angle_3;          // ���� 3
                float angle_4;          // ���� 4
                float angle_5;          // ���� 5
                float angle_6;          // ���� 6
                float angle_7;          // ���� 7
                float angle_8;          // ���� 8
                float angle_9;          // ���� 9
                float angle_10;         // ���� 10
                float angle_11;         // ���� 11
                float angle_12;         // ���� 12
                unsigned long par1;     // �������� 1
                unsigned long par2;     // �������� 2
                unsigned long par3;     // �������� 3
                unsigned long par4;     // �������� 4
                unsigned long par5;     // �������� 5
                unsigned long par6;     // �������� 6
                unsigned long par7;     // �������� 7
                unsigned long par8;     // �������� 8
                unsigned long par9;     // �������� 9
                unsigned long par10;    // �������� 10

                struct
                {
                    unsigned break_sin1 : 1;      // ��������� DBSKT sin1 ch1: 0 - ��, 1 - ����
                    unsigned break_cos1 : 1;      // ��������� DBSKT cos1 ch1: 0 - ��, 1 - ����
                    unsigned break_sin2 : 1;      // ��������� DBSKT sin2 ch2: 0 - ��, 1 - ����
                    unsigned break_cos2 : 1;      // ��������� DBSKT cos2 ch1: 0 - ��, 1 - ����
                    unsigned break_sens1 : 1;     // ��������� ������� DBSKT ch1: 0 - ��, 1 - ����
                    unsigned break_sens2 : 1;     // ��������� ������� DBSKT ch2: 0 - ��, 1 - ����
                    unsigned coil_1_res_high : 1; // ������������� ������� 1: 0 - ��, 1 - ������� ������� �������������
                    unsigned coil_1_res_low : 1;  // ������������� ������� 1: 0 - ��, 1 - ������� ������ �������������
                    unsigned coil_2_res_high : 1; // ������������� ������� 2: 0 - ��, 1 - ������� ������� �������������
                    unsigned coil_2_res_low : 1;  // ������������� ������� 2: 0 - ��, 1 - ������� ������ �������������
                    unsigned I_1_fault : 1;       // ������ ����������� ������ 1: 0 - ��, 1 - ������
                    unsigned I_2_fault : 1;       // ������ ����������� ������ 2: 0 - ��, 1 - ������
                    unsigned I_in_fault : 1;      // ������ ����������� ������ 2: 0 - ��, 1 - ������
                    unsigned : 19;                // ��������� ����
                };
            };
            unsigned short output[54]; // ������ ��� �������� ������
        };

        union
        {
            struct
            {
                float fl_1;              // ����� � ��������� ������� 1
                float fl_2;              // ����� � ��������� ������� 2
                float fl_3;              // ����� � ��������� ������� 3
                float fl_4;              // ����� � ��������� ������� 4
                float fl_5;              // ����� � ��������� ������� 5
                float fl_6;              // ����� � ��������� ������� 6
                float fl_7;              // ����� � ��������� ������� 7
                unsigned short command1; // ������� 1
                unsigned short command2; // ������� 2
                unsigned short command3; // ������� 3
                unsigned short command4; // ������� 4
                unsigned short command5; // ������� 5
                unsigned short command6; // ������� 6
                unsigned short command7; // ������� 7
                unsigned short command8; // ������� 8

                struct
                {
                    unsigned command_On : 1;       // ������� ���! ��� ����� "Semicrone"
                    unsigned command_Off : 1;      // ������� ����! ��� ����� "Semicrone"
                    unsigned command_Istab_On : 1; // ������� ���! ��� ������� ������������ ����
                    unsigned command_Integ_ON : 1; // ������� ���! ��� ��������� I-����� � PI-��������� (������� ������������ ����)
                    unsigned : 28;                 // ��������� 12 ��� = ���� ��� �������� ���������� Kp (������� ������������ ����)
                };
            };
            unsigned short input[24]; // ������ ��� ������� ������
        };
    };
    unsigned short buf[78];         // �����
} MB, MB_swap, calibr, calibr_swap; // ��������� ��� �������, ������ - 2000 ... 2078, ������ - 0 ... 8
/* ��� ��������� ������������ ����� ����������� (union) ������, ������� ����� ���� ������������ ��� ������ ������� ����� �������� Modbus.
��� �������� ��������� ���� ��� ������ � �������� (sensor1 - sensor8), ����� (angle_1 - angle_12), ���������� (par1 - par10), � ����� ������
(command1 - command8). ����� ����, ��� �������� ������� ��������� (tag_mb_statusBITS), �������������� ��������� ������� � ������� ��� ����������
�������. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct tag_usart
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
    unsigned short hl_err;              // ������ �������� ������.
    unsigned short mbm_status_hl;       // ������ MODBUS �������� ������.
    unsigned short mbm_status_05;       // ������ MODBUS 05.
    unsigned short repeat_05;           // ������ MODBUS 05.
    unsigned short repeat_05_;          // ������ ������ MODBUS 05.
    unsigned short mbm_timeout;         // ����-��� MODBUS.
    unsigned short answer_count;        //

    struct tag_mb_statusBITS
    {
        unsigned modb_mode : 1;        // 1 ��� ��� ������ MODBUS
        unsigned term_mode : 1;        // 1 ��� ��� ������ ���������
        unsigned modb_received : 1;    // ���� ��������� MODBUS
        unsigned modb_transmited : 1;  // ���� �������� MODBUS
        unsigned modb_receiving : 1;   // ���� ������ MODBUS
        unsigned modb_transmiting : 1; // ���� �������� MODBUS
        unsigned tx_mode : 1;          // ����� �������� (USART TX mode)
        unsigned tx_data_rdy : 1;      // ���������� ������ � ��������
        unsigned master_error : 1;     // ������ �������
        unsigned bussy1 : 1;           // ��������� ����
        unsigned bussy2 : 1;           // ��������� ����
        unsigned last_byte : 1;        // ���� ���������� �����
        unsigned byte_missing : 1;     // ���������� �����
        unsigned coll_1 : 1;           // �������� 1
        unsigned coll_2 : 1;           // �������� 2
        unsigned coll_3 : 1;           // �������� 3
        unsigned tx_start : 1;         // ������ ��������
        unsigned master_start : 1;     // ������ �������
        unsigned master_timeout : 1;   // ����-��� �������
        unsigned tm_on : 1;            // ��������� �������
        unsigned device_error : 1;     // ������ ����������
        unsigned crc_error : 1;        // ������ CRC
        unsigned : 10;                 // ��������� ���� (19-32)
    } mb_status;
} usart1, usart2, usart3, usart4, usart5;
/* ��� ��������� tag_usart ������ ��� ���������� � ����������� �������� ������ ����� ��������� USART, � ����� ��� ���������� ����������,
���������� � ���������� MODBUS. ��� ������������ ��� �������� � ��������� ��������� � �������� ������, �������� ��������� �������� ������,
������������ ������ � ���������� ���������� ��������� ������ �������.
���������� ���� � ������� ��������� ������ ���� ��������� ������������ ��������� �������, ����� ��� �������� ��������� �������� ������ (��������,
�������� ������, ������� MODBUS), ������������ ������ (������ MODBUS, ������ �������� ������) � ���������� �������� �������� ������ (��������, ������
MODBUS � ���������). ����� �������, ��� ��������� ������ �������� ���� � ����������� � �������� ������ ������� ����� USART, � ����� � �����������
�������� � ����������� ������ ��������� MODBUS � �������. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct tag_timers_BITS
{
    unsigned bit_1 : 1;   // ������ ��� (1)
    unsigned bit_2 : 1;   // ������ ��� (2)
    unsigned bit_3 : 1;   // ������ ��� (3)
    unsigned bit_4 : 1;   // ��������� ��� (4)
    unsigned bit_5 : 1;   // ����� ��� (5)
    unsigned ch_1 : 1;    // ������ ����� (6)
    unsigned ch_2 : 1;    // ������ ����� (7)
    unsigned ch_3 : 1;    // ������ ����� (8)
    unsigned t_del_1 : 1; // �������� ������� 1 (9)
    unsigned t_del_2 : 1; // �������� ������� 2 (10)
    unsigned t_del_3 : 1; // �������� ������� 3 (11)
    unsigned t_del_4 : 1; // �������� ������� 4 (12)
    unsigned t_del_5 : 1; // �������� ������� 5 (13)
    unsigned t_del_6 : 1; // �������� ������� 6 (14)
    unsigned t_del_7 : 1; // �������� ������� 7 (15)
    unsigned t_del_8 : 1; // �������� ������� 8 (16)
} timer9_bits;            // ����������� ��������� � ������ tag_timers_BITS � �������� ���������� timer9_bits

// ������ ���� ������ ��������� ������������ ����� ��������� ���, ������������ ��� ���������� ��������� � ��������.
// ����� ���� ������ � ����������� ������ �� ����������.
// ��� ��������� ������������ ����� �������� ����������, ������� ����� ���� ������������ ��� ���������� ���������� ��������� � ��������.
// ���������� timer9_bits ������������ ��� ������� � ���� ��������� �� ������ ������ ���������.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ����������� tag_Modbus
union tag_Modbus
{
    // ��������� ��������� ��� �������� ��������� ���������� Modbus
    struct
    {
        // ��������� ����������� ��� �������� ������� ������
        union
        {
            // ��������� ��������� ��� ���������� �������� �������
            struct
            {
                unsigned flap_On : 1;           // ���� �������� ��������
                unsigned start : 1;             // ���� ������ ���������
                unsigned ignit_allow : 1;       // ���������� �� ���������
                unsigned CV_dir_ctrl : 1;       // ���������� ������������ ������� �������
                unsigned PWM_dir_ctrl : 1;      // ���������� ������������ ���
                unsigned ign_ctrl : 1;          // ���������� ����������
                unsigned unlock : 1;            // ���� �������������
                unsigned AO : 1;                // ���� ����������� ������
                unsigned clr_err_cnt : 1;       // ������� �������� ������
                unsigned stop : 1;              // ���� ���������
                unsigned press_mode_int : 1;    // ���������� ����� ��������
                unsigned press_mode_analog : 1; // ���������� ����� ��������
                unsigned deep_on : 1;           // ���� ��������� ������
                unsigned NO : 1;                // ����������������� ���
                unsigned stop_pid_on : 1;       // ��������� PID ��� ���������
                unsigned stop_pid_off : 1;      // ���������� PID ��� ���������
                unsigned forced_pid_on : 1;     // �������������� ��������� PID
                unsigned forced_pid_off : 1;    // �������������� ���������� PID
                unsigned : 14;                  // ����������������� ����
            } bits;                             // ����� ��������� ��������� bits

            unsigned long cmd1; // ������� 1 (4 �����)
        }; // ����� ���������� �����������

        unsigned short num_check_cyl; // ����� ������������ ��������
        unsigned short cyl_mask;      // ����� ��������
        float RPM_set;                // ��������� �������� ���������
        float CV_dir_set;             // ��������� ����������� ������� �������
        float work_status;            // ������ ������ ���
        float RPM11;                  // �������, ���������� ����� ������ 11-�������� �����
        float RPM40;                  // �������, ���������� ����� ������� 40-�������� �����
        float CV_set;                 // ��������� ������� �������
        float CV_pos;                 // ����������� ��������� ������� �������
        float CV_current;             // ����������� ��� �������
        float actual_UOZ;             // ����������� ���� ���������
        unsigned short AO_reason;     // ������� ����������� ������
        unsigned short AO_cyl_num;    // ����� �������� ��� ����������� ������
        unsigned short ADC_CV_pos;    // ��� ������� �������
        unsigned short ADC_CV_curr;   // ��� ���� �������
        unsigned short pulses_11;     // �������� ������ 11
        unsigned short pulses_40;     // �������� ������ 40
        float err_rpm;                // ������ ��������

        // ��������� ����������� ��� �������� �������������� ��������
        union
        {
            // ��������� ��������� ��� ���������� ��������������� ���������
            struct
            {
                unsigned CV_locked : 1;        // ������������ ������ �������
                unsigned press_via_analog : 1; // ���������� ��������� ����� ������
                unsigned CV_magnet_brake : 1;  // ��������� ������ �������
                unsigned CV_sensor_err : 1;    // ������ ������� �������
                unsigned deep_mode : 1;        // �������� �����
                unsigned Protect_unswitch : 1; // ������ �� ����������������� ����������
                unsigned DI1_ctrl : 1;         // ���������� DI1
                unsigned CONTROL1 : 1;         // �������� 1
                unsigned CONTROL2 : 1;         // �������� 2
                unsigned CONTROL3 : 1;         // �������� 3
                unsigned CONTROL4 : 1;         // �������� 4
                unsigned s12 : 1;              // ����������������� ���
                unsigned deep_is_on : 1;       // �������� ����� �������
                unsigned stop_pid : 1;         // ���������� PID
                unsigned miss_sync : 1;        // �������� ������
                unsigned miss_rpm : 1;         // ��������� ������ RPM
                unsigned forced_pid : 1;       // �������������� PID
                unsigned : 15;                 // ����������������� ����
            } status_bits;                     // ����� ��������� ��������� status_bits

            unsigned long statuses; // ������� (4 �����)
        }; // ����� ���������� �����������

        float ign_err_num1; // ������ ��������� �1
        float ign_err_num2; // ������ ��������� �2
    } Modbus_data;          // ����� ��������� Modbus_data
    unsigned short buf[82]; // ����� ������ (164 �����)

} Modbus, Modbus_sw; // ����� ����������� tag_Modbus, � ����� ���������� ���� ����������: Modbus � Modbus_sw

// MB_READ_ MB_WRITE_ 0 ... 80 - ��������� ��� ������ � ������ ������ Modbus
/* ��� ����������� tag_Modbus ������������ ��� �������� ��������� ���������� � �������� Modbus, � ����� ��� ������ � ������� ������.
������ ��������� ���������� ��������� ���� ��� �������� ���������� � ��������� �������, ���������� ���������� � �������� ������. ������ ����
����� ���� ��� ������ � ���� ��������� �������������. ����� ������ ������������ ��� �������� ����������, ������� ����� ���� �������� �� ���������
Modbus. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
union tag_MB_diag
{
    // ��������� ��������� ��� �������� ��������������� ������
    struct
    {
        unsigned short break_low[10];  // ������� ������� ������ �������������� ������� ��� ������� �� 10 ���������
        unsigned short short_low[10];  // ������� ������� ��������� ��������� �������������� ������� ��� ������� �� 10 ���������
        unsigned short break_high[10]; // ������� ������� ������ ��������������� ������� ��� ������� �� 10 ���������
        float discharge_hold[10];      // ���������� ����� �������, ��������������� ��� 10 ���������
        float discharge_middle[10];    // ������� ����� ������� ��� 10 ���������
    } data_struct;                     // ����� ��������� ��������� data_struct

    // ������ ���� ��� �������� ��������������� ������
    unsigned short buf[70]; // ������ ������ ������
} MB_diag, MB_diag_sw;      // ���������� �����������
/* ��� ����������� tag_MB_diag ����� ���������� ��������� ��� �������� ��������������� ������ �������. ��������� ���������
data_struct �������� ��������� ��������������� ��������� ��� ������� �� 10 ��������� ���������. ����� ����, ������ buf ������������
��� �������� ���� ���������� � ���� ������� ����. ����������� ��������� ���������� ������������ ������, ����������� ������ � ���������������
������ ��� ��������� � ��� ������� ������������. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ����������� tag_diag
union tag_diag
{
    // ��������� ��������� ��� �������� ��������������� ������
    struct
    {
        unsigned short break_low[CYLINDERS_NUM];  // ������� ������� ������ �������������� ������� ��� ������� �� 10 ���������
        unsigned short short_low[CYLINDERS_NUM];  // ������� ������� ��������� ��������� �������������� ������� ��� ������� �� 10 ���������
        unsigned short break_high[CYLINDERS_NUM]; // ������� ������� ������ ��������������� ������� ��� ������� �� 10 ���������
        float discharge_hold[CYLINDERS_NUM];      // ���������� ����� �������, ��������������� ��� 10 ���������
        float charge_hold[CYLINDERS_NUM];         // ������� ����� ������� ��� 10 ���������
    } data_struct;                                // ����� ��������� ��������� data_struct

    // ������ ���� ��� �������� ��������������� ������
    unsigned short buf[112]; // ������ ������ ������
} MB_diagn, MB_diagn_sw;     // ���������� �����������
/* ��� ����������� tag_diag ���������� ��������� ��� �������� ��������������� ������ �������. ��������� ��������� data_struct ��������
��������� ��������������� ��������� ��� ������� �� 10 ��������� ���������. ����� ����, ������ buf ������������ ��� �������� ����
���������� � ���� ������� ����. ����������� ��������� ���������� ������������ ������, ����������� ������ � ��������������� ������ ���
��������� � ��� ������� ������������. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ����������� tag_MB_conf
union tag_MB_conf
{
    // ��������� ��������� ��� �������� ���������������� ����������
    struct
    {
        float max_RPM;                      // ������������ �������� �������� ��������� ��� ��������� ���������
        float min_RPM;                      // ����������� �������� �������� ��������� ��� ��������� ���������
        float UOZ_high;                     // ����������� �������� �������� ��������� ��� ���
        float UOZ_low;                      // ������ �������� �������� ��������� ��� ���
        float UOZ_global_shift;             // �������� ���������������� �������� ��� ��� ���� ���������
        float UOZ_RPM_max;                  // �������� ���������, ��� ������� ��� ���������� UOZ_high
        float UOZ_RPM_min;                  // �������� ���������, ��� ������� ��� ���������� UOZ_low
        float discharge_sc_low;             // ����� ������� ��� ����������� ������� ���������� �� ������� SC
        float discharge_br_high;            // ����� ������� ��� ����������� �������� ���������� �� ������� �������� ����������
        float constructive_UOZ;             // �������������� ���� ����� ������������� � ����� ��������� (18 ��������)
        float CV_start_val;                 // ��������� �������� �������� ������� ��� ������� ���������
        float CV_start_spd;                 // �������� �������� ������� �� ���������� ��������
        float CV_open_spd;                  // �������� �������� ������� ��� ������� ��������� �� ��� ���
        float PID_spd;                      // ���, ��� ������� ���������� ������ ��-���������� ���������
        float Ignit_spd;                    // ���, ��� ������� �������� ������ ���������
        float CV_pos_min;                   // ����������� ��� ��� �������
        float CV_pos_max;                   // ������������ ��� ��� �������
        float CV_curr_min;                  // ����������� ��� ��� ���� �������
        float CV_curr_max;                  // ������������ ��� ��� ���� �������
        float CV_curr_scale;                // ��������������� ���� ������� ����� ������������ � ������������� ������
        float CV_KP;                        // ���������������� ����������� ��-���������� �������
        float CV_KD;                        // ���������������� ����������� ��-���������� �������
        float CV_KI;                        // ������������ ����������� ��-���������� �������
        float NUM_ERR_AO;                   // ������
        float KP_mpid;                      // ������
        float KI_mpid;                      // ������
        float KD_mpid;                      // ������
        float Timer_to_PID;                 // ������
        float PID_deadband;                 // ������
        float KP_res_limit;                 // ������
        float CV_check_level;               // ������
        float UOZ_shift_ind[CYLINDERS_NUM]; // ������ ������ ��� ��� ������� ��������
    } data_struct;                          // ����� ��������� ��������� data_struct

    // ������ ���� ��� �������� ���������������� ������
    unsigned short buf[90]; // ������ ������ ������
} MB_conf, MB_sw_conf;      // ���������� �����������
/* ��� ����������� tag_MB_conf ���������� ��������� ��� �������� ��������� ���������������� ���������� �������. ��� ��������
��������� ��������� data_struct, ������� ��������� ������ ���������������� ��������. ����� ����, ������ buf ������������ ���
�������� ���� ���������� � ���� ������� ����. ����������� ��������� ���������� ������������ ������, ����������� ������ � ����������������
������ ��� ��������� � ��� ������� ������������. */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct tag_MOPS
{

    struct
    {

        union
        {

            struct
            {
                unsigned int info[3];                    // ����������������� �������: ��� �������, ������ ��������, ������ �����
                unsigned int status[num_zone_mops];      // ������� ���
                unsigned int hold_status[num_zone_mops]; // ����������� ������� ���
                unsigned int current[num_zone_mops + 1]; // ���� ���
            };
            unsigned int read[num_zone_mops * 3 + 4]; // ������� ������
        };

        union
        {

            struct
            {
                unsigned int command[num_zone_mops]; // ������� ���
                unsigned int type[num_zone_mops];    // ���� ���: �������, �������� � �� � ��� ��
                unsigned int limit1[num_zone_mops];  // ������ ���� - ����� ��� ���� ���
                unsigned int limit2[num_zone_mops];  // ������ ����� - �������� ��� ���� ���
                unsigned int limit3[num_zone_mops];  // ������ �������� - ����� ��� ���� ���
                unsigned int limit4[num_zone_mops];  // ������ ����� - �� ��� ���� ���
                unsigned int timer1[num_zone_mops];  // ������������� ������� ���� ���
                unsigned int timer2[num_zone_mops];
                unsigned int timer3[num_zone_mops];
                unsigned int timer4[num_zone_mops];
            };
            unsigned int write[num_zone_mops * 10];
        };
    };
    unsigned int main_area[num_zone_mops * 13 + 4];
} MOPS, MOPS_swap;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned short DINPUT1;
unsigned short DINPUT2;
unsigned short DINPUT3;
