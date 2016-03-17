#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef void (*text_f)(const char* text);

void sent_fl(const char* text){
  printf("Sentence: \"%s\"\n", text);
}

void word_fl(const char* text){
  printf("Word: \"%s\"\n", text);
}

void process(const char* _str, text_f sentenceCB, text_f wordCB){
  char* str = malloc(strlen(_str)+1);
  strcpy(str, _str);

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
      ,sent_fl, word_fl);
  return EXIT_SUCCESS;
}
