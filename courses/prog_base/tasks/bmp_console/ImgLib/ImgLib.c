#include <ImgLib/ImgLib.h>

#include <stdlib.h>
#include <assert.h>

IL_Image *il_img_alloc(size_t width, size_t height) {
  IL_Image *img =
      malloc(sizeof(IL_Image) + sizeof(IL_RGBPixel) * width * height);
  img->width = width;
  img->height = height;
  return img;
}

inline void il_img_free(IL_Image *img) { free(img); }

inline IL_RGBPixel* get_pixel(IL_Image *img, size_t x, size_t y){
    assert(x<img->width && x>= 0);
    assert(y<img->height && x>=0);
    return &img->pixels[img->width*y + x];
}
