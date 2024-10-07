#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "extern.h"
#include "stddef.h"


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


void MOPS_S_control_flag (struct tag_usartm * usart, unsigned short *mops_end_flag)
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
            if (mops_num >= 10) {++(*mops_end_flag); mops_num = 0; mops_stat++ ; break;}
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
void MUPS_S_control_flag(struct tag_usartm * usart, unsigned short *flag)
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
            {++(*flag); mups_num = 0; mups_stat++ ; break;}
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
            {++incr_stages; mups_num = 0; mups_stat++ ; break;}
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
//void change_mups_strategy_cmmon(struct tag_usartm * usart)
//{
//    switch(stages)
//    {   
//        case READ_INPUT_SLAVE_ID: {slave_id = Stand.buf[20]; if(slave_id > 0){stages++;} break;}
//        case READ_INPUT_MUPS_STRATEGY: 
//            {
//                strategy_num = Stand.buf[21]; 
//                if(strategy_num > 0 && strategy_num < 4){strategy_set_flag = 0; stages++; strategy_num_fix = strategy_num;} 
//                break;
//            }
//        case READ_MODULS_INFO: {MUPS_S_control_stg (&usart5m); if(incr_stages > 0){incr_stages = 0; stages++; break;} break;}
//        case CHECK_STRATEGY: 
//            {
//                if((strategy_num == MUPS_S_arr[slave_id - 1].main_area[12]) && (strategy_num != 0) && (strategy_num_fix != 0)) 
//                    {stages = READ_INPUT_SLAVE_ID; break;}
//                else{stages++; break;}
//            }
//        case CONFIG_MEMORY: {
//            switch(strategy_num) 
//            {
//                case 1: {memcpy(mups_strategy, mups_1_strategy, sizeof(mups_1_strategy)); stages++; break;}
//                case 2: {memcpy(mups_strategy, mups_2_strategy, sizeof(mups_2_strategy)); stages++; break;}
//                case 3: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); stages++; break;}
//                default: {memcpy(mups_strategy, mups_3_strategy, sizeof(mups_3_strategy)); stages++; break;}
//            }
//        }
//        case CONFIG_MUPS: {mbm_16(usart, slave_id, 212, 4, mups_strategy, 115200); stages = 0; strategy_set_flag++; break;}
//    }
//}


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
 * @brief this function timer 500 milisec
 */
void _500_msec()
{
    if(++_500_msec_counter > 500)
    {
        _500_msec_counter = 0;
//        LED_TOGGLE;
    }
}

//====== MOPS AREA ======//

// vars for mops_service_check
enum 
{
    CHECK_START_BUTTON = 0,
    RELEY_ON,                               // 4 - 84 releys turne on
    WAIT_SEC_INIT,                          // just waite one sec to init modules
    READ_MOPS_PRE_CONNACTION,               // get full modules information during 3 sec
    READ_MOPS_CONNACTION_STATMENT,          // check connection with active modules and normal statment 
    WRITE_ATTANTION_STATMENT,               // 530 board write attantion
    WAIT_SEC_ATTANTION,                     // just waite one sec after init attantion to 530 board and init sys
    READ_MOPS_PRE_ATTANTION,                // get full modules information during 3 sec
    READ_MOPS_ATTANTION_STATMENT,           // check connection with active modules and attantion statment
    WRITE_FIRE_STATMENT,                    // 530 board write fire
    WAIT_SEC_FIRE,                          // just wait one sec after init fire to 530 board and inti sys
    READ_MOPS_PRE_FIRE,                     // get full modules information durind 3 sec
    READ_MOPS_FIRE_STATMENT,                // check connection with activ modules and fire statment
    WRITE_SC_STATMENT,                      // ...
    WAIT_SEC_SC,                            // ...
    READ_MOPS_PRE_SC,                       // ...
    READ_MOPS_SC_STATMENT,                  // ...
    WRITE_BREAK_STATMENT,                   // ...
    WAIT_SEC_BREAK,                         // ...
    READ_MOPS_PRE_BREAK,                    // ...
    READ_MOPS_BREAK_STATMENT,               // ...
    CHECK_POWER_CYCLE                       // this case implements the execution of the cycle 3 times
}mops_service_check_stages;

short var_a;                    //mbm_16 success end flag
short var_b;                    // ..
short var_c;                    // ..
short var_d;                    // ..
short mups_read_flag;           //mops read last module flag
short start_1_sec_timer;        //
short end_1_sec_timer;          //
short start_var_sec_timer;      //
short end_var_sec_timer;        //

/**
 * @brief this function timer 1 second
 */
void _1_sec()
{
    if(start_1_sec_timer > 0)
    {
        if(++_1_sec_counter > 2000)
        {
            end_1_sec_timer = 1;             // timer off
            _1_sec_counter = 0;              // reset
//            LED_TOGGLE;
        }
    }    
}

/**
 * @brief This function is a configurable timer
 * 
 * @param time. The variable is set in milliseconds, 1000 = 1 second
 * 
 * @note to get started, you need to assign a value greater than zero to 
 * the start_var_sec_timer variable
 */
void _var_sec(unsigned short time)
{
    if(start_var_sec_timer > 0)
        if(++_var_sec_conunter > time)
        {
            end_var_sec_timer = 1;
            _var_sec_conunter = 0;
            LED_TOGGLE;
        }
}

/**
 * @brief this function checks the status of the connection to the module, as 
 * well as the status of the channels
 * @param ch_statment it is necessary to substitute the channel strategy number
 * @param just_check_online (0 - The function is just to check whether the module 
 * is online or not) (1 - full-fledged verification with channels)
 * @param power_cycle_mops  18v/24v/28v
 */
