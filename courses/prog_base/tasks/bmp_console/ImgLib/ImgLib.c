#include <ImgLib/ImgLib.h>

#include <stdlib.h>

IL_Image *il_img_alloc(unsigned int width, unsigned int height) {
  IL_Image *img =
      malloc(sizeof(IL_Image) + sizeof(IL_RGBPixel) * width * height);
  img->width = width;
  img->height = height;
  return img;
}

inline void il_img_free(IL_Image *img) { free(img); }
