#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int char_dupliChecker(char str[])
{
    int len = strlen(str);
    for (int i = 1; i < len; i++)
    {
        char left_c = str[i - 1];
        char c = str[i];

        if (c == left_c)
        {
            return 1;
        }
    }
    return 0;
}

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

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Duplicates aren't allowed
    if (char_dupliChecker(argv[1]) == 1)
    {
        printf("Key must not have duplicate characters.\n");
        return 1;
    }
    // Number aren't allowed
    if (str_isAlpha(argv[1]) == 1)
    {
        printf("Key must not contain numbers.\n");
        return 1;
    }



    string key = argv[1];
    string plainText = get_string("plaintext: ");
    int len_text = strlen(plainText);
    string cipheredText = plainText;  // For readability only, just a reference
    for (int i = 0; i < len_text; i++)
    {
        char c_pTXT = plainText[i]; // character of plainText
        int pos_inAlpha;
        if ((c_pTXT >= 'A') && (c_pTXT <= 'Z'))
        {
            pos_inAlpha = c_pTXT - 'A';  // index position in the alphabet(0-26)
            key[pos_inAlpha] = toupper(key[pos_inAlpha]);  // uppercase particular char of key
        }
        else if ((c_pTXT >= 'a') && (c_pTXT <= 'z'))
        {
            pos_inAlpha = c_pTXT - 'a';  // index position in the alphabet(0-26)
            key[pos_inAlpha] = tolower(key[pos_inAlpha]); // uppercase particular char of key
        }
        else  // if a special character
        {
            continue;  // leave it untouched
        }

        int p = pos_inAlpha;  // p means position
        cipheredText[i] = key[p];
    }
    printf("ciphertext: %s\n", cipheredText);

    return 0;
}