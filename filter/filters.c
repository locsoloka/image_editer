#include <stdio.h>

#include "../file_types/raw_image.h"

void grayscale(int height, int width, RGB *image)
{
  for (LONG y = 0;y < height;y++)
  {
      for (LONG x = 0 ; x < width;x++)
      {
        LONG index = y * width + x;
        
        BYTE R = image[index].rgbtRed;
        BYTE G = image[index].rgbtGreen;
        BYTE B = image[index].rgbtBlue;

        LONG average = (R + G + B) / 3;

        image[index].rgbtRed = average;
        image[index].rgbtGreen = average;
        image[index].rgbtBlue = average;
    }
  }
  printf("gray");
  return;
}

