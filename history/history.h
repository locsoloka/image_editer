#include "../file_types/raw_image.h"
#include <stdbool.h>

typedef struct 
{
    void (*filter)(int, int, RGB*, float, bool);
    int height;
    int width;
    RGB *image;
    float strength;
    struct history_node *next;
}history_node;


void history_push(
    history_node *head, void (*filter)(int, int, RGB*, float, bool), int height, int width, RGB *image, float strength);

void history_undo(
    history_node *head);

void recompute(
    history_node *head, RGB **image_orginal);
    
  