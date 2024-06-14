
#include "define.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


extern unsigned char __attribute__((coherent)) buf_tx5 [300];
extern unsigned char __attribute__((coherent)) buf_tx4 [300]; 
extern unsigned char __attribute__((coherent)) buf_tx3 [300]; 
extern unsigned char __attribute__((coherent)) buf_tx2 [300]; 
extern unsigned char __attribute__((coherent)) buf_tx1 [300]; 
    
extern float swapfloat (float data ); 
extern unsigned long swaplong (unsigned long data );
extern unsigned short swapshort (unsigned short data );


extern unsigned long U4_speed;
extern unsigned long U5_speed;



extern unsigned short help_strobe;
extern unsigned short help_reset;
extern unsigned short help_load;
    
 extern union tag_direct{
	struct  {
		union {
			struct {
				unsigned short sensor1;						// data channel 1
				unsigned short sensor2;						// data channel 2
				unsigned short sensor3;						// data channel 3
				unsigned short sensor4;						// data channel 4
				unsigned short sensor5;						// data channel 5
				unsigned short sensor6;						// data channel 6
				unsigned short sensor7;						//  7
				unsigned short sensor8;						//  8
				float angle_1;                          	//  9
				float angle_2;                          	//  11
				float angle_3;                          	//  13
				float angle_4;                          	//  15
				float angle_5;                          	//  17
				float angle_6;                          	//  19
                float angle_7;                          	//  21
                float angle_8;                          	//  23
                float angle_9;                          	//  25
                float angle_10;                          	//  27
                float angle_11;                          	//  29
                float angle_12;                          	//  31
				unsigned long par1;                         //  33
				unsigned long par2;                         //  35
				unsigned long par3;                         //  37
				unsigned long par4;                         //  39
				unsigned long par5;                         //  41
				unsigned long par6;                         //  43
				unsigned long par7;                         //  45
				unsigned long par8;                         //  47
				unsigned long par9;                         //  49
				unsigned long par10;                        //  51
				struct {
					unsigned break_sin1  		:1;			// Status DBSKT sin1 ch1: 0 - OK, 1 - NOK 
					unsigned break_cos1  		:1;			// Status DBSKT sos1 ch1: 0 - OK, 1 - NOK 
					unsigned break_sin2  		:1;			// Status DBSKT sin2 ch2: 0 - OK, 1 - NOK 
					unsigned break_cos2  		:1;			// Status DBSKT cos2 ch1: 0 - OK, 1 - NOK 
					unsigned break_sens1  		:1;			// Status DBSKT sensor ch1: 0 - OK, 1 - NOK 
					unsigned break_sens2  		:1;			// Status DBSKT sensor ch2: 0 - OK, 1 - NOK 
					unsigned coil_1_res_high	:1;			// Coil 1 resistance: 0 - OK, 1 - too high resistance 
					unsigned coil_1_res_low		:1;			// Coil 1 resistance: 0 - OK, 1 - too low resistance
					unsigned coil_2_res_high	:1;			// Coil 2 resistance: 0 - OK, 1 - too high resistance 
					unsigned coil_2_res_low		:1;			// Coil 2 resistance: 0 - OK, 1 - too low resistance
					unsigned I_1_fault			:1;			// analog out 1 fault: 0 - OK, 1 - fault
					unsigned I_2_fault			:1;			// analog out 2 fault: 0 - OK, 1 - fault
					unsigned I_in_fault			:1;			// analog out 2 fault: 0 - OK, 1 - fault
					unsigned                    :19;

					};
				};
			unsigned short output [54];
		      };
		union {
			struct {
				float fl_1;                          	//  55
				float fl_2;                          	//  57
				float fl_3;                          	//  59
				float fl_4;                          	//  61
				float fl_5;                          	//  63
				float fl_6;                          	//  65
                float fl_7;                          	//  67              
				unsigned short command1;				//  69
				unsigned short command2;				//  70
				unsigned short command3;				//  71
				unsigned short command4;				//  72
				unsigned short command5;				//  73
				unsigned short command6;				//  74
				unsigned short command7;				//  75
				unsigned short command8;				//  76
				struct {
					unsigned command_On  :1;                 	//  Command ON! "Semicrone" unit
					unsigned command_Off :1;                	//  Command OFF! "Semicrone" unit
					unsigned command_Istab_On :1;           	// Comman ON current stabilization function
					unsigned command_Integ_ON :1;           	// Comman ON I-unit into the PI-regulator (current current stabilization function)
					unsigned             :28;               	// Last 12 bits = byte for value of Kp regulator (current current stabilization function)
					};
				};		
			unsigned short input [24];
			};
		};
	unsigned short buf [78] ;
	} MB, MB_swap, calibr, calibr_swap;	// ???????? ?????? 2000 - 2078 (READ / WRITE)

 extern  struct tag_usart
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
    unsigned short mbm_err16;           // Ошибка 16 функции
    unsigned short mbm_status_hl;       // Статус MODBUS высокого уровня.
    unsigned short mbm_status16;        // Статус MODBUS 16 функция.
    unsigned short repeat_05;           // Повтор MODBUS 05.
    unsigned short repeat_05_;          // Другой повтор MODBUS 05.
    unsigned short mbm_timeout_counter; // Тайм-аут счетчик MODBUS. //
    unsigned short answer_count;        //

    struct tag_mb_statusBITS
    {
        unsigned modb_mode : 1;             // 1 бит для режима MODBUS
        unsigned term_mode : 1;             // 1 бит для режима терминала
        unsigned modb_received : 1;         // Флаг получения MODBUS
        unsigned modb_transmited : 1;       // Флаг передачи MODBUS
        unsigned modb_receiving : 1;        // Флаг приема MODBUS
        unsigned modb_transmiting : 1;      // Флаг отправки MODBUS
        unsigned tx_mode : 1;               // Режим передачи (USART TX mode)
        unsigned mbm_data_rdy : 1;          // Готовность данных к передаче
        unsigned master_error : 1;          // Ошибка мастера
        unsigned bussy1 : 1;                // Резервное поле
        unsigned bussy2 : 1;                // Резервное поле
        unsigned last_byte : 1;             // Флаг последнего байта
        unsigned byte_missing : 1;          // Отсутствие байта
        unsigned coll_1 : 1;                // Коллизия 1
        unsigned coll_2 : 1;                // Коллизия 2
        unsigned coll_3 : 1;                // Коллизия 3
        unsigned start16 : 1;               // Начало передачи
        unsigned master_start : 1;          // Начало мастера
        unsigned master_timeout_flag : 1;   // флаг ошибки тайм-аута
        unsigned tm_on : 1;                 // Включение таймера
        unsigned device_error : 1;          // Ошибка устройства
        unsigned crc_error : 1;             // Ошибка CRC
        unsigned : 10;                      // Резервные биты (19-32)
    } mb_status;
} usart1, usart2, usart3, usart4, usart5;

 extern  struct tag_usartm
{
    unsigned char out_buffer[OUT_SIZE]; // Массив буфера для исходящих данных (отправляемые данные).
    unsigned char in_buffer[IN_SIZE];   // Массив буфера для входящих данных (принимаемые данные).
    unsigned short out_buffer_count;    // Счетчик числа байт в буфере исходящих данных.
    unsigned short in_buffer_count;     // Счетчик числа байт в буфере входящих данных.
    unsigned short in_buffer_count2;    // Дополнительный счетчик числа байт в буфере входящих данных (второй счетчик).
    unsigned short number_send;         // Количество байт для отправки.
    unsigned short mbm_status03;        // Статус MODBUS.
    unsigned short mbm_status16;        // Статус MODBUS 16 функция.
    unsigned short mbm03_tm_err;        // Счетчик ошибок таймаута функция 3
    unsigned short mbm03_c01_err;       // Счетчик ошибок коллизия 1 функция 3
    unsigned short mbm03_c02_err;       // Счетчик ошибок коллизия 2 функция 3
    unsigned short mbm03_c03_err;       // Счетчик ошибок коллизия 3 функция 3
    unsigned short mbm03_crc_err;       // Счетчик ошибок CRC16 функция 3
    unsigned short mbm16_tm_err;        // Счетчик ошибок таймаута функция 16
    unsigned short mbm16_c01_err;       // Счетчик ошибок коллизия 1 функция 16
    unsigned short mbm16_c02_err;       // Счетчик ошибок коллизия 2 функция 16
    unsigned short mbm16_c03_err;       // Счетчик ошибок коллизия 3 функция 16
    unsigned short mbm16_crc_err;       // Счетчик ошибок CRC16 функция 16
    unsigned short repeat_05;           // Повтор MODBUS 05.
    unsigned short repeat_05_;          // Другой повтор MODBUS 05.
    unsigned short mbm_timeout_counter; // Тайм-аут счетчик MODBUS. //
    unsigned short answer_count;        //

    struct stag_mb_statusBITS
    {
        unsigned modb_mode : 1;        // 1 бит для режима MODBUS
        unsigned term_mode : 1;        // 1 бит для режима терминала
        unsigned modb_received : 1;    // Флаг получения MODBUS
        unsigned modb_transmited : 1;  // Флаг передачи MODBUS
        unsigned modb_receiving : 1;   // Флаг приема MODBUS
        unsigned modb_transmiting : 1; // Флаг отправки MODBUS
        unsigned tx_mode : 1;          // Режим передачи (USART TX mode) прерывание или ДМА
        unsigned mbm_data_rdy : 1;     // Готовность данных к передаче
        unsigned master_error : 1;     // Ошибка мастера
        unsigned bussy1 : 1;           // Резервное поле
        unsigned bussy2 : 1;           // Резервное поле
        unsigned last_byte : 1;        // Флаг последнего байта
        unsigned byte_missing : 1;     // Отсутствие байта
        unsigned coll_1 : 1;           // Коллизия 1
        unsigned coll_2 : 1;           // Коллизия 2
        unsigned coll_3 : 1;           // Коллизия 3
        unsigned start16 : 1;         // Начало передачи
        unsigned master_start : 1;     // Начало мастера
        unsigned master_timeout_flag : 1;   // флаг ошибки тайм-аута
        unsigned tm_on : 1;            // Включение таймера
        unsigned device_error : 1;     // Ошибка устройства
        unsigned crc_error : 1;        // Ошибка CRC
        unsigned : 10;                 // Резервные биты (19-32)
    } mb_status;
} usart1m, usart2m, usart3m, usart4m, usart5m;

