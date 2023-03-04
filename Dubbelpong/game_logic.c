
 #include "player_points.h"
 #include "game_logic.h"
 //#include "delay.h"

void new_game(POBJECT paddle1, POBJECT paddle2, POBJECT ball) {
    player1_points = 0;
    player2_points = 0;
    
    
    end_game = 0;
    
    // RESET PADDLE POSITION
    paddle1->clear(paddle1);
    paddle1->posy = 30;
    paddle1->draw(paddle1);
    
    paddle2->clear(paddle2);
    paddle2->posy= 30;
    paddle2->draw(paddle2);
    
    
   
    remove_GO();
    
    initialize_player_points();
    
    delay_mikro(10);
    
    restart_game(paddle1, ball);
    
}

void restart_game(POBJECT p, POBJECT o) {
    int newx,newy;
        
    o-> clear(o);
    newx=o->dirx+o->posx;
    newy=o->diry+o->posy;
    
    newx = 60;
    newy = 10;
    
    //int random_number = rand();
    
    o->posx = newx;
    o->posy = newy;
    o-> draw(o);
    
    if (player1_points > player2_points) {
        o->set_speed(o,4,2);
    } else {
        o->set_speed(o,-4,2);
    }
    //o->set_speed(o,-4,2);
    
    remove_GO();
}

void kbdActivate(unsigned int row)
{
    switch (row)
    {
        case 1:
            *GPIO_ODR_HIGH = 0x10;
            break;
        case 2:
            *GPIO_ODR_HIGH = 0x20;
            break;
        case 3:
            *GPIO_ODR_HIGH = 0x40;
            break;
        case 4:
            *GPIO_ODR_HIGH = 0x80;
            break;
        case 0:
            *GPIO_ODR_HIGH = 0x00;
            break;
    }
}

// from slides
int kbdGetCol(void)
{
    unsigned int c;
    c = *GPIO_IDR_HIGH;
    if (c & 0x8) return 4;
    if (c & 0x4) return 3;
    if (c & 0x2) return 2;
    if (c & 0x1) return 1;
    return 0;
}

unsigned char keyb(void)
{
    unsigned char key[] = { 1, 2, 3, 0xA, 4, 5, 6, 0xB, 7, 8, 9, 0xC, 0xE, 0, 0xF, 0xD
    };

    int row, col;
    for (row = 1; row <= 4; row++)
    {
        kbdActivate(row);
        if ((col = kbdGetCol()))
        {
            return key[4 *(row - 1) + (col - 1)];
        }
    }

    kbdActivate(0);
    return 0xFF;
}



int object_intersect(POBJECT p, POBJECT b) {
    
    int paddle_x = p->posx;
    int paddle_min_x = p->posx + p->geo->sizex;
    int paddle_max_y = p->geo->sizey + p->posy;
    int paddle_min_y = p->posy;
    
    for (int i = 0; i < b->geo->numpoints; i++) {
        POINT ball_p = {b->geo->px[i].x + b->posx, b->geo->px[i].y+b->posy};
        
        if (ball_p.x >= paddle_x && ball_p.x <= paddle_min_x && ball_p.y <= paddle_max_y && ball_p.y >= paddle_min_y) {
            return 1;
        }
      
    }
    
    return 0;
}

int compare_points(POINT p1, POINT p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        return 1;
    } else {
        return 0;
    }
}