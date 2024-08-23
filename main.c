#include <stdio.h>
/*#include "./core/terminal_control.h"*/
#include "headers.h"


int main(){
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
    char ch;
    scanf("%c", &ch);
    if(ch == 'q'){
        clear_screen();
        move_cursor(0,0);
        exit(0);
    }

    return 0;
}
