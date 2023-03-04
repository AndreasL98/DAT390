#ifndef GAMELOGIC_H
#define PLAYERPOINTS_H


#define PORT_D 0x40020C00
#define GPIO_MODER ((volatile unsigned int *)(PORT_D))
#define GPIO_OTYPER ((volatile unsigned short *)(PORT_D + 0x4))
#define GPIO_SPEEDR ((volatile unsigned int *)(PORT_D + 0x8))
#define GPIO_PUPDR ((volatile unsigned int *)(PORT_D + 0xC))
#define GPIO_IDR_LOW ((volatile unsigned char *)(PORT_D + 0x10))
#define GPIO_IDR_HIGH ((volatile unsigned char *)(PORT_D + 0x11))
#define GPIO_ODR_LOW ((volatile unsigned char *)(PORT_D + 0x14))
#define GPIO_ODR_HIGH ((volatile unsigned char *)(PORT_D + 0x15))

extern int end_game;

typedef struct{
    char x,y;
} POINT, *PPOINT;

typedef struct{
    POINT p0;
    POINT p1;
} LINE, *PLINE;


#define MAX_POINTS 30

typedef struct {
    int numpoints;
    int sizex;
    int sizey;
    POINT px [MAX_POINTS];
} GEOMETRY, *PGEOMETRY;

typedef struct tobj{
    PGEOMETRY geo;
    int dirx,diry;
    int posx,posy;
    void (*draw) (struct tobj*);
    void (*clear) (struct tobj*);
    void (*move) (struct tobj*);
    void (*set_speed) (struct tobj * ,int,int);
}OBJECT,*POBJECT;

void new_game();
void restart_game(POBJECT p, POBJECT o);
void kbdActivate(unsigned int row);
int kbdGetCol(void);
unsigned char keyb(void);
int object_intersect(POBJECT p, POBJECT b);
int compare_points(POINT p1, POINT p2);

#endif