#include <stdint.h>
#include <stdbool.h>

void save_as_bmp(char *dest_name,char *src_name,
     uint32_t height, uint32_t width, uint8_t *image, bool is_png, uint8_t bpp);
