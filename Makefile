image:
gcc image.c image_loader.c -o file -Wall `pkg-config --cflags --libs sdl2`