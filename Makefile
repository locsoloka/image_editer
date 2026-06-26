# gcc image.c image_readers/bmp/bmp_loader.c image_readers/png/png_loader.c image_readers/helpers/reader_functions.c  image_readers/helpers/.arithmetic_functions.c filter/filters.c zlib-1.3.2/libz.a -I./zlib-1.3.2 -o file -Wall `pkg-config --cflags --libs sdl2` -lm
CC = gcc

CFLAGS = -Wall -I./zlib-1.3.2 `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2` -lm

SOURCES = \
image.c \
	image_readers/bmp/bmp_loader.c \
	image_readers/png/png_loader.c \
	image_readers/helpers/reader_functions.c \
	image_readers/helpers/arithmetic_functions.c \
	filter/filters.c

TARGET = file 

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) zlib-1.3.2/libz.a $(CFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)
