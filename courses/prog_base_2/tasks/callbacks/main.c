#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

typedef void (*text_f)(const char* text);

void sent_print_cb(const char* text){
  printf("Sentence: \"%s\"\n", text);
}

void text_word_length_cb(const char* _text){
  const char* text = _text;
  size_t str_words_len = 0;
  while(*text != '\0'){
    if(isalpha(*text))
      ++str_words_len;
    ++text;
  }
  printf("\"%s\" length of words: %zu\n",_text,str_words_len);
}

void bad_word_checker_cb(const char* text){
  const char* const bad_words[] =
    {"assembly", "windows", "matan", "kursach", "deadline"};

  char* low_text = malloc(strlen(text));
  strcpy(low_text, text);
  for(size_t i = 0; i < strlen(text); i++)
    low_text[i] = tolower(low_text[i]);
  
  for(size_t i = 0 ; i < LEN(bad_words); ++i){
    char* bad_word = strstr(low_text,bad_words[i]);
    if(bad_word) {
      printf("A bad word found: %s\n", bad_word);
      break;
    }
  }
  free(low_text);
}

void word_print_cb(const char* text){
  printf("Word: \"%s\"\n", text);
}

static void noop_text_cb(const char* text){
}

void process(const char* _str, text_f sentenceCB, text_f wordCB){
  char* str = malloc(strlen(_str)+1);
  strcpy(str, _str);

  if(!sentenceCB) sentenceCB = noop_text_cb;
  if(!wordCB) wordCB = noop_text_cb;

  char* tokenized = strtok(str,".?!");
  while(tokenized){
    sentenceCB(tokenized);
    while(*tokenized!='\0'){
      char* word_start;

      while(!isalpha(*tokenized) && *tokenized != '\0')
	tokenized++; //Find word beginning

      word_start = tokenized;

      while(isalpha(*tokenized) && *tokenized != '\0') 
	tokenized++; //Go to end of word

      if(*tokenized!='\0'){
	*(tokenized) = '\0';
	tokenized++;
      }

      if(*word_start != '\0')
	wordCB(word_start);
    }

    tokenized = strtok(NULL, ".?!");
  }

  free(str);
}

int main(void){
  process("Oh, lol! Tthis is insanity. " \
      "  What are me doein here?   " \
      "I love rabbits????  Penguins  "
      ,sent_print_cb, word_print_cb);
  
  puts("\n#####Another launch ######\n");
  
  process("I have just done some strstrtestmatan."\
	  "It is time to write some ASSembly"	\
          " for !!WinDoWS?!!. It is going to be"\
	  " my kursach?Writting assembly is the"\
	  " best way to fail deadline"
	  ,text_word_length_cb, bad_word_checker_cb);
  return EXIT_SUCCESS;
}
