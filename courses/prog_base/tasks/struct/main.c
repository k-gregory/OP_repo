#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

#define COMMENT_LENGTH 140

typedef struct {
  size_t comment_id;
  size_t author_id;
  size_t related_post_id;
  char text[COMMENT_LENGTH];
  size_t likes;
} Comment;

size_t count(size_t size, Comment comment[size]) {
  size_t ret = 0;
  for (size_t i = 0; i < size; i++)
    if (comment[i].likes > 100)
      ret++;
  return ret;
}

void change(Comment *old, const char *new_text) {
  assert(strlen(new_text) < COMMENT_LENGTH);
  strcpy(old->text, new_text);
}

void print(Comment *comment) {
  puts("-----------------------");
  printf("ID:#%zu; posted by #%zu(%zu likes) in response to #%zu\n%s\n",
         comment->comment_id, comment->author_id, comment->likes,
         comment->related_post_id, comment->text);
}

int main(void) {
  Comment comments[] = {
      /*Uniq id, author_id, related_post_id, text, likes*/
      {1, 32674, 0, "APXNBbI specslujb besplatno bez SMS", 15},
      {2, 5122, 0, "3ABE3NTE UTF-8 B C", 100500},
      {3, 2236, 2, "Po4emu ya doljen pisat translitom?", 123},
      {4, 845, 1, "Autism intensifies", 20},
      {5, 15390, 1, "Ololo, nabigaem", 237},
      {6, 2238, 5, "Hy u PAKi TyT", 1},
      {7, 8112, 3, "+15, Olga", 15},
      {8, 454, 0, " ▲\n"
                  "▲ ▲",
       100501},
      {9, 400902465, 0, "А тут я протестирую кириллицу", 0},
      {10, 378, 0, "Ogo, da tut u nas pervij GET!!!1", 1},
      {11, 21345, 0, "Один лайк и я сдам все лабораторные", 1},
      {12, 21345, 11, "Окей", 0},
  };
  for (size_t i = 0; i < LEN(comments); i++)
    print(&comments[i]);
  printf("\nWe have %zu comments with > 100 likes, here they go:\n",
         count(LEN(comments), comments));

  for (size_t i = 0; i < LEN(comments); i++)
    if (comments[i].likes > 100)
      print(&comments[i]);

  size_t id_to_change;
  while(1){
    char buff[100];
    puts("Print index of comment which you want to change");
    fgets(buff,LEN(buff),stdin);
    if(sscanf(buff,"%zu",&id_to_change)==1)
      break;
  }

  size_t i;
  for(i =0; i< LEN(comments);i++)
    if(comments[i].comment_id==id_to_change){
      change(&comments[i], "Avtor etogo komentarija bul zobanen");
      break;
    }
  if(i!=LEN(comments)){
  puts("Now that comment was changed, it now looks like:");
  print(&comments[i]);
  }

  return EXIT_SUCCESS;
}
