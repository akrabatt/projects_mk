
#include "define.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C"
{
#endif

    unsigned char __attribute__((coherent)) buf_tx5[300];
    unsigned char __attribute__((coherent)) buf_tx4[300];
    unsigned char __attribute__((coherent)) buf_tx3[300];
    unsigned char __attribute__((coherent)) buf_tx2[300];
    unsigned char __attribute__((coherent)) buf_tx1[300];

    unsigned short U1_speed;
    unsigned short U2_speed;
    unsigned short U3_speed;
    unsigned short U4_speed;
    unsigned short U5_speed;

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
    } MB, MB_swap, calibr, calibr_swap; // ???????? ?????? MODBUS_READ_ = 2000 ... 2078   MODBUS_WRITE = 0 ... 8

    struct tag_usart
    {
        unsigned char out_buffer[OUT_SIZE]; // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).
        unsigned char in_buffer[IN_SIZE];   // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).
        unsigned short out_buffer_count;    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short in_buffer_count;     // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short in_buffer_count2;    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ).
        unsigned short number_send;         // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short port_type;           // пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ.
        unsigned short mbm_status;          // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS.
        unsigned short mbm_err;             // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS.
        unsigned short mbm_err16;           // пїЅпїЅпїЅпїЅпїЅпїЅ 16 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
        unsigned short mbm_status_hl;       // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short mbm_status16;        // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS 16 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short repeat_05;           // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS 05.
        unsigned short repeat_05_;          // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS 05.
        unsigned short mbm_timeout_counter; // пїЅпїЅпїЅпїЅ-пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS. //
        unsigned short answer_count;        //

        struct tag_mb_statusBITS
        {
            unsigned modb_mode : 1;           // 1 пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned term_mode : 1;           // 1 пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned modb_received : 1;       // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned modb_transmited : 1;     // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned modb_receiving : 1;      // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned modb_transmiting : 1;    // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned tx_mode : 1;             // пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (USART TX mode)
            unsigned mbm_data_rdy : 1;        // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned master_error : 1;        // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned bussy1 : 1;              // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned bussy2 : 1;              // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned last_byte : 1;           // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
            unsigned byte_missing : 1;        // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
            unsigned coll_1 : 1;              // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 1
            unsigned coll_2 : 1;              // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 2
            unsigned coll_3 : 1;              // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
            unsigned start16 : 1;             // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned master_start : 1;        // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned master_timeout_flag : 1; // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅ
            unsigned tm_on : 1;               // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned device_error : 1;        // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned crc_error : 1;           // пїЅпїЅпїЅпїЅпїЅпїЅ CRC
            unsigned : 10;                    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ (19-32)
        } mb_status;
    } usart1, usart2, usart3, usart4, usart5;

    struct tag_usartm
    {
        unsigned char out_buffer[OUT_SIZE]; // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).
        unsigned char in_buffer[IN_SIZE];   // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ).
        unsigned short out_buffer_count;    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short in_buffer_count;     // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short in_buffer_count2;    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ (пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ).
        unsigned short number_send;         // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short mbm_status03;        // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS.
        unsigned short mbm_status16;        // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS 16 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ.
        unsigned short mbm03_tm_err;        // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
        unsigned short mbm03_c01_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 1 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
        unsigned short mbm03_c02_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 2 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
        unsigned short mbm03_c03_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
        unsigned short mbm03_crc_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ CRC16 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
        unsigned short mbm16_tm_err;        // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 16
        unsigned short mbm16_c01_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 1 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 16
        unsigned short mbm16_c02_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 2 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 16
        unsigned short mbm16_c03_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 16
        unsigned short mbm16_crc_err;       // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ CRC16 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ 16
        unsigned short repeat_05;           // пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS 05.
        unsigned short repeat_05_;          // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS 05.
        unsigned short mbm_timeout_counter; // пїЅпїЅпїЅпїЅ-пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS. //
        unsigned short answer_count;        //

        struct stag_mb_statusBITS
        {
            unsigned modb_mode : 1;           // 1 пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned term_mode : 1;           // 2 пїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned modb_received : 1;       // 3 пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned modb_transmited : 1;     // 4 пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned modb_receiving : 1;      // 5 пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned modb_transmiting : 1;    // 6 пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ MODBUS
            unsigned tx_mode : 1;             // 7 пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ (USART TX mode) пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅ
            unsigned mbm_data_rdy : 1;        // 8 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned master_error : 1;        // 9 пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned bussy1 : 1;              // 10 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned bussy2 : 1;              // 11 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned last_byte : 1;           // 12 пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
            unsigned byte_missing : 1;        // 13 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
            unsigned coll_1 : 1;              // 14 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 1
            unsigned coll_2 : 1;              // 15 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 2
            unsigned coll_3 : 1;              // 16 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ 3
            unsigned start16 : 1;             // 17 пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned master_start : 1;        // 18 пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned master_timeout_flag : 1; // 19 пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ-пїЅпїЅпїЅпїЅ
            unsigned tm_on : 1;               // 20 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned device_error : 1;        // 21 пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned crc_error : 1;           // 22 пїЅпїЅпїЅпїЅпїЅпїЅ CRC
            unsigned : 10;                    // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ (23-32)
        } mb_status;
    } usart1m, usart2m, usart3m, usart4m, usart5m;

    unsigned short mbm_sync;

    union tag_mops
    {
        struct
        {
            union
            {
                struct
                {
                    unsigned short info[3];                // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ: пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
                    unsigned short status[num_zones];      // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short hold_status[num_zones]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short current[num_zones + 1]; // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                };
                unsigned short read[num_zones * 3 + 4]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
            };
            union
            {
                struct
                {
                    unsigned short command[num_zones]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short type[num_zones];    // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ: пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅ пїЅ пїЅпїЅпїЅ пїЅпїЅ
                    unsigned short limit1[num_zones];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short limit2[num_zones];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short limit3[num_zones];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short limit4[num_zones];  // пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ - пїЅпїЅ пїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short timer1[num_zones];  // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
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
    
    
    union tag_mops_short
    {
        struct
        {
            union
            {
                struct
                {
                    unsigned short info[3];                // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ: пїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅ
                    unsigned short status[num_zones];      // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short hold_status[num_zones]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned short current[num_zones + 1]; // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                };
                unsigned short read[num_zones * 3 + 4]; // пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
            };
            union
            {
                struct
                {
                    unsigned short command[num_zones]; 
                    unsigned short type[num_zones];    // пїЅпїЅпїЅпїЅ пїЅпїЅпїЅ: пїЅпїЅпїЅпїЅпїЅпїЅпїЅ, пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅ пїЅпїЅ пїЅ пїЅпїЅпїЅ пїЅпїЅ
                };
                unsigned short write[num_zones * 2];
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
        unsigned short main_area[num_zones * 6 + 15];
    };

    union tag_mops MOPS_arr[10];
    union tag_mops MOPS_arr_sw[10];
    
    union tag_mops_short MOPS_S_arr[10];
    union tag_mops_short MOPS_S_arr_sw[10];

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
        
    // ike tag_mups but shorted
    union tag_mups_short
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
                unsigned short timeout_err;     // 25
                unsigned short crc_err;         // 26  
                unsigned short coll_1_err;      // 27 
                unsigned short coll_2_err;      // 28
                unsigned short coll_3_err;      // 29
            };
            unsigned short read[29];    //выровнять
        };
        unsigned short main_area[29];
    } mups_short;
    
    union tag_mups MUPS_arr[10];
    union tag_mups MUPS_arr_sw[10];
    
    union tag_mups_short MUPS_S_arr[10];
    union tag_mups_short MUPS_S_arr_sw[10];

    unsigned short mops_stat;
    unsigned short mups_stat;
    unsigned short mops_done;
    unsigned short mups_done;
    unsigned short mops_num;
    unsigned short mups_num;

    union tag_Modbus
    {
        struct
        {
            union
            {
                struct
                {
                    unsigned flap_On : 1;           // 1
                    unsigned start : 1;             // 2 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
                    unsigned ignit_allow : 1;       // 4 Comman ON current stabilization function
                    unsigned CV_dir_ctrl : 1;       // 8 пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned PWM_dir_ctrl : 1;      // 16 пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ
                    unsigned ign_ctrl : 1;          // 32 пїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned unlock : 1;            // 64 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned AO : 1;                // 128 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned clr_err_cnt : 1;       // 256 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned stop : 1;              // 512 пїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ - пїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned press_mode_int : 1;    // 1024 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned press_mode_analog : 1; // 2048 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned deep_on : 1;           // 4096 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned NO : 1;                // 8192 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned stop_pid_on : 1;       // 16384 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned stop_pid_off : 1;      // 32768 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned forced_pid_on : 1;     // 65536 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
                    unsigned forced_pid_off : 1;    // 131072 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅ-пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
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
            unsigned short pulses_11;     // 27    пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            unsigned short pulses_40;     // 28	пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ
            float err_rpm;                // 29
            union
            {
                struct
                {
                    unsigned CV_locked : 1;        // 1 "пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ" пїЅпїЅпїЅ
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

    unsigned short dir_sc_low[CYLINDERS_NUM];
    unsigned short dir_br_low[CYLINDERS_NUM];
    unsigned short dir_br_high[CYLINDERS_NUM];
    unsigned short bit_sc_low;
    unsigned short bit_br_low;
    unsigned short bit_br_high;

    union tag_stand
    {
        struct
        {
            unsigned short active_mops[10];      // 1 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short active_mups[10];      // 11 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mops_timeout_err[10]; // 21
            unsigned short mops_crc_err[10];     // 31 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mops_coll_1_err[10];  // 41 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mops_coll_2_err[10];  // 51 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mops_coll_3_err[10];  // 61 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mups_timeout_err[10]; // 71
            unsigned short mups_crc_err[10];     // 81 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mups_coll_1_err[10];  // 91 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mups_coll_2_err[10];  // 101 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short mups_coll_3_err[10];  // 111 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short beak_err[10];         // 121 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short norma_err[10];        // 131 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short att_err[10];          // 141 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short fire_err[10];         // 151 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short short_err[10];        // 161 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
            unsigned short current_err[10];      // 171 пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅ
        };
        //    unsigned short buf [168];
        unsigned short buf[180];
    } Stand, Stand_sw;

    unsigned short DINPUT1;
    unsigned short DINPUT2;
    unsigned short DINPUT3;

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

/* *****************************************************************************
 End of File
 */
