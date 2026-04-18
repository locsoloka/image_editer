#include <SDL2/SDL.h>

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("C grafika", 100,100,640,480,0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_CreateTexture(renderer,);

    SDL_RenderPresent(renderer);
    SDL_Delay(10000);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}