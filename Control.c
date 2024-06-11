#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "define.h"
#include "extern.h"


extern void mbm_03 (struct tag_usart * usart, unsigned char mbm_adres, unsigned short shift_03, unsigned short quant_03, unsigned short * dest, unsigned long speed);

enum 
{
    INIT = 0,
	START_MM,
    READ_CYCLE,
    CHECK_CYCLE,
    WRITE_MM_1,
	W_WAIT_MM_1,
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

void group_read (struct tag_usart * usart)
{
    
}
unsigned short control_stat;
unsigned short mops_num;

void MM_control (struct tag_usartm * usart)
{

    
    switch (control_stat) 
        {
        case INIT: {usart->mb_status.master_start = 1; mops_num = 0; control_stat++; break;}
        case START_MM: { control_stat++; break;}

        case READ_CYCLE:    {
            if (mops_num >= 10) {mops_num = 0; control_stat++ ; break;}
            mbm_03_str (&usart5m, (mops_num + 1), 0, 28, (unsigned short * ) &MOPS_arr [mops_num], 115200);
            if (usart->mb_status.mbm_data_rdy == 1) {mops_num++; usart->mb_status.mbm_data_rdy = 0;}
            if (usart->mb_status.master_timeout_flag == 1) {mops_num++; usart->mb_status.master_timeout_flag = 0;}    
//            if (usart->mb_status.crc_error == 1) { usart->mbm_status = 0;}
//            if ((usart->mb_status.coll_1 == 1) || (usart->mb_status.coll_2 == 1) || (usart->mb_status.coll_3 == 1)) 
//                {usart->mb_status.master_start=0; usart->mbm_status=0;  }
            break;}

        case CHECK_CYCLE:  {
            control_stat = START_MM; 
//            usart->mb_status.mbm_data_rdy = 0;
//            usart->mb_status.master_timeout_flag = 0;
            break;}        

        default : {control_stat = START_MM; break;}
        }
    Modbus.buf [13] = control_stat;  
    Modbus.buf [14] = mops_num; 
    Modbus.buf [15] = usart->mb_status.mbm_data_rdy;
    Modbus.buf [16] = usart->mb_status.master_timeout_flag;
}




/* *****************************************************************************
 End of File
 */
