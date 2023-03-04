#ifndef DELAY_H
#define DELAY_H

//klocka
#define STK			0xE000E010
#define STK_CTRL	((unsigned long *) (STK))
#define STK_LOAD	((unsigned long *) (STK+0x4))
#define STK_VAL		((unsigned long *)(STK+0x8))

void delay_250ns(void);
void delay_mikro(unsigned int us);
void delay_milli(unsigned int ms);

#endif