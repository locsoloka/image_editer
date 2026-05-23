#include <stdio.h>
#include <stdlib.h>
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

      int sepiaRed   = round((1 - strength) * R + strength * (.393 * R + .769 * G + .189 * B));
      int sepiaGreen = round((1 - strength) * G + strength * (.349 * R + .686 * G + .168 * B));
      int sepiaBlue  = round((1 - strength) * B + strength * (.272 * R + .534 * G + .131 * B));

      if (sepiaRed > 255)   sepiaRed = 255;
      if (sepiaGreen > 255) sepiaGreen = 255;
      if (sepiaBlue > 255)  sepiaBlue = 255;

      image[index].rgbtRed = sepiaRed;                    
      image[index].rgbtGreen = sepiaGreen;            
      image[index].rgbtBlue = sepiaBlue;                    
    }   
  }
}

void mirror_horizontal(int height, int width, RGB *image, float strength)
{
    for (int y = 0;y < height;y++)
    {
        for (int x = 0 ; x < width / 2;x++)
        {
            LONG index = y * width + x;

            int R = image[index].rgbtRed;
            int G = image[index].rgbtGreen;
            int B = image[index].rgbtBlue;

            int R_b = image[y * width - x].rgbtRed;
            int G_b = image[y * width - x].rgbtGreen;
            int B_b = image[y * width - x].rgbtBlue;

            image[index].rgbtRed   = R_b;
            image[index].rgbtGreen = G_b;
            image[index].rgbtBlue  = B_b;

            image[y * width - x].rgbtRed   = R;
            image[y * width - x].rgbtGreen = G;
            image[y * width - x].rgbtBlue  = B;
        }
    }
    return;
}

void blur(int height, int width, RGB *image, float strength)
{
    RGB *copy = malloc(width * height * sizeof(RGB));
    
    for (int y = 0;y < height;y++)
    {
        for (int x = 0 ; x < width;x++)
        {
          LONG index = y * width + x;
          copy[index] = image[index];
        }
    }
    for (int y = 0;y < height;y++)
    {    for (int x = 0;x < width;x++)
        {
            LONG index = y * width + x;
          
            int sum_of_Red   = 0;
            int sum_of_Green = 0;
            int sum_of_Blue  = 0;
            int count        = 0;

            for (int ki = y -1;ki < y + 2;ki++)
                for (int kj = x -1;kj < x + 2;kj++)
                {
                    if (ki >= 0 && ki < height && kj >= 0 && kj < width)
                    {
                        LONG jindex = ki * width + kj;
                        sum_of_Red   += copy[jindex].rgbtRed;
                        sum_of_Green += copy[jindex].rgbtGreen;
                        sum_of_Blue  += copy[jindex].rgbtBlue;
                        count++;

                        image[index].rgbtRed   = sum_of_Red   / count;
                        image[index].rgbtGreen = sum_of_Green / count;
                        image[index].rgbtBlue  = sum_of_Blue  / count;
                    }
                }

        }

    }
    return;
}
