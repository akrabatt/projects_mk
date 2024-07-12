#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "extern.h"

/** 
 * @brief stages for control functions
 */
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


/**
 * @brief read mops full
 * 
 * @param usart - tag_usartm
 */
void MOPS_control (struct tag_usartm * usart)
{
    unsigned short cc;
    Stand_sw.mops_timeout_err [mops_num] = swapshort (Stand.mops_timeout_err [mops_num]);
    Stand_sw.mops_crc_err [mops_num] = swapshort (Stand.mops_crc_err [mops_num]);    
    Stand_sw.mops_coll_1_err [mops_num] = swapshort (Stand.mops_coll_1_err [mops_num]);    
    Stand_sw.mops_coll_2_err [mops_num] = swapshort (Stand.mops_coll_2_err [mops_num]);    
    Stand_sw.mops_coll_3_err [mops_num] = swapshort (Stand.mops_coll_3_err [mops_num]); 
    
    switch (mops_stat) 
        {
        case INIT: {usart->mb_status.master_start = 1; mops_num = 0; mops_stat++; break;}
        case START_MM: { mops_stat++; break;}

        case READ_CYCLE:    {
            if (mops_num >= 10) {mops_num = 0; mops_stat++ ; break;}
            if (Stand.active_mops [mops_num] != 0) {    mbm_03_str (&usart5m, (mops_num + 1), 0, 109, (unsigned short * ) &MOPS_arr [mops_num], 115200); }
            else {mops_num++;}
            if (usart->mb_status.mbm_data_rdy == 1)  {
                for (cc = 0; cc < 109; cc++)    { MOPS_arr_sw [mops_num].main_area [cc] = swapshort (MOPS_arr [mops_num].main_area [cc]); }
                usart->mb_status.mbm_data_rdy = 0; mops_num++; 
                }
            if (usart->mb_status.master_timeout_flag == 1)  
                {MOPS_arr [mops_num].timeout_err++; Stand.mops_timeout_err [mops_num]++; usart->mb_status.master_timeout_flag = 0;mops_num++; }    
            if (usart->mb_status.crc_error == 1)    {MOPS_arr [mops_num].crc_err++; Stand.mops_crc_err [mops_num]++; usart->mb_status.crc_error = 0; mops_num++; }
            if (usart->mb_status.coll_1 == 1)       {MOPS_arr [mops_num].coll_1_err++; Stand.mops_coll_1_err [mops_num]++; usart->mb_status.coll_1 = 0; mops_num++; }
            if (usart->mb_status.coll_2 == 1)       {MOPS_arr [mops_num].coll_2_err++; Stand.mops_coll_2_err [mops_num]++; usart->mb_status.coll_2 = 0; mops_num++; }
            if (usart->mb_status.coll_3 == 1)       {MOPS_arr [mops_num].coll_3_err++; Stand.mops_coll_3_err [mops_num]++; usart->mb_status.coll_3 = 0; mops_num++; }
            break;}

        case CHECK_CYCLE:  {  mops_done = 1;  mops_stat = START_MM;   break;}        

        default : {mops_stat = START_MM; break;}
        }

    Modbus.buf [13] = mops_stat;  
    Modbus.buf [14] = mops_num; 
    Modbus.buf [15] = usart->mb_status.mbm_data_rdy;
    Modbus.buf [16] = usart->mb_status.master_timeout_flag;
}


/**
 * @brief read mops short
 * 
 * @param usart - tag_usartm
 */
