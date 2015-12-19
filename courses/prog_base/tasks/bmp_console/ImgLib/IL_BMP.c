#include <ImgLib/ImgLib.h>
#include <ImgLib/IL_BMP.h>

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <assert.h>

#if !(defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#error big endian peasants are unwelcome
#endif


IL_Image *il_load_bmp_fromfile(const char *filename) {
    IL_Image* img;

  int32_t width;
  int32_t height;
  uint32_t off_bits;

  FILE *f = fopen(filename, "r");
  uint16_t u16;
  uint32_t u32;
  int32_t i32;
  // BMP FILE HEADER.
  // u16 bfType
  fread(&u16, sizeof(u16), 1, f);
  if(u16!=0x4D42)
    return NULL;
  // u32 bfSize
  fread(&u32,sizeof(u32),1,f);
  //printf("Size: %d\n",u32);
  // u16 bfReserved1
  fread(&u16, sizeof(u16), 1, f);
  if(u16!=0)
    return NULL;
  // u16 bfReserved2
  fread(&u16, sizeof(u16), 1, f);
  if(u16!=0)
    return NULL;
  // u32 bfOffBits
  fread(&off_bits, sizeof(off_bits), 1, f);
  //printf("Bits: %ud\n",off_bits);

  //BMP INFO HEADER (CORE)
  // i32 bcSize
  fread(&u32, sizeof(u32), 1, f);
  //printf("bcSize: %d\n",u32);
  //Finaly, width and height
  fread(&width,sizeof(width), 1, f);
  fread(&height,sizeof(height), 1, f);
  //printf("Width: %"PRIu16", Height: %"PRIu16, width, height);

  //WORD biPlanes must be 1
  fread(&u16, sizeof(u16), 1, f);
  assert(u16==1);

  //WORD biBitCount bits per pixel, only 24 is supported
  fread(&u16, sizeof(u16), 1, f);
  assert(u16==24);

  /*START READING PIXELS!*/
  img = il_img_alloc(width,height);
  fseek(f, off_bits, SEEK_SET);
  for(size_t y = 0; y< height;y++){
      int read_bytes = 0;
      for(size_t x = 0; x< width;x++){
          int real_y = height - y-1;
          get_pixel(img,x,real_y)->b = (int)fgetc(f);
          get_pixel(img,x,real_y)->g = (int)fgetc(f);
          get_pixel(img,x,real_y)->r = (int)fgetc(f);
          read_bytes+=3;
      }
      while(read_bytes++ % 4 != 0)
          fgetc(f);
  }

  fclose(f);
  return img;
}
