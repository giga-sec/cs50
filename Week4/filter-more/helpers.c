#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int grayscale = round((r + g + b) / 3.0);
            image[i][j].rgbtRed = grayscale;
            image[i][j].rgbtGreen = grayscale;
            image[i][j].rgbtBlue = grayscale;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    
    {
        for (int column = 0; column < round(width / 2.0); column++)
        {
            // It's expected for right index to be > left index
            int left = column;  // left index
            int right = width - 1;  // right index

            RGBTRIPLE temp[1][1];
            temp[0][0] = image[row][right - left];
            image[row][right - left] = image[row][left];
            image[row][left] = temp[0][0];
        }
    }
    return;
}

// Helper function for Blur
/**
 * Vocabulary of parameters
  cR = current row, cC = current column
  h = height, w = width
  miR = mininum Row, mar = Maximum Row
  miC = minimum Column, maC = maximum Column
 **/
void assign_min_max(int cR, int cC, int h, int w, int *miR, int *maR, int *miC, int *maC)
{
    // Determines the navigation of neighbouring pixels

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
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // To temporary place all the blurred pixels
    RGBTRIPLE temp[height][width];


    // Search through each pixel in the photo
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            /**
            miR = mininum Row <--AND--> maR = Maximum Row
            miC = minimum Column <--AND--> maC = maximum Column
            **/
            int miR, maR, miC, maC;
            assign_min_max(row, column, height, width, &miR, &maR, &miC, &maC);

            // Navigate through each neighbouring pixels
            int prev_num[3] = {0, 0, 0};  // R, G, B
            float counter = 0.0;

            // Find all neighbouring values and all color values of it
            for (int i = miR; i <= maR; i++)
            {
                for (int j = miC; j <= maC; j++)
                {
                    // Add all the neighbouring values
                    prev_num[0] += image[i][j].rgbtRed;
                    prev_num[1] += image[i][j].rgbtGreen;
                    prev_num[2] += image[i][j].rgbtBlue;
                    counter++;
                }
            }

            // Pixel to be replaced, this is where the average happens
            temp[row][column].rgbtRed = round(prev_num[0] / counter);
            temp[row][column].rgbtGreen = round(prev_num[1] / counter);
            temp[row][column].rgbtBlue = round(prev_num[2] / counter);
        }
    }

    // Transfer temp to original
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = temp[row][column].rgbtRed;
            image[row][column].rgbtGreen = temp[row][column].rgbtGreen;
            image[row][column].rgbtBlue = temp[row][column].rgbtBlue;
        }
    }
    return;
}

int sobel_operator(int gX, int gY)
{
    int sobel = round(sqrt((gX * gX) + (gY * gY)));

    // Color value must be capped at 255
    if (sobel > 255)
    {
        sobel = 255;
    }

    return sobel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // To temporary place all the modified pixels
    RGBTRIPLE temp[height][width];

    // Set the kernel
    int gX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gY[3][3] = {{-1, -2, -1}, {0, 0, 0,}, {1, 2, 1}};

    // Search through each pixel in the photo
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int prev_num_x[3] = {0, 0, 0};  // R, G, B
            int prev_num_y[3] = {0, 0, 0};  // R, G, B

            // Navigate the kernel
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {
                    //Navigate neighbouring pixels
                    int r = (row - 1) + x;
                    int c = (column - 1) + y;

                    // Index must never go outside of the image pixel
                    if (r > height - 1 || r < 0)
                    {
                        continue;
                    }
                    if (c > width - 1 || c < 0)
                    {
                        continue;
                    }

                    // Add all values
                    // previous number of x direction + (kernel multiplied to pixel)
                    prev_num_x[0] = prev_num_x[0] + (gX[x][y] * image[r][c].rgbtRed);
                    prev_num_x[1] = prev_num_x[1] + (gX[x][y] * image[r][c].rgbtGreen);
                    prev_num_x[2] = prev_num_x[2] + (gX[x][y] * image[r][c].rgbtBlue);

                    // previous number of y direction + (kernel multiplied to pixel)
                    prev_num_y[0] = prev_num_y[0] + (gY[x][y] * image[r][c].rgbtRed);
                    prev_num_y[1] = prev_num_y[1] + (gY[x][y] * image[r][c].rgbtGreen);
                    prev_num_y[2] = prev_num_y[2] + (gY[x][y] * image[r][c].rgbtBlue);
                }
            }

            // Combine both x and y
            int red = sobel_operator(prev_num_x[0], prev_num_y[0]);
            int green = sobel_operator(prev_num_x[1], prev_num_y[1]);
            int blue = sobel_operator(prev_num_x[2], prev_num_y[2]);

            // Assign to temp
            temp[row][column].rgbtRed = red;
            temp[row][column].rgbtGreen = green;
            temp[row][column].rgbtBlue = blue;
        }
    }

    // Transfer temp to original
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = temp[row][column].rgbtRed;
            image[row][column].rgbtGreen = temp[row][column].rgbtGreen;
            image[row][column].rgbtBlue = temp[row][column].rgbtBlue;
        }
    }
    return;
}
