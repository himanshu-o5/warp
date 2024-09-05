#include <stdio.h>
#include <time.h>
#include "screenHeaders.h"

#ifndef clear_screen
#define clear_screen() puts("\x1B[2J")
#define move_cursor(row, col) printf("\x1B[%d;%dH", row, col)
#endif 


void display_side_by_side(FILE *file1, FILE *file2) {
    char line1[12], line2[1000];

    while (1) {
        // Read one line from the first file (numbers)
        if (fgets(line1, sizeof(line1), file1) == NULL) {
            break; // Exit if end of file1 is reached
        }

        // Remove newline from the number line, if it exists
        line1[strcspn(line1, "\n")] = '\0';
        time_t reminder_time = atoi(line1);
        char* time_str = ctime(&reminder_time);
        time_str[strlen(time_str) - 1] = '\0';

        // Read one line from the second file (strings)
        if (fgets(line2, sizeof(line2), file2) == NULL) {
            break; // Exit if end of file2 is reached
        }

        // Print the number and string side by side
        printf("%s\t%s", time_str, line2);
    }
}


void list_reminders(){
    clear_screen();
    move_cursor(2, 0);
    char arr[8][51] = {
        "______ ________  ________ _   _______ ___________ ",
        "| ___ \\  ___|  \\/  |_   _| \\ | |  _  \\  ___| ___ \\",
        "| |_/ / |__ | .  . | | | |  \\| | | | | |__ | |_/ /",
        "|    /|  __|| |\\/| | | | | . ` | | | |  __||    / ",
        "| |\\ \\| |___| |  | |_| |_| |\\  | |/ /| |___| |\\ \\ ",
        "\\_| \\_\\____/\\_|  |_/\\___/\\_| \\_/___/ \\____/\\_| \\_|",
        "                                                  ",
        "                                                  "
    };

    for(int i=0; i<8; i++){
        for(int j=0; j<51; j++){
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    FILE *file1 = fopen(".time.warp", "r"); // File containing numbers
    FILE *file2 = fopen(".reminder.warp", "r"); // File containing strings

    if (file1 == NULL || file2 == NULL) {
        printf("No Reminders");
        return;
    }

    display_side_by_side(file1, file2);

    fclose(file1);
    fclose(file2);

    return;
}
