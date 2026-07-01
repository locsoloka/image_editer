#include <stdbool.h>
#include <stdlib.h>

#include "../file_types/raw_image.h"

typedef struct history_node 
{
    void (*filter)(int, int, RGB*, float, bool);
    int height;
    int width;
    RGB *image;
    float strength;
    bool is_png;
    struct history_node *next;
}history_node;

uint16_t linked_list_len = 0;

// this function req a     history_node *history = NULL;
void history_push(
    history_node *head, void (*filter)(int, int, RGB*, float, bool), int height, int width, RGB *image, float strength, bool is_png)
{
    history_node *tmp = malloc(sizeof(history_node));
    if (tmp == NULL) return;

    tmp->filter = (*filter);
    tmp->height = height;
    tmp->width = width;
    tmp->image = image;
    tmp->strength = strength;
    tmp->is_png = is_png;

    tmp->next = NULL;

    if (head == NULL)
    {
        head = tmp;
    }
    else
    {
        history_node *last = head; 
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = tmp;
    }        
}

void history_undo(
    history_node *head)
{
    if (head == NULL)
    {
        return;
    }

    history_node *current = head;

    if (current->next == NULL)
    {
        free(current);
        head = NULL;
        return;
    }

    history_node *before = head;

    while (current->next != NULL)
    {
        before = current;
        current = current->next;
    }

    before->next = NULL;
    free(current);
}

void recompute(
    history_node *head, RGB *image_orginal)
{
    history_node *current = head;
    while (current != NULL)
    {
        current->filter(current->height, current->width, image_orginal, current->strength, current->is_png);
        current = current->next;
    }
}