void MOPS_S_control (struct tag_usartm * usart)
{
    unsigned short cc;
    Stand_sw.mops_timeout_err [mops_num] = swapshort (Stand.mops_timeout_err [mops_num]);
    Stand_sw.mops_crc_err [mops_num] = swapshort (Stand.mops_crc_err [mops_num]);    
    Stand_sw.mops_coll_1_err [mops_num] = swapshort (Stand.mops_coll_1_err [mops_num]);    
    Stand_sw.mops_coll_2_err [mops_num] = swapshort (Stand.mops_coll_2_err [mops_num]);    
    Stand_sw.mops_coll_3_err [mops_num] = swapshort (Stand.mops_coll_3_err [mops_num]); 
    
    switch (mops_stat) 
        {
        case INIT: {usart->mb_status.master_start = 1; mops_num = 0; mops_stat++; break;}
        case START_MM: { mops_stat++; break;}

        case READ_CYCLE:    {
            if (mops_num >= 10) {mops_num = 0; mops_stat++ ; break;}
            if (Stand.active_mops [mops_num] != 0) { mbm_03_str (&usart5m, (mops_num + 1), 0, 63, (unsigned short * ) &MOPS_S_arr [mops_num], 115200); }
            else {mops_num++;}
            if (usart->mb_status.mbm_data_rdy == 1)  {
                for (cc = 0; cc < 63; cc++)    { MOPS_S_arr_sw [mops_num].main_area [cc] = swapshort (MOPS_S_arr [mops_num].main_area [cc]); }
                usart->mb_status.mbm_data_rdy = 0; mops_num++; 
                }
            if (usart->mb_status.master_timeout_flag == 1)  
                { MOPS_S_arr [mops_num].timeout_err++; Stand.mops_timeout_err [mops_num]++; usart->mb_status.master_timeout_flag = 0;mops_num++; }    
            if (usart->mb_status.crc_error == 1)    {MOPS_S_arr [mops_num].crc_err++; Stand.mops_crc_err [mops_num]++; usart->mb_status.crc_error = 0; mops_num++; }
            if (usart->mb_status.coll_1 == 1)       {MOPS_S_arr [mops_num].coll_1_err++; Stand.mops_coll_1_err [mops_num]++; usart->mb_status.coll_1 = 0; mops_num++; }
            if (usart->mb_status.coll_2 == 1)       {MOPS_S_arr [mops_num].coll_2_err++; Stand.mops_coll_2_err [mops_num]++; usart->mb_status.coll_2 = 0; mops_num++; }
            if (usart->mb_status.coll_3 == 1)       {MOPS_S_arr [mops_num].coll_3_err++; Stand.mops_coll_3_err [mops_num]++; usart->mb_status.coll_3 = 0; mops_num++; }
            break;}

        case CHECK_CYCLE:  {  mops_done = 1;  mops_stat = START_MM;   break;}        

        default : {mops_stat = START_MM; break;}
        }

    Modbus.buf [13] = mops_stat;  
    Modbus.buf [14] = mops_num; 
    Modbus.buf [15] = usart->mb_status.mbm_data_rdy;
    Modbus.buf [16] = usart->mb_status.master_timeout_flag;
}


/**
 * @brief read mus full
 * 
 * @param usart - tag_usartm
 */
