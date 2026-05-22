#include <stdio.h>
#include <math.h>

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
        

        image[index].rgbtRed   =  round((1 - strength) * image[index].rgbtRed   + strength * average);
        image[index].rgbtGreen =  round((1 - strength) * image[index].rgbtGreen + strength * average);
        image[index].rgbtBlue  =  round((1 - strength) * image[index].rgbtBlue  + strength * average);
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

            double R = image[index].rgbtRed;
            double G = image[index].rgbtGreen;
            double B = image[index].rgbtBlue;

            int sepiaRed   = round( .393 * R + .769 * G + .189 * B);
            int sepiaGreen = round( .349 * R + .686 * G + .168 * B);
            int sepiaBlue  = round( .272 * R + .534 * G + .131 * B);

            if (sepiaRed > 255)   sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255)  sepiaBlue = 255;

            image[index].rgbtRed = sepiaRed;                    
            image[index].rgbtGreen = sepiaGreen;            
            image[index].rgbtBlue = sepiaBlue;                    
    }   
  }
}
