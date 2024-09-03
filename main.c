#include <stdio.h>
#include "headers.h"

void start_warp();
void handle_demon_process(char* argv[]);
void make_demon_warp();
void repeatedly_check_reminder();
void remove_top_reminder();
bool kill_demon_warp();

int main(int argc, char* argv[]){

    switch(argc){
        case 1:
            // Start Warp
            start_warp();
            break;
        
        case 2:
            // Handle Demon Process
            handle_demon_process(argv);
            break;

        default:
            printf("Give one argument only.");
            exit(0);
            break;
    }


    return 0;
}



// Start Warp
void start_warp(){
    char ch = homepage();

    switch (ch) {
        case 'q':
            exit(0);
            break;

        case 'a':
            add_reminder(); 
            break;

        case 'l':
            printf("Pressed l");
            break;

        default:
            exit(0);
            break;
    }

    return;
}



// Handle Demon Process
void handle_demon_process(char* argv[]){
    char* argument_values[] = {"init", "halt"};

    if(strcmp(argv[1], argument_values[0]) == 0){
        // Check and Start Demon Process.
        kill_demon_warp();
        make_demon_warp();
    }
    else if(strcmp(argv[1], argument_values[1]) == 0){
        // Check and kill the demon process.
        if(!kill_demon_warp()) printf("Error Killing the process");
    }
    else{
        printf("Enter valid argument");
    }
}

// Gracefully shutdown the process.
bool kill_demon_warp(){
    FILE* pid_warp = NULL;
    pid_warp = fopen(".pid.warp", "r");
    if(pid_warp == NULL) return 0;

    int pid;
    bool killed = 0;

  // Check if fscanf successfully reads an integer
    if (fscanf(pid_warp, "%d", &pid) == 1) {
        // Attempt to send SIGTERM to the process
        if (kill(pid, SIGTERM) == 0) {
            killed = true; // Successful signal sent
        } else {
            perror("Failed to send SIGTERM");
        }
    } else {
        fprintf(stderr, "Failed to read PID from file or file is empty\n");
    } 


    fclose(pid_warp);
    if(!remove(".pid.warp"));
    return killed;
}


// Start Tracking for Reminders.
void make_demon_warp(){
    // Making Demon Process
    int P_ID = fork();
    switch (P_ID){
        case -1:
            printf("An Error Occurred while creating demon process!!!");
            exit(1);
            break;

        case 0:
            //Child Process
            repeatedly_check_reminder();
            break;
                
        default:
            // Parent Process
            FILE* pid_warp = NULL;
            pid_warp = fopen(".pid.warp", "w");
            if(pid_warp == NULL) exit(1);
            fprintf(pid_warp, "%d", P_ID);
            fclose(pid_warp);

            exit(0);
    }
}


void repeatedly_check_reminder(){
    while(1){
        time_t curr_time;
        long int reminder_time = 0;
        
        // Open .time.warp file
        FILE* file_time = NULL;
        file_time = fopen(".time.warp", "r");
        // If file doesn't exist.
        if(file_time == NULL){
            sleep(5);
            continue;
        }
        
        // Get first value from .time.warp 
        char buffer[11];
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
        if(reminder_time < curr_time){
            // Take first reminder from .reminder.warp
            FILE* file_reminder = NULL;
            file_reminder = fopen(".reminder.warp", "r");
            char reminder[1000];
            fgets(reminder, sizeof(reminder), file_reminder);
            fclose(file_reminder);
            
            // Create the command string.
            char notify[1050] = "notify-send -t 15000 ";
            strcat(notify, reminder);
            // Call the command string.
            system(notify);

            remove_top_reminder(".time.warp"); 
            remove_top_reminder(".reminder.warp"); 
        }

        // Sleep some time.
        sleep(5);
    }
}




void remove_top_reminder(char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return;
    }

    // Create a temporary file
    char temp_filename[FILENAME_MAX];
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