void MUPS_control(struct tag_usartm * usart)
{   
    // usart->mb_status.master_start = 1;
    // mbm_03_str(usart, 2, 200, 100, (unsigned short*) &MUPS_arr[1], 115200);
//    mbm_03_str(&usart5m, 2, 200, 100, (unsigned short*) &MUPS_arr[1], 115200);

unsigned short cc;
    Stand_sw.mups_timeout_err [mups_num] = swapshort (Stand.mups_timeout_err [mups_num]);
    Stand_sw.mups_crc_err [mups_num] = swapshort (Stand.mups_crc_err [mups_num]);    
    Stand_sw.mups_coll_1_err [mups_num] = swapshort (Stand.mups_coll_1_err [mups_num]);    
    Stand_sw.mups_coll_2_err [mups_num] = swapshort (Stand.mups_coll_2_err [mups_num]);    
    Stand_sw.mups_coll_3_err [mups_num] = swapshort (Stand.mups_coll_3_err [mups_num]); 
    
    switch (mups_stat) 
        {
        case INIT: {usart->mb_status.master_start = 1; mups_num = 0; mups_stat++; break;}
        case START_MM: { mups_stat++; break;}

        case READ_CYCLE:    {
            if (mups_num >= 10) {mups_num = 0; mups_stat++ ; break;}
            if (Stand.active_mups [mups_num] != 0) {    mbm_03_str (&usart5m, (mups_num + 1), 200, 86, (unsigned short * ) &MUPS_arr [mups_num], 115200); }
            else {mups_num++;}
            if (usart->mb_status.mbm_data_rdy == 1)  {
                for (cc = 0; cc < 86; cc++)    { MUPS_arr_sw [mups_num].main_area [cc] = swapshort (MUPS_arr [mups_num].main_area [cc]); }
                usart->mb_status.mbm_data_rdy = 0; mups_num++; 
                }
            if (usart->mb_status.master_timeout_flag == 1)  
                {MUPS_arr [mups_num].timeout_err++; Stand.mups_timeout_err [mups_num]++; usart->mb_status.master_timeout_flag = 0;mups_num++; }    
            if (usart->mb_status.crc_error == 1)    {MUPS_arr [mups_num].crc_err++; Stand.mups_crc_err [mups_num]++; usart->mb_status.crc_error = 0; mups_num++; }
            if (usart->mb_status.coll_1 == 1)       {MUPS_arr [mups_num].coll_1_err++; Stand.mups_coll_1_err [mups_num]++; usart->mb_status.coll_1 = 0; mups_num++; }
            if (usart->mb_status.coll_2 == 1)       {MUPS_arr [mups_num].coll_2_err++; Stand.mups_coll_2_err [mups_num]++; usart->mb_status.coll_2 = 0; mups_num++; }
            if (usart->mb_status.coll_3 == 1)       {MUPS_arr [mups_num].coll_3_err++; Stand.mups_coll_3_err [mups_num]++; usart->mb_status.coll_3 = 0; mups_num++; }
            break;}

        case CHECK_CYCLE:  {  mups_done = 1;  mups_stat = START_MM;   break;}        

        default : {mups_stat = START_MM; break;}
        }

    Modbus.buf [13] = mups_stat;  
    Modbus.buf [14] = mups_num; 
    Modbus.buf [15] = usart->mb_status.mbm_data_rdy;
    Modbus.buf [16] = usart->mb_status.master_timeout_flag;
}



/**
 * @brief read mups short
 * 
 * @param usart - tag_usartm
 */
void MUPS_S_control(struct tag_usartm * usart)
{   
unsigned short cc;
    Stand_sw.mups_timeout_err [mups_num] = swapshort (Stand.mups_timeout_err [mups_num]);
    Stand_sw.mups_crc_err [mups_num] = swapshort (Stand.mups_crc_err [mups_num]);    
    Stand_sw.mups_coll_1_err [mups_num] = swapshort (Stand.mups_coll_1_err [mups_num]);    
    Stand_sw.mups_coll_2_err [mups_num] = swapshort (Stand.mups_coll_2_err [mups_num]);    
    Stand_sw.mups_coll_3_err [mups_num] = swapshort (Stand.mups_coll_3_err [mups_num]); 
    
    switch (mups_stat) 
        {
        case INIT: {usart->mb_status.master_start = 1; mups_num = 0; mups_stat++; break;}
        case START_MM: { mups_stat++; break; }

        case READ_CYCLE:    {
            if (mups_num >= 10) {mups_num = 0; mups_stat++ ; break;}
            if (Stand.active_mups [mups_num] != 0) { mbm_03_str (&usart5m, (mups_num + 1), 200, 29, (unsigned short * ) &MUPS_S_arr[mups_num], 115200); }
            else {mups_num++;}
            if (usart->mb_status.mbm_data_rdy == 1)  {
                for (cc = 0; cc < 29; cc++)    { MUPS_S_arr_sw [mups_num].main_area [cc] = swapshort (MUPS_S_arr [mups_num].main_area [cc]); }
                usart->mb_status.mbm_data_rdy = 0; mups_num++; 
                }
            if (usart->mb_status.master_timeout_flag == 1)  
                {MUPS_S_arr [mups_num].timeout_err++; Stand.mups_timeout_err [mups_num]++; usart->mb_status.master_timeout_flag = 0;mups_num++; }    
            if (usart->mb_status.crc_error == 1)    {MUPS_S_arr [mups_num].crc_err++; Stand.mups_crc_err [mups_num]++; usart->mb_status.crc_error = 0; mups_num++; }
            if (usart->mb_status.coll_1 == 1)       {MUPS_S_arr [mups_num].coll_1_err++; Stand.mups_coll_1_err [mups_num]++; usart->mb_status.coll_1 = 0; mups_num++; }
            if (usart->mb_status.coll_2 == 1)       {MUPS_S_arr [mups_num].coll_2_err++; Stand.mups_coll_2_err [mups_num]++; usart->mb_status.coll_2 = 0; mups_num++; }
            if (usart->mb_status.coll_3 == 1)       {MUPS_S_arr [mups_num].coll_3_err++; Stand.mups_coll_3_err [mups_num]++; usart->mb_status.coll_3 = 0; mups_num++; }
            break;}

        case CHECK_CYCLE:  {  mups_done = 1;  mups_stat = START_MM;   break;}        

        default : {mups_stat = START_MM; break;}
        }

    Modbus.buf [13] = mups_stat;  
    Modbus.buf [14] = mups_num; 
    Modbus.buf [15] = usart->mb_status.mbm_data_rdy;
    Modbus.buf [16] = usart->mb_status.master_timeout_flag;
}


