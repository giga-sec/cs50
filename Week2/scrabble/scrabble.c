#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

string str_toUpper(char str[]);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }
}

string str_toUpper(char str[])
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        int c = str[i];  // c means character

        // Skips if already in uppercase
        if ((c >= 'A') && (c <= 'Z'))
        {
            continue;
        }

        // Convert lower to UPPER
        str[i] = toupper(str[i]);
    }
    return str;
}


int compute_score(string word)
{
    // TODO: Compute and return score for string
    // ltr means letter
    // pos means position

    // Convert every letter to uppercase
    string uppercase_word = str_toUpper(word);



    int len = strlen(uppercase_word);
    int points = 0;
    char ltr;
    for (int i = 0; i < len; i++)
    {
        ltr = uppercase_word[i];

        // Make non letter be zero points
        // Also assumes that every letter is only uppercase
        if ((ltr >= 94) || (ltr <= 64))
        {
            points += 0;
        }
        else  // Assumes that everything are letters
        {
            int pos = ltr - 65;  // Ascii `A` - 65 equates to 0
            points += POINTS[pos];
        }
    }
    return points;
}
