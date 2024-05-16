#include "define.h"

// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ dma
unsigned char __attribute__((coherent)) buf_tx5[300];
unsigned char __attribute__((coherent)) buf_tx4[300];
unsigned char __attribute__((coherent)) buf_tx3[300];
unsigned char __attribute__((coherent)) buf_tx2[300];
unsigned char __attribute__((coherent)) buf_tx1[300];

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
int blink_counter = 0;

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
unsigned int U4_speed;
unsigned int U5_speed;
unsigned int U3_speed;
unsigned int U2_speed;
unsigned int U1_speed;

// пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
unsigned int frame_delay;

// пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
unsigned short help_reset;

// пїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
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
} MB, MB_swap, calibr, calibr_swap; // ???????? ?????? MODBUS_READ_ = 2000 ... 2078   MODBUS_WRITE = 0 ... 8
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct tag_usart
{
    unsigned char out_buffer[OUT_SIZE]; // Массив буфера для исходящих данных (отправляемые данные).
    unsigned char in_buffer[IN_SIZE];   // Массив буфера для входящих данных (принимаемые данные).
    unsigned short out_buffer_count;    // Счетчик числа байт в буфере исходящих данных.
    unsigned short in_buffer_count;     // Счетчик числа байт в буфере входящих данных.
    unsigned short in_buffer_count2;    // Дополнительный счетчик числа байт в буфере входящих данных (второй счетчик).
    unsigned short number_send;         // Количество байт для отправки.
    unsigned short port_type;           // Тип порта.
    unsigned short mbm_status;          // Статус MODBUS.
    unsigned short mbm_err;             // Ошибка MODBUS.
    unsigned short hl_err;              // Ошибка высокого уровня.
    unsigned short mbm_status_hl;       // Статус MODBUS высокого уровня.
    unsigned short mbm_status_05;       // Статус MODBUS 05.
    unsigned short repeat_05;           // Повтор MODBUS 05.
    unsigned short repeat_05_;          // Другой повтор MODBUS 05.
    unsigned short mbm_timeout;         // Тайм-аут MODBUS.
    unsigned short answer_count;        //

    struct tag_mb_statusBITS
    {
        unsigned modb_mode : 1;        // 1 бит для режима MODBUS
        unsigned term_mode : 1;        // 1 бит для режима терминала
        unsigned modb_received : 1;    // Флаг получения MODBUS
        unsigned modb_transmited : 1;  // Флаг передачи MODBUS
        unsigned modb_receiving : 1;   // Флаг приема MODBUS
        unsigned modb_transmiting : 1; // Флаг отправки MODBUS
        unsigned tx_mode : 1;          // Режим передачи (USART TX mode)
        unsigned tx_data_rdy : 1;      // Готовность данных к передаче
        unsigned master_error : 1;     // Ошибка мастера
        unsigned bussy1 : 1;           // Резервное поле
        unsigned bussy2 : 1;           // Резервное поле
        unsigned last_byte : 1;        // Флаг последнего байта
        unsigned byte_missing : 1;     // Отсутствие байта
        unsigned coll_1 : 1;           // Коллизия 1
        unsigned coll_2 : 1;           // Коллизия 2
        unsigned coll_3 : 1;           // Коллизия 3
        unsigned tx_start : 1;         // Начало передачи
        unsigned master_start : 1;     // Начало мастера
        unsigned master_timeout : 1;   // Тайм-аут мастера
        unsigned tm_on : 1;            // Включение таймера
        unsigned device_error : 1;     // Ошибка устройства
        unsigned crc_error : 1;        // Ошибка CRC
        unsigned : 10;                 // Резервные биты (19-32)
    } mb_status;
} usart1, usart2, usart3, usart4, usart5;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern struct tag_timers_BITS
{
    unsigned bit_1 : 1;   // 1
    unsigned bit_2 : 1;   // 2
    unsigned bit_3 : 1;   // 3
    unsigned bit_4 : 1;   // 4
    unsigned bit_5 : 1;   // 5
    unsigned ch_1 : 1;    // 6
    unsigned ch_2 : 1;    // 7
    unsigned ch_3 : 1;    // 8
    unsigned t_del_1 : 1; // 9
    unsigned t_del_2 : 1; // 10
    unsigned t_del_3 : 1; // 11
    unsigned t_del_4 : 1; // 12
    unsigned t_del_5 : 1; // 13
    unsigned t_del_6 : 1; // 14
    unsigned t_del_7 : 1; // 15
    unsigned t_del_8 : 1; // 16
} timer9_bits;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
union tag_Modbus
{

    struct
    {

        union
        {