/**
 * @brief this function changes the strategy of the 4 channels of the MUPS with 
 * programmatically set parameters
 * 
 * @param strategy_num - mups's strategy
 * @param slave_id - mups's id address
 */
void change_mups_strategy(int slave_id, int strategy_num)
{
    switch(strategy_num) 
    {
            case 1: {memcpy(mups_strategy, mups_1_strategy, sizeof(mups_1_strategy)); break;}
            case 2: {memcpy(mups_strategy, mups_2_strategy, sizeof(mups_2_strategy)); break;}
            case 3: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); break;}
        default: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); break;}
    }
    
    // exemp work with var end reg
    unsigned short test;
    test = Stand_sw.buf[25-1];
    Stand_sw.buf[26-1] = test;
    
    mbm_16(&usart5m, slave_id, 212, 4, mups_strategy, 115200);
}


// global vars for @change_mups_strategy_wp
int slave_id = 0;           // mups slave_id
int strategy_num = 0;       // mups chan. strategy
int strategy_num_fix = 0;   // flag for fix strtegy  

enum {READ_SLAVE_ID = 0,
            READ_MUPS_STRATEGY,
//            CASE_CHECK,
            CONFIG_MEMORY,
            CONFIG_MUPS
    } stages;
    
/**
 * @brief this function changes the strategy of the 4 channels of the MUPS at 
 * once
 * 
 * @note The beginning of the requested range in mudbus poll is 501, 
 * slave_id = 521 reg(Stand.buf[20]), mups_strategy = 522 reg(Stand.buf[21])
 * 
 */
void change_mups_strategy_wp()
{
    switch(stages)
    {   
        case READ_SLAVE_ID: {slave_id = Stand.buf[20]; if(slave_id > 0){stages++;} break;}
        case READ_MUPS_STRATEGY: 
            {
                strategy_num = Stand.buf[21]; 
                if((strategy_num == strategy_num_fix) && (strategy_num != 0) && (strategy_num_fix != 0)) {break;}
                if(strategy_num > 0 && strategy_num < 4){stages++; strategy_num_fix = strategy_num;} 
                break;
            }
        case CONFIG_MEMORY: {
            switch(strategy_num) 
            {
                    case 1: {memcpy(mups_strategy, mups_1_strategy, sizeof(mups_1_strategy)); break;}
                    case 2: {memcpy(mups_strategy, mups_2_strategy, sizeof(mups_2_strategy)); break;}
                    case 3: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); break;}
                default: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); break;}
            }
            stages++;
        }
        case CONFIG_MUPS: {mbm_16(&usart5m, slave_id, 212, 4, mups_strategy, 115200); stages = 0; break;}
    }
}
