#ifndef RAW_IMAGE_H_DEFINED
#define RAW_IMAGE_H_DEFINED

#include <stdint.h>

typedef uint8_t  BYTE;
typedef int32_t LONG;


typedef struct 
{
    LONG raheight;
    LONG rawidht;
}RAW_IMAGE_HEADER;

typedef struct
{
    BYTE rgbtRed;
    BYTE rgbtGreen;
    BYTE rgbtBlue;
} RGB;



#endif