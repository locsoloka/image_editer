#include <stdint.h>
#include <stdio.h>

uint32_t read_be32(FILE *infile)
{
    uint8_t b[4];
    fread(b, 1, 4, infile);

    return ((uint32_t)b[0] << 24) |
           ((uint32_t)b[1] << 16) |
           ((uint32_t)b[2] << 8)  |
           ((uint32_t)b[3]);
}

uint8_t read_be8(FILE *infile)
{
  uint8_t value;
  fread(&value, sizeof(uint8_t), 1, infile);
  return value;
}


