#include <stdio.h>
#include "terminal_control.h"
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

void print_centre(char arr[13][29], int row, int col){
    
    // Get terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int term_width = w.ws_col;
    int term_height = w.ws_row;

    int start_row = (term_height - row)/2;
    int start_column = (term_width - col)/2;

    //printing in center
    for(int i=0; i<row; i++){
        move_cursor(start_row+i, start_column);
        /*printf("%s", arr[i]);*/
        for(int j=0; j<col; j++){
            printf("%c", arr[i][j]);
        }        
    }
    char ch;
    scanf("%c", &ch);
    if(ch == 'q'){
        clear_screen();
        move_cursor(0,0);
        exit(0);
    }
    return;
}

int main(){
    clear_screen();
    char arr[13][29] = {
        " _    _   ___  ______ ______",
        "| |  | | / _ \\ | ___ \\| ___ \\",
        "| |  | |/ /_\\ \\| |_/ /| |_/ /",
        "| |/\\| ||  _  ||    / |  __/ ",
        "\\  /\\  /| | | || |\\ \\ | |    ",
        " \\/  \\/ \\_| |_/\\_| \\_|\\_|    ",
        "                            ",
        "                            ",
        "> Quit                     q",
        "> Add Reminder             a",
        "> List Reminders           l",
        "                            ",
        "Your Option :              ",
    };

    print_centre(arr, 13, 29);


    return 0;
}