void check_mops_online_status(unsigned short ch_statment, unsigned short just_check_online, unsigned short power_cycle_mops)
{
    unsigned short mops_num_ = 0;
    size_t mops_num = sizeof(Stand.active_mops)/sizeof(Stand.active_mops[0]);
    for(mops_num_ = 0; mops_num_ < mops_num; mops_num_++)
    {
        if(Stand.active_mops[mops_num_] > 0 && Stand.mops_timeout_err[mops_num_] <= 1)  // ActivMOPS == 1 && connection with modul == 1
        {
            Stand.mops_timeout_err[mops_num_] = 0;
            Stand_sw.mops_timeout_err[mops_num_] = 0;
            MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment.mops_online = 1;
            if(just_check_online == 0){continue;}  // just check online end function
            memcpy(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_current_ch_status, MOPS_S_arr[mops_num_].status, sizeof(unsigned short)*8);
        }
        if(Stand.active_mops[mops_num_] > 0 && Stand.mops_timeout_err[mops_num_] > 0)   // ActivMOPS == 1 && connection with modul == 0 // 1 - timeout
        {
            MACRO_SET_MOPS_STATMENT(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment, 0, 1, 0, 1, 0);
            continue;
        }
        if(Stand.active_mops[mops_num_] > 0 && Stand.mops_crc_err[mops_num_] > 0)   // ActivMOPS == 1 && crc error // 2 - crc error
        {
            MACRO_SET_MOPS_STATMENT(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment, 0, 2, 0, 1, 0);
            continue;
        }
        if(Stand.active_mops[mops_num_] > 0 && Stand.mops_coll_1_err[mops_num_] > 0)   // ActivMOPS == 1 && col_1 error // 3 - col_1
        {
            MACRO_SET_MOPS_STATMENT(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment, 0, 3, 0, 1, 0);
            continue;
        }
        if(Stand.active_mops[mops_num_] > 0 && Stand.mops_coll_2_err[mops_num_] > 0)   // ActivMOPS == 1 && col_2 error // 4 - col_2
        {
            MACRO_SET_MOPS_STATMENT(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment, 0, 4, 0, 1, 0);
            continue;
        }
        if(Stand.active_mops[mops_num_] > 0 && Stand.mops_coll_3_err[mops_num_] > 0)   // ActivMUPS == 1 && col_3 error // 5 - col_3
        {
            MACRO_SET_MOPS_STATMENT(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment, 0, 5, 0, 1, 0);
            continue;
        }
        if(Stand.active_mops[mops_num_] == 0)       // ActivMOPS == 0 // offline = 1
        {
            MACRO_SET_MOPS_STATMENT(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment, 0, 0, 1, 0, 0);
            continue;
        }
        unsigned short ch_num_;
        size_t ch_num = sizeof(MOPS_statment_18v[mops_num_].mops_current_ch_status)/sizeof(MOPS_statment_18v[mops_num_].mops_current_ch_status[0]);
        for(ch_num_ = 0; ch_num_ < ch_num; ch_num_++)   // start of the verification cycle for each channel
        {
            if(MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_current_ch_status[ch_num_] != ch_statment)    //check ch status //
            {
                switch(ch_statment)
                {
                    case 1: 
                    {
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_ch_statement.mops_ch_err_break[ch_num_] = 1;
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment.mops_not_operable = 1;
                        break;
                    }
                    case 2: 
                    {
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_ch_statement.mops_ch_err_normal[ch_num_] = 1;
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment.mops_not_operable = 1;
                        break;
                    }
                    case 4: 
                    {
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_ch_statement.mops_ch_err_attantion[ch_num_] = 1;
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment.mops_not_operable = 1;
                        break;
                    }
                    case 5: 
                    {
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_ch_statement.mops_ch_err_fire[ch_num_] = 1;
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment.mops_not_operable = 1;
                        break;
                    }
                    case 6: 
                    {
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_ch_statement.mops_ch_err_sc[ch_num_] = 1;
                        MACRO_SELECT_MOPS_STATMENT(power_cycle_mops)[mops_num_].mops_statment.mops_not_operable = 1;
                        break;
                    }
                }
            }
        }
    }
    return;
}

/**
 * @brief this function performs a service check of the modules MOPS
 * 
 * @param usart_a. A pointer to the port to which the main number of 530 cards 
 * is connected is passed to usart_a (start reley 4)
 * @param usart_b. The pointer to which the port is transmitted to which one 
 * 530th board is connected (end reley 84)
 * @param usart_c. this port is used to read the states of the modules (read MOPS)
 * 
 */
