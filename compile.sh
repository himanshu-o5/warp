#!/bin/bash
cd core/
gcc -c demon_warp.c -o demon_warp.o
gcc -c print_centre.c -o print_centre.o
gcc -c sort_both_files.c -o sort_both_files.o
gcc -c time.c -o time.o
ar rcs lib_core.a print_centre.o time.o sort_both_files.o demon_warp.o
rm *.o
cd ..


cd screens/
gcc -c add_reminder.c -o add_reminder.o
gcc -c home.c -o home.o
gcc -c list_reminders.c -o list_reminders.o
ar rcs lib_screens.a home.o add_reminder.o list_reminders.o 
rm *.o
cd ..


gcc -c main.c -o main.o
gcc -o warp main.o -L. ./screens/lib_screens.a ./core/lib_core.a
rm *.o
rm ./screens/lib_screens.a ./core/lib_core.a

echo "Compilation Successful"
echo "You can start warp by './warp'."
