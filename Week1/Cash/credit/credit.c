#include <cs50.h>
#include <stdio.h>
#include <string.h>
// cc means Credit Card
// sec means second as in 2nd
// arr means array
// len means length

int get_len_ofNum(long num)
{
    int digits = 0;
    while (num != 0)
    {
        num = num / 10;  // Removes the last digit
        digits++;
    }
    return digits;
}

int get_first_digits(long cc, int n_digits_toGet)
{
    // Decides how many digits to get
    int digits_toGet = 1;  // The amount of zeros determines how many numbers to get
    for (int i = 1; i <= n_digits_toGet; i++)
    {
        digits_toGet = digits_toGet * 10;
    }

    // Reduce the numbers into the desired length of digits
    long first_digits = cc;
    while (first_digits > digits_toGet)
    {
        first_digits = first_digits / 10;
    }
    return first_digits;
}


int print_cardType(long cc)
{
    int len = get_len_ofNum(cc);
    int first_twoDigits = get_first_digits(cc, 2);

    // Determine if its AMEX
    if (first_twoDigits == 34 || 37 == first_twoDigits)
    {
        if (len == 15)
        {
            printf("AMEX\n");
            return 1;
        }
    }

    // Determine if its MASTERCARD
    // Only 51-55 numbers are accepted
    if (first_twoDigits >= 51 && 55 >= first_twoDigits)
    {
        if (len == 16)
        {
            printf("MASTERCARD\n");
            return 1;
        }
    }

    // Determine if its VISA
    int first_digit = get_first_digits(cc, 1);
    if (first_digit == 4)
    {
        if (len == 13 || 16 == len)
        {
            printf("VISA\n");
            return 1;
        }
    }

    // If all tests fails
    return 0;
}

int luhns_algorithm(long cc)
{
    int len = get_len_ofNum(cc);
    int arr_num[len];
    memset(arr_num, 0, len * sizeof(int));
    // ^-- https://stackoverflow.com/questions/3082914/c-compile-error-variable-sized-object-may-not-be-initialized

    long temp_cc = cc;
    int inc = 0;
    while (temp_cc > 0)
    {
        // Get the 2nd to the last digit
        int sec_lastDigit = (temp_cc % 100) / 10;
        arr_num[inc] = sec_lastDigit * 2;
        inc++;


        // Get the last digit
        int lastDigit = temp_cc % 10;
        arr_num[len - inc] = lastDigit;


        // Remove the last two digits
        temp_cc = temp_cc / 100;
    }


    // Add all digits in the stored array
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        // If 2 digited number, Split it into single digits
        int digit = arr_num[i];
        if (digit >= 10)
        {
            // Code here, assumes that the number is limited to 2 digits
            int left_digit = arr_num[i] % 10;
            int right_digit = arr_num[i] / 10;
            digit = right_digit + left_digit;
        }

        sum = sum + digit;
    }


    // Check the last digit of the sum if its zero
    int last_digit = sum % 10;
    if (last_digit == 0)
    {
        printf("%i", 1);
        return 1;  // card is legit
    }
    printf("%i", 0);
    return 0;  // Card IS NOT LEGIT
}

void check_card(long cc)
{
    // Identify if its American Express, Mastercard or Visa
    // Check the validity of the card
    if (luhns_algorithm(cc) == 0 || 0 == print_cardType(cc))
    {
        printf("INVALID\n");
    }
}

int main(void)
{
    long cc = get_long("Credit Card: ");
    check_card(cc);
}