void mops_service_check(struct tag_usartm * usart_a, struct tag_usartm * usart_b, struct tag_usartm * usart_c)
{
    static unsigned short reley_on_cycle = 0;
    static unsigned short attantion_on_cycle = 0;
    static unsigned short fire_on_cycle = 0;
    static unsigned short sc_on_cycle = 0;
    static unsigned short break_on_cycle = 0;
    static unsigned short power_cycle = 0;  // 0 - 18v, 1 - 24v, 2 - 28v
    
    // vars for cycles
    size_t mops_size_buf = sizeof(MOPS_statment_18v)/sizeof(MOPS_statment_18v[0]);  // size == 10
    size_t mops_size_main_buf = sizeof(MOPS_statment_sw_18v[0].main_buff)/sizeof(MOPS_statment_sw_18v[0].main_buff[0]); // size == 56
    
    switch(mops_service_check_stages)
    {
        case CHECK_START_BUTTON: // this case checks that the check start button has been pressed
        {
            if(conf_stand.stand_commands.start_check_mops > 0) 
            {
                mops_service_check_stages++; 
                conf_stand.stand_commands.mops_diagnostics_in_progress = 1;
                conf_stand_sw.stand_commands.mops_diagnostics_in_progress = 0x0100;
                conf_stand.stand_commands.start_check_mops = 0; 
                conf_stand_sw.stand_commands.start_check_mops = 0;
                break;
            }
            else{mops_service_check_stages = 0; break;}
        }
        case RELEY_ON:      // turne on releys 4-84
        {
            // NORMAL
            switch(reley_on_cycle)
            {
                case 0:
                {
                    mbm_16_flag(usart_a, 1, 0, 8, _530_board_normal_mops, 115200, &var_a);   // 1id 530 board
                    if(var_a > 0)
                    {reley_on_cycle++; break;}
                    break;
                }
                case 1:
                {
                    mbm_16_flag(usart_a, 2, 0, 8, _530_board_normal_mops, 115200, &var_b);             // 2id 530 board
                    if(var_b > 0)
                    {reley_on_cycle++; break;}
                    break;
                }
                case 2:
                {
                    _530_board_normal_start_reley_4_mops[4] = MACRO_SELECT_SW_RELEY_ON_START_4(power_cycle); // 18v 24v 28v
                    mbm_16_flag(usart_a, 3, 0, 8, _530_board_normal_start_reley_4_mops, 115200, &var_c);             // 3id 530 board
                    if(var_c> 0)
                    {reley_on_cycle++; break;}
                    break;
                }
                case 3:
                {
                    mbm_16_flag(usart_a, 4, 0, 8, _530_board_84_reley_on_mops, 115200, &var_d);             // 4id 530 board
                    if(var_d > 0)
                    {reley_on_cycle = 0; break;}
                    break;
                }
                default:
                {
                    reley_on_cycle = 0; mops_service_check_stages = RELEY_ON; break;
                }
            }
            if(MACRO_MBM_END_SEND(var_a, var_b, var_c, var_d)) {MACRO_MBM_RESET_FLAGS(var_a, var_b, var_c, var_d); mops_service_check_stages++; break;}          // reset vars end exit
            break;
        }
        case WAIT_SEC_INIT:    // wait 1 second for initial modules
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mops_service_check_stages++; break;}
            else{mops_service_check_stages = WAIT_SEC_INIT; break;}
        }
        case READ_MOPS_PRE_CONNACTION:     // read modules info during 3 seconds
        {
            start_var_sec_timer = 1;
            _var_sec(3000);
            if(end_var_sec_timer == 0)
            {
                MOPS_S_control_flag(usart_c, &mups_read_flag);
            }else {mups_read_flag = 0; ++mops_service_check_stages; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case READ_MOPS_CONNACTION_STATMENT:     // check connection module and normal statment
        {
            int i = 0;
            for(i = 0; i < mops_size_buf; i++)
            {
                memset(&MACRO_SELECT_MOPS_STATMENT(power_cycle)[i], 0, sizeof(union tag_mops_stand_statment));    //clear MOPS_statment 18 24 28
            }
            check_mops_online_status(2, 1, power_cycle); // check normal
            mops_service_check_stages++;     // next step
            break;
        }
        case WRITE_ATTANTION_STATMENT:      // write the attention status to all 530 boards 
        {
            // ATTANTION
            switch(attantion_on_cycle)
            {
                case 0: 
                {
                    mbm_16_flag(usart_a, 1, 0, 8, _530_board_attantion_mops, 115200, &var_a);   // 1id 530 board, all board attantion
                    if(var_a > 0)
                    {attantion_on_cycle++; break;}
                    break;
                }
                case 1:
                {
                    mbm_16_flag(usart_a, 2, 0, 8, _530_board_attantion_mops, 115200, &var_b);   // 2id 530 board, all board attantion
                    if(var_b > 0)
                    {attantion_on_cycle++; break;}
                    break;
                }
                case 2:
                {
                    _530_board_attantion_start_reley_4_mops[4] = MACRO_SELECT_SW_RELEY_ON_START_4(power_cycle); // 18v 24v 28v
                    mbm_16_flag(usart_a, 3, 0, 8, _530_board_attantion_start_reley_4_mops, 115200, &var_c);   // 3id 530 board, 50/50 start reley 4 turne on, attantion
                    if(var_c > 0)
                    {attantion_on_cycle++; break;}
                    break;
                }
                case 3:
                {
                    mbm_16_flag(usart_a, 4, 0, 8, _530_board_84_reley_on_mops, 115200, &var_d);   // 4id 530 board, 84 reley turne on 
                    if(var_d > 0)
                    {attantion_on_cycle = 0; break;}
                    break;
                }
                default:
                {
                    attantion_on_cycle = 0; mops_service_check_stages = WRITE_ATTANTION_STATMENT; break;
                }
            }
            if(MACRO_MBM_END_SEND(var_a, var_b, var_c, var_d)) {MACRO_MBM_RESET_FLAGS(var_a, var_b, var_c, var_d); mops_service_check_stages++; break;} // reset vars end exit
            break;
        }
        case WAIT_SEC_ATTANTION:    // waiting for a second to initialize the state
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mops_service_check_stages++; break;}
            else{mops_service_check_stages = WAIT_SEC_ATTANTION; break;}
        }
        case READ_MOPS_PRE_ATTANTION:   // read modules info during 3 seconds
        {
            start_var_sec_timer = 1;
            _var_sec(3000);
            if(end_var_sec_timer == 0)
            {
                MOPS_S_control_flag(usart_c, &mups_read_flag);
            }else {mups_read_flag = 0; mops_service_check_stages++; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case READ_MOPS_ATTANTION_STATMENT:  // check attantion statment 
        {
            check_mops_online_status(4, 1, power_cycle); // check attantion
            mops_service_check_stages++;     // next step
            break;
        }
        case WRITE_FIRE_STATMENT:           // wirte fire statment to 530 boards
        {
            // FIRE
            switch(fire_on_cycle)
            {
                case 0: 
                {
                    mbm_16_flag(usart_a, 1, 0, 8, _530_board_fire_mops, 115200, &var_a);   // 1id 530 board, all board fire
                    if(var_a > 0)
                    {fire_on_cycle++; break;}
                    break;
                }
                case 1:
                {
                    mbm_16_flag(usart_a, 2, 0, 8, _530_board_fire_mops, 115200, &var_b);   // 2id 530 board, all board fire
                    if(var_b > 0)
                    {fire_on_cycle++; break;}
                    break;
                }
                case 2:
                {
                    _530_board_fire_start_reley_4_mops[4] = MACRO_SELECT_SW_RELEY_ON_START_4(power_cycle); // 18v 24v 28v
                    mbm_16_flag(usart_a, 3, 0, 8, _530_board_fire_start_reley_4_mops, 115200, &var_c);   // 3id 530 board, 50/50 start reley 4 turne on, fire
                    if(var_c > 0)
                    {fire_on_cycle++; break;}
                    break;
                }
                case 3:
                {
                    mbm_16_flag(usart_a, 4, 0, 8, _530_board_84_reley_on_mops, 115200, &var_d);   // 4id 530 board, 84 reley turne on 
                    if(var_d > 0)
                    {fire_on_cycle = 0; break;}
                    break;
                }
                default:
                {
                    fire_on_cycle = 0; mops_service_check_stages = WRITE_FIRE_STATMENT; break;
                }
            }
            if(MACRO_MBM_END_SEND(var_a, var_b, var_c, var_d)) {MACRO_MBM_RESET_FLAGS(var_a, var_b, var_c, var_d); mops_service_check_stages++; break;} // reset vars end exit
            break;
        }
        case WAIT_SEC_FIRE:         // wait 1 sec to init fire statment
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mops_service_check_stages++; break;}
            else{mops_service_check_stages = WAIT_SEC_FIRE; break;}
        }
        case READ_MOPS_PRE_FIRE:        // read modules info during 3 seconds
        {
            start_var_sec_timer = 1;
            _var_sec(3000);
            if(end_var_sec_timer == 0)
            {
                MOPS_S_control_flag(usart_c, &mups_read_flag);
            }else {mups_read_flag = 0; mops_service_check_stages++; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case READ_MOPS_FIRE_STATMENT:
        {
            check_mops_online_status(5, 1, power_cycle); // check fire
            mops_service_check_stages = WRITE_SC_STATMENT;     // next step
            break;
        }
        // SHORT CURRENT
        case WRITE_SC_STATMENT: 
        {
            switch(sc_on_cycle)
            {
                case 0: 
                {
                    mbm_16_flag(usart_a, 1, 0, 8, _530_board_short_current_mops, 115200, &var_a);   // 1id 530 board, all board sc
                    if(var_a > 0)
                    {sc_on_cycle++; break;}
                    break;
                }
                case 1:
                {
                    mbm_16_flag(usart_a, 2, 0, 8, _530_board_short_current_mops, 115200, &var_b);   // 2id 530 board, all board sc
                    if(var_b > 0)
                    {sc_on_cycle++; break;}
                    break;
                }
                case 2:
                {
                    _530_board_short_current_start_reley_4_mops[4] = MACRO_SELECT_SW_RELEY_ON_START_4(power_cycle); // 18v 24v 28v
                    mbm_16_flag(usart_a, 3, 0, 8, _530_board_short_current_start_reley_4_mops, 115200, &var_c);   // 3id 530 board, 50/50 start reley 4 turne on, sc
                    if(var_c > 0)
                    {sc_on_cycle++; break;}
                    break;
                }
                case 3:
                {
                    mbm_16_flag(usart_a, 4, 0, 8, _530_board_84_reley_on_mops, 115200, &var_d);   // 4id 530 board, 84 reley turne on 
                    if(var_d > 0)
                    {sc_on_cycle = 0; break;}
                    break;
                }
                default:
                {
                    sc_on_cycle = 0; mops_service_check_stages = WRITE_SC_STATMENT; break;
                }
            }
            if(MACRO_MBM_END_SEND(var_a, var_b, var_c, var_d)) {MACRO_MBM_RESET_FLAGS(var_a, var_b, var_c, var_d); mops_service_check_stages++; break;} // reset vars end exit
            break;
        }
        case WAIT_SEC_SC:
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mops_service_check_stages++; break;}
            else{mops_service_check_stages = WAIT_SEC_SC; break;}
        }
        case READ_MOPS_PRE_SC:
        {
            start_var_sec_timer = 1;
            _var_sec(3000);
            if(end_var_sec_timer == 0)
            {
                MOPS_S_control_flag(usart_c, &mups_read_flag);
            }else {mups_read_flag = 0; mops_service_check_stages++; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case READ_MOPS_SC_STATMENT:
        {
            check_mops_online_status(6, 1, power_cycle); // check sc
            mops_service_check_stages++;     // next step
            break;
        }
        // BREAK
        case WRITE_BREAK_STATMENT:
        {
            switch(break_on_cycle)
            {
                case 0: 
                {
                    _530_board_none_mops[4] = 0x0000; // 18v 24v 28v
                    mbm_16_flag(usart_a, 1, 0, 8, _530_board_none_mops, 115200, &var_a);   // 1id 530 board, all board sc
                    if(var_a > 0)
                    {break_on_cycle++; break;}
                    break;
                }
                case 1:
                {
                    _530_board_none_mops[4] = 0x0000; // 18v 24v 28v
                    mbm_16_flag(usart_a, 2, 0, 8, _530_board_none_mops, 115200, &var_b);   // 2id 530 board, all board sc
                    if(var_b > 0)
                    {break_on_cycle++; break;}
                    break;
                }
                case 2:
                {
                    _530_board_none_mops[4] = MACRO_SELECT_VAR_3ID_530(power_cycle);
                    mbm_16_flag(usart_a, 3, 0, 8, _530_board_none_mops, 115200, &var_c);   // 3id 530 board, 50/50 start reley 4 turne on, sc
                    if(var_c > 0)
                    {break_on_cycle++; break;}
                    break;
                }
                case 3:
                {
                    _530_board_none_mops[4] = 0x0000; // 18v 24v 28v
                    mbm_16_flag(usart_a, 4, 0, 8, _530_board_none_mops, 115200, &var_d);   // 4id 530 board, 84 reley turne on 
                    if(var_d > 0)
                    {break_on_cycle = 0; break;}
                    break;
                }
                default:
                {
                    break_on_cycle = 0; mops_service_check_stages = WRITE_BREAK_STATMENT; break;
                }
            }
            if(MACRO_MBM_END_SEND(var_a, var_b, var_c, var_d)) {MACRO_MBM_RESET_FLAGS(var_a, var_b, var_c, var_d); mops_service_check_stages++; break;} // reset vars end exit
            break;
        }
        case WAIT_SEC_BREAK:
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mops_service_check_stages++; break;}
            else{mops_service_check_stages = WAIT_SEC_BREAK; break;}
        }
        case READ_MOPS_PRE_BREAK:
        {
            start_var_sec_timer = 1;
            _var_sec(3000);
            if(end_var_sec_timer == 0)
            {
                MOPS_S_control_flag(usart_c, &mups_read_flag);
            }else {mups_read_flag = 0; mops_service_check_stages++; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case READ_MOPS_BREAK_STATMENT:
        {
            check_mops_online_status(1, 1, power_cycle); // check break
            mops_service_check_stages++;     // next step
            break;
        }
        case CHECK_POWER_CYCLE:
        {
            // check errors on current power level end set flags in to local buffef
            int check_power;
            for(check_power = 0; check_power < mops_size_buf; check_power++)
            {
                if(MACRO_SELECT_MOPS_STATMENT(power_cycle)[check_power].mops_statment.mops_not_operable >= 1)
                {
                    MACRO_SET_SUPPLY_FLAG(MACRO_SELECT_MOPS_STATMENT(power_cycle)[check_power], power_cycle, 1);
                }
                if(MACRO_SELECT_MOPS_STATMENT(power_cycle)[check_power].mops_statment.mops_not_operable <= 0)
                {
                    MACRO_SET_SUPPLY_FLAG(MACRO_SELECT_MOPS_STATMENT(power_cycle)[check_power], power_cycle, 0);
                }
            }
            
            // COPY and SWAP the buffer for data swap to transfer to the top
            int i, ii;
            for(i = 0; i < mops_size_buf; i++)    
            {
                for(ii = 0; ii <= mops_size_main_buf; ii++)
                {
                    MACRO_SELECT_MOPS_STATMENT_SW(power_cycle)[i].main_buff[ii] = swapshort(MACRO_SELECT_MOPS_STATMENT(power_cycle)[i].main_buff[ii]);
                }
            }
            
            ++power_cycle;  // increase the power supply
            // EXITE
            if(power_cycle > 2) // end if power supply == 28v
            {
                mops_service_check_stages = CHECK_START_BUTTON; // end
                power_cycle = 0;
                
                conf_stand.stand_commands.mops_diagnostics_in_progress = 0;
                conf_stand_sw.stand_commands.mops_diagnostics_in_progress = 0;
                break;
            }
            // NEXT POWER STEP
            if(power_cycle <= 2)    // up power
            {
                mops_service_check_stages = RELEY_ON;   // start again with apped supply
                break;
            }
            break;
        }
    }
}
//====== MUPS AREA ======//
/**
 * @brief this function checks the status of the connection to the module, as 
 *        well as the status of the channels
 * @param ch_strategy it is necessary to substitute the channel strategy number
 * @param just_check_online (0 - The function is just to check whether the module 
 * @param id_mups it is used only when checking one module if just_check_online 
 *        is set to 0, if not used then set the value to 0
 * @param single_module_mode set 0 if you want to test one module, set 1 if you 
 *        want to test all modules is online or not) (1 - full-fledged 
 *        verification with channels)
 * @param power_toggle current supply valtage 18v 24v 28v
 */
