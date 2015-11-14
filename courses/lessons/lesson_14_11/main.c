#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_STRING_LENGTH 500
#define MAX_SENTENCES 10
#define MAX_WORDS 100
#define MAX_GROUPS 100
#define MAX_GROUP_LEN 50

struct _Sentence{
  char* it[MAX_STRING_LENGTH];
  char* words[MAX_WORDS];
  size_t words_len;
  char* groups[MAX_GROUPS];
  size_t groups_len;
};

typedef struct _Sentence Sentence;

void process(const char* str){
  Sentence sents[MAX_SENTENCES];
  char buff[MAX_STRING_LENGTH];
  size_t s_n=0;
  
  //Find sentences
  {
    strcpy(buff,str);
    char*  s = strtok(buff,".!?");
    while(s!=NULL){
      strcpy(sents[s_n].it,s);
      s_n++;
      s  = strtok(NULL, ".!?");
    }
  } 
  //Find words
  {
    for(size_t i = 0 ;i<s_n;i++){
      size_t w_l =0;
      strcpy(buff,sents[i].it);
      char* w = strtok(buff," :;-()\"'");
      while(w!=NULL){
	strcpy(sents[s_n].words[w_l++],w);
	w = strtok(buff," :;-()\"'");
      }
      sents[s_n].words_len = w_l;
    }
  }
 for(size_t  i = 0; i< s_n;i++)
  printf("Sentence: %s",sents[i].it); 
}

int main(void){
  const char* str = "My first thought was. \"Ooops, man!\" (and so on)";
  process(str);
  return EXIT_SUCCESS;
}
