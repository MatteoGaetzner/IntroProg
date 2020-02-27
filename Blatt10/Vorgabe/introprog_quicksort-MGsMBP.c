#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "quicksort.h"

/*****************************************************
 * Die benoetigten structs findet Ihr in quicksort.h *
 *****************************************************/

void init_list(list* mylist)
{
    mylist->first = NULL;
    mylist->last = NULL;
}

// Diese Funktion fügt Listenelemente an die Liste an
void insert_list(list_element* le, list* mylist)
{
    if (mylist->last == NULL && mylist->first == NULL)
    {
        mylist->first = le;
        mylist->last = le;
    } else 
    {
        mylist->last->next = le;
        mylist->last = le;
    }
}

// Speicher für Listenelemente wieder freigeben
void free_list(list* mylist)
{
    list_element *head = mylist->first;
    list_element *tmp;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->password);
        free(tmp);
    }
}

list_element *make_ele(char* password, int n)
{
    list_element * ele = malloc(sizeof *ele);
    ele->password = malloc(sizeof(char) * (strlen(password)+2));
    strcpy(ele->password, password);
    ele->count = n;
    ele->next = NULL;
    return ele;
}

void reverse_string(char* string)
{
    char tmp[strlen(string)];
    int k = strlen(string)-1;
    for (int i = 0; i <= strlen(string)-1; ++i)
    {
        tmp[i] = string[k];
        k--;
    }
    tmp[strlen(string)] = '\0';
    strcpy(string, tmp);
}

// Namen, Zahlen Paare in Liste einlesen
void read_data(char* filename, list* mylist)
{
     // FILE * fPointer;
     //    fPointer = fopen(filename, "r");
     //    char line[256] = "";
     //    while (fgets(line, sizeof(line), fPointer)) {
     //        char password[256] = "";
     //        int n = 0;
            
     //        // char number[32] = "";
     //        // reverse_string(line);
     //        // printf("%s\n", line);
     //        // sscanf(line, "%s %[^\n]", number, password);
     //        // sscanf(password, "%[^\n]", password);
     //        // reverse_string(number);
     //        // reverse_string(password);
     //        // n = atoi(number);

     //        sscanf(line, "%s %d", password, &n);

     //        list_element *lele = make_ele(password, n);
     //        insert_list(lele, mylist);
     //    }
     //    fclose(fPointer);
    char *line_buf = NULL;
    size_t line_buf_size = 0;
    int line_count = 0;
    ssize_t line_size;
    FILE * fPointer;
    fPointer = fopen(filename, "r");
    if (!fPointer)
    {
        printf("Error opening file '%s'\n", filename);
        exit(-1);
    }
    line_size = getline(&line_buf, &line_buf_size, fPointer);
    while (line_size >= 0)
    {
      char password[256] = "";
      int n = 0;
      /* Increment our line count */
      line_count++;
    
      /* Show the line details */
      sscanf(line_buf, "%s %d", password, &n);
      list_element *lele = make_ele(password, n);
      insert_list(lele, mylist);

      /* Get the next line */
      line_size = getline(&line_buf, &line_buf_size, fPointer);
    }
    
    /* Free the allocated line buffer */
    free(line_buf);
    line_buf = NULL;

    fclose(fPointer);
}

int i = 0;
// Liste teilen. Teillisten werden in left und right zurück gegeben
list_element* partition( list* input, list* left, list* right )
{
    printf("List %d:\n", i);
    print_list(input);
    printf("\n");
    i++;
    if (input->last != input->first)
    {
        list_element * pivot = input->first;
        list_element * head = input->first->next;
        list_element * tmp = head;
        while(head != NULL)
        {
            tmp = head;
            head = head->next;
            tmp->next = NULL;
            if (tmp->count < pivot->count)
            {
                if (left->last == NULL)
                {
                    left->first = tmp;
                    left->last = tmp;
                } else {
                    left->last->next = tmp;
                    left->last = tmp;
                }
            } else {
                if (right->last == NULL)
                {
                    right->first = tmp;
                    right->last = tmp;
                } else {
                    right->last->next = tmp;
                    right->last = tmp;
                }
            }
        }
    }
    return input->first;
}


// Hauptfunktion des quicksort Algorithmus
void qsort_list(list* mylist)
{
    if (mylist->first == mylist->last)
    {
        return;
    } else {    
        list * left;
        list * right;
        left->first = NULL;
        left->last = NULL;
        right->first = NULL;
        right->last = NULL;
        list_element * pivot = partition(mylist, left, right);
        qsort_list(left);
        qsort_list(right);
        if (left->first == NULL)
        {
            mylist->first = pivot;
        } else {
            mylist->first = left->first;
            left->last->next = pivot;
        }
        if (right->first == NULL)
        {
            mylist->last = pivot;
            pivot->next = NULL;
        } else {
            pivot->next = right->first;
            mylist->last = right->last;
        }
        mylist->last->next = NULL;
        free(left);
        free(right);
    }
}

void check_list(list* mylist)
{

}

// Liste ausgeben
void print_list(list* mylist)
{
        list_element * head = mylist->first;
        while(head != NULL)
        {
            printf("%s %d\n", head->password, head->count);
            head = head->next;
        }
}

