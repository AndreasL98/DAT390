#ifndef ASCII_H
#define ASCII_H

//klocka
#define STK			0xE000E010
#define STK_CTRL	((unsigned long *) (STK))
#define STK_LOAD	((unsigned long *) (STK+0x4))
#define STK_VAL		((unsigned long *)(STK+0x8))

void main_1(void);
void ascii_startup ( void );
void init_ascii_app(void);
void ascii_ctrl_bit_set( char x );
void ascii_ctrl_bit_clear(char x);
char ascii_read_controller(void);
void ascii_write_controller(char c);
char ascii_read_status(void);
unsigned char ascii_read_data(void);
void ascii_write_cmd(unsigned char command);
void ascii_write_data(unsigned char data);
void ascii_write_char(unsigned char c, int delay);
void ascii_init();
void ascii_gotoxy1(char x, char y);
void ascii_gotoxy(char x, char y);
void write_top_display(char text[], int delay);
void write_bottom_display(char text[], int delay);

#endif