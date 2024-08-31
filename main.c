#include <stdio.h>
#include "headers.h"


int main(){
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
            printf("Random Input");
            exit(0);
            break;
    }

    return 0;
}
