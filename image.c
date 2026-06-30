#include <SDL2/SDL.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "image_readers/png/png_loader.h"
#include "image_readers/bmp/bmp_loader.h"

#include "file_types/raw_image.h"
#include "filter/filters.h"

#include "history/history.h"

int width = 0;
int height = 0;
bool running = true;

bool texture_needs_update = false;

bool is_png;

RGB *out_texture = NULL;
RGB *image_original = NULL;
SDL_Texture *texture = NULL;

history_node *history = NULL;

void (*fptr)(int height, int width, RGB *image, float strength);

void* input_thread(void *);

void file_type_switch(char *filename);
void gray_scale_switch(void);
void sepia_switch(void);

int main(void)
{
    // here i used ai for SDL2 functions
    SDL_Init(SDL_INIT_VIDEO);

    char *user_path = calloc(100, sizeof(char));
    scanf("%s", user_path);

    file_type_switch(user_path);
    
    
    // kezdődik a SDl
    SDL_Window* window = SDL_CreateWindow("C grafika", 100,100,640,480,0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (is_png == true)
    {
        texture = SDL_CreateTexture(renderer,
                    SDL_PIXELFORMAT_RGB24,
                    SDL_TEXTUREACCESS_STATIC,
                    width,height);
        printf("\ntexture_created \n");
    }
    else
    {
        texture = SDL_CreateTexture(renderer,
                    SDL_PIXELFORMAT_BGR24,
                    SDL_TEXTUREACCESS_STATIC,
                    width,height);
        printf("\ntexture_created \n");
    }

    SDL_UpdateTexture(texture, NULL, out_texture, width * sizeof(RGB));
    
    SDL_Event e;
    // i used ai for the multi threading beacuse I couldn' t figure out have multiple loops at once
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
                running = false;
            }
        }
        
        if (texture_needs_update)
        {
            SDL_UpdateTexture(texture, NULL, out_texture, width * sizeof(RGB));
            texture_needs_update = false; // Visszaállítjuk, mert elvégeztük a munkát
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
void file_type_switch(char *filename)
{
    const uint8_t png_header[4] = {0x89, 0x50, 0x4E, 0x47};    

    char buffer[5];
    FILE *src = fopen(filename, "rb");
    fread(buffer, 4, sizeof(char), src);

    if (memcmp(buffer, png_header, 4) == 0)
    {
        int status = open_png(filename, &width, &height, &out_texture, &image_original);
        is_png = true;
    }
    else if (buffer[0] == 0x42 && buffer[1] == 0x4D)
    {
        is_png = false;
        int status = open_bmp(filename, &width, &height, &out_texture);
        if (status != 0)
        {
            printf("%i\n", status);
            fprintf(stderr, "Error loading BMP file\n");
            SDL_Quit();
        }
        memcpy(image_original, out_texture, width * height * sizeof(RGB));
    }
    else
    {
        printf("unuporrted file type");
    }
    fclose(src);
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
            running = false;
            break;
        
        case 'g':
            gray_scale_switch();
            break;
        
        case 's':
            sepia_switch();
            break;
        case 'b':
            float strength = 1;
            blur(height, width, out_texture, strength);       
    
            // History managment
            fptr = &sepia;
            history_push(history, fptr, height, width, out_texture, strength);

            texture_needs_update = true;
            break;
        case 'm':
            strength = 1;    
            mirror_horizontal(height, width, out_texture, strength);
        
            // History managment
            fptr = &sepia;
            history_push(history, fptr, height, width, out_texture, strength);

            texture_needs_update = true;
            break;
        case 'u':
            history_undo(history);
            memcpy(out_texture, image_original, width * height * sizeof(RGB));
            recompute(history, &out_texture);
        }
    }
    
    return NULL;
}
void gray_scale_switch(void)
{
    printf("\n GRAYSCALE --help or e\n");
    
    // we need this or else it would execute it self without user input
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
        { printf("execute: press: e\n");
            printf("change: strength: --config -s\n");
        }
        else if (strcmp(sub_command, "--config -s") == 0)
        {
            printf("strength: ");
            scanf("%f", &strength);
            
            grayscale(height, width, out_texture, strength);

            // history managment
            fptr = &grayscale;
            history_push(history, fptr, height, width, out_texture, strength);

            texture_needs_update = true;
        }
        else if (strcmp(sub_command, "e") == 0)
        {
            grayscale(height, width, out_texture, strength);
            // history managment
            fptr = &grayscale;
            history_push(history, fptr, height, width, out_texture, strength);
            
            texture_needs_update = true;                    
        }
        else
        {
            printf("command not found\n");
        }
    }
}
void sepia_switch(void)
{
    printf("--help or e\n");
    float strength = 1;    
    // we need this or else it would execute it self without user input
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    char sub_command[100];
    fflush(stdout);

    if (fgets(sub_command, sizeof(sub_command), stdin) != NULL)
    {
        // we remove /n from the end
        sub_command[strcspn(sub_command, "\n")] = 0;
        if (strcmp(sub_command, "--help") == 0)
        {
            printf("Configure strenth: --config -s\n");
            printf("default: e\n");
        }
        else if (strcmp(sub_command, "e") == 0)
        {
            sepia(height, width, out_texture, strength);       

            // history managment
            fptr = &sepia;
            history_push(history, fptr, height, width, out_texture, strength);

            texture_needs_update = true;
        }
        else if (strcmp(sub_command, "--config -s") == 0)
        {
            printf("strength: ");
            scanf("%f", &strength);
            sepia(height, width, out_texture, strength);       
            
            // History managment
            fptr = &sepia;
            history_push(history, fptr, height, width, out_texture, strength);

            texture_needs_update = true;
            
        }
        else
        {
            printf("\ncommand not found\n");
        }
    }
}