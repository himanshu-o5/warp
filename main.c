#include <stdio.h>
#include "./core/terminal_control.h"
#include "headers.h"


int main(){
    char ch = homepage();


    switch (ch) {
        case 'q':
            exit(0);
            break;
        
        case 'a':
            printf("Pressed a");
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
