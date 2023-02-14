#include <ctype.h>
#include <cs50.h>
#include <stdio.h>


void print_spaces(int height, int n_row)
{
    for (int column = n_row; column < height; column++)
    {
        printf(" ");  // Print Spaces
    }
}

void print_hashtag(int height, int n_row)
{
    for (int column = 1; column <= n_row; column++)
    {
           printf("#");
    }
}

int height_check(int user_input)
{
    // Only accept 1 - 8 numbers and numbers only
    if ((user_input < 1) || (user_input > 8))
    {
        return 1; // The user_input inputted negative and outside of 8 numbers
    }
    return 0;  // The input didn't violated any rules
}

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height_check(height));

    for (int row = 1; row <= height; row++)
    {
        print_spaces(height, row);
        print_hashtag(height, row);
        printf("  ");  // Space in between
        print_hashtag(height, row);
        printf("\n");
    }
}

