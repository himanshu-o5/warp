#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold a pair of integer and string
typedef struct {
    long int number;
    char string[100];
} Pair;

// Function to compare pairs based on the number for qsort
int compare_pairs(const void *a, const void *b) {
    Pair *pairA = (Pair *)a;
    Pair *pairB = (Pair *)b;
    return pairA->number - pairB->number;
}

void sort_both_files() {
    FILE *number_file, *string_file;
    Pair pairs[100];
    int count = 0;

    // Open files for reading
    number_file = fopen(".time.warp", "r");
    string_file = fopen(".reminder.warp", "r");

    if (number_file == NULL || string_file == NULL) {
        perror("Error opening files");
        return;
    }

    // Read pairs from the files
    while (fscanf(number_file, "%ld", &pairs[count].number) != EOF &&
           fgets(pairs[count].string, sizeof(pairs[count].string), string_file) != NULL) {
        // Remove trailing newline character from string
        pairs[count].string[strcspn(pairs[count].string, "\n")] = 0;
        count++;
    }

    // Close the input files
    fclose(number_file);
    fclose(string_file);

    // Sort the pairs based on the number
    qsort(pairs, count, sizeof(Pair), compare_pairs);

    // Open files for writing the sorted data
    number_file = fopen(".time.warp", "w");
    string_file = fopen(".reminder.warp", "w");

    if (number_file == NULL || string_file == NULL) {
        perror("Error opening files for writing");
        return;
    }

    // Write the sorted pairs back to the files
    for (int i = 0; i < count; i++) {
        fprintf(number_file, "%ld\n", pairs[i].number);
        fprintf(string_file, "%s\n", pairs[i].string);
    }

    // Close the output files
    fclose(number_file);
    fclose(string_file);

    printf("Reminder added!!! Make sure you have warp initialised by \"warp init\"\n");
}