void check_mups_online_status(unsigned short ch_statment, unsigned short just_check_online, unsigned short id_mups, unsigned short single_module_mode, unsigned short power_toggle)
{
    switch(single_module_mode)
    {
        case 0:             // single module
        {
            if(Stand.active_mups[id_mups] > 0 && Stand.mups_timeout_err[id_mups] <= 1)  // ActivMUPS == 1 && connection with modul == 1
            {
                Stand.mups_timeout_err[id_mups] = 0;
                Stand_sw.mups_timeout_err[id_mups] = 0;
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 1, 0, 0, 0, 0); // online flag up
                if(just_check_online == 0){return;}  // just check online end function
                memcpy(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups].mups_current_ch_status, MUPS_S_arr[id_mups].Ch_State, sizeof(unsigned short)*4);  // copy current ch status
            }
            if(Stand.active_mups[id_mups] > 0 && Stand.mups_timeout_err[id_mups] > 0)   // ActivMUPS == 1 && connection with modul == 0   // 1 - timeout
            {
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 0, 1, 0, 1, 0); // online_err ^1; not_oper ^1
                return;
            }
            if(Stand.active_mups[id_mups] > 0 && Stand.mups_crc_err[id_mups] > 0)   // ActivMUPS == 1 && crc error    // 2 - crc
            {
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 0, 2, 0, 1, 0); // online_err ^2; not_oper ^1
                return;
            }
            if(Stand.active_mups[id_mups] > 0 && Stand.mups_coll_1_err[id_mups] > 0)   // ActivMUPS == 1 && col_1 error // 3 - col_1
            {
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 0, 3, 0, 1, 0); // online_err ^3; not_oper ^1
                return;
            }
            if(Stand.active_mups[id_mups] > 0 && Stand.mups_coll_2_err[id_mups] > 0)   // ActivMUPS == 1 && col_2 error // 4 - col_2
            {
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 0, 4, 0, 1, 0); // online_err ^4; not_oper ^1
                return;
            }
            if(Stand.active_mups[id_mups] > 0 && Stand.mups_coll_3_err[id_mups] > 0)   // ActivMUPS == 1 && col_3 error // 5 - col_3
            {
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 0, 5, 0, 1, 0); // online_err ^5; not_oper ^1
                return;
            }
            if(Stand.active_mups[id_mups] == 0)       // ActivMOPS == 0 // offline 
            {
                MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups], 0, 0, 1, 0, 0); // offline ^1
                return;
            }
            unsigned short ch_num_;
            size_t ch_num = sizeof(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups].mups_current_ch_status)/sizeof(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups].mups_current_ch_status[0]);
            for(ch_num_ = 0; ch_num_ < ch_num; ch_num_++)   // start of the verification cycle for each channel
            {
                if(MACRO_SELECT_MUPS_STATMENT(power_toggle)[id_mups].mups_current_ch_status[ch_num_] != ch_statment)    //check ch status
                {
                    MACRO_SET_ERR_CH_FLAG(MACRO_SELECT_MUPS_STATMENT(power_toggle), ch_statment, id_mups, ch_num_);     // set ch error
                }
            }
            break;
        }
        case 1:             // all avalible modules
        {
            unsigned short mups_num_ = 0;
            size_t mups_num = sizeof(Stand.active_mups)/sizeof(Stand.active_mups[0]);
            for(mups_num_ = 0; mups_num_ < mups_num; mups_num_++)
            {
                if(Stand.active_mups[mups_num_] > 0 && Stand.mups_timeout_err[mups_num_] <= 1)  // ActivMUPS == 1 && connection with modul == 1
                {
                    Stand.mups_timeout_err[mups_num_] = 0;
                    Stand_sw.mups_timeout_err[mups_num_] = 0;
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 1, 0, 0, 0, 0); // online flag up
                    if(just_check_online == 0){continue;}  // just check online end function
                    memcpy(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_].mups_current_ch_status, MUPS_S_arr[mups_num_].Ch_State, sizeof(unsigned short)*4);
                }
                if(Stand.active_mups[mups_num_] > 0 && Stand.mups_timeout_err[mups_num_] > 0)   // ActivMUPS == 1 && connection with modul == 0  // 1 - timeout
                {
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 0, 1, 0, 1, 0); // online_err ^1; not_oper ^1
                    continue;
                }
                if(Stand.active_mups[mups_num_] > 0 && Stand.mups_crc_err[mups_num_] > 0)   // ActivMUPS == 1 && crc error  // 1 - crc
                {
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 0, 2, 0, 1, 0); // online_err ^2; not_oper ^1
                    continue;
                }
                if(Stand.active_mups[mups_num_] > 0 && Stand.mups_coll_1_err[mups_num_] > 0)   // ActivMUPS == 1 && col_1 error  // 3 - col_1
                {
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 0, 3, 0, 1, 0); // online_err ^3; not_oper ^1
                    continue;
                }
                if(Stand.active_mups[mups_num_] > 0 && Stand.mups_coll_2_err[mups_num_] > 0)   // ActivMUPS == 1 && col_2 error  // 4 - col_2
                {
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 0, 4, 0, 1, 0); // online_err ^4; not_oper ^1
                    continue;
                }
                if(Stand.active_mups[mups_num_] > 0 && Stand.mups_coll_3_err[mups_num_] > 0)   // ActivMUPS == 1 && col_3 error  // 5 - col_3
                {
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 0, 5, 0, 1, 0); // online_err ^3; not_oper ^1
                    continue;
                }
                if(Stand.active_mups[mups_num_] == 0)       // ActivMOPS == 0
                {
                    MACRO_SET_MUPS_STATMENT(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_], 0, 0, 1, 0, 0); // offline ^1
                    continue;
                }
                unsigned short ch_num_;
                size_t ch_num = sizeof(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_].mups_current_ch_status)/sizeof(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_].mups_current_ch_status[0]);
                for(ch_num_ = 0; ch_num_ < ch_num; ch_num_++)   // start of the verification cycle for each channel
                {
                    if(MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_num_].mups_current_ch_status[ch_num_] != ch_statment)    //check ch status
                    {
                        MACRO_SET_ERR_CH_FLAG(MACRO_SELECT_MUPS_STATMENT(power_toggle), ch_statment, mups_num_, ch_num_);     // set ch error
                    }
                }
            }
            break;
        }
    }
    return;
}


