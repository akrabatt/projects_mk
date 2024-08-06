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
            if (Stand.active_mops [mops_num] != 0) {    mbm_03_str (usart, (mops_num + 1), 0, 109, (unsigned short * ) &MOPS_arr [mops_num], 115200); }
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
            if (Stand.active_mops [mops_num] != 0) { mbm_03_str (usart, (mops_num + 1), 0, 44, (unsigned short * ) &MOPS_S_arr [mops_num], 115200); }
            else {mops_num++;}
            if (usart->mb_status.mbm_data_rdy == 1)  {
                for (cc = 0; cc < 44; cc++)    { MOPS_S_arr_sw [mops_num].main_area [cc] = swapshort (MOPS_S_arr [mops_num].main_area [cc]); }
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
            if (Stand.active_mups [mups_num] != 0) {    mbm_03_str (usart, (mups_num + 1), 200, 86, (unsigned short * ) &MUPS_arr [mups_num], 115200); }
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
            if (Stand.active_mups [mups_num] != 0) { mbm_03_str (usart, (mups_num + 1), 200, 29, (unsigned short * ) &MUPS_S_arr[mups_num], 115200); }
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
 * @brief this function reads modules and, if the last module is read, 
 * increments the value of stages
 * 
 * @param usart - tag_usartm
 * @param stg - var for stages
 */
void MUPS_S_control_stg(struct tag_usartm * usart)
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
            if (mups_num >= 10) 
            {incr_stages++; mups_num = 0; mups_stat++ ; break;}
            if (Stand.active_mups [mups_num] != 0) { mbm_03_str (usart, (mups_num + 1), 200, 29, (unsigned short * ) &MUPS_S_arr[mups_num], 115200); }
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
void change_mups_strategy(int slave_id, int strategy_num, struct tag_usartm *usart)
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
    
    mbm_16(usart, slave_id, 212, 4, mups_strategy, 115200);
}


// global vars for @change_mups_strategy_wp
int slave_id = 0;           // mups slave_id
int strategy_num = 0;       // mups chnls strategy
int strategy_num_fix = 0;   // num current strategy
int strategy_set_flag = 0;  // flag
int incr_stages = 0;        // incr flag for stages

enum {READ_INPUT_SLAVE_ID = 0,
            READ_INPUT_MUPS_STRATEGY,
            READ_MODULS_INFO,
            CHECK_STRATEGY,
            CONFIG_MEMORY,
            CONFIG_MUPS
    } stages;
    
/**
 * @brief this function changes the strategy of the 4 channels of the MUPS at 
 * once
 * 
 * @param usart pointer to struct usartm
 * 
 * @note The beginning of the requested range in mudbus poll is 501, 
 * slave_id = 521 reg(Stand.buf[20]), mups_strategy = 522 reg(Stand.buf[21])
 * 
 */
void change_mups_strategy_cmmon(struct tag_usartm * usart)
{
    switch(stages)
    {   
        case READ_INPUT_SLAVE_ID: {slave_id = Stand.buf[20]; if(slave_id > 0){stages++;} break;}
        case READ_INPUT_MUPS_STRATEGY: 
            {
                strategy_num = Stand.buf[21]; 
                if(strategy_num > 0 && strategy_num < 4){strategy_set_flag = 0; stages++; strategy_num_fix = strategy_num;} 
                break;
            }
        case READ_MODULS_INFO: {MUPS_S_control_stg (&usart5m); if(incr_stages > 0){incr_stages = 0; stages++; break;} break;}
        case CHECK_STRATEGY: 
            {
                if((strategy_num == MUPS_S_arr[slave_id - 1].main_area[12]) && (strategy_num != 0) && (strategy_num_fix != 0)) 
                    {stages = READ_INPUT_SLAVE_ID; break;}
                else{stages++; break;}
            }
        case CONFIG_MEMORY: {
            switch(strategy_num) 
            {
                case 1: {memcpy(mups_strategy, mups_1_strategy, sizeof(mups_1_strategy)); stages++; break;}
                case 2: {memcpy(mups_strategy, mups_2_strategy, sizeof(mups_2_strategy)); stages++; break;}
                case 3: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); stages++; break;}
                default: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); stages++; break;}
            }
        }
        case CONFIG_MUPS: {mbm_16(usart, slave_id, 212, 4, mups_strategy, 115200); stages = 0; strategy_set_flag++; break;}
    }
}


