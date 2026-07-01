#ifndef FILTERS_H
#define FILTERS_H

#include "../file_types/raw_image.h"

void grayscale(int height, int width, RGB *image, float strength, bool is_png);
void sepia(int height, int width, RGB *image, float strength, bool is_png);
void mirror_horizontal(int height, int width, RGB *image, float strength, bool is_png);
void blur(int height, int width, RGB *image, float strength, bool is_png);
#endif