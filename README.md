# C Image Editor with Custom PNG Reader and Operation-Based Undo System

#### GitHub Username: locsoloka
#### edX Username: Tirpak-Zoltan
#### Location: Debrecen, Hungary
#### Date: July 12 2026

## Video Demo:  <URL https://youtu.be/7Z8HGsF8QO4>
### Description: This  is a image processing application written entirly in native C using SDL2 for rendering And zlib for png deflation. The goal of the project was to dive deep into binary file structures and memory managment without high-level framworks.

## Project Overview

This project is a high-preformance, modular image-processing desktop application written in native C from sratch.

The application utilizes the SDL2 (Simple DirectMedia Layer) library to render the pixel and the window.

## Detaild Technical Architecture and Modules

To prevent tightly coupled sphagetti code, the software is engineered with strict modularity. Each core susbsytem is isolted into its own header and source files.

### 1. The core of the project ("image.c")
This is the entry point off the application. It handles user data and decides which function should be called and when.
One of the first big problem i faced while writting my project was that SDL2 has its own main loop so if I want to get user input with for example scanf. The application whould be stucked beacuse we are waiting for user input. So i had to implement another thread for only user input.

### 2. The Custom PNG Decoder ("png_reader.c" & "png_reader.h")
Writing the PNG decoder was the undeniably the most complex and intentionally challenging phase of the entire development process. It also took the longest.

* **Chunk Parsing:** The module reads the binary stream byte by byte, verifies the mandatory 8-byte PNG signature, and iterates through standard chunks such as `IHDR` (Image Header), `IDAT` (Image Data), and `IEND` (Image End).
It was the first bigger issue i encunterterd while writing the reader beacuse i had off by one issues all the time. I used a hexeditor to manually find the IHDR chunk and this way i could find my mistakes.

* **Zlib Decompression:** The actual raw pixel data inside the 'IDAT' chunks is compressed. So i integrated the libary zlib to decompress it.
* **Unfiltering Pixels:** PNG utilizes adaptive filtering where each row of pixels can be filtered using one of 5 methods (None, Sub, Up, Average, Paeth) to optimize compression. This module loops through the decompressed scanlines and applies the inverse mathematical functions to reconstruct the actual RGB values.

### 3. The BMP Parser ("bmp_reader.c" & "bmp_saver.c")
Compared to PNG, the BMP format is uncompressed and its really simple. I implemented it with no problem.

### 4. The undo Subsystem(history.c & history.h)
I store all the filters and parameters in a linked list. It wasnt to hard for the filters you write the function pointers and save all the parameters in a structure. Then you go trough the list and applay everthing on the original data.

### 5. Image Processing Filters (filters.c & filters.h)
Every filter is applied to the active canvas is implemented through direct raw byte manupulation within the allocated 1D arrray representing the 2D grid of pixels.

The problem here was that png uses RGB but bmp uses BGR. So i if its BMP i just switch the channels then I do the math then switch back. 

## Key Features
#### Custom PNG Decoder: Parsed chunks, bit-manipulation, and IDAT decompression using the libary zlib.
#### Fully supporting BMP opening and saving.
#### Operation-Based Undo System: Uses a dynamic Linked List to store past filter functions and parameters.
#### Filters: Grayscale and Sepia (with adjustable intensity), Box Blur, and Horizontal Mirror.

## File Struchture
#### image.c The main file deals with user input.
#### png_reader.c/png_reader.h Opening pngs to a raw buffer.
#### bmp_loader.c Loading bmp images.
#### bmp_saver.c Saves bmp and png images to bmp.
#### history.c Managing history.
#### filters.c Pixel manipulation algorithms.
#### arithmetic_functions.c/reader_functions.c are both have helper functions.

## Challanges Overcome & Personal Reflections

This project was a brutal but rewarding teacher. The two most prominent bottlenecks I encountered were **memory leaks** and **pointer arithmetic debugging**.

This project taught me how to identify issues while working with binary files. 

I think it was also a basic introduction to grapics programming.

I learned how to write a muli threading program and when is it useful.

## How to Run
### Install dependencies
### Debian / Ubuntu / Mint

sudo apt update
sudo apt install libsdl2-dev

## Fedora / RHEL

sudo dnf install SDL2-devel

## Arch Linux / Manjaro

sudo pacman -S sdl2

## Compile

make

## Run

./file
