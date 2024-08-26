#include <time.h>
// If you change anything to homescreen char arr, change here and in print_centre.c file also.
void print_centre(char arr[13][29], int row, int col);

#define convert_to_epoch(x) mktime(x)
struct tm* convert_to_struct_tm(time_t time);
void print_epoch_time(time_t time);
void print_struct_time(struct tm* time);
int compare_time(struct tm* time1, struct tm* time2);
time_t input_future_time_left();
time_t input_future_date(struct tm* future_date);