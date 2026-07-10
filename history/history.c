#include <stdbool.h>
#include <stdio.h>
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
    history_node **head, void (*filter)(int, int, RGB*, float, bool), int height, int width, RGB *image, float strength, bool is_png)
{
    printf("history push");
    history_node *tmp = malloc(sizeof(history_node));
    if (tmp == NULL) return;

    tmp->filter = (*filter);
    tmp->height = height;
    tmp->width = width;
    tmp->image = image;
    tmp->strength = strength;
    tmp->is_png = is_png;

    tmp->next = NULL;

    if (*head == NULL)
    {
        *head = tmp;
    }
    else
    {
        history_node *last = *head; 
        while (last->next != NULL)
        {
            last = last->next;
        }
        last->next = tmp;
    }        
}

uint16_t history_undo(
    history_node **head)
{
    uint16_t length_of_list = 0;
    if (*head == NULL)
    {
        return length_of_list;
    }

    history_node *current = *head;

    if (current->next == NULL)
    {
        printf("current->next == NULL\n");
        free(current);
        *head = NULL;
        return length_of_list;
    }

    history_node *before = *head;

    while (current->next != NULL)
    {
        length_of_list++;
        before = current;
        current = current->next;
    }
    history_node *last = current; 
    free(last);
    before->next = NULL;
    return length_of_list;
}

void recompute(
    history_node *head, RGB *image_orginal)
{
    history_node *current = head;
    while (current != NULL)
    {
        current->filter(current->height, current->width, image_orginal, current->strength, current->is_png);
        printf("asd%i\n", current->filter);
        current = current->next;
    }
}
