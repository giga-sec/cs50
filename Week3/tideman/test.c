// Important: See first ArrayDynamicMemory.C for more context
// Abstract: Simplifies the process of ArrayDynamicMemory.C
// Title: Realloc Function

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // List of size 3 and put numbers on it
    int *list = malloc(3 * sizeof(int)); if (list == NULL) { return 1; } list[0] = 1;    list[1] = 2;    list[2] = 3;


    // Realloc is basically copying the values of "list"
    // At the same time, increasing the size of it by 4
    list = realloc(list, 4 * sizeof(int));


    // Since we now have a 4 size list.
    // We can now safely add number to list
    list[3] = 4;


    // Print list
    for (int i = 0; i < 4; i++) { printf("%i\n", list[i]); }


    free(list); return 0;
}