gcc image.c image_loader.c filter/filters.c -o file -Wall `pkg-config --cflags --libs sdl2` -lm
