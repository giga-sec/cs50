#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int str_isAlpha(char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] >= 'A') && (str[i] <= 'Z'))
        {
            continue;
        }
        else if ((str[i] >= 'a') && (str[i] <= 'z'))
        {
            continue;
        }
        else // if its not Alphabetical
        {
            return 1;
        }
    }
    return 0;  // All characters are alphabet
}


int main(int argc, string argv[])
{
    if (str_isAlpha(argv[1]) == 0)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}