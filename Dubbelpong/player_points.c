

#include "ascii.h"
#include "player_points.h"
#include "game_logic.h"

int player1_points = 0;
int player2_points = 0;

// function to get the length of a string
int strLength(char* str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

// function to convert an integer to a string
void intToString(int num, char* str) {
    int i = 0, rem, len = 0, n;

    n = num;

    // count the number of digits in the number
    while (n != 0) {
        len++;
        n /= 10;
    }

    // convert the number to a string by extracting the digits
    for (i = 0; i < len; i++) {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';  // add null terminator to the end of the string
}

void add_to_string(int* len, char* string, char* text) {
    
    for (int i = 0; i < strLength(string); i++){
        text[(*len)] = string[i];
        (*len)++;
    }
}

void add_points(int player) {
    if (player == 1) {
        
        player1_points++;
        set_player_points(1,0);
    }
    if (player == 2) {
        player2_points++;
        set_player_points(2,0);
    }
    
    check_for_winner();
    

}

void check_for_winner() {
    if (player1_points >= 1 || player2_points >= 1){
        
        if (player1_points >= (player2_points + 2)) {
            //PLayer 1 Wins
            end_game = 1;
            draw_GO();
            
            char top_row[] = "Player 1 Wins!!   ";
            write_top_display(top_row, 5);
             
            char bottom_row[] = "Press 5 for rematch!";
            write_bottom_display(bottom_row, 5);
            
            
            
        } 
        
        if (player2_points >= (player1_points + 2)) {
            // Player 2 Wins
            end_game = 1;
            draw_GO();
            
            char top_row[] = "Player 2 Wins!!   ";
            write_top_display(top_row, 10);
             
            char bottom_row[] = "Press 5 for rematch!";
            write_bottom_display(bottom_row, 10);
            
        }
    }
}

void initialize_player_points() {
    ascii_init();
    player1_points = 0;
    player2_points = 0;
    
     set_player_points(1, 10);
     set_player_points(2, 10);
}

void set_player_points(int player, int delay) {
    char initial_text1[] = "Player 1:";
    char initial_text2[] = "Player 2:";
    char player_text[20];
    int len = 0;
    
    if (player == 1) add_to_string(&len, initial_text1, player_text);
    if (player == 2) add_to_string(&len, initial_text2, player_text);

    //add_to_string(&len, initial_text, player_text);
    
    char s_points[5];
    int p_points;
    if (player == 1) p_points = player1_points;
    if (player == 2) p_points = player2_points;
    
    if (p_points == 0) {
        s_points[0] = '0';
        s_points[1] = '\0';
    } else {
        intToString(p_points, s_points);
    }
    
    
    player_text[len] = ' ';
    len++;
    add_to_string(&len, s_points, player_text); 
    
    char end_string[] = " points";
    add_to_string(&len, end_string, player_text);
    
    player_text[len] = '\0';
    
    
    if (player == 1) write_top_display(player_text, delay);
    if (player == 2) write_bottom_display(player_text, delay);
    //return 0;
}




int generate_text(int p1_points, int p2_points) {
    

    
    
    char initial_text[] = "Player 1:";
    char my_text[20];
    
    int len = 0;
    //for (int i = 0; i < strLength(my_text1); i++){
    //    my_text[i] = my_text1[i];
    //    len++;
    //}
    add_to_string(&len, initial_text, my_text);
    
    char s_points[5];
    //intToString(p_points, s_points);
    
    my_text[len] = ' ';
    len++;
    
    add_to_string(&len, s_points, my_text);
    //for (int i = 0; i < strLength(s_points); i++){
    //    my_text[len] = s_points[i];
    //    len++;
    //}
     
    
    char end_string[] = " points";
    add_to_string(&len, end_string, my_text);
    //for (int i = 0; i < strLength(end_string); i++){
    //    my_text[len] = end_string[i];
    //    len++;
    //}
    
    //my_text[len] = '0';
    //len++;
    my_text[len] = '\0';
    
    write_bottom_display(my_text, 0);
    return 0;
    
    

    

    // output the final string
    //for (i = 0; i < 25 + strLength(points_str); i++) {
    //    printf("%c", text[i]);
    //}
    //printf("\n");
    //write_bottom_display(points_str, 0);
    

    //return 0;
}
