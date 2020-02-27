#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */

// Function to create new node
bst_node* createNewNode(unsigned long phone, char *name){
	struct bst_node* new_node = (struct bst_node*)malloc(sizeof(struct bst_node));
	char* new_name;
	new_name = (char*)malloc((strlen(name)+1)*sizeof(char));
	strcpy(new_name, name);
	new_node->phone = phone;
	new_node->name = new_name;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->parent = NULL;
	return (new_node);
}

// Function to insert new node into tree recursively
/*
void insertNode(struct bst_node* current_node, struct bst_node* new_node)
{
	unsigned long nnp = new_node->phone;
	unsigned long cnp = current_node->phone;
	if (nnp < cnp)
	{
		if (current_node->left == NULL)
		{
			current_node->left = new_node;
			return;
		} else 
		{
			insertNode(current_node->left, new_node);
		}
	}
	if (nnp > cnp)
	{
		if (current_node->right == NULL)
		{
			current_node->right = new_node;
			return;
		} else 
		{
			insertNode(current_node->right, new_node);
		}
	}
	if (nnp == cnp)
	{
		printf("%s\n", "Error: Phone number already taken");
		return;
	}
}
*/

void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
	struct bst_node* new_node = createNewNode(phone, name);
	if (bst->root == NULL)
	{
		bst->root = new_node;
	} else {	
		struct bst_node* current_node = bst->root;
		while(1 == 1)
		{
			unsigned long nnp = new_node->phone;
			unsigned long cnp = current_node->phone;
			if (nnp < cnp)
			{
				if (current_node->left == NULL)
				{
					current_node->left = new_node;
					break;
				} else 
				{
					current_node = current_node->left;
				}
			}
			else if (nnp > cnp)
			{
				if (current_node->right == NULL)
				{
					current_node->right = new_node;
					break;
				} else 
				{
					current_node = current_node->right;
				}
			}
			else if (nnp == cnp)
			{
				printf("%s\n", "Error: Telefonnummer bereits hinterlegt");
				break;
			}
		}
	}
}

/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */

bst_node* find_node(bstree* bst, unsigned long phone) {
	bst_node* current_node = bst->root;
	
	unsigned long cnp = current_node->phone;
	while(cnp != phone){
		cnp = current_node->phone; 

		if (current_node == NULL)
		{
			return NULL;
		}
		else if (cnp == phone)
		{
			return current_node;
		}
		else if (phone > cnp)
		{
			if (current_node->right != NULL)
			{
				current_node = current_node->right;
			} else {
				return NULL;
			}			
		}
		else
		{
			if (current_node->left != NULL)
			{
				current_node = current_node->left;
			} else {
				return NULL;
			}
		}
	}
	return current_node;
}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {
	struct bst_node* current_node = node;
	if (current_node->left == NULL && current_node->right == NULL)
	{
		print_node(current_node);
		return;
	} else if (current_node->left == NULL && current_node->right != NULL)
	{
		print_node(current_node);
		bst_in_order_walk_node(current_node->right);
	} else if (current_node->left != NULL && current_node->right == NULL)
	{
		bst_in_order_walk_node(current_node->left);
		print_node(current_node);
	} else if(current_node->left != NULL && current_node->right != NULL) {
		bst_in_order_walk_node(current_node->left);
		print_node(current_node);
		bst_in_order_walk_node(current_node->right);
	} else {
		return;	
	}
}

/* 
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {
	if(node->left != NULL && node->right != NULL)
	{
		bst_free_subtree(node->left);
		bst_free_subtree(node->right);
	} else if(node->left != NULL)
	{
		bst_free_subtree(node->left);
	} else if(node->right != NULL)
	{
		bst_free_subtree(node->right);
	} 
	free(node->name);
	free(node);
}

/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
