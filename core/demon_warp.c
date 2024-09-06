#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <signal.h>


// Gracefully shutdown the process.
bool kill_demon_warp(){
    // Open file which store PID.
    FILE* pid_warp = NULL;
    pid_warp = fopen(".pid.warp", "r");
    if(pid_warp == NULL) return 0;

    // Variables to store 
    int pid;
    bool killed = 0;

  // Check if fscanf successfully reads PID.
    if (fscanf(pid_warp, "%d", &pid) == 1) {
        // Attempt to send killing signal to the process
        if (kill(pid, SIGTERM) == 0) {
            killed = true; // Successfully Killed
        } else {
            fclose(pid_warp);
            if(!remove(".pid.warp"));
            return 0;
        }
    } 

    // Close and remove the PID file
    fclose(pid_warp);
    if(!remove(".pid.warp"));
    return killed;
}


// Remove the top reminder for a given file.
void remove_top_reminder(char *filename){
    // Open file.
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    // Create a temporary file
    char temp_filename[1000];
    snprintf(temp_filename, sizeof(temp_filename), "%s%s", filename, ".tmp");
    FILE *temp_file = fopen(temp_filename, "w");
    if (temp_file == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    // Skip the first line
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            break;  // Skip the first line
        }
    }

    // Copy the rest of the file to the temporary file
    while ((ch = fgetc(file)) != EOF) {
        fputc(ch, temp_file);
    }

    // Close files
    fclose(file);
    fclose(temp_file);

    // Replace original file with temporary file
    if (remove(filename) != 0) {
        perror("Error deleting original file");
        return;
    }
    if (rename(temp_filename, filename) != 0) {
        perror("Error renaming temporary file");
    }

    return;
}



// Demon process job.
void repeatedly_check_reminder(){
    while(1){
        // Variables to compare current and reminder time.
        time_t curr_time;
        long int reminder_time = 0;
        
        // Open .time.warp file to read reminder time.
        FILE* file_time = NULL;
        file_time = fopen(".time.warp", "r");
        // If file doesn't exist.
        if(file_time == NULL){
            sleep(5);
            continue;
        }
        
        // Get first value from .time.warp 
        char buffer[11];
        // Read to the variable and check if file is empty.
        if(fgets(buffer, sizeof(buffer), file_time) == NULL){
            fclose(file_time);
            sleep(5);
            continue;
        }
        // Close .time.warp file
        fclose(file_time);

        // Convert string time to number.
        reminder_time = atoi(buffer);

        // If reminder is due.
        curr_time = time(NULL);
        if(reminder_time <= curr_time){
            // Take first reminder from .reminder.warp
            FILE* file_reminder = NULL;
            file_reminder = fopen(".reminder.warp", "r");
            char reminder[1000];
            fgets(reminder, sizeof(reminder), file_reminder);
            fclose(file_reminder);
            
            // Create the command string.
            char notify[1050];
            reminder[strcspn(reminder, "\n")] = 0;
            int result = snprintf(notify, sizeof(notify), "notify-send -t 15000 \"%s\"", reminder);
            // Call the command string.
            system(notify);

            //After Successfully reminding, free memory and delete the top reminder. 
            remove_top_reminder(".time.warp"); 
            remove_top_reminder(".reminder.warp"); 
        }

        // Sleep some time.
        sleep(5);
    }
}





// Start Tracking for Reminders.
void make_demon_warp(){
    // Making Demon Process
    int P_ID = fork();
    switch (P_ID){
        case -1:
            // Error Forking();
            printf("An Error Occurred while creating demon process!!!");
            exit(1);
            break;

        case 0:
            //Child Process
            repeatedly_check_reminder();
            break;
                
        default:
            // Parent Process
            // Add the child process PID to a file.
            FILE* pid_warp = NULL;
            pid_warp = fopen(".pid.warp", "w");
            if(pid_warp == NULL) exit(1);
            fprintf(pid_warp, "%d", P_ID);
            fclose(pid_warp);

            // Make sure the parent process gets terminated so child process will run in background.
            exit(0);
    }
}