// vars for mups check
enum 
{
    CHECK_BUTTON_TO_START_CHECK_MUPS,               // start check service cycle if button turned on
    TURNE_ON_18V,                                   // apply a reduced power supply of 18 volts
    WRITE_DOWN_THE_DEFAULT_STRATEGY,                // write to all mups strategy 1 fire fighting
    TEST_READING_MODULES,
    WRITE_TURNE_OFF_MUPS_RELEYS,
    TEST_READING_MODULES_2,                         // read again all modules
    TURNE_OFF_ALL_REALAYS,                          // Turn off all relays to check the status (1) breakage
    ONE_SEC_DELAY_INIT_BREAK,                       // a delay of 1 second before reading the status break
    READ_MODULS_BREAK,                              // reading the status of the modules for 1 second
    DATA_ANALYSIS_BREAK,                            // subtraction of breakage states on channels
    TURNE_ON_RELEY_NORMA,                           //
    ONE_SEC_DELAY_INIT_NORMA,                       //
    READ_MODULS_NORMA,                              //
    DATA_ANALYSIS_NORMA,                            //
    TURNE_ON_RELEY_SC,                              //
    ONE_SEC_DELAY_INIT_SC,                          //
    READ_MODULS_SC,                                 //
    DATA_ANALYSIS_SC,                               //
    ALL_RELEYS_TURNE_OFF,                           //
    /*individual v*/
    CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM,     //
    TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE,            //
    ONE_SEC_DELAY_INIT_SEPARATE_MODULE_NORM,
    READ_SEPARATE_MODULE_NORM,
    DATA_ANALYSIS_SEPARATE_MODULE_NORM,
    TURNE_ON_RELEYS_HIGH_CURRENT,
    ONE_SEC_DELAY_INIT_SEPARATE_MODULE_HIGH_CURRENT,
    READ_SEPARATE_MODULE_HIGH_CURRENT,
    DATA_ANALYSIS_SEPARATE_HIGH_CURRENT,
    TURNE_OFF_RELEYS_HIGH_CURRENT,
    TURNE_OFF_RELEYS_IN_SEPARATE_MODULE,
    TURNE_OFF_LOAS_RELEYS_FOR_MODULE,
    CHECK
}mups_service_stages;



unsigned short mups_strat_buff[4] = {0x0100, 0x0100, 0x0100, 0x0100};
unsigned short mups_start_rel_buff[4] = {0x0200, 0x0200, 0x0200, 0x0200};
unsigned short mups_com_1_rel_on[4] = {0x0100, 0x0100, 0x0100, 0x0100};


/**
 * @brief
 * @param usart_d_4
 * @param usart_e_2
 * @param usart_f_5
 */
