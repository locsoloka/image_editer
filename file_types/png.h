#include <stdint.h>

#ifndef PNG_H_DEFINED
#define PNG_H_DEFINED

typedef struct {
    u_int32_t height;
    u_int32_t width;
    uint8_t  bit_depth;
    uint8_t  color_type;
    uint8_t  compression_method;
    uint8_t  filter_method;
    uint8_t  interlace_method;
} PNG_IHDR;
#endif
