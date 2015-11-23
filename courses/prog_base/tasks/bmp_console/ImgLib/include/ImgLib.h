#pragma once

typedef struct _IL_RGBPixel {
  int r,g,b;
} IL_RGBPixel;

typedef struct _IL_Image {
  int width,height;
  IL_RGBPixel pixels[];
} IL_Image;

IL_Image* il_img_alloc(unsigned int width,unsigned int height);
void il_img_free(IL_Image* img);
