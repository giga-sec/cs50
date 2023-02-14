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

    // Forensic image cannot be opened for reading
    // --> Replace this comment with code

    FILE *file = fopen(argv[1], "r");
    unsigned int buffer[700];
    int BLOCK_SIZE = 512;


    char hexa[8];
    char jpeg[8] = "E0FFD8FF";
    char img_name[10];
    int img_count = 1;
    int jpeg_header = -520103681;


    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Convert int to hexadecimal
        // sprintf(hexa, "%X", *buffer);

        int i = 0; int j = 0;  // Index Counter
        // if (hexa[i] == 'E')
        // {
        if (*buffer == jpeg_header)
        {
            // Scan the array until the end of the string
            // while (hexa[i] != '\0')
            // {
                // if (check_jpegHeader(buffer) == 1)
                // {
                    sprintf(img_name, "%0.3d.jpeg\n", img_count++);
                    printf("%s", img_name);
                // }
                // i += 2; j += 2;
                // if ((hexa[i] != jpeg[j]) || (hexa[i + 1] != jpeg[j + 1]))
                // {
                //     break;  // Not a jpeg
                // }

                // if (i == 6)
                // {
                //     // Guaranteed that it's an image

                // }
            // }

        }
        else
        {
            continue;
        }
        // Make a file name
        // sprintf(img_name, "%0.3d.jpeg\n", img_count++);
        // printf("%s", img_name);
    }

    // fread(buffer, 1, 512, file);
    // fread(buffer, 1, 512, file);
    // fread(buffer, 1, 512, file);
    // printf("%X\n", *buffer);

    fclose(file);
}