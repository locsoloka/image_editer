#include <stdint.h>
#include <stdlib.h>

uint8_t sum_8b(uint8_t a, uint8_t b)
{
  uint16_t sum = a + b;
  if (sum > 256)
  {
    sum =- 256;
  }
  return sum;
}

uint8_t paeth_predictor(uint8_t a, uint8_t b, uint8_t c)
{
  uint32_t p = a + b - c;
  uint16_t pa = abs(p - a);
  uint16_t pb = abs(p - b);
  uint16_t pc = abs(p - c);
  // megkeressük a legkisebb távot.
  if (pa <= pb && pa <= pc) return a;
  else if (pb <= pc) return b;
  else return c;  
}