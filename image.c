#include <SDL2/SDL.h>
#include <stdio.h>

//#include "file_types/bmp.h"

#include "image_loader.h"
int width = 0;
int height = 0;

RGBTRIPLE (*out_texture) = NULL;

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

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                    SDL_PIXELFORMAT_BGR24,
                    SDL_TEXTUREACCESS_STATIC,
                    width,height);
    printf("texture_created \n");

    SDL_UpdateTexture(texture, NULL, out_texture, width * sizeof(RGBTRIPLE));
    
    int running = 1;
    SDL_Event e;
    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = 0;
            }
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