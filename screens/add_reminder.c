#include <stdio.h>
#include "screenHeaders.h"
#include <string.h>

#define REMINDER_SIZE 1000
#define MAX_REMINDERS 100

#ifndef move_cursor
#define clear_screen() puts("\x1B[2J")
#define move_cursor(row, col) printf("\x1B[%d;%dH", row, col)
#endif

// Helping Functions
bool is_future_time(int* input_date, int* input_time);
time_t get_entered_epoch_time(int* input_date, int* input_time);





bool add_reminder_to_file(char* reminder, time_t time) {
    // File names for storing reminders and time_t values
    char* reminder_filename = ".reminder.warp";
    char* time_filename = ".time.warp";

    // Open the file for the reminder in append mode
    FILE *reminder_file = fopen(reminder_filename, "a");
    if (reminder_file == NULL) {
        perror("Error opening reminder file");
        return false;
    }

    // Open the file for the time in append mode
    FILE *time_file = fopen(time_filename, "a");
    if (time_file == NULL) {
        perror("Error opening time file");
        fclose(reminder_file); // Close the reminder file if time file fails to open
        return false;
    }

    // Write the reminder to the reminder file
    fprintf(reminder_file, "%s", reminder);

    // Write the time_t value to the time file
    fprintf(time_file, "%ld\n", time);

    // Close the files
    fclose(reminder_file);
    fclose(time_file);

    return true;
}




void add_reminder(){
    int* date = NULL;
    int* time = NULL;

    clear_screen();
    move_cursor(3, 0);

    do{
        date = input_valid_date();
        time = input_valid_time();

        if(is_future_time(date, time)) break;
        else printf("Enter a future time...\n");
    
    } while(1);
    
    time_t entered_epoch_time = get_entered_epoch_time(date, time);
    
    clear_screen();
    move_cursor(3, 0);
    printf("> Date : %d/%d/%d\n", date[0], date[1], date[2]);
    printf("> Time : %d:%d\n", time[0], time[1]);
    printf("\n");
    printf("> Reminder : ");

    char* reminder = (char*) malloc(sizeof(char) * 1000);
    fgets(reminder, REMINDER_SIZE, stdin);


    if(add_reminder_to_file(reminder, entered_epoch_time)){
        sort_both_files();
    } 

    // Free the allocated memory.
    free(reminder);
    free(date);
    free(time);
    date = NULL;
    reminder = NULL;
    time = NULL;

    return ;
}





bool is_future_time(int* input_date, int* input_time){
    struct tm struct_input_time = {0};
    time_t current_time, entered_time;

    current_time = time(NULL);

    struct_input_time.tm_mday = input_date[0];
    struct_input_time.tm_mon = input_date[1] - 1;
    struct_input_time.tm_year = input_date[2] - 1900;
    struct_input_time.tm_hour = input_time[0];
    struct_input_time.tm_min = input_time[1];
    struct_input_time.tm_sec = 0;

    entered_time = mktime(&struct_input_time);

    return difftime(entered_time, current_time) > 0;
}



time_t get_entered_epoch_time(int* input_date, int* input_time){
    struct tm struct_input_time = {0};
    time_t entered_time;

    struct_input_time.tm_mday = input_date[0];
    struct_input_time.tm_mon = input_date[1] - 1;
    struct_input_time.tm_year = input_date[2] - 1900;
    struct_input_time.tm_hour = input_time[0];
    struct_input_time.tm_min = input_time[1];
    struct_input_time.tm_sec = 0;

    entered_time = mktime(&struct_input_time);

    return entered_time;
}

