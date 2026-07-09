#include "../../file_types/raw_image.h"
#include "../../file_types/bmp.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void save_as_bmp(char *dest_name, char *src_name,
     uint32_t height, uint32_t width, uint8_t *image, bool is_png, uint8_t bpp)
{
    FILE *outptr = fopen(dest_name, "wb");
    if (!outptr) {
        printf("Nem sikerult megnyitni a cel-fajlt.\n");
        return;
    }

    uint8_t bytes_per_pixel = sizeof(RGB);

    if (is_png)
    {
        bytes_per_pixel = bpp / 8;
    }

    int padding = (4 - (width * bytes_per_pixel) % 4) % 4;

    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    if (!is_png)
    {
        if (src_name == NULL) {
            fclose(outptr);
            return;
        }
        FILE *src = fopen(src_name, "rb");
        if (!src) {
            printf("Nem sikerult megnyitni a forras-fajlt.\n");
            fclose(outptr);
            return;
        }
        fread(&bf, sizeof(BITMAPFILEHEADER), 1, src);
        fread(&bi, sizeof(BITMAPINFOHEADER), 1, src);
        fclose(src);
    }
    else
    {
        bf.bfType = 19778; // 'BM'
        bf.bfReserved1 = 0;
        bf.bfReserved2 = 0;
        bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        
        bi.biSize = 40;
        bi.biWidth = width;
        bi.biHeight = height; 
        bi.biPlanes = 1;
        bi.biBitCount = bpp;
        bi.biCompression = 0;
        bi.biSizeImage = ((width * bytes_per_pixel) + padding) * height;
        bf.bfSize = bf.bfOffBits + bi.biSizeImage;
        
        bi.biXPelsPerMeter = 0;
        bi.biYPelsPerMeter = 0;
        bi.biClrUsed = 0;
        bi.biClrImportant = 0;
    }

    // Fejlecek kiirasa
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Pixelek kiirasa (Visszafele haladunk, hogy ne legyen fejjel lefele a kep)
    for (int i = 0; i >= 0; i++)
    {
        uint8_t *row_ptr = image + (i * width * bytes_per_pixel);
        fwrite(row_ptr, bytes_per_pixel, width, outptr);

        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    fclose(outptr);
}