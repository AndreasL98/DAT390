/*
 * 	startup.c
 *
 */
 
#include "delay.h"
#include "ascii.h"
#include "player_points.h"
#include "game_logic.h"

int end_game = 0;
 
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */

#define SIMULATOR

//klocka
#define STK			0xE000E010
#define STK_CTRL	((unsigned long *) (STK))
#define STK_LOAD	((unsigned long *) (STK+0x4))
#define STK_VAL		((unsigned long *)(STK+0x8))

}



__attribute__((naked))
void graphic_initalize(void){
	__asm volatile (".HWORD 0xDFF0\n");
	__asm volatile ("BX LR \n");
}

__attribute__((naked))
void graphic_clear_screen(void){
	__asm volatile (".HWORD 0xDFF1\n");
	__asm volatile ("BX LR \n");
}

__attribute__((naked))
void graphic_pixel_set(int x,int y){
	__asm volatile (".HWORD 0xDFF2\n");
	__asm volatile ("BX LR \n");
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y){
	__asm volatile (".HWORD 0xDFF3\n");
	__asm volatile ("BX LR \n");
}

void init_app(void)
{
    /* starta klockor port D och E */
    *((unsigned long *) 0x40023830) = 0x18;

    *GPIO_MODER = 0x55005555;
   	// pull down inputs 
    *GPIO_PUPDR = 0x00AA0000;
}


	
GEOMETRY ball_geometry={
	12,//totpixla
	4, //4x
	4,//4y
	{{0,1},{0,2},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}}//ger geometrin
};

GEOMETRY paddle_geometry={
    27, //totpix
    5, //x
    9, //y
    {{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8}, {0,0},{1,0},{2,0},{3,0},{4,0}, {2,3}, {2,4}, {2,5}, {4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8}, {0,8},{1,8},{2,8},{3,8},{4,8}}
};

////POINT points_G[] = {
//    {16, 8}, {8, 16}, {8, 40}, {16, 48},
//    {32, 48}, {40, 40}, {40, 24}, {24, 24},
//    {24, 32}, {32, 32}, {32, 40}, {24, 40}
//};

// Define the geometry for the letter G
GEOMETRY geometry_G = {
    12,   // numpoints
    4,   // sizex
    5,   // sizey
    { {1,0},{2,0},{3,0}, {0,1}, {0,2},{2,2},{3,2}, {0,3},{3,3}, {1,4},{2,4},{3,4} }
    //points_G   // px
};

GEOMETRY geometry_O = {
    12,   // numpoints
    4,   // sizex
    5,   // sizey
    { {1,0},{2,0},{3,0}, {0,1},{4,1}, {0,2},{4,2}, {0,3},{4,3}, {1,4},{2,4},{3,4} }
    //points_G   // px
};


void draw_ballobject (POBJECT o){

    for (int i=0; o->geo->numpoints > i; i++){
        graphic_pixel_set(o -> geo->px[i].x+o->posx,o->geo->px[i].y+o->posy);	
    }
}

void clear_ballobject (POBJECT o){
    for (int i =0; o->geo->numpoints > i; i++){
        graphic_pixel_clear( o-> geo ->px[i].x+o->posx,o->geo->px[i].y+o->posy);
    }
}
    
void move_ballobject(OBJECT *o){

    int newx,newy;
    o-> clear(o);
    newx=o->dirx+o->posx;
    newy=o->diry+o->posy;

    if(newx<1){
        o->set_speed(o,0,0);
        add_points(2);
        newx = 60;
        newy = 10;
    }

    if(newx>128){
        o->set_speed(o,0,0); // BALL STOPS MOVING. YOU LOST
   
        add_points(1);
        newx = 60;
        newy = 10;
            
    }

    if(newy<1){
        o->diry=-o->diry;
        newy=1;
    }
    if(newy>64){
        o->diry=-o->diry;
        newy=64;
    }
    o->posx = newx;
    o->posy = newy;
    o-> draw(o);

}


