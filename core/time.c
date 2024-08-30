#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 100

// Some helping function declaration, definition is down;
int compare_time(struct tm* time1, struct tm* time2);
bool is_leap_year(int year);
bool is_valid_date(int date[3]);
void remove_extra_spaces(char* str);
void fill_input_array(int arr[], int n, char* input_string);
bool take_n_integer_input(int arr[], int n);
int* return_array(int arr[], int n);


// Converting in different format functions.
#define convert_to_epoch(x) mktime(x)

struct tm* convert_to_struct_tm(time_t time){
    return localtime(&time);
}



// Printing functions for debugging.
void print_epoch_time(time_t time){
    printf("%s", ctime(&time));
    return;
}

void print_struct_time(struct tm* time){
    printf("%s", asctime(time));
    return;
}



// Input functions
time_t input_time_left(){
    int time_left[3]; // time_left -> 0:day, 1:hour, 2:minutes
    time_t seconds = 0;
    while(seconds<=0){
        seconds = 0;
        /*printf("Enter future time : Days, Hours, Minutes respectively : ");*/
        while(!take_n_integer_input(time_left, 3));
        if(time_left[0] < 10000){
            seconds = 24*60*60*time_left[0] + 60*60*time_left[1] + 60*time_left[2]; 
        }
    }
    return seconds;
}


int* input_valid_date(){
    int date[3];
    do{
        printf("Enter Date(dd/mm/yyyy) : ");
        while(!take_n_integer_input(date, 3));
    }
    while(!is_valid_date(date));
    /*printf("Valid Date is %d/%d/%d", date[0], date[1], date[2]);*/
    return return_array(date, 3);   
}


int* input_valid_time(){
    int time[2];
    do{
        printf("Enter time(hh/mm) : ");
        while(!take_n_integer_input(time, 2));
    }
    while(!((time[0]<24 && time[0]>=0) && (time[1]<60 && time[1]>=0)));
    /*printf("Valid time -> %d:%d", time[0], time[1]);*/

    return return_array(time, 2);
}





// Helping functions
int compare_time(struct tm* time1, struct tm* time2){
    time_t t1 = convert_to_epoch(time1);
    time_t t2 = convert_to_epoch(time2);
    
    return t1-t2;
}

int* return_array(int arr[], int n){
    int* return_ptr = (int*) malloc(sizeof(int) * n);
    for(int i=0; i<n; i++){
        return_ptr[i] = arr[i];
    }
    return return_ptr;

}


bool is_leap_year(int year){
    //Checking for leap year
    if(year % 400 == 0){
        return true;
    } else if(year % 100 == 0){
        return false;
    } else if(year % 4 == 0){
        return true;
    }
    return false;
}


bool is_valid_date(int date[3]){
    //Restrictions added
    if(date[2]>2050 || date[2]<1970) return false;
    if(date[1]<1 || date[1]>12) return false;
    if(date[0]<1) return false;

    //Days in Month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(is_leap_year(date[2])) daysInMonth[1] = 29;

    //Restriction on date
    if(date[0] > daysInMonth[date[1]-1]) return false;

    //All Conditions Passed
    return true;
}


void remove_extra_spaces(char* str){
    int start = 0;
    int end = strlen(str) - 1;

    while (isspace((unsigned char)str[start])) start++;
    while (end >= start && isspace((unsigned char)str[end])) end--;

    // Shift actual string to left.
    for (int i = start; i <= end; i++) {
        str[i - start] = str[i];
    }

    // Null terminate the string.
    str[end - start + 1] = '\0';
    return;
} 


void fill_input_array(int arr[], int n, char* input_string){
    // Making char array of input_string for strtok();
    char input_str_char_array[MAX_INPUT];
    strcpy(input_str_char_array, input_string);

    char* token;
    int i = 0;

    // Using strtok() to split the string.
    token = strtok(input_str_char_array, " ");
    while(token != NULL && i < n){
        // atoi -> string integer to integer 
        arr[i] = atoi(token);
        i++;
        token = strtok(NULL, " ");
    }

    return;    
}


bool take_n_integer_input(int arr[], int n){
    // Input a string.
    char* input_string = (char*) malloc(MAX_INPUT * sizeof(char));
    fgets(input_string, MAX_INPUT, stdin);

    // Remove starting and ending spaces. 
    char* formatted_input = input_string;
    remove_extra_spaces(formatted_input);

    // Checking if given input is number only.
    int string_length = strlen(formatted_input);
    for(int i=0; i<string_length; i++){
        if(!((formatted_input[i] >= '0' && formatted_input[i] <= '9') || formatted_input[i] == ' ')) return false;
    }
    
    // Checking if input consist of n integer inputs.
    int space_count = 0;
    for(int i=0; i<string_length; i++){
        if(formatted_input[i] == ' ') space_count++;
    }
    if(space_count != n-1) return false;


    // Filling the arrray with inputs.
    fill_input_array(arr, n, formatted_input);

    return true;
}

