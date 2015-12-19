#include <ncurses.h>
#include <ImgLib/ImgLib.h>
#include <ImgLib/IL_BMP.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int max_y, max_x;

// Color scale factor = (1000/256)
#define CSF(x) ((x * 1000) / 256)
#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define CC(x,y) init_pair(x,y,y);

struct color {
  int n;
  int r;
  int g;
  int b;
} known_colors[] = {{COLOR_RED, 255, 0, 0},
                    {COLOR_GREEN, 0, 255, 0},
                    {COLOR_BLUE, 0, 0, 255},
                    {COLOR_BLACK, 0, 0, 0},
                    {COLOR_WHITE, 255, 255, 255},
                    {COLOR_CYAN, 0, 255, 255},
                    {COLOR_YELLOW, 255, 255, 0},
                    {COLOR_MAGENTA, 255, 0, 255}};

int cp;

#define sq(x) ((x) * (x))

static int cl(IL_RGBPixel *p, int ci) {
  int dr = p->r - known_colors[ci].r;
  int dg = p->g - known_colors[ci].g;
  int db = p->b - known_colors[ci].b;
  int res = dr * dr + dg * dg + db * db;
  return res;
}

static size_t get_color(IL_RGBPixel *p) {
  int rc = known_colors[0].n;
  int minl = cl(p, 0);
  for (size_t i = 1; i < LEN(known_colors); i++)
    if (cl(p, i) < minl) {
      rc = known_colors[i].n;
      minl = cl(p, i);
    }
  return rc;
}

void draw_img(IL_Image *img) {
  for (size_t y = 0; y < img->height; y++)
    for (size_t x = 0; x < img->width; x++) {
      IL_RGBPixel *p = get_pixel(img, x, y);
      attron(COLOR_PAIR(get_color(p)+2));
      mvaddch(y, x, ' ');
    }
  refresh();
}

void init(void) {
  cp = 0;
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, max_y, max_x);
}

void finalize(void) { endwin(); }

int main(int argc, char* argv[]) {
  if(argc!=2){
    printf("Usage:%s image.bmp", argv[0]);
    return EXIT_FAILURE;
  }
  init();
  for(size_t i =2; i<10;i++)
    CC(i,i-2);

  IL_Image *img = il_load_bmp_fromfile(argv[1]);
  draw_img(img);
//  IL_RGBPixel* p = get_pixel(img,6,7);
//  printf("%d %d %d %d",get_color(p),p->r,p->g,p->b);
  while(getchar()!='q');
  refresh();
  il_img_free(img);

  finalize();
  return EXIT_SUCCESS;
}
