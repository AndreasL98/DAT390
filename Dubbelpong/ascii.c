/*
 * 	startup.c
 *
 */
 
 #include "ascii.h"
 #include "delay.h"
 
__attribute__((naked)) __attribute__((section (".start_section")) )
void ascii_startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */

//#define SIMULATOR

#define PORT_BASE 0x40021000  
#define GPIO_MODER  ((volatile unsigned int *) (PORT_BASE))  
#define GPIO_OTYPER ((volatile unsigned short *) (PORT_BASE+0x4)) 
#define GPIO_OSPEEDR ((volatile unsigned int *) (PORT_BASE+0x08))
#define GPIO_PUPDR  ((volatile unsigned int *) (PORT_BASE+0xC))    
#define GPIO_IDRLSB ((volatile unsigned char *) (PORT_BASE+0x10)) 
#define GPIO_IDRMSB ((volatile unsigned char *) (PORT_BASE+0x11))
#define GPIO_ODRLSB ((volatile unsigned char *) (PORT_BASE+0x14))
#define GPIO_ODRMSB ((volatile unsigned char *) (PORT_BASE+0x15))

#define Bargraph ((volatile unsigned char *) (PORT_BASE+0x14))
#define STK	 0xE000E010
#define STK_CTRL ((unsigned long *) (STK))
#define STK_LOAD ((unsigned long *) (STK+0x4))
#define STK_VAL ((unsigned long *)(STK+0x8))

#define B_E 0x40
#define B_SELECT 4
#define B_RW 2
#define B_RS 1

}



void init_ascii_app(void) {


    // starta klockor port D och E 
//((unsigned long *) (0x40023830)) = 0x18;
*((unsigned long *) (0x40023830)) = 0x18;


// port D medium speed
*((volatile unsigned int *)0x40020C08) = 0x55555555;

    *GPIO_MODER= 0x55555555;// alla ut
	*GPIO_PUPDR= 0x55550000;//input ports pullup
	*GPIO_OTYPER &= 0xFFFF0000;
    *GPIO_OSPEEDR = 0x55555555;
}



// From Slides
void ascii_ctrl_bit_set( char x ) {
    char c;
    c = *GPIO_ODRLSB;
    *GPIO_ODRLSB = B_SELECT | x | c;
}

// From Slides
void ascii_ctrl_bit_clear(char x) {
    char c;
    c = *GPIO_ODRLSB;
    c = c & ~x;
    *GPIO_ODRLSB = B_SELECT | c;
}

// From Slides
char ascii_read_controller(void) {
    char c;
    ascii_ctrl_bit_set(B_E);
    
    delay_250ns();
    delay_250ns();
    
    c = *GPIO_IDRLSB;
    
    ascii_ctrl_bit_clear(B_E);
    
    return c;
}

// From Slides
void ascii_write_controller(char c) {
    ascii_ctrl_bit_set(B_E);
    *GPIO_ODRMSB = c;
    delay_250ns();
    ascii_ctrl_bit_clear(B_E);
    
}

// From Slides
char ascii_read_status(void) {
    char c;
    *GPIO_MODER = 0x00005555;
    ascii_ctrl_bit_set(B_RW);
    ascii_ctrl_bit_clear(B_RS);
    c = ascii_read_controller();
    
    *GPIO_MODER = 0x55555555;
    return c;
}


//Implementation (Book)
unsigned char ascii_read_data(void) {
    *GPIO_MODER = 0x00005555;
    
    ascii_ctrl_bit_set(B_RW);
    ascii_ctrl_bit_clear(B_RS);
}

//Implementation (Book)
void ascii_write_cmd(unsigned char command) {
    
    ascii_ctrl_bit_clear(B_RS);
    ascii_ctrl_bit_clear(B_RW);
    
    ascii_write_controller(command);
}

//Implementation (Book)
void ascii_write_data(unsigned char data) {
    
    ascii_ctrl_bit_set(B_RS);
    ascii_ctrl_bit_clear(B_RW);
    
    ascii_write_controller(data);
}

void ascii_write_char(unsigned char c, int delay)
{
    while ((ascii_read_status() &0x80) == 0x80) {}
    delay_mikro(8); /*latenstid för kommando */
	
    ascii_write_data(c);
    delay_mikro(delay);
}

void ascii_init()
{
   	// function
    while ((ascii_read_status() &0x80) == 0x80) {}
    delay_mikro(8); /*latenstid för kommando */
	
    ascii_write_cmd(0x38);
    delay_mikro(39);
    while ((ascii_read_status() &0x80) == 0x80) {}
    delay_mikro(8); /*latenstid för kommando */

   	// activate display
    ascii_write_cmd(0x0C);
    delay_mikro(39);
    while ((ascii_read_status() &0x80) == 0x80) {}

    delay_mikro(8); /*latenstid för kommando */

   	// from slides
    /*vänta tills display är klar att ta emot kommando */
    while ((ascii_read_status() &0x80) == 0x80) {}

    delay_mikro(8); /*latenstid för kommando */
    ascii_write_cmd(1); /*kommando: "Clear display" */
    delay_milli(2); /*i stället för 1,53 ms */

   	// entry mode
    ascii_write_cmd(6);
    //delay_mikro(39);
}

void ascii_gotoxy1(char x, char y)
{
    char address;

    if (y != 1)
    {
       	// why tho??
        address = 0x40 | (x - 1);
    }
    else
    {
        address = x - 1;
    }

    ascii_write_cmd(0x80 | address);
}

void ascii_gotoxy(char x, char y)
{
    char address;
    
    //if ( y == 2) address = address + 0x40;
    if ( y == 2) address = 0x40 | (x - 1);
    else address = x-1;

    ascii_write_cmd(0x80 | address);
    
}

void write_top_display(char text[], int delay) {
    //ascii_init();
    ascii_gotoxy(1,1);
    char *s;
    s = text;
    while(*s) {
        ascii_write_char(*s++, delay);
    }
}

void write_bottom_display(char text[], int delay) {
    
    ascii_gotoxy(1,2);
    char *s;
    s = text;
    while(*s) {
        ascii_write_char(*s++, delay);
    }
}

void main_1(void)
{
	
    char *s;
    char test1[] = "How is 8+8=4?";
    char test2[] = "Rotate the clock.";
    
    init_app();
    
    ascii_init();
    ascii_gotoxy(1,1);
    s = test1;
    while(*s) {
        //ascii_write_char(*s++);
    }
    ascii_gotoxy(1,2);
    s=test2;
    while(*s) {
        ///ascii_write_char(*s++);
    }
    return 0;
}


