# Image Editor
## Video Demo:  <URL HERE>
### Description: This  is a image processing application written entirly in native C using SDL2 for rendering And zlib for png deflation. The goal of the project was to dive deep into binary file structures and memory managment without high-level framworks.

## Key Features
### Custom PNG Decoder: Parsed chunks, bit-manipulation, and IDAT decompression using the libary zlib.
### Fully supporting BMP opening and saving.
### Operation-Based Undo System: Uses a dynamic Linked List to store past filter functions and parameters.
### Filters: Grayscale and Sepia (with adjustable intensity), Box Blur, and Horizontal Mirror.

## File Struchture
### image.c The main file deals with user input.
### png_reader.c/png_reader.h Opening pngs to a raw buffer.
### bmp_loader.c Loading bmp images.
### bmp_saver.c Saves bmp and png images to bmp.
### history.c Managing history.
### filters.c Pixel manipulation algorithms.
### arithmetic_functions.c/reader_functions.c are both have helper functions.

## How to Run
## Install dependencies
## Debian / Ubuntu / Mint
'''bash 
sudo apt update
sudo apt install libsdl2-dev
'''

## Fedora / RHEL
'''bash
sudo dnf install SDL2-devel
'''

## Arch Linux / Manjaro
'''bash
sudo pacman -S sdl2
'''

## Compile
'''bash
make
'''

## Run
'''bash
./file
'''

## Challenges & Reflection
### The hardest part off this project was the PNG decoder and also those little annyoning off by one bugs.