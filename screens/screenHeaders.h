#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// print_centre.c headers.
void print_centre(char* arr, int row, int col);

//sort_both_files.c headers.
void sort_both_files();
int conpare_pairs(const void *a, const void *b);

// time.c headers
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
