#include "core/terminal_control.h"
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>

// If you change anything to homescreen char arr, change here and in print_centre.c file also.
void print_centre(char* arr, int row, int col);

char homepage();
