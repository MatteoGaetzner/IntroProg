#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;
int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    for(int j = 0; j < len; j++){
        if(count_array[j]<0){
            count_array[j] = 0;
        }
        count_array[input_array[j]]++;
    }
}

void count_sort_write_output_array(int count_array[], int len, int output_array[]) {
    int k = 0;
   for(int j=0; j<len; j++){
       int i = 0;
       while(i < count_array[j]){        
           output_array[k] = j;
           k++;
           i++;
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
    int *count_array = malloc(sizeof(int) * MAX_LAENGE);
    if (count_array == NULL) {
        fprintf(stderr, "Unable to allocate enough memory for array!\n");
        return -1;
    }
    int *output_array = malloc(sizeof(int) * MAX_LAENGE);
    if (output_array == NULL) {
        fprintf(stderr, "Unable to allocate enough memory for array!\n");
        return -1;
    }
    count_sort_calculate_counts(input_array, len, count_array);

    
    count_sort_write_output_array(count_array, MAX_LAENGE, output_array);
    printf("Sortiertes Array:");

    
    print_array(output_array, len);
    free(count_array);
    free(output_array);
    return 0;
}
