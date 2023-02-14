#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    char *word;
    // int help;
    struct node *next;
}
node;

node *pointer;



int main()
{
    if (fopen("dictionaries/large", "w") != NULL)
    {
        printf("File Opened");
    }
}