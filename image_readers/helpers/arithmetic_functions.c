#include <stdint.h>

uint8_t sum_8b(uint8_t a, uint8_t b)
{
  uint16_t sum = a + b;
  if (sum > 256)
  {
    sum =- 256;
  }
  return sum;
}
