#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;
int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    for(int j = 0; j < len; j++){
        count_array[input_array[j]] += 1;
    }
}

void count_sort_write_output_array(int output_array[], int len, int count_array[]) {
    int k = 1;
    for (size_t h = 0; h < len; h++)
    {
        for (size_t i = 0; i < count_array[h]; i++)
        {
            output_array[k] = h;
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
    int count_array[MAX_LAENGE];
    int output_array [MAX_LAENGE];

    count_sort_calculate_counts(input_array, len, count_array);

    int len_count_array = sizeof(count_array)/sizeof(count_array[0]);

    count_sort_write_output_array(count_array, len_count_array, output_array);
    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    print_array(output_array, len);
    
    return 0;
}