// channels strategy
unsigned short strategy_num_ch1;
unsigned short strategy_num_ch2;
unsigned short strategy_num_ch3;
unsigned short strategy_num_ch4;
unsigned short apply_strategy;

enum {CHECK_GLOBAL_FLAG_SEP = 0,
            READ_INPUT_SLAVE_ID_SEP,
            READ_MODULS_INFO_SEP,
            READ_INPUT_MUPS_STRATEGY_SEP,
            PREPEAR_BUF_SEP,
            HECK_APPLY_STR_SEP,
            CONFIG_MUPS_SEP
    } stages_sep;
    
    //vars for relay toggle
unsigned short apply_toggle;

enum {CHECK_GLOBAL_FLAG_REL = 0,
            READ_INPUT_SLAVE_ID_REL,
            READ_MODULS_INFO_REL,
            READ_INPUT_MUPS_RELAY_REL,
            PREPEAR_BUF_REL,
            HECK_APPLY_STR_REL,
            CONFIG_MUPS_REL
    } stages_relay;

/**
 * @brief this function changes the strategy of the 4 channels of the MUPC 
 * separately
 * 
 * @param usart pointer to struct usartm
 * 
 * @note The beginning of the requested range in mudbus poll is 501, 
 * slave_id = 524 reg(Stand.buf[23]), start mups_strategy = 525 reg(Stand.buf[24])
 * etc.1, apply_strategy = 531 reg(Stand.buf[28])
 */
void change_mups_strategy_separately(struct tag_usartm *usart)
{
    switch(stages_sep)
    {
        case CHECK_GLOBAL_FLAG_SEP: 
        {
            if(mbm_fun_in_work == 0){mbm_fun_in_work++; stages_sep++; break;} 
            else{stages_sep = 0; break;} 
        }
        case READ_INPUT_SLAVE_ID_SEP: 
        {
            slave_id = Stand.buf[23]; 
            if(slave_id > 0){stages_sep++; break;} 
            else{stages_sep = 0; mbm_fun_in_work = 0; break;} 
        }
        case READ_MODULS_INFO_SEP: 
        {
            if((stages_sep = READ_MODULS_INFO_SEP) && (stages_relay == READ_MODULS_INFO_REL)) {stages_sep++; break;}
            MUPS_S_control_stg (usart); 
            if(incr_stages > 0)
            {incr_stages = 0; stages_sep++; break;} 
            break;
        }
        case READ_INPUT_MUPS_STRATEGY_SEP: 
        {
            mups_strategy_sep[0] = Stand.buf[24]; 
            mups_strategy_sep[1] = Stand.buf[25]; 
            mups_strategy_sep[2] = Stand.buf[26]; 
            mups_strategy_sep[3] = Stand.buf[27];
            apply_strategy = Stand.buf[28];
                
            if((mups_strategy_sep[0] > 0 && mups_strategy_sep[0] < 4) || (mups_strategy_sep[1] > 0 && mups_strategy_sep[1] < 4) || 
                (mups_strategy_sep[2] > 0 && mups_strategy_sep[2] < 4) || (mups_strategy_sep[3] > 0 && mups_strategy_sep[3] < 4))
                {stages_sep++;} 
            else {stages_sep = READ_INPUT_MUPS_STRATEGY_SEP; break;}
            break;
        }
        case PREPEAR_BUF_SEP: 
            {
                mups_strategy_sep[0] = swapshort(mups_strategy_sep[0]);
                mups_strategy_sep[1] = swapshort(mups_strategy_sep[1]);
                mups_strategy_sep[2] = swapshort(mups_strategy_sep[2]);
                mups_strategy_sep[3] = swapshort(mups_strategy_sep[3]);
                stages_sep++;
            }
        case HECK_APPLY_STR_SEP: 
            {
                if(apply_strategy > 0) {stages_sep++; break;}
                else{stages_sep = READ_INPUT_SLAVE_ID_SEP; mbm_fun_in_work = 0; break;}
            }
        case CONFIG_MUPS_SEP: 
        {
            mbm_16(usart, slave_id, 212, 4, mups_strategy_sep, 115200);
            // check end 16 funktion
            if(mbm_16_end_flag > 0){mbm_16_end_flag = 0; stages_sep = 0; Stand.buf[28] = 0; Stand_sw.buf[28] = 0; mbm_fun_in_work = 0;}
            break;
        }
    }
}


