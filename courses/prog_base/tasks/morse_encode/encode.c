#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static const char *morse_str(char x) {
  switch (toupper(x)) {
  case 'A':
    return ".-";
    break;
  case 'B':
    return "-...";
    break;
  case 'C':
    return "-.-.";
    break;
  case 'D':
    return "-..";
    break;
  case 'E':
    return ".";
    break;
  case 'F':
    return "..-.";
    break;
  case 'G':
    return "--.";
    break;
  case 'H':
    return "....";
    break;
  case 'I':
    return "..";
    break;
  case 'J':
    return ".---";
    break;
  case 'K':
    return "-.-";
    break;
  case 'L':
    return ".-..";
    break;
  case 'M':
    return "--";
    break;
  case 'N':
    return "-.";
    break;
  case 'O':
    return "---";
    break;
  case 'P':
    return ".--.";
    break;
  case 'Q':
    return "--.-";
    break;
  case 'R':
    return ".-.";
    break;
  case 'S':
    return "...";
    break;
  case 'T':
    return "-";
    break;
  case 'U':
    return "..-";
    break;
  case 'V':
    return "...-";
    break;
  case 'W':
    return ".--";
    break;
  case 'X':
    return "-..-";
    break;
  case 'Y':
    return "-.--";
    break;
  case 'Z':
    return "--..";
    break;
  case '0':
    return "-----";
    break;
  case '1':
    return ".----";
    break;
  case '2':
    return "..---";
    break;
  case '3':
    return "...--";
    break;
  case '4':
    return "....-";
    break;
  case '5':
    return ".....";
    break;
  case '6':
    return "-....";
    break;
  case '7':
    return "--...";
    break;
  case '8':
    return "---..";
    break;
  case '9':
    return "----.";
    break;
  case '.':
    return ".-.-.-";
    break;
  case ',':
    return "--..--";
    break;
  case '?':
    return "..--..";
    break;
  }
  return "x";
}

static inline void morse_put(char *dest, char mr, const char* dot, const char* tier){
    if(mr=='.')
        strcat(dest,dot);
    else strcat(dest, tier);
}

char *morse_encode(char *_signal, const char *message, int unit_len,
                   int pad_len) {
  char *signal = _signal;
  char *dot, *tier, *dt_separ, *sym_separ, *word_separ;
  dot = malloc(unit_len + 1);
  tier = malloc(unit_len * 3 + 1);
  dt_separ = malloc(unit_len + 1);
  sym_separ = malloc(unit_len * 3 + 1);
  word_separ = malloc(unit_len * 7 + 1);

  signal[0] = '\0';
  dot[0] = '\0';
  tier[0] = '\0';
  dt_separ[0] = '\0';
  sym_separ[0] = '\0';
  word_separ[0] = '\0';

  for (int i = 0; i < unit_len; i++)
    strcat(dot, "1");
  for (int i = 0; i < 3; i++)
    strcat(tier, dot);

  for (int i = 0; i < unit_len; i++)
    strcat(dt_separ, "0");
  for (int i = 0; i < 3; i++)
    strcat(sym_separ, dt_separ);
  for (int i = 0; i < 7; i++)
    strcat(word_separ, dt_separ);

  for (int i = 0; i < pad_len; i++)
    strcat(signal, "0");

  for(size_t i =0; i<strlen(message);i++){
      if(message[i]==' '){
          strcat(signal, word_separ);
          continue;
      }
      const char* mr = morse_str(message[i]);
      size_t j;
      for(j =0; j< strlen(mr)-1;j++){
          morse_put(signal, mr[j], dot, tier);
          strcat(signal,dt_separ);
      }
      morse_put(signal, mr[j], dot, tier);
      if(message[i+1]!=' ' && message[i+1]!='\0')
          strcat(signal, sym_separ);
  }

  for (int i = 0; i < pad_len; i++)
    strcat(signal, "0");
  free(dot);
  free(tier);
  free(dt_separ);   // Kill them with fire
  free(sym_separ);  // Kill them with fire
  free(word_separ); // Kill them with fire
  return signal;
}

int main(void) {
  const char *src = "HEY DUDE";
  char buff[1024];
  puts(morse_encode(buff, src, 2, 0));
  return EXIT_SUCCESS;
}
