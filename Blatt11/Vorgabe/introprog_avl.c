#include <stdlib.h>		
#include <stdio.h>	// Ein- / Ausgabe
#include <math.h>	// Für die Berechnungen der Ausgabe
#include "avl.h"

void adjust_height(AVLNode *node){
    if (node != NULL)
    {
        AVLNode * tmp = node;
        while(tmp != NULL){
            if (tmp->left != NULL && tmp->right != NULL)    // Calculate height of rotated node
            {
                if (tmp->left->height >= tmp->right->height)
                {
                    tmp->height = tmp->left->height - tmp->right->height;
                } else {
                    tmp->height = tmp->right->height - tmp->left->height;
                }
            } else if (tmp->left != NULL)
            {
                tmp->height = tmp->left->height + 1;
            } else if (tmp->right != NULL)
            {
                tmp->height = tmp->right->height + 1;
            } else {
                tmp->height = 0;
            }
            tmp = tmp->parent;
        }
    }
}

void recursive_walk(AVLNode* node)
{
	if (node->left != NULL && node->right != NULL)
	{
		recursive_walk(node->left);
		printf("%d[%d] ", node->value, node->height);
		recursive_walk(node->right);
	} else if (node->left != NULL)
	{
		recursive_walk(node->left);
		printf("%d[%d] ", node->value, node->height);
	} else if (node->right != NULL)
	{
		printf("%d[%d] ", node->value, node->height);
		recursive_walk(node->right);
	} else {
		printf("%d[%d] ", node->value, node->height);
	}
}

/* Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus. */
void AVL_in_order_walk(AVLTree* avlt)
{
	recursive_walk(avlt->root);
    printf("\n");
}

/* Diese Funktion führt eine Linksrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_left(AVLTree* avlt, AVLNode* x)
{
    AVLNode *y = x->right;  // y: right node
    x->right = y->left;

    if (y->left != NULL)    // if right node has left node as child assign it rotated node as new parent
    {
    	y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL)
    {
    	avlt->root = y;
    } else if (x == x->parent->left)
    {
    	x->parent->left = y;
    } else {
    	x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

    // Calculate new heights

    if (x->left != NULL && x->right != NULL)    // Calculate height of rotated node
    {
        if (x->left->height >= x->right->height)
        {
            x->height = x->left->height - x->right->height;
        } else {
            x->height = x->right->height - x->left->height;
        }
    } else if (x->left != NULL)
    {
        x->height = x->left->height + 1;
    } else if (x->right != NULL)
    {
        x->height = x->right->height + 1;
    } else {
        x->height = 0;
    }

     if (y->right != NULL) // Calculate height of right node (also rotated)
    {
        y->height = y->right->height - x->height + 1;
    } else {
        y->height = x->height + 1;
    }

    if (x->parent != NULL)
    {
        adjust_height(x->parent);
    }
}

/* Diese Funktion führt eine Rechtsrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_right(AVLTree* avlt, AVLNode* y)
{
    AVLNode *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
     {
     	x->right->parent = y;
     }
     x->parent = y->parent;
     if (y->parent == NULL)
     {
     	avlt->root = x;
     } else if (y->parent->left == y)
     {
     	y->parent->left = x;
     } else if (y->parent->right == y)
     {
     	y->parent->right = x;
     }
     x->right = y;
     y->parent = x;

     // Calculate new heights

    if (y->left != NULL && y->right != NULL)    // Calculate height of rotated node
    {
        if (y->left->height >= y->right->height)
        {
            y->height = y->left->height - y->right->height;
        } else {
            y->height = y->right->height - y->left->height;
        }
    } else if (y->left != NULL)
    {
        y->height = y->left->height + 1;
    } else if (y->right != NULL)
    {
        y->height = y->right->height + 1;
    } else {
        y->height = 0;
    }

     if (x->right != NULL) // Calculate height of left node (also rotated)
    {
        x->height = x->right->height - y->height + 1;
    } else {
        x->height = y->height + 1;
    }
    if (y->parent != NULL)
    {
        adjust_height(y->parent);
    } 
}	

/* Balanciere den Teilbaum unterhalb von node.
 * 
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen _nicht_
 * angepasst werden, da dieses schon in den Rotationen geschieht.
 * Falls dies nicht eingehalten wird funktionieren die Unit-Tests
 * ggf. nicht.
 */
