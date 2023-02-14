#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct node
{
    int val;
    struct node *next;
}
node;



int main ()
{
    node *current_ltrs = malloc(sizeof(node));
    current_ltrs->val = 1;
    current_ltrs->next = malloc(sizeof(node));

    current_ltrs->next->val = 2;
    current_ltrs->next->next = NULL;

    while (current_ltrs != NULL)
    {
        node *tmp = current_ltrs->next;
        free(current_ltrs);
        current_ltrs = tmp;
    }

    current_ltrs = malloc(sizeof(node));
    current_ltrs->val = 3;
    current_ltrs->next = NULL;

    while (current_ltrs != NULL)
    {
        node *tmp = current_ltrs->next;
        free(current_ltrs);
        current_ltrs = tmp;
    }
}