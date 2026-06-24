#include <arpa/inet.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../zlib-1.3.2/zlib.h"

#include "../../file_types/png.h"
#include "../../file_types/raw_image.h"

#include "../helpers/reader_functions.h"

uint32_t all_length;
unsigned long destlen;

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

int bytes_per_pixel_switch(PNG_IHDR IHDR)
{
  switch (IHDR.color_type)
  {
    case 0:
    return 0; // greayscale
    break;

    case 2:
    return 3; // RGB
    break;

    case 6:
    return 4; // RGBA
    break;

  }
  return 0;
}

int read_IDAT(FILE *infile, uint8_t **IDAT_raw)
{
  uint32_t length;
  char chunk_type[5];

  int IDAT_count = 0;
  chunk_type[4] = '\0';

  fseek(infile, 4, SEEK_CUR);
  while (true)
  {
    length = read_be32(infile); // read length
    if (length == 0)
    {
      printf("length 0\n\n");
      break;
    }
    fread(&chunk_type, 1, 4, infile);
    printf("chunk_type: %s\n", chunk_type);
    printf("length: %u\n\n", length);

    if (strcmp(chunk_type, "IEND") == 0)
    {
      printf("IEND");
      break;
    }
    if (strcmp(chunk_type, "IDAT") == 0)
    {
      printf("IDAT");

      if (IDAT_count == 0) 
      {
        all_length = length;
        *IDAT_raw = calloc(length, sizeof(uint8_t));
      }
      else
      {
        all_length += length;
        uint8_t *temp = realloc(*IDAT_raw, all_length * sizeof(uint8_t));

        if (temp == NULL) 
        {
          printf("realloc error");
          free(*IDAT_raw);
          return 1;
        }
        else
        {
          *IDAT_raw = temp;
        }
      }

      size_t read_data = fread(*IDAT_raw + all_length - length, 1, length, infile);
      if (read_data != length) 
      {
        printf("Wasnt't able to read IDAT");
      }
      else
      {
        IDAT_count++;
      }
    }
    else 
    {
      fseek(infile, length, SEEK_CUR);
    }

    fseek(infile, 4, SEEK_CUR);
  }
  return 0;
}

int  uncompress_png(uint8_t *IDAT_raw)
{
  uint8_t (*image_ptr) = calloc(all_length, sizeof(uint16_t));
  if (image_ptr == NULL)
  {
    printf("couldn 't calloc enugh memory");
  }
  int state = uncompress(image_ptr, &destlen, IDAT_raw, all_length);
  if (state == Z_OK)
  {
    printf("uncompress cussesfuly");
  }
  if (state == Z_BUF_ERROR)
  {
    printf("Z_BUF_ERROR");
  }
  if (state == Z_DATA_ERROR)
  {
    printf("Z_BUF_ERROR");
  }
  if (state == Z_MEM_ERROR)
  {
    printf("Z_BUF_ERROR");
  }
  if (state == Z_STREAM_ERROR)
  {
    printf("Z_STREAM_ERROR");
  }
  else
  {
    printf("error:%i\n", state);
  }
  return state;
}

int open_png(char *path,int *width,int *height, RGB **out_texture)
{
  PNG_IHDR IHDR;
  
  int bytes_per_pixel;
  uint8_t *IDAT_raw = NULL;

  FILE (*infile) = fopen(path, "rb");
  read_png_header(&IHDR, infile);

  read_IDAT(infile, &IDAT_raw);

  bytes_per_pixel = bytes_per_pixel_switch(IHDR);

  *height = IHDR.height;
  *width  = IHDR.width;

  printf("height: %i\n", *height);
  printf("width: %i\n", *width);
  destlen = *height * (1 + (*width * bytes_per_pixel));

  uncompress_png(IDAT_raw);

 return 0;
}
