#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;
int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    for (int i = 0; i < len; ++i)
    {
        count_array[input_array[i]] = count_array[input_array[i]]+1;
    }
}

void count_sort_write_output_array(int count_array[], int len, int output_array[]) {
    int k = 0;
    for (int i = 0; i < MAX_VALUE; ++i)
    {
        for (int j = 0; j < count_array[i]; ++j)
        {
            output_array[k] = i;
            k++;
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier alle nötigen Deklarationen und Funktionsaufrufe für
     * Countsort einfügen!
     */
    int *count_array = malloc(MAX_VALUE*sizeof(int));
    int *output_array = malloc(MAX_LAENGE*sizeof(int));
    count_sort_calculate_counts(input_array, len, count_array);
    count_sort_write_output_array(count_array, len, output_array);
    print_array(output_array, len);
    free(count_array);
    free(output_array);
    return 0;
}
