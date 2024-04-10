#include <xc.h>
#include <p32xxxx.h>
#include "def.h"
#include "str.h"


int count1, count2;     //tesc com

extern void InitSys(void);  //agagin test com
extern void timer_1_init(void); //test comment
extern void timer_2_init(void);
extern void port_init(void);
extern void stop_uart_tx(void);
extern void uart5_init (void);

void main(void) {
    
    //initialization
    InitSys();
    port_init();
    
    timer_1_init();
    timer_2_init();
    uart5_init();
    
    
    while(1){
        stop_uart_tx();
    }
}