void reverse_object_directon(POBJECT o) {
    int newx,newy;
    o-> clear(o);
    newx=o->dirx+o->posx;
    newy=o->diry+o->posy;
    
    o->dirx=-o->dirx;
    //o->diry=-o->diry;
    
    //o->posx = newx;
    //o->posy = newy;
    o-> draw(o);
    
}
    
void move_paddleobject(POBJECT o){

    int newx,newy;

    o-> clear(o);

    newx=o->dirx+o->posx;
    newy=o->diry+o->posy;
    
    if(newy<1){
        o->diry=-o->diry;
        newy=1;
    }
    if(newy>64){
        o->diry=-o->diry;
        newy=64;
    }
    o->posx = newx;
    o->posy = newy;
    o-> draw(o);
        
    o->set_speed(o,0,0); //Så att den slutar röra sig om man släpper tangenten.
}

set_ballobject_speed(POBJECT o, int speedx,int speedy){
	o->dirx = speedx;
	o->diry = speedy;
    
    //o->set_speed(o,0,0); //Så att den slutar röra sig.
}



static OBJECT ball_object= {
	&ball_geometry,
	//0.0,
	//1.1,
    4,2, // 2,1
    60,20,
	draw_ballobject,
	clear_ballobject,
	move_ballobject,
	set_ballobject_speed
};

static OBJECT paddle_object= {
	&paddle_geometry,
	0,0,
	120,30,
	draw_ballobject,
	clear_ballobject,
	move_paddleobject,
	set_ballobject_speed
};

static OBJECT paddle2_object= {
	&paddle_geometry,
	0,0,
	5,30,
	draw_ballobject,
	clear_ballobject,
	move_paddleobject,
	set_ballobject_speed
};

static OBJECT object_G = {
	&geometry_G,
	//0.0,
	//1.1,
    0,0,
    55,30,
	draw_ballobject,
	clear_ballobject,
	move_ballobject,
	set_ballobject_speed
};
static OBJECT object_O = {
	&geometry_O,
	//0.0,
	//1.1,
    0,0,
    65,30,
	draw_ballobject,
	clear_ballobject,
	move_ballobject,
	set_ballobject_speed
};


void main (void) {
    
    char c;
    POBJECT p = &ball_object;
    POBJECT paddle = &paddle_object;

    POBJECT paddle2 = &paddle2_object;

    init_app();
    graphic_initalize();
    graphic_clear_screen();

    paddle_object.move = &move_paddleobject;
    paddle_object.draw = &draw_ballobject;

    paddle2_object.move = &move_paddleobject;
    paddle2_object.draw = &draw_ballobject;

    ball_object.move = &move_ballobject;
    ball_object.draw = &draw_ballobject;


    initialize_player_points(); // Initalize ASCII and set points to 0
 
    while(1){
        
        p->move (p);
        delay_milli(1); //ORG=20
        paddle->move(paddle);
        paddle2->move(paddle2);
        
        int intersect1 = object_intersect(paddle, p);
        int intersect2 = object_intersect(paddle2, p);
        //int intersect = 0;
        if (intersect1 || intersect2) reverse_object_directon(p);
        
        c=keyb();
            switch(c){
            
            case 5: 
                if (end_game) new_game(paddle, paddle2, p);
                else restart_game(paddle, p);
                break;
            
            case 1: paddle2->set_speed(paddle2,0,-3);break;
            case 7: paddle2->set_speed(paddle2,0,3);break;
            
            case 3: paddle->set_speed(paddle,0,-3);break;
            case 9: paddle->set_speed(paddle,0,3);break;
            }
    }

 }

POBJECT g_l = &object_G;
POBJECT o_l = &object_O;

draw_GO() {
   //POBJECT g = &object_G;
   object_G.move = &move_ballobject;
   object_G.draw = &draw_ballobject;
   g_l->move(g_l);
   
   //POBJECT o = &object_O;
   object_O.move = &move_ballobject;
   object_O.draw = &draw_ballobject;
   o_l->move(o_l);
}

remove_GO() {
    g_l-> clear(g_l);
    o_l->clear(o_l);
}

