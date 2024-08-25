#include <stdio.h>
#include "terminal_control.h"
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

void print_centre(char arr[13][29], int row, int col){
    clear_screen();

    // Get terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_width = w.ws_col;
    int term_height = w.ws_row;

    //Find where to start printing.
    int start_row = (term_height - row)/2;
    int start_column = (term_width - col)/2;

    //printing in center
    for(int i=0; i<row; i++){
        move_cursor(start_row+i, start_column);
        for(int j=0; j<col; j++){
            printf("%c", arr[i][j]);
        }        
    }
    return;
}

