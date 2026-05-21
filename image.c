#include <SDL2/SDL.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>


//#include "file_types/bmp.h"

#include "image_loader.h"
#include "file_types/history.h"
#include "file_types/raw_image.h"
#include "filter/filters.h"


int width = 0;
int height = 0;
int running = 1;

int texture_needs_update = 0;

RGB (*out_texture) = NULL;
SDL_Texture *texture = NULL;

void* input_thread(void *);

void gray_scale_switch(void);

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    char *user_path = calloc(100, sizeof(char));
    scanf("%s", user_path);

    int status = open_bmp(user_path ,&width, &height, &out_texture);
    if (status != 0)
    {
        printf("%i\n", status);
        fprintf(stderr, "Error loading BMP file\n");
        SDL_Quit();
        return 1;
    }

    // kezdődik a SDl
    SDL_Window* window = SDL_CreateWindow("C grafika", 100,100,640,480,0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(renderer,
                    SDL_PIXELFORMAT_BGR24,
                    SDL_TEXTUREACCESS_STATIC,
                    width,height);
    printf("texture_created \n");

    SDL_UpdateTexture(texture, NULL, out_texture, width * sizeof(RGB));
    
    SDL_Event e;
    
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, input_thread, NULL) != 0) {
        fprintf(stderr, "Nem sikerult letrehozni a szalat\n");
    }

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        
        if (texture_needs_update)
        {
            SDL_UpdateTexture(texture, NULL, out_texture, width * sizeof(RGB));
            texture_needs_update = 0; // Visszaállítjuk, mert elvégeztük a munkát
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        
    }
    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    free(out_texture);
    free(user_path);

    return 0;
}

void* input_thread(void *arg)
{
    printf("input: \n");
    char command;

    while (running)
    {
        command = getchar();

        if (command == '\n' || command == EOF)
        {
            continue;
        }
        
        switch (command)
        {
        case 'q':
            running = 0;
            break;
        
        case 'g':
            gray_scale_switch();
            break;
        
        case 's':
            sepia(height, width, out_texture, 1);       
            texture_needs_update++;
            break;
        }
    }
    
    return NULL;
}
void gray_scale_switch(void)
{
    printf("\n GRAYSCALE --help or e\n");

    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    char sub_command[100];
    fflush(stdout);

    if (fgets(sub_command, sizeof(sub_command), stdin) != NULL)
    {
        float strength = 1;
        sub_command[strcspn(sub_command, "\n")] = 0;

        if (strcmp(sub_command, "--help") == 0)
        {
            printf("execute: press: e\n");
            printf("change: strength: --config -s\n");
        }
        else if (strcmp(sub_command, "--config -s") == 0)
        {
            printf("strength: ");
            scanf("%f", &strength);
            
            grayscale(height, width, out_texture, strength);
            texture_needs_update++;
        }
        else if (strcmp(sub_command, "e") == 0)
        {
            grayscale(height, width, out_texture, strength);
            texture_needs_update++;                    
        }
        else
        {
            printf("command not found\n");
        }
    }
}