            struct
            {
                unsigned flap_On : 1;           
                unsigned start : 1;             
                unsigned ignit_allow : 1;       
                unsigned CV_dir_ctrl : 1;       
                unsigned PWM_dir_ctrl : 1;      
                unsigned ign_ctrl : 1;          
                unsigned unlock : 1;            
                unsigned AO : 1;                
                unsigned clr_err_cnt : 1;       
                unsigned stop : 1;              
                unsigned press_mode_int : 1;    
                unsigned press_mode_analog : 1; 
                unsigned deep_on : 1;           
                unsigned NO : 1;                
                unsigned stop_pid_on : 1;       
                unsigned stop_pid_off : 1;      
                unsigned forced_pid_on : 1;     
                unsigned forced_pid_off : 1;    
                unsigned : 14;                  
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
                unsigned press_via_analog : 1; // 2 1 - пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ; 0 - пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                unsigned CV_magnet_brake : 1;  // 4 пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned CV_sensor_err : 1;    // 8 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned deep_mode : 1;        // 16 Command ON
                unsigned Protect_unswitch : 1; // 32 Command ON
                unsigned DI1_ctrl : 1;         // 64 Command ON
                unsigned CONTROL1 : 1;         // 128
                unsigned CONTROL2 : 1;         // 256
                unsigned CONTROL3 : 1;         // 512
                unsigned CONTROL4 : 1;         // 1024
                unsigned s12 : 1;              // 2048 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                unsigned deep_is_on : 1;       // 4096 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                unsigned stop_pid : 1;         // 8192 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                unsigned miss_sync : 1;        // 16384 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                unsigned miss_rpm : 1;         // 32768 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                unsigned forced_pid : 1;       // 65536 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned : 15;                 // Last 16 bits = byte for value of Kp regulator (current current stabilization function)
            };
            unsigned long statuses; // 31
        };
        float ign_err_num1; // 33
        float ign_err_num2; // 35
    };
    unsigned short buf[82]; // MB_READ_ MB_WRITE_  0 ... 80
} Modbus, Modbus_sw;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
union tag_MB_conf
{

    struct
    {
        float max_RPM;                      // 1     max speed of engine RPM for emergecy stop
        float min_RPM;                      // 3     min speed of engine RPM for emergecy stop
        float UOZ_high;                     // 5     UOZ nominal speed of engine
        float UOZ_low;                      // 7     UOZ low speed of engine
        float UOZ_global_shift;             // 9     main UOZ correction for all cylinders
        float UOZ_RPM_max;                  // 11    enginae speed when UOZ bekomes UOZ_high
        float UOZ_RPM_min;                  // 13    enginae speed when UOZ bekomes UOZ_low
        float discharge_sc_low;             // 15    discharge time for detection SC low voltage wire
        float discharge_br_high;            // 17    discharge time for detection break high voltage wire
        float constructive_UOZ;             // 19    constructive angle sinchro point and ignition point (18 degreece)
        float CV_start_val;                 // 21    start value of valve opening during the engine start
        float CV_start_spd;                 // 23    speed of valve opening to start value
        float CV_open_spd;                  // 25    speed of valve opening during the engine start to PID RPM
        float PID_spd;                      // 27    RPM when starts the engine PI regulator
        float Ignit_spd;                    // 29    RPM when ignition start is possible
        float CV_pos_min;                   // 31    min valve adc code
        float CV_pos_max;                   // 33    max valve adc code
        float CV_curr_min;                  // 35    min valve current adc code
        float CV_curr_max;                  // 37    max valve current adc code
        float CV_curr_scale;                // 39    valve current scale between min and max codes
        float CV_KP;                        // 41
        float CV_KD;                        // 43
        float CV_KI;                        // 45
        float NUM_ERR_AO;                   // 47    reserve
        float KP_mpid;                      // 49    reserve
        float KI_mpid;                      // 51    reserve
        float KD_mpid;                      // 53    reserve
        float Timer_to_PID;                 // 55    reserve
        float PID_deadband;                 // 57    reserve
        float KP_res_limit;                 // 59    reserve
        float CV_check_level;               // 61    reserve
        float UOZ_shift_ind[CYLINDERS_NUM]; // 63 - 82    пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ  пїЅпїЅпїЅпїЅпїЅ
    };
    //    unsigned short buf [168];
    unsigned short buf[90];
} MB_conf, MB_sw_conf;
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
                unsigned int info[3];                    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ: пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
                unsigned int status[num_zone_mops];      // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int hold_status[num_zone_mops]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int current[num_zone_mops + 1]; // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
            };
            unsigned int read[num_zone_mops * 3 + 4]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
        };

        union
        {

            struct
            {
                unsigned int command[num_zone_mops]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int type[num_zone_mops];    // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ: пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅ пїЅ пїЅпїЅпїЅ пїЅпїЅ
                unsigned int limit1[num_zone_mops];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int limit2[num_zone_mops];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int limit3[num_zone_mops];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int limit4[num_zone_mops];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ - пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                unsigned int timer1[num_zone_mops];  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
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
