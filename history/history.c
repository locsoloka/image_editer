#include <stdlib.h>

#include "../file_types/raw_image.h"

typedef struct 
{
    void (*filter)(int, int, RGB*, float);
    int height;
    int width;
    RGB *image;
    float strength;
    struct history_node *next;
}history_node;


// this function req a     history_node *history = NULL;
void history_push(
    history_node **head, void (*filter)(int, int, RGB*, float), int height, int width, RGB *image, float strength)
{
    history_node *tmp = malloc(sizeof(history_node));
    
    tmp->filter = (*filter);
    tmp->height = height;
    tmp->width = width;
    tmp->image = image;
    tmp->strength = strength;

    // insert into the start of the list
    tmp->next = *head;

    // list starts with the newet element
    *head = tmp;
}

void history_undo(
    history_node **head, void (*filter)(int, int, RGB*, float), int height, int width, RGB *image, float strength)
{

}

void recompute(
    history_node **head, void (*filter)(int, int, RGB*, float), int height, int width, RGB **image, float strength, uint8_t undo_count)
{
    
}
