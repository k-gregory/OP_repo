#pragma once

#include <stdlib.h>

typedef struct _IL_RGBPixel { int r, g, b; } IL_RGBPixel;

typedef struct _IL_Image {
  int width, height;
  IL_RGBPixel pixels[];
} IL_Image;

IL_Image *il_img_alloc(size_t width, size_t height);
void il_img_free(IL_Image *img);

IL_RGBPixel* get_pixel(IL_Image* img, size_t x, size_t y);
