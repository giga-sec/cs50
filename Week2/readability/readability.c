#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>


int str_length(char str[])
{
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        len++;
    }
    return len;
}


int count_sentences(char str[])
{
    int len = str_length(str);
    int n_sentences = 0;
    char c;  // c means character

    for (int i = 0; i < len; i++)
    {
        c = str[i];
        if ((c == '.') || (c == '!') || (c == '?'))
        {
            n_sentences++;
        }
    }
    return n_sentences;
}


int count_words(char str[])
{
    int len = str_length(str);
    int n_words = 0;
    char c;  // c means character

    // Start counting words
    for (int i = 0; i < len; i++)
    {
        c = str[i];
        if (c == ' ')
        {
            n_words++;
        }
    }
    // Word at the end of the sentence isn't counted on for loop
    n_words++;  // so we count it manually;
    return n_words;
}


int count_letters(char str[])
{
    int len = str_length(str);
    int n_letters = 0;
    char c;  // c means character

    // Start counting letters
    for (int i = 0; i < len; i++)
    {
        c = str[i];
        if (isalpha(c) != 0)
        {
            n_letters++;
        }
    }
    return n_letters;
}


int main(void)
{
    string inputted_paragraph = get_string("Text: ");

    float n_letters = count_letters(inputted_paragraph);
    float n_words = count_words(inputted_paragraph);
    float n_sentences = count_sentences(inputted_paragraph);

    // Coleman-Liau
    float L = (n_letters / n_words) * 100.0;  // average number of letters per 100 words
    float S = (n_sentences / n_words) * 100.0;  // average number of sentences per 100 words

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}