/**
 * @brief this funktion is designed to control MUPS relay
 * 
 * @param usart pointer to struct usartm
 * 
 * @note The beginning of the requested range in mudbus poll is 501, 
 * slave_id = 530 reg(Stand.buf[23]), start mups_strategy = 530 reg(Stand.buf[30])
 * etc.1, apply_strategy = 531 reg(Stand.buf[34])
 */
void control_mups_reley(struct tag_usartm * usart)
{
    switch(stages_relay)
    {
        case CHECK_GLOBAL_FLAG_REL:
        {
            if(mbm_fun_in_work == 0){mbm_fun_in_work++; stages_relay++; break;} 
            else{stages_relay = 0; break;} 
        }
        case READ_INPUT_SLAVE_ID_REL: 
        {
            slave_id = Stand.buf[23]; 
            if(slave_id > 0){stages_relay++; break;} 
            else{stages_relay = 0; mbm_fun_in_work = 0; break;} 
        }
        case READ_MODULS_INFO_REL: 
        {
            MUPS_S_control_stg (usart); 
            if(incr_stages > 0){incr_stages = 0; stages_relay++; break;} 
            break;
        }
        case READ_INPUT_MUPS_RELAY_REL: 
        {
            relay_toggle[0] = Stand.buf[29]; 
            relay_toggle[1] = Stand.buf[30]; 
            relay_toggle[2] = Stand.buf[31]; 
            relay_toggle[3] = Stand.buf[32]; 
            apply_toggle = Stand.buf[33];
                
            if((relay_toggle[0] > 0 && relay_toggle[0] < 7) || (relay_toggle[1] > 0 && relay_toggle[1] < 7) || 
                (relay_toggle[2] > 0 && relay_toggle[2] < 7) || (relay_toggle[3] > 0 && relay_toggle[3] < 7))
                {stages_relay++;}
            break;
        }
        case PREPEAR_BUF_REL: 
            {
                relay_toggle[0] = swapshort(relay_toggle[0]);
                relay_toggle[1] = swapshort(relay_toggle[1]);
                relay_toggle[2] = swapshort(relay_toggle[2]);
                relay_toggle[3] = swapshort(relay_toggle[3]);
                stages_relay++;
            }
        case HECK_APPLY_STR_REL: 
            {
                if(apply_toggle > 0) {stages_relay++; break;}
                else{stages_relay = CHECK_GLOBAL_FLAG_REL; mbm_fun_in_work = 0; break;}
            }
        case CONFIG_MUPS_REL: 
        {
            mbm_16(usart, slave_id, 208, 4, relay_toggle, 115200);
            // check end 16 funktion
            if(mbm_16_end_flag > 0){mbm_16_end_flag = 0; stages_relay = 0; Stand.buf[33] = 0; Stand_sw.buf[33] = 0; mbm_fun_in_work = 0;}
            break;
        }
    }
}

// vars for 530 board
unsigned short slave_530_id;
unsigned short mode_num_530;
unsigned short apply_530;

enum
{
    READ_INPUT_SLAVE_ID_530 = 0,
    READ_INPUT_MUPS_RELAY_530,
    CHECK_APPLY_530,
    WRITE_MODE_530
}stages_530;

/**
 * @brief this function sends a signal to all modules at the same time
 * 
 * @param usart pointer to struct usartm
 * 
 * @note The beginning of the requested range in mudbus poll is 536, 
 * com_slave_530_id = 535 reg(Stand.buf[35]), com_mode_num_530 = 536reg(Stand.buf[36])
 * etc.1, com_apply_530 = 531 reg(Stand.buf[37])
 */
