#include "delay.h"

void delay_250ns(void){
	
	*STK_CTRL = 0;
	*STK_LOAD = (0x2A-1);
	*STK_VAL=0;
	*STK_CTRL = 1;
	while((*STK_CTRL & 0x10000) == 0) {}
		*STK_CTRL = 0;
	
}

void delay_mikro(unsigned int us){
	
	for (us;us>0;us--){
		for(int i=0;i<4;i++){
			delay_250ns();
		}
	}
}
	
void delay_milli(unsigned int ms){
    int us=100;// ändrad från 1000 till 100
    
    #ifdef SIMULATOR    //För att kompensera för att simulatorn är långsam
        ms/=10000;
        ms++;
        us/=4;
    #endif
    
    for(ms;ms>0;ms--){
        delay_mikro(us);
    }
}