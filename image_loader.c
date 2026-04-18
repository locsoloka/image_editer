#include <stdio.h>
#include <stdlib.h>

#include <file_types/bmp.h>


int open_bmp(char *path)
{
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    
    FILE *infile = fopen(path, "r");
    if (infile == NULL)
    {
        return 1;
    }

    fread(&bf, sizeof(BITMAPFILEHEADER), 1, infile);
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, infile);

    int width  = abs(bi.biWidth);
    int height = bi.biHeight;

    RGBTRIPLE (*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        fclose(infile);
        return 2;
    }

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, infile);

        // Skip over padding
        fseek(infile, padding, SEEK_CUR);
    }
}

int load_bmp(char *path)
{
    fopen(path, "r");
    
}