void AVL_balance(AVLTree* avlt, AVLNode* node)
{	
	AVLNode * l = node->left;
	AVLNode * r = node->right;
    if (l != NULL && r != NULL)
    {
        printf("Left & Right != NULL\n");
        if (l->height > r->height + 1)
        {
            if (l->left->height < l->right->height)
            {
                printf("rotating left: %d\n", l->value);
                AVL_rotate_left(avlt, l);
            }
            printf("rotating right: %d\n", node->value);
            AVL_rotate_right(avlt, node);
        } else if (r->height > l->height + 1)
        {
            if (r->left->height > r->right->height)
            {
                printf("rotating right: %d\n", r->value);
                AVL_rotate_right(avlt, r);
            }
            printf("rotating left: %d\n", node->value);
            AVL_rotate_left(avlt, node);
        }
    } else if (l != NULL)
    {
        if (l->height >= 1)
        {
            if (l->right != NULL && l->left != NULL)
            {
                if (l->right->height > l->left->height)
                {
                    printf("rotating left: %d\n", l->value);
                    AVL_rotate_left(avlt, l);
                }
            } else if (l->right != NULL)
            {
                printf("rotating left: %d\n", l->value);
                AVL_rotate_left(avlt, l);
            }
            printf("rotating right: %d\n", node->value);
            AVL_rotate_right(avlt, node);
        }
    } else if (r != NULL)
    {
        if (r->height >= 1)
        {
            if (r->left != NULL && r->right != NULL)
            {
                if (r->left->height > r->right->height)
                {
                    printf("rotating right: %d\n", r->value);
                    AVL_rotate_right(avlt, r);
                }
            } else if (r->left != NULL)
            {
                printf("rotating right: %d\n", r->value);
                AVL_rotate_right(avlt, r);
            }
            printf("rotating left: %d\n", node->value);
            AVL_rotate_left(avlt, node);
        }
    }
}


/* Fügt der Wert value in den Baum ein.
 *
 * Die Implementierung muss sicherstellen, dass der Baum nach dem
 * Einfügen immer noch balanciert ist!
 */
void AVL_insert_value(AVLTree* avlt, int value)
{
	AVLNode * checkedNode = avlt->root;
    AVLNode * nNode = malloc(sizeof *nNode);
    nNode->left = NULL;
    nNode->right = NULL;
    nNode->parent = NULL;
    nNode->value = value;
    nNode->height = 0;
    int left = -2;

    if (checkedNode == NULL)
    {
    	avlt->root = nNode;
    	return;
    }
	
    while(checkedNode != NULL)
    {
    	if(nNode->value > checkedNode->value)
    	{
    		left = 0;
    		if (checkedNode->right != NULL)
    		{
    			checkedNode = checkedNode->right;
    		} else {
    			break;
    		}
    	} else if(nNode->value < checkedNode->value) {
    		left = 1;
    		if (checkedNode->left != NULL)
    		{
    			checkedNode = checkedNode->left;
    		} else {
    			break;
    		}
    	} else {
            left = -1;
        }
    }
	
    if (left != -1)
    {
        if (left == 1)
        {
        	checkedNode->left = nNode;
        } else {
        	checkedNode->right = nNode;
        }

        nNode->parent = checkedNode;

        // Calc height of parent
        adjust_height(nNode);
        AVLNode *tmp = nNode->parent;
        while(tmp != NULL){
            if (tmp->height >= 2)
            {
                AVL_balance(avlt, tmp);
            }
            tmp = tmp->parent;
        }
    }
}

/* Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten
 * frei.
 */
void recursive_remove(AVLNode *node){
	if (node->left != NULL && node->right != NULL)
	{
		recursive_walk(node->left);
		recursive_walk(node->right);
		free(node);
	} else if (node->left != NULL)
	{
		recursive_walk(node->left);
		free(node);
	} else if (node->right != NULL)
	{
		recursive_walk(node->right);
		free(node);
	} else {
		free(node);
	}
}

void AVL_remove_all_elements(AVLTree* avlt)
{
    recursive_remove(avlt->root);
}
