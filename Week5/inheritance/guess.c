#include <stdio.h>


typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;


int main()
{
    // int i = 0;
    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            int j = 1;
        }
        else
        {
            printf("%i", j);
        }
    }
}