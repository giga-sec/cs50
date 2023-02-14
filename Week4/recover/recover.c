#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Scan the array until the end of the string
// int check_jpegHeader(char hexa[])
int check_jpegHeader(unsigned int num[])
{
    int jpeg_header = -520103681;
    // int i = 0; int j = 0;

    // Check all hexadecim
    // do
    // {
    //     i += 2; j += 2;
    //     if ((hexa[i] != jpeg[j]) || (hexa[i + 1] != jpeg[j + 1]))
    //     {
    //         return 0;  // Not a jpeg
    //     }
    // }
    // while (i < 6);
    if (*num == jpeg_header)
    {
        return 1;
    }

    // All the hexadecimals have been checked
    // Therefore guaranteed its an image
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./recover <filename.ext>");
        printf("Example: ./recover card.raw");
        return 1;
    }

    // Variables for reading the card.raw file
    FILE *file = fopen(argv[1], "r");
    unsigned int buffer[700];
    int BLOCK_SIZE = 512;

    // Variables for file name
    char img_name[10];
    int img_count = 0;

    // Hexadecimal to "decimal signed 2"
    int jpeg_header = -520103681;


    int transfer_bytes = 0;
    FILE *img;
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // If file is jpeg
        if (*buffer == jpeg_header)
        {
            // Create a file and file name
            sprintf(img_name, "%0.3d.jpg", img_count++);
            img = fopen(img_name, "wb");

            // Copy the header to the file
            fwrite(buffer, 1, BLOCK_SIZE, img);

            // Enable transfering of bytes
            transfer_bytes = 1;
        }

        else if (transfer_bytes == 1)
        {
            // Append bytes to a new file
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
    }

    fclose(img);
}