#include <proc/p32mz1024efh100.h>
#include <xc.h>
#include <sys/attribs.h>
#include "define.h"
#include "extern.h"

enum 
{
	START_MM = 0,
    READ_MM_1,
    R_WAIT_MM_1,
    CHECK_MM_1,
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



///////////////// InCap	///////////////////////
void group_read (struct tag_usart * usart)
{
    
}

void MM_control (struct tag_usart * usart)
{
unsigned short control_stat;
    
    switch (control_stat) 
        {
        case START_MM: {}
        default : {control_stat = START_MM;}
        }
            

}



/* *****************************************************************************
 End of File
 */
