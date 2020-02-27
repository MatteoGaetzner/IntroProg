#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_structs_lists_input.h"

#define MAX_STR 255

/* Bewirkt, dass statt 'struct _element' auch 'element' verwendet
 * werden kann.
 */
typedef struct _element element; 

/* Bewirkt, dass statt 'struct _list' auch 'list' verwendet werden
 * kann.  Hier in einem geschrieben, so dass man auch 'list'
 * innerhalb der struct-Definition selbst verwenden kann.
 */
typedef struct _list { /* Separater Wurzelknoten */
    element *first;    /* Anfang/Kopf der Liste */
    int count;         /* Anzahl der Elemente */
} list;

struct _element {
    char title[MAX_STR];
    char author[MAX_STR];
    int year;
    long long int isbn;
    struct _element * next;
}_element_t;

element* insert_sorted(element *first, element *new_elem) {  
    element *current_elem;
    current_elem = first;
    element *prev_elem;

    if (first == NULL)
    {
        return new_elem;
    }

    while(current_elem != NULL && current_elem->isbn < new_elem->isbn){
        if (current_elem->next == NULL)
        {
            current_elem->next = new_elem;
            return first;
        }
        prev_elem = current_elem;
        current_elem = current_elem->next;
    }

    if (current_elem == first)
    {
        new_elem->next = first;
        return new_elem;
    }

    prev_elem->next = new_elem;
    new_elem->next = current_elem;
    
    return first;
}

element *construct_element(char *title, char* author, int year, long long int isbn) {
    element *tmp_elem;
    tmp_elem = malloc(sizeof(*tmp_elem));
    if (strlen(title) > MAX_STR)
    {
        char tmp_title[MAX_STR]; 
        for (int i = 0; i < MAX_STR-1; ++i)
        {
            tmp_title[i] = title[i];
        }
        tmp_title[MAX_STR-1]='\0';
        strcpy(tmp_elem->title, tmp_title);    
    } else {
        strcpy(tmp_elem->title, title);
    }
    strcpy(tmp_elem->author, author);
    tmp_elem->year = year;
    tmp_elem->isbn = isbn;
    tmp_elem->next = NULL;
    return tmp_elem;
}

void free_list(list *alist) {
    element* tmp;
    element* first = alist->first;
    free(alist);
    while (first != NULL)
    {
        tmp = first;
        first = first->next;
        free(tmp);
    }
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 */
void read_list(char* filename, list *alist) {
    element* new_elem;
    char* title;
    char* author;
    int year;
    long long int isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_elem = construct_element(title, author, year, isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}

/* Gib die Liste aus:
 * _Soll nicht angepasst werden_
 */
void print_list(list *alist) {
    printf("Meine Bibliothek\n================\n\n");
    int counter = 1;
    element *elem = alist->first;
    while (elem != NULL) {
        printf("Buch %d\n", counter);
        printf("\tTitel: %s\n", elem->title);
        printf("\tAutor: %s\n", elem->author);
        printf("\tJahr:  %d\n", elem->year);
        printf("\tISBN:  %lld\n", elem->isbn);
        elem = elem->next;
        counter++;
    }
}

/* Main Funktion
 * _Soll nicht angepasst werden_
 */
int main(int argc, char** argv) {
    list *alist = construct_list();
    read_list(argc>1?argv[1]:"buecherliste.txt", alist);
    print_list(alist);
    free_list(alist);
    return 0;
}