void mups_service_check(struct tag_usartm* usart_d_4, struct tag_usartm* usart_e_2, struct tag_usartm* usart_f_5)
{
    // vars for function
    static unsigned short read_mups_conf = 0;       // read mupses status
    static unsigned short mups_mbm_flag_d = 0;      // flag port 4
    static unsigned short mups_mbm_flag_e = 0;      // flag port 2
    static unsigned short mups_mbm_flag_f = 0;      // flag port 5
    static unsigned short mups_id = 0;              // mups id counter
    unsigned short _530_board_supply_u4_ap3_id3 = 3;    // for ap3    
    unsigned short _530_board_u5_ap5_id1 = 1;           // for ap5
    unsigned short _530_board_u4_ap4_id4 = 4;           // for ap4
    unsigned short _530_board_start_register = 0;
    unsigned short _530_board_quant_reg = 8;
    unsigned short mups_reley_start_reg = 208;          // reley
    unsigned short mups_reley_quant_reg = 4;
    unsigned short mups_strat_start_reg = 212;          // strategy
    unsigned short mups_strat_quant_reg = 4;
    static unsigned short individual_moduls_num = 1;
    unsigned short time_delay = 2000;
    static unsigned short try_again = 0;            // var for CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM
    static unsigned short power_toggle = 0;         // toggle for power suply 18v 24v 28v
    
    
    size_t mups_size_buf = sizeof(MUPS_statment_18v)/sizeof(MUPS_statment_18v[0]);  // size == 10
    size_t mups_size_main_buf = sizeof(MUPS_statment_sw_18v[0].main_buff)/sizeof(MUPS_statment_sw_18v[0].main_buff[0]); // size == 36
    
    
    switch(mups_service_stages) 
    {
        case CHECK_BUTTON_TO_START_CHECK_MUPS:          // check button start test
        {
            if(conf_stand.stand_commands.start_check_mups > 0)
            {
                mups_service_stages = TURNE_ON_18V; 
                conf_stand.stand_commands.mups_diagnostics_in_progress = 1;
                conf_stand_sw.stand_commands.mups_diagnostics_in_progress= 0x0100;
                conf_stand.stand_commands.start_check_mups = 0; 
                conf_stand_sw.stand_commands.start_check_mups = 0; 
                int i = 0;
                for(i = 0; i < mups_size_buf; i++) {memset(&MACRO_SELECT_MUPS_STATMENT(power_toggle)[i], 0, sizeof(union tag_mups_stand_statment));} //clear MUPS_statment
                break;
            }
            else{mups_service_stages = CHECK_BUTTON_TO_START_CHECK_MUPS; break;}
        }
        case TURNE_ON_18V:                              // AP3 CAB11
        {
            mups_mbm_flag_d = 0;
            mbm_16_flag(usart_d_4, _530_board_supply_u4_ap3_id3, _530_board_start_register, _530_board_quant_reg, MACRO_530_SUPPLY(power_toggle), 115200, &mups_mbm_flag_d);
            if(mups_mbm_flag_d != 0)
                {mups_mbm_flag_d = 0; mups_service_stages = TEST_READING_MODULES; break;}
            else if(mups_mbm_flag_d == 0)
                {mups_service_stages = TURNE_ON_18V; break;}
            break;
        }
        case TEST_READING_MODULES:                  // just read mupses online status for next case
        {
           start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = WRITE_DOWN_THE_DEFAULT_STRATEGY; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break; 
        }
        case WRITE_DOWN_THE_DEFAULT_STRATEGY:       // write strategy 1 - oborudovanie
        {
            check_mups_online_status(0, 0, 0, 1, power_toggle); 
            if(mups_id >= 10){mups_id = 0; mups_service_stages = WRITE_TURNE_OFF_MUPS_RELEYS; break;}
            if(Stand.active_mups[mups_id] != 0 && MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_id].mups_statment.mups_online == 1)
                {mups_mbm_flag_e = 0; mbm_16_flag(usart_e_2, (mups_id + 1), mups_strat_start_reg, mups_strat_quant_reg, mups_strat_buff, 115200, &mups_mbm_flag_e);} 
            else 
                {mups_id++;}
            if(mups_mbm_flag_e > 0)
                {mups_id++; mups_service_stages = WRITE_DOWN_THE_DEFAULT_STRATEGY; break;}
            break;
        }
        case WRITE_TURNE_OFF_MUPS_RELEYS:           // releys in all mups turne off
        { 
            if(mups_id >= 10){mups_id = 0; mups_service_stages = TEST_READING_MODULES_2; break;}
            if(Stand.active_mups[mups_id] != 0 && MACRO_SELECT_MUPS_STATMENT(power_toggle)[mups_id].mups_statment.mups_online == 1)
                {mups_mbm_flag_e = 0; mbm_16_flag(usart_e_2, (mups_id + 1), mups_reley_start_reg, mups_reley_quant_reg, mups_start_rel_buff, 115200, &mups_mbm_flag_e);} 
            else 
                {mups_id++;}
            if(mups_mbm_flag_e > 0)
                {mups_id++; mups_service_stages = WRITE_TURNE_OFF_MUPS_RELEYS; break;}
            break;
        }
        case TEST_READING_MODULES_2:                // just read mupses online status
        {
            start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = TURNE_OFF_ALL_REALAYS; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case TURNE_OFF_ALL_REALAYS:                 // AP4(id4) CAB13-14-19 turne off releys // AP5 (id1) CAB15-16-17-18 turne off releys for break status
        {
            mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, _530_board_all_releys_off_for_break, 115200, &mups_mbm_flag_d);
            mbm_16_flag(usart_f_5, _530_board_u5_ap5_id1, _530_board_start_register, _530_board_quant_reg, _530_board_all_releys_off_for_break, 115200, &mups_mbm_flag_f);
            if(mups_mbm_flag_d != 0 && mups_mbm_flag_f !=0)
                {mups_mbm_flag_d = 0; mups_mbm_flag_f = 0; mups_service_stages = ONE_SEC_DELAY_INIT_BREAK; break;}
            else if(mups_mbm_flag_d == 0 || mups_mbm_flag_f == 0)
                {mups_service_stages = TURNE_OFF_ALL_REALAYS; break;}
            break;
        }
        case ONE_SEC_DELAY_INIT_BREAK:              // just delay during 1 sec to init
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mups_service_stages = READ_MODULS_BREAK; break;}
            else{mups_service_stages = ONE_SEC_DELAY_INIT_BREAK; break;}
        }
        case READ_MODULS_BREAK:                     // just read ALL mups modules
        {
            start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = DATA_ANALYSIS_BREAK; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case DATA_ANALYSIS_BREAK:                   // analysis break status in ALL mups modules
        {
            check_mups_online_status(1, 1, 0, 1, power_toggle);
            mups_service_stages = TURNE_ON_RELEY_NORMA;
            break;
        }
        case TURNE_ON_RELEY_NORMA:                  // AP4(id4) CAB19 turne on releys // AP5 (id1) CAB15-16-17-18 turne on releys } to status norm ch off
        {
            mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, _530_mups_88_91_94_reley_on_ap4, 115200, &mups_mbm_flag_d);
            mbm_16_flag(usart_f_5, _530_board_u5_ap5_id1, _530_board_start_register, _530_board_quant_reg, _530_mups_88_91_94_reley_on_ap5, 115200, &mups_mbm_flag_f);
            if(mups_mbm_flag_d != 0 && mups_mbm_flag_f !=0)
                {mups_mbm_flag_d = 0; mups_mbm_flag_f = 0; mups_service_stages = ONE_SEC_DELAY_INIT_NORMA; break;}
            else if(mups_mbm_flag_d == 0 || mups_mbm_flag_f == 0)
                {mups_service_stages = TURNE_ON_RELEY_NORMA; break;}
            break;
        }
        case ONE_SEC_DELAY_INIT_NORMA:              // just delay during 1 sec to init
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mups_service_stages = READ_MODULS_NORMA; break;}
            else{mups_service_stages = ONE_SEC_DELAY_INIT_NORMA; break;}
        }
        case READ_MODULS_NORMA:                     // just read ALL mups modules
        {
            start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = DATA_ANALYSIS_NORMA; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case DATA_ANALYSIS_NORMA:                   // analysis norm ch off status in ALL mups modules
        {
            check_mups_online_status(2, 1, 0, 1, power_toggle);
            mups_service_stages = TURNE_ON_RELEY_SC;
            break;
        }
        case TURNE_ON_RELEY_SC:                     // AP4(id4) CAB19 turne on releys // AP5 (id1) CAB15-16-17-18 turne on releys } to status sc ch off
        {
            mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, _530_mups_88_89_reley_on_ap4, 115200, &mups_mbm_flag_d);
            mbm_16_flag(usart_f_5, _530_board_u5_ap5_id1, _530_board_start_register, _530_board_quant_reg, _530_mups_88_89_reley_on_ap5, 115200, &mups_mbm_flag_f);
            if(mups_mbm_flag_d != 0 && mups_mbm_flag_f !=0)
                {mups_mbm_flag_d = 0; mups_mbm_flag_f = 0; mups_service_stages = ONE_SEC_DELAY_INIT_SC; break;}
            else if(mups_mbm_flag_d == 0 || mups_mbm_flag_f == 0)
                {mups_service_stages = TURNE_ON_RELEY_SC; break;}
            break;
        }
        case ONE_SEC_DELAY_INIT_SC:                 // just delay during 1 sec to init
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mups_service_stages = READ_MODULS_SC; break;}
            else{mups_service_stages = ONE_SEC_DELAY_INIT_SC; break;}
        }
        case READ_MODULS_SC:                        // just read ALL mups modules
        {
            start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = DATA_ANALYSIS_SC; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case DATA_ANALYSIS_SC:                      // analysis sc status in ALL mups modules               
        {
            check_mups_online_status(3, 1, 0, 1, power_toggle);
            mups_service_stages = ALL_RELEYS_TURNE_OFF;
            break;
        }
        case ALL_RELEYS_TURNE_OFF:                  // AP4(id4) CAB13-14-19 turne off releys // AP5 (id1) CAB15-16-17-18 turne off releys
        {
            mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, _530_board_all_releys_off_for_break, 115200, &mups_mbm_flag_d);
            mbm_16_flag(usart_f_5, _530_board_u5_ap5_id1, _530_board_start_register, _530_board_quant_reg, _530_board_all_releys_off_for_break, 115200, &mups_mbm_flag_f);
            if(mups_mbm_flag_d != 0 && mups_mbm_flag_f !=0)
                {mups_mbm_flag_d = 0; mups_mbm_flag_f = 0; mups_service_stages = CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM; break;}
            else if(mups_mbm_flag_d == 0 || mups_mbm_flag_f == 0)
                {mups_service_stages = ALL_RELEYS_TURNE_OFF; break;}
            break;
        }
        ///////////////////////////////////////////////////////////////        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////SEPARATE/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM:    // connect load for CURRENT mups
        {
            if(MACRO_SELECT_MUPS_STATMENT(power_toggle)[(individual_moduls_num - 1)].mups_statment.mups_online == 1)
            {
                switch(individual_moduls_num)
                {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 9:
                    {
                        mups_mbm_flag_f = 0;
                        mbm_16_flag(usart_f_5, _530_board_u5_ap5_id1, _530_board_start_register, _530_board_quant_reg, MACRO_RET_XP(individual_moduls_num), 115200, &mups_mbm_flag_f);
                        break;
                    }
                    case 2:
                    case 4:
                    case 6:
                    case 8:
                    case 10:
                    {
                        mups_mbm_flag_d = 0;
                        mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, MACRO_RET_XP(individual_moduls_num), 115200, &mups_mbm_flag_d);
                        break;
                    }
                }
                if(individual_moduls_num == 1 || individual_moduls_num == 2 || individual_moduls_num == 3 || individual_moduls_num == 4 ||
                   individual_moduls_num == 5 || individual_moduls_num == 6 || individual_moduls_num == 7 || individual_moduls_num == 8)
                {
                    if(mups_mbm_flag_f != 0 && try_again <= 2)      // turne again
                        {try_again++; mups_mbm_flag_f = 0; mups_service_stages = CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM; break;}
                    else if(mups_mbm_flag_f != 0 && try_again > 2)
                        {try_again = 0; mups_mbm_flag_f = 0; mups_service_stages = TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE; break;}
                    else if(mups_mbm_flag_f == 0)
                        {mups_service_stages = CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM; break;}
                    break;
                }
                if(individual_moduls_num == 9 || individual_moduls_num == 10)
                {
                    if(mups_mbm_flag_d != 0 && try_again <= 2)      // turne again
                        {try_again++; mups_mbm_flag_d = 0; mups_service_stages = CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM; break;}
                    else if(mups_mbm_flag_d != 0 && try_again > 2)
                        {try_again = 0; mups_mbm_flag_d = 0; mups_service_stages = TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE; break;}
                    else if(mups_mbm_flag_d == 0)
                        {mups_service_stages = CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM; break;}
                    break; 
                }
            } 
            else    // if mups not operable - skip to next mups
            {
                mups_service_stages = CHECK;
                break;
            }
        }
        case TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE:           // turne on channels IN THE CURRENT mups to com. 1 - reley turne on
        {
            mups_mbm_flag_e = 0;
            mbm_16_flag(usart_e_2, individual_moduls_num, mups_reley_start_reg, mups_reley_quant_reg, mups_com_1_rel_on, 115200, &mups_mbm_flag_e);
            
            
//            if(mups_mbm_flag_e != 0)
//                {mups_mbm_flag_e = 0; mups_service_stages = ONE_SEC_DELAY_INIT_SEPARATE_MODULE_NORM; break;}
//            else if(mups_mbm_flag_e == 0)
//                {mups_service_stages = TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE; break;}
//            break;
            
            if(mups_mbm_flag_e != 0 && try_again <= 3)
                {try_again++; mups_mbm_flag_e = 0; mups_service_stages = TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE; break;}
            else if(mups_mbm_flag_e != 0 && try_again > 3)
                {try_again = 0; mups_mbm_flag_e = 0; mups_service_stages = ONE_SEC_DELAY_INIT_SEPARATE_MODULE_NORM; break;}
            else if(mups_mbm_flag_e == 0)
                {mups_service_stages = TURNE_ON_ALL_CHS_IN_SEPARATE_MODULE; break;}
            break; 
        }
        case ONE_SEC_DELAY_INIT_SEPARATE_MODULE_NORM:       // just delay during 1 sec to init
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mups_service_stages = READ_SEPARATE_MODULE_NORM; break;}
            else{mups_service_stages = ONE_SEC_DELAY_INIT_SEPARATE_MODULE_NORM; break;}
        }
        case READ_SEPARATE_MODULE_NORM:                     // just read ALL mups modules
        {
            start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = DATA_ANALYSIS_SEPARATE_MODULE_NORM; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case DATA_ANALYSIS_SEPARATE_MODULE_NORM:           // analysis norm status IN THE CURRENT mups modul
        {
            check_mups_online_status(4, 1, (individual_moduls_num - 1), 0, power_toggle);
            mups_service_stages = TURNE_ON_RELEYS_HIGH_CURRENT;
            break;
        }
        case TURNE_ON_RELEYS_HIGH_CURRENT:                 // turne on high curren turne on releys (84-85-86-87) AP4 CAB14
        {
            mups_mbm_flag_d = 0;
            mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, high_current, 115200, &mups_mbm_flag_d);
            if(mups_mbm_flag_d != 0)
                {mups_mbm_flag_d = 0; mups_service_stages = ONE_SEC_DELAY_INIT_SEPARATE_MODULE_HIGH_CURRENT; break;}
            else if(mups_mbm_flag_d == 0)
                {mups_service_stages = TURNE_ON_RELEYS_HIGH_CURRENT; break;}
            break;
        }
        case ONE_SEC_DELAY_INIT_SEPARATE_MODULE_HIGH_CURRENT:       // just delay during 1 sec to init
        {
            start_1_sec_timer = 1;
            _1_sec();
            if(end_1_sec_timer == 1){start_1_sec_timer = 0; end_1_sec_timer = 0; mups_service_stages = READ_SEPARATE_MODULE_HIGH_CURRENT; break;}
            else{mups_service_stages = ONE_SEC_DELAY_INIT_SEPARATE_MODULE_HIGH_CURRENT; break;}
        }
        case READ_SEPARATE_MODULE_HIGH_CURRENT:                 // just read ALL mups modules
        {
            start_var_sec_timer = 1;
            _var_sec(time_delay);
            if(end_var_sec_timer == 0)
            {
                MUPS_S_control_flag(usart_e_2, &read_mups_conf);
            }else {read_mups_conf = 0; mups_service_stages = DATA_ANALYSIS_SEPARATE_HIGH_CURRENT; start_var_sec_timer = 0; end_var_sec_timer = 0; break;}
            break;
        }
        case DATA_ANALYSIS_SEPARATE_HIGH_CURRENT:               // analysis high current status IN THE CURRENT mups modul
        {
            check_mups_online_status(5, 1, (individual_moduls_num - 1), 0, power_toggle);
            mups_service_stages = TURNE_OFF_RELEYS_HIGH_CURRENT;
            break;
        }
        case TURNE_OFF_RELEYS_HIGH_CURRENT:                     // turne off high curren turne off releys (84-85-86-87) AP4 CAB14 
        {
            mups_mbm_flag_d = 0;
            mbm_16_flag(usart_d_4,_530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, none, 115200, &mups_mbm_flag_d);
            if(mups_mbm_flag_d != 0)
                {mups_mbm_flag_d = 0; mups_service_stages = TURNE_OFF_RELEYS_IN_SEPARATE_MODULE; break;}
            else if(mups_mbm_flag_d == 0)
                {mups_service_stages = TURNE_OFF_RELEYS_HIGH_CURRENT; break;}
            break;
        }
        case TURNE_OFF_RELEYS_IN_SEPARATE_MODULE:               // turne off releys IN THE CURRENT mups module com.1 - releys off
        {
            mups_mbm_flag_e = 0;
            mbm_16_flag(usart_e_2, individual_moduls_num, mups_reley_start_reg, mups_reley_quant_reg, mups_start_rel_buff, 115200, &mups_mbm_flag_e);
            if(mups_mbm_flag_e != 0)
                {mups_mbm_flag_e= 0; mups_service_stages = TURNE_OFF_LOAS_RELEYS_FOR_MODULE; break;}
            else if(mups_mbm_flag_e == 0)
                {mups_service_stages = TURNE_OFF_RELEYS_IN_SEPARATE_MODULE; break;}
            break;
        }
        case TURNE_OFF_LOAS_RELEYS_FOR_MODULE:                  // turne off load 
        {
            mbm_16_flag(usart_d_4, _530_board_u4_ap4_id4, _530_board_start_register, _530_board_quant_reg, none, 115200, &mups_mbm_flag_d);
            mbm_16_flag(usart_f_5, _530_board_u5_ap5_id1, _530_board_start_register, _530_board_quant_reg, none, 115200, &mups_mbm_flag_f);
            if(mups_mbm_flag_d != 0 && mups_mbm_flag_f !=0)
                {mups_mbm_flag_d = 0; mups_mbm_flag_f = 0; mups_service_stages = CHECK; break;}
            else if(mups_mbm_flag_d == 0 || mups_mbm_flag_f == 0)
                {mups_service_stages = TURNE_OFF_LOAS_RELEYS_FOR_MODULE; break;}
            break;
        }
        case CHECK:
        {
            // set errors on current power supply and current module
            if(MACRO_SELECT_MUPS_STATMENT(power_toggle)[individual_moduls_num].mups_statment.mups_not_operable == 1)
            {
                MACRO_SET_MUPS_SUPPLY_FLAG(MACRO_SELECT_MUPS_STATMENT(power_toggle)[individual_moduls_num], power_toggle, 1);
            }
            else {MACRO_SET_MUPS_SUPPLY_FLAG(MACRO_SELECT_MUPS_STATMENT(power_toggle)[individual_moduls_num], power_toggle, 0);}
            
            // swap and copy current module 
            int i = 0;
            for(i = 0; i < mups_size_main_buf; i++)
            {
                MACRO_SELECT_MUPS_STATMENT_SW(power_toggle)[individual_moduls_num].main_buff[i] = swapshort(MACRO_SELECT_MUPS_STATMENT(power_toggle)[individual_moduls_num].main_buff[i]);
            }
            
            ++individual_moduls_num;    // incr mups id
            
            // EXITE
            if(individual_moduls_num > mups_size_buf && power_toggle == 2)
            {
                individual_moduls_num = 0;
                power_toggle = 0;
                mups_service_stages = CHECK_BUTTON_TO_START_CHECK_MUPS;
                
                // clear stand flags
                conf_stand.stand_commands.mups_diagnostics_in_progress = 0;
                conf_stand_sw.stand_commands.mups_diagnostics_in_progress = 0;
                
//                // clear timeout errors 
//                // timeout
//                memset(&Stand.mups_timeout_err, 0, sizeof(Stand.mups_timeout_err));
//                // crc
//                memset(&Stand.mups_crc_err, 0, sizeof(Stand.mups_crc_err));
//                // col_1
//                memset(&Stand.mups_coll_1_err, 0, sizeof(Stand.mups_coll_1_err));
//                // col_2
//                memset(&Stand.mups_coll_2_err, 0, sizeof(Stand.mups_coll_2_err));
//                // col_3
//                memset(&Stand.mups_coll_3_err, 0, sizeof(Stand.mups_coll_3_err));
                
                break;
            }
            // UP SUPPLY
            else if(individual_moduls_num > mups_size_buf && power_toggle < 2)
            {
                individual_moduls_num = 0;
                power_toggle++;
                mups_service_stages = TURNE_ON_18V;
                break;
            }
            // NEXT MUPS
            else if(individual_moduls_num <= mups_size_buf)
            {
                mups_service_stages = CONNECT_A_SEPARATE_MODULE_TO_THE_LOAD_NORM;
                break;
            }
            break;
        }
    }
}