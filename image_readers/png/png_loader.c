#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../file_types/png.h"
#include "../../file_types/raw_image.h"

#include "../helpers/reader_functions.h"

int read_png_header(PNG_IHDR *IHDR, FILE *infile)
{
    // goto the end of the "IHDR"
    fseek(infile, 16, SEEK_SET);
    
    // read header
    IHDR->width  = read_be32(infile);
    IHDR->height = read_be32(infile);

    IHDR->bit_depth           = read_be8(infile);
    IHDR->color_type          = read_be8(infile);
    IHDR->compression_method  = read_be8(infile);
    IHDR->filter_method       = read_be8(infile);
    IHDR->interlace_method    = read_be8(infile);

    printf("%u\n", IHDR->width);
    printf("%u\n", IHDR->height);
    
    printf("%i\n", IHDR->bit_depth);
    printf("%i\n", IHDR->color_type);
    printf("%i\n", IHDR->compression_method);
    printf("%i\n", IHDR->filter_method);
    printf("%i\n", IHDR->interlace_method);
    
    if (IHDR->compression_method != 0)
    {
      printf("unsuported compression_method");
      return 1;
    }
    return 0;
}

int open_png(char *path,int *width,int *height, RGB **out_texture)
{
    PNG_IHDR IHDR;
    uint32_t length;
    char chunk_type[5];

    chunk_type[4] = '\0';

    FILE (*infile) = fopen(path, "rb");
    read_png_header(&IHDR, infile);

    RGB (*image_ptr) = calloc(*height, *width * sizeof(RGB));

    fseek(infile, 4, SEEK_CUR);

    length = read_be32(infile); // read length

    fread(&chunk_type, 1, 4, infile);

    printf("chunk_type: %s\n", chunk_type);

    printf("length: %u\n\n", length);
    if (strcmp(chunk_type, "IDAT") == 0)
    {
      printf("IDAT");
      while (fread(image_ptr, 1, length, infile) == length);
    }
    
    else if (strcmp(chunk_type, "IEND") == 0)
    {
      printf("IEND");
    }

    else 
    {
      length = read_be32(infile);
      printf("length: %u", length);
      fseek(infile, length + 4, SEEK_CUR);
    }
    *out_texture = image_ptr;
    return 0;
}
