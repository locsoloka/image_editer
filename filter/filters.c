#include <stdio.h>

#include "../file_types/raw_image.h"

void grayscale(int height, int width, RGB *image, float strength)
{
  for (LONG y = 0;y < height;y++)
  {
      for (LONG x = 0 ; x < width;x++)
      {
        LONG index = y * width + x;
        
        BYTE R = image[index].rgbtRed;
        BYTE G = image[index].rgbtGreen;
        BYTE B = image[index].rgbtBlue;

        int average = (R + G + B) / 3;
        

        image[index].rgbtRed   =  (1 - strength) * image[index].rgbtRed   + strength * average;
        image[index].rgbtGreen =  (1 - strength) * image[index].rgbtGreen + strength * average;
        image[index].rgbtBlue  =  (1 - strength) * image[index].rgbtBlue  + strength * average;
    }
  }
  return;
}

void sepia(int height, int width, RGB *image, float strength)
{
  for (LONG y = 0;y < height;y++)
  {
    for (LONG x = 0 ; x < width;x++)
    {
        LONG index = y * width + x;

        image[index].rgbtRed   =  (image[index].rgbtRed   * .393) * 2.3;       
        image[index].rgbtGreen =  (image[index].rgbtGreen * .349) * 2.3;      
        image[index].rgbtBlue  =  (image[index].rgbtBlue  * .272) * 2.3;     
    }   
  }
}
