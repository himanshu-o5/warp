#include <stdio.h>
#include <time.h>
#include <stdbool.h>

// Some helping function declaration, definition is down;
int compare_time(struct tm* time1, struct tm* time2);
bool is_leap_year(int year);
bool is_valid_date(int date[3]);



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
time_t input_future_time_left(){
    int days=-1, hours=-1, minutes=-1;
    time_t seconds = 0;
    while(seconds<=0){
        seconds = 0;
        printf("Enter future time : Date, Hours, Minutes respectively : ");
        scanf("%d%d%d", &days, &hours, &minutes);
        if(days<10000){
            seconds = 24*60*60*days + 60*60*hours + 60*minutes; 
        }
    }
    return seconds;
}
//                                                                                         YOU HAVE TO CHANGE THIS RETURN TYPE!!!!!!
void input_valid_date(){
    int date[3];
    do{
        printf("Enter Date : dd/mm/yyyy : ");
        scanf("%d%d%d", &date[0], &date[1], &date[2]);
        if(!is_valid_date(date)){
            printf("Enter a valid date...\n");
        }
    }
    while(!is_valid_date(date));
    printf("Valid Date is %d/%d/%d", date[0], date[1], date[2]);
    return;   
}







int main(){
    time_t currTime = time(NULL);
    struct tm* curr_time = convert_to_struct_tm(currTime);
    print_struct_time(curr_time);
    print_epoch_time(currTime);
    // printf("%d", compare_time(curr_time, curr_time));
    // printf("%ld", input_future_time());
    input_valid_date();
    


    return 0;
}










// Helping functions
int compare_time(struct tm* time1, struct tm* time2){
    time_t t1 = convert_to_epoch(time1);
    time_t t2 = convert_to_epoch(time2);
    
    return t1-t2;
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