extern unsigned short mbm_sync;

union tag_mops{
	struct  {
		union {
			struct {
				unsigned short info[3];					// идентификационная область: тип прибора, версия прошивки, версия платы
				unsigned short status [num_zones];		// статусы зон
				unsigned short hold_status [num_zones];	// запомненные статусы зон
				unsigned short current [num_zones+1];		// токи зон
				};
			unsigned short read [num_zones*3+4];			// область чтения
			};
		union {
			struct {
				unsigned short command [num_zones];		// команды зон
				unsigned short type [num_zones];		// типы зон: обычная, пожарная с ПЗ и без ПЗ
				unsigned short limit1 [num_zones];		// пороги обыв - норма для всех зон
				unsigned short limit2 [num_zones];		// пороги норма - внимание для всех зон
				unsigned short limit3 [num_zones];		// пороги внимание - пожар для всех зон
				unsigned short limit4 [num_zones];		// пороги пожар - КЗ для всех зон
				unsigned short timer1 [num_zones];		// настраиваемые таймера всех зон
				unsigned short timer2 [num_zones];
				unsigned short timer3 [num_zones];
				unsigned short timer4 [num_zones];
				unsigned short stat_hysteresis;
				};
			unsigned short write [num_zones*10 +1];	
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
	unsigned short main_area [num_zones*13+16] ;
	} ;

extern union tag_mops MOPS_arr [10];
extern union tag_mops MOPS_arr_sw [10];        
 
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


extern union tag_Modbus {
    struct {
        union {
			struct {
				unsigned flap_On  :1;			// 1
				unsigned start  :1;			// 2 команда пуск
				unsigned ignit_allow :1;		// 4 Comman ON current stabilization function
				unsigned CV_dir_ctrl :1;		// 8 режим прямого управления ТРК
				unsigned PWM_dir_ctrl :1;		// 16 режим прямого управления ШИМ 
				unsigned ign_ctrl :1;			// 32 режим проверки зажигания 
				unsigned unlock :1;			// 64 деблокировка
				unsigned AO :1;				// 128 команда аварийного останова
				unsigned clr_err_cnt :1;		// 256 очистка счетчиков ошибок
				unsigned stop :1;			// 512 команда стоп - выход из диагностических режимов 
				unsigned press_mode_int :1;		// 1024 давление по интерфейсу
				unsigned press_mode_analog :1;		// 2048 давление по аналогу
				unsigned deep_on :1;			// 4096 глубокое запаздывание
				unsigned NO :1;				// 8192 нормальный останов
				unsigned stop_pid_on :1;		// 16384 приостановка пид-регулятора				
				unsigned stop_pid_off :1;		// 32768 включение пид-регулятора	
				unsigned forced_pid_on :1;		// 65536 включение форсированного пид-регулятора				
				unsigned forced_pid_off :1;		// 131072 выключение форсированного пид-регулятора
				unsigned             :14;		// Last 8 bits = byte for value of Kp regulator (current current stabilization function)
				};
			unsigned long cmd1;						// 1
			};
	unsigned short num_check_cyl;   //3	
	unsigned short cyl_mask;	//4
        float RPM_set;                  //5      setting the ngine speed
        float CV_dir_set;               //7      setting the ngine speed
        float work_status;              //9      status BUD
        float RPM11;                    //11      rpm, measured via sinchro 11-teeth-channel
        float RPM40;                    //13      rpm, measured via rpm 40-teeth-channel
        float CV_set;                   //15      fuel valve setting
        float CV_pos;                   //17      actual fuel valve position
        float CV_current;               //19      actual valve currrent
        float actual_UOZ;               //21      ignition angle
	unsigned short AO_reason;	//23
	unsigned short AO_cyl_num;      //24
        unsigned short ADC_CV_pos;      //25
        unsigned short ADC_CV_curr;     //26
        unsigned short pulses_11;       //27      
	unsigned short pulses_40;	//28	количество импульсов по каналу оборотов на обин оборот по каналу синхронизации
        float err_rpm;                  //29
        union {
		struct {
			unsigned CV_locked :1;				// 1 "закусывание" ТРК
			unsigned press_via_analog :1;			// 2 1 - работа по аналоговому сигналу; 0 - работа по интерфейсу
			unsigned CV_magnet_brake :1;			// 4 обрыв электромагнита ТРК
			unsigned CV_sensor_err :1;			// 8 недостоверность датчика положения ТРК
			unsigned deep_mode :1;				// 16 Command ON 
			unsigned Protect_unswitch :1;			// 32 Command ON 
			unsigned DI1_ctrl :1;				// 64 Command ON 
			unsigned CONTROL1 :1;				// 128 
			unsigned CONTROL2 :1;				// 256 
			unsigned CONTROL3 :1;				// 512 
			unsigned CONTROL4 :1;				// 1024 
			unsigned s12 :1;		// 2048 давление по аналогу
			unsigned deep_is_on :1;		// 4096 глубокое запаздывание
			unsigned stop_pid :1;		// 8192 отключен пид-регулятор
			unsigned miss_sync :1;		// 16384 пропуски канала синхронизации
			unsigned miss_rpm :1;		// 32768 пропуски канала оборотов	
			unsigned forced_pid :1;		// 65536 включен форсированный ПИД
			unsigned             :15;	// Last 16 bits = byte for value of Kp regulator (current current stabilization function)
			};
		unsigned long statuses;			// 31
		};
	float ign_err_num1 ;			// 33  
	float ign_err_num2 ;			// 35 

    };
    unsigned short buf [82];		// MB_READ_ MB_WRITE_  0 ... 80
} Modbus, Modbus_sw;

extern union tag_MB_diag {
    struct {
        unsigned short break_low [10];   //      event counter of break low voltage wire for every of 10 cylinders
        unsigned short short_low [10];   //      event counter of short circuit low voltage wire for every of 10 cylinders
        unsigned short break_high [10];  //      event counter of break high voltage wire for every of 10 cylinders
        float discharge_hold [10];      //  -   momental discharge time captured for 10 cylinders
        float discharge_middle [10];    //  -   middle discharge time capture for 10 cylinders
    };
    unsigned short buf [70];
} MB_diag, MB_diag_sw;			// MB_DIAGN_READ_ MB_DIAGN_WRITE_  200 ... 270 

extern union tag_diag {
    struct {
        unsigned short break_low [CYLINDERS_NUM];	    //      event counter of break low voltage wire for every of 10 cylinders
        unsigned short short_low [CYLINDERS_NUM];	    //      event counter of short circuit low voltage wire for every of 10 cylinders
        unsigned short break_high [CYLINDERS_NUM];    //      event counter of break high voltage wire for every of 10 cylinders
        float discharge_hold [CYLINDERS_NUM];	    //  -   momental discharge time captured for 10 cylinders
        float charge_hold [CYLINDERS_NUM];	    //  -   middle discharge time capture for 10 cylinders
    };
    unsigned short buf [112];
} MB_diagn, MB_diagn_sw;			// MB_DIAGN_READ_ MB_DIAGN_WRITE_  200 ... 270  диагностические данные

extern unsigned short dir_sc_low [CYLINDERS_NUM] ;
extern unsigned short dir_br_low [CYLINDERS_NUM] ;
extern unsigned short dir_br_high [CYLINDERS_NUM] ;
extern unsigned short bit_sc_low ;
extern unsigned short bit_br_low ;
extern unsigned short bit_br_high ;




extern union tag_stand {
    struct {
        unsigned short active_mops[10];         // 1 управление модулями МОПС
        unsigned short active_mups[10];         // 11 управление модулями МУПС
        unsigned short mops_timeout_err[10];    // 21 
        unsigned short mops_crc_err[10];        // 31 управление модулями МОПС
        unsigned short mops_coll_1_err[10];     // 41 управление модулями МОПС
        unsigned short mops_coll_2_err[10];     // 51 управление модулями МОПС
        unsigned short mops_coll_3_err[10];     // 61 управление модулями МОПС        
        unsigned short mups_timeout_err[10];    // 71 
        unsigned short mups_crc_err[10];        // 81 управление модулями МОПС
        unsigned short mups_coll_1_err[10];     // 91 управление модулями МОПС
        unsigned short mups_coll_2_err[10];     // 101 управление модулями МОПС
        unsigned short mups_coll_3_err[10];     // 111 управление модулями МОПС        
        unsigned short beak_err[10];            // 121 управление модулями МОПС        
        unsigned short norma_err[10];           // 131 управление модулями МОПС        
        unsigned short att_err[10];             // 141 управление модулями МОПС        
        unsigned short fire_err[10];            // 151 управление модулями МОПС        
        unsigned short short_err[10];           // 161 управление модулями МОПС        
        unsigned short current_err[10];         // 171 управление модулями МОПС        
        };
//    unsigned short buf [168];
    unsigned short buf [180];     
} Stand, Stand_sw;



extern unsigned short DINPUT1;
extern unsigned short DINPUT2;
extern unsigned short DINPUT3;


#ifdef __cplusplus
}
#endif



/* *****************************************************************************
 End of File
 */
