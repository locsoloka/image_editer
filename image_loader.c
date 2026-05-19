#include <stdio.h>
#include <stdlib.h>

#include "file_types/bmp.h"
#include "file_types/raw_image.h"

int open_bmp(char *path,int *width,int *height, RGB **out_texture)
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

    *width  = abs(bi.biWidth);
    *height = abs(bi.biHeight);

    RGBTRIPLE (*image_ptr) = calloc(*height, *width * sizeof(RGBTRIPLE));

    int padding = (4 - (*width * sizeof(RGBTRIPLE)) % 4) % 4;

    printf("width: %i\n", *width);
    printf("height: %i\n", *height);
    printf("padding: %i\n", padding);
    for (int i = 0; i < *height; i++)
    {   
        fread(&image_ptr[i * (*width)], sizeof(RGBTRIPLE), *width, infile);
        fseek(infile, padding, SEEK_CUR);
    }
    fclose(infile);
    *out_texture = image_ptr;
    return 0;
}
