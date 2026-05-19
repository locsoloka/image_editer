#include "../file_types/bmp.h"

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0;i < height;i++)
  {
      for (int j = 0 ; j < width;j++)
      {
          //assign R G B values
        int R = image[i][j].rgbtRed;
        int G = image[i][j].rgbtGreen;
        int B = image[i][j].rgbtBlue;

        int average = (R + G + B) / 3;

        image[i][j].rgbtRed = average;
        image[i][j].rgbtGreen = average;
        image[i][j].rgbtBlue = average;
    }
  }
  return;
}
