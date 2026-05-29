#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_types/bmp.h"
#include "file_types/raw_image.h"
#include "file_types/png.h"

int open_bmp(char *path,int *width,int *height,RGB **out_texture);
int open_png(char *path,int *width,int *height,RGB **out_texture);
