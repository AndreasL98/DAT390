#ifndef PLAYERPOINTS_H
#define PLAYERPOINTS_H

//klocka

extern int player1_points; //defined in source file player_points.c
extern int player2_points;

void add_points(int player);
void check_score();
void initialize_player_points();
void set_player_points(int player, int delay);
int strLength(char* str);
void intToString(int num, char* str);
int generate_text();

#endif