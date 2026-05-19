#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "../processors/filters.h"

void* input_thread(void* arg,int *running)
{
    char *buffer = calloc(256, sizeof(char));

    while (running)
    {
        if (fgets(buffer, sizeof(buffer), stdin))
        {
            printf("COMMAND: %s", buffer);

            switch (*buffer)
            {
            case 'q':
                running = 0;
                break;
            
            case 'g':
                
                break;
            }
        }
    }

    return;
}