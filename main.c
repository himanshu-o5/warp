#include <stdio.h>
#include "headers.h"


int main(int argc, char* argv[]){
    // Start according to the arguments.
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
            // Handle more cases.
            printf("Give one argument only.");
            exit(0);
            break;
    }


    return 0;
}



// Start Warp
void start_warp(){
    // Warp options.
    char ch = homepage();

    switch (ch) {
        case 'q':
            clear_screen();
            move_cursor(1, 0);
            exit(0);
            break;

        case 'a':
            // Add reminder.
            add_reminder(); 
            break;

        case 'l':
            list_reminders();
            break;

        default:
            // Handle Edge Case.
            exit(0);
            break;
    }

    return;
}



// Handle Demon Process
void handle_demon_process(char* argv[]){
    // Possible value for valid argument
    char* argument_values[] = {"init", "halt"};

    // If Run the background process.
    if(strcmp(argv[1], argument_values[0]) == 0){
        // Check and Start Demon Process.
        kill_demon_warp();
        make_demon_warp();
    }

    // To kill the background process
    else if(strcmp(argv[1], argument_values[1]) == 0){
        // Check and kill the demon process.
        if(!kill_demon_warp()) printf("Error Killing the process or process not found.");
        else printf("Killed the the prcess successfully!!!");
    }
    else{
        printf("Enter valid argument");
    }
}

