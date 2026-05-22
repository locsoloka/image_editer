#ifndef FILTERS_H
#define FILTERS_H

#include "../file_types/raw_image.h"

void grayscale(int height, int width, RGB *image, float strength);
void sepia(int height, int width, RGB *image, float strength);
void blur(int height, int width, RGB *image, float strength);
#endif