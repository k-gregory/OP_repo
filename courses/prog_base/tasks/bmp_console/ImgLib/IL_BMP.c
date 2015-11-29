#include <ImgLib/ImgLib.h>
#include <ImgLib/IL_BMP.h>

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

#if !(defined __BYTE_ORDER__ && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#error big endian peasants are unwelcome
#endif

IL_Image *il_load_bmp_fromfile(const char *filename, IL_Image* img) {

  uint16_t width;//,height;
  uint16_t height;

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
  printf("Size: %d\n",u32);
  // u16 bfReserved1
  fread(&u16, sizeof(u16), 1, f);
  if(u16!=0)
    return NULL;
  // u16 bfReserved2
  fread(&u16, sizeof(u16), 1, f);
  if(u16!=0)
    return NULL;
  // u32 bfOffBits
  fread(&u32, sizeof(u32), 1, f);
  printf("Bits: %d\n",u32);

  //BMP INFO HEADER (CORE)
  // i32 bcSize
  fread(&i32, sizeof(i32), 1, f);
  printf("bcSize: %d\n",i32);
  //Finaly, width and height
  fread(&width,sizeof(width), 1, f);
  fread(&height,sizeof(height), 1, f);
  printf("Width: %"PRIu16", Height: %"PRIu16, width, height);
  if(height==0)
    puts("shit");
  fclose(f);
  if(img==NULL)
    img = il_img_alloc(width,height);
  return img;
}