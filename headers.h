#include "core/terminal_control.h"
#include <time.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>


// CORE
// print_centre.c
void print_centre(char* arr, int row, int col);

// demon_warp.
void start_warp();
void handle_demon_process(char* argv[]);
void make_demon_warp();
void repeatedly_check_reminder();
void remove_top_reminder();
bool kill_demon_warp();

// sort_both_files.c
void sort_both_files();
int conpare_pairs(const void *a, const void *b);

// time.c
#define MAX_INPUT 100
#define convert_to_epoch(x) mktime(x)
int compare_time(struct tm* time1, struct tm* time2);
bool is_leap_year(int year);
bool is_valid_date(int date[3]);
void remove_extra_spaces(char* str);
void fill_input_array(int arr[], int n, char* input_string);
bool take_n_integer_input(int arr[], int n);
int* return_array(int arr[], int n);

struct tm* convert_to_struct_tm(time_t time);
void print_epoch_time(time_t time);
void print_struct_time(struct tm* time);
time_t input_time_left();
int* input_valid_date();
int* input_valid_time();


// SCREENS
// home.c
char homepage();

// add_reminder.c
bool is_future_time(int* input_date, int* input_time);
time_t get_entered_epoch_time(int* input_date, int* input_time);
bool add_reminder_to_file(char* reminder, time_t time);
void add_reminder();
