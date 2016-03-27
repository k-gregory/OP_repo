#include "Printer.h"

#include <stdio.h>

int main(void){
  Printer *p1, *p2, *p3;
  PRINTER_INIT();
  p1 = printer_new("Printer 1");
  p2 = printer_new("Printer 2");
  p3 = printer_new("Printer 3");
  printer_exec(p1);
  printer_exec(p2);
  printer_exec(p3);

  getchar(); //Exit by ENTER
  
  printer_free(p1);
  printer_free(p2);
  printer_free(p3);
  
  PRINTER_DEINIT();
}