void board_530_mode_common(struct tag_usartm * usart)
{
    switch(stages_530)
    {
        case READ_INPUT_SLAVE_ID_530:
        {
            slave_530_id = Stand.buf[35]; 
            if(slave_530_id > 0){stages_530++; break;} 
            else{stages_530 = 0; /*mbm_fun_in_work = 0;*/ break;}
        }
        case READ_INPUT_MUPS_RELAY_530:
        {   
            mode_num_530 = Stand.buf[36];
            apply_530 = Stand.buf[37];
            // check range
            if(mode_num_530 < 0 || mode_num_530 > 4) {mode_num_530 = 0;}
            
            switch(mode_num_530)
            {
                case 0: {memcpy(_530_board_mode_mops, _530_board_normal_mops, sizeof(_530_board_normal_mops)); stages_530++; break;}                // 2 - norma in mops
                case 1: {memcpy(_530_board_mode_mops, _530_board_short_current_mops, sizeof(_530_board_short_current_mops)); stages_530++; break;}  // 6 - short current in mops
                case 2: {memcpy(_530_board_mode_mops, _530_board_fire_mops, sizeof(_530_board_fire_mops)); stages_530++; break;}                    // 5 - fire in mops
                case 3: {memcpy(_530_board_mode_mops, _530_board_attantion_mops, sizeof(_530_board_attantion_mops)); stages_530++; break;}          // 4 - attantion
                case 4: {memcpy(_530_board_mode_mops, _530_board_84_reley_on_mops, sizeof(_530_board_84_reley_on_mops)); stages_530++; break;}
            }
        }
        case CHECK_APPLY_530:
        {
            if(apply_530 > 0) {stages_530++; break;}
            else{stages_530 = READ_INPUT_SLAVE_ID_530; /*mbm_fun_in_work = 0;*/ break;}
        }
        case WRITE_MODE_530:
        {
            mbm_16(usart, slave_530_id, 0, 8, _530_board_mode_mops, 115200);
            // check end 16 funktion
            if(mbm_16_end_flag > 0){mbm_16_end_flag = 0; stages_530 = 0; Stand.buf[37] = 0; Stand_sw.buf[37] = 0; /*mbm_fun_in_work = 0;*/}
            break;
        }
    }
}

/**
 * @brief this function timer 1 second
 */
void _1_sec()
{
    if(++_1_sec_counter > 1000)
    {
        _1_sec_counter = 0;
//        LED_TOGGLE;
    }
}

/**
 * @brief this function timer 500 milisec
 */
void _500_msec()
{
    if(++_500_msec_counter > 500)
    {
        _500_msec_counter = 0;
        LED_TOGGLE;
    }
}


// vars for mops_service_check

enum 
{
    RELEY_ON = 0,
    
}mops_service_check_stages;
short var_a;
short var_b;


/**
 * @brief this function performs a service check of the module
 * 
 * @param usart_a. A pointer to the port to which the main number of 530 cards 
 * is connected is passed to usart_a (start reley 4)
 * 
 * @param usart_b. The pointer to which the port is transmitted to which one 
 * 530th board is connected (end reley 84)
 * 
 * @param usart_c. this port is used to read the states of the modules (read MOPS)
 * 
 */
void mops_service_check(struct tag_usartm * usart_a, struct tag_usartm * usart_b, struct tag_usartm * usart_c)
{
    switch(mops_service_check_stages)
    {
        case RELEY_ON: 
        {
            var_a = mbm_16_flag(usart_a, 1, 0, 8, _530_board_only_reley_on_start_4_mops, 115200);
            var_b = mbm_16_flag(usart_b, 1, 0, 8, _530_board_84_reley_on_mops, 115200);
            if(var_a > 0 && var_b > 0) {var_a = 0; var_b = 0; mops_service_check_stages++; break;}
            break;
        }
    }
    mops_service_check_stages = 0;
}