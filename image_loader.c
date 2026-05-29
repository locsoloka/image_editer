#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_types/bmp.h"
#include "file_types/raw_image.h"
#include "file_types/png.h"

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

    RGB (*image_ptr) = calloc(*height, *width * sizeof(RGB));

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

uint32_t read_be32(FILE *f)
{
    uint8_t b[4];
    fread(b, 1, 4, f);

    return ((uint32_t)b[0] << 24) |
           ((uint32_t)b[1] << 16) |
           ((uint32_t)b[2] << 8)  |
           ((uint32_t)b[3]);
}

int read_png_header(PNG_IHDR *IHDR)
  {
    
  }

int open_png(char *path,int *width,int *height, RGB **out_texture)
{
    FILE (*image_ptr) = fopen(path, "rb");
    PNG_IHDR IHDR;
     // goto IHDR end
    fseek(image_ptr, 16, SEEK_SET);
    
    // read every part of the header
    
    IHDR.width  = read_be32(image_ptr);
    IHDR.height = read_be32(image_ptr);

    fread(&IHDR.bit_depth, sizeof(uint8_t), 1, image_ptr);
    fread(&IHDR.color_type, sizeof(uint8_t), 1, image_ptr);
    fread(&IHDR.compression_method, sizeof(uint8_t), 1, image_ptr);
    fread(&IHDR.filter_method, sizeof(uint8_t), 1, image_ptr);
    fread(&IHDR.interlace_method,sizeof(uint8_t), 1, image_ptr);
    
    printf("%u\n", IHDR.width);
    printf("%u\n", IHDR.height);
    
    printf("%i\n", IHDR.bit_depth);
    printf("%i\n", IHDR.color_type);
    printf("%i\n", IHDR.compression_method);
    printf("%i\n", IHDR.filter_method);
    printf("%i\n", IHDR.interlace_method);
    return 0;
}
