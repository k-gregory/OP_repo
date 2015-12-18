#include <ncurses.h>
#include <ImgLib/ImgLib.h>
#include <ImgLib/IL_BMP.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int max_y, max_x;

//Color scale factor = (1000/256)
#define CSF(x) ((x*1000)/256)

static void _set_color(IL_RGBPixel* p){
    init_color(COLOR_RED, CSF(p->r),CSF(p->g),CSF(p->b));
    if(CSF(p->b < 800)) mvprintw(40,50,"%d", CSF(p->b));
}

void draw_img(IL_Image* img){
    for(size_t y =0; y<img->height;y++)
        for(size_t x =0; x<img->width;x++){
            IL_RGBPixel* p = get_pixel(img,x,y);
            _set_color(p);

            //attron(COLOR_PAIR(1));
            //printw("%d %d %d,", CSF(p->r), CSF(p->g), CSF(p->b));
            mvaddch(y,x,' ');
        }
    refresh();
}

void init(void) {
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, max_y, max_x);

  init_pair(1, COLOR_BLACK, COLOR_RED);
  attron(COLOR_PAIR(1));
}

void finalize(void){
    endwin();
}

int main(void) {
  init();

  IL_Image* img = il_load_bmp_fromfile("test.bmp");
  draw_img(img);
  il_img_free(img);

  finalize();
  return 0;
}
