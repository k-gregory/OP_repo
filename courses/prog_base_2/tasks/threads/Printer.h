#pragma once

typedef struct Printer Printer;

void PRINTER_INIT();
void PRINTER_DEINIT();

Printer* printer_new(const char* msg);
void printer_free(Printer* p);

void printer_exec(Printer* p);
