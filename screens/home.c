#include "screenHeaders.h"
#include <stdio.h>

char homepage(){
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

    // Getting input
    char ch;


    // Error handling
    while(!(ch == 'q' || ch == 'a' || ch == 'l')){
        scanf("%c", &ch);
        // If uppercase convert to lowercase.
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch + ('a' - 'A');
        }

        // Print Homepage again.
        print_centre(arr, 13, 29);   
    }

    return ch;
}
