#include <stdio.h>
#include <math.h>

void assign_min_max(int cR, int cC, int h, int w, int *miR, int *maR, int *miC, int *maC)
{
    // Index should be cap at 0
    *miR = cR;
    if (*miR != 0)
    {
        *miR = cR - 1;
    }
    // Index should be capped at maximum height
    *maR = cR;
    if (*maR != h - 1)
    {
        *maR = cR + 1;
    }

    // Index should be cap at 0
    *miC = cC;
    if (*miC != 0)
    {
        *miC = cC - 1;
    }

    // Column Index should be capped at maximum width
    *maC = cC;
    if (*maC != w - 1)
    {
        *maC = cC + 1;
    }
}

// Blur image
int main()
{
    // // To temporary place all the blurred pixels
    // int temp[3][3];
    // int num[3][3] = {{10, 40, 70}, {110, 120, 130}, {200, 220, 240}};

    // // Search through each pixel in the photo
    // for (int row = 0; row < 3; row++)
    // {
    //     for (int column = 0; column < 3; column++)
    //     {
    //         int miR, maR, miC, maC;
    //         assign_min_max(row, column, 3, 3, &miR, &maR, &miC, &maC);

    //         // Navigate through each neighbouring pixels
    //         int prev_num[3] = {0, 0, 0};  // R, G, B
    //         float counter = 0.0;
    //         for (int i = miR; i <= maR; i++)
    //         {
    //             for (int j = miC; j <= maC; j++)
    //             {
    //                 // Find all neighbouring values and all color values of it
    //                 prev_num[0] += num[-1][-1];
    //                 counter++;
    //             }
    //         }

    //         // Pixel to be replaced, this is where the average happens
    //         temp[row][column] = round(prev_num[0]/counter);
    //     }
    // }

    // // Transfer temp to original
    // for (int row = 0; row < 3; row++)
    // {
    //     for (int column = 0; column < 3; column++)
    //     {
    //         num[row][column] = temp[row][column];
    //     }
    // }
    // printf("%i", num[0][0]);

    int jpeg = -520103681;
    printf("%i", jpeg);
}