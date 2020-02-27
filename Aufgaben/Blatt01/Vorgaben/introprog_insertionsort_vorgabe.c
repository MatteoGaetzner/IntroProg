#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;

void insertion_sort(int array[], int len) {

    for (int j = 1; j < len; ++j)
    {
        int key = array[j];
        int i = j-1;
        while((i >= 0) && (array[i] > key))
        {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int array[MAX_LAENGE];
    int len = read_array_from_file(array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(array, len);

    /* Aufruf Insertionsort */
    insertion_sort(array, len);
    print_array(array, len);
    return 0;
}
