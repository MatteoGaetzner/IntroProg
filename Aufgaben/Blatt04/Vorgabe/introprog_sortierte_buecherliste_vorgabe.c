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

/* HIER struct _element implementieren. */
typedef struct _element {
    char *title;
    char *author;
    int year;
    long long int isbn;
    element *next;
} element;
/* Fuege ein Element in die Liste ein, sodass die Liste aufsteigend
 * nach ISBN sortiert ist.  Dafür muss das erste Element ermittelt
 * werden, dass in der bisher sortierten Liste eine ISBN besitzt
 * die größer ist als die des neuen Elements.  Wenn die Liste leer
 * ist soll das Element direkt an den Anfang platziert werden.
 *
 * first    - Erstes Element (bzw. Anfang) der Liste
 * new_elem - Neues Element das in die Liste eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen oder alten Anfang der Liste
 * zurueck.
 */
element* insert_sorted(element *first, element *new_elem) {
   element *prev_ele = first;
   element *cur_ele = first;

   if (first == NULL)
   {
       return new_elem;
   }

   while((cur_ele != NULL) && (cur_ele->isbn < new_elem->isbn))
   {
    prev_ele = cur_ele;
    cur_ele = cur_ele->next;

    if (cur_ele == NULL)
    {
        prev_ele->next = new_elem;
        break;
    } else if (cur_ele->isbn > new_elem->isbn)
    {
        prev_ele->next = new_elem;
        new_elem->next = cur_ele;
    }
   }

   if (new_elem->isbn < first->isbn)
   {
       return new_elem;
   } else return first;
}

/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Der Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char *title, char* author, int year, long long int isbn) {

    element *new_elem = malloc(sizeof *new_elem);
    new_elem->author = malloc(strlen(author) + 1);
    new_elem->title = malloc(strlen(title) + 1);
    strcpy(new_elem->author, author);
    strcpy(new_elem->title, title);
    new_elem->year = year;
    new_elem->isbn = isbn;
    new_elem->next = NULL;
    return new_elem;
}

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list *alist) {
    element *cur_ele = alist->first;
    element *prev_ele = NULL;
    while(cur_ele != NULL){
        prev_ele = cur_ele;
        cur_ele = cur_ele->next;
        free(prev_ele);
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