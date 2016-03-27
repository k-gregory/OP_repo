#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LEN(arr) (sizeof(arr)/sizeof((arr)[0]))

#define TASK_SERVER "pb-homework.appspot.com"
#define TASK_SERVER_PORT 80

#define TASK_VARIANT "5"

#define CRLF "\r\n"

ssize_t make_http_get_request(int sockfd, const char* url, const char* host){
  char buffer[1024];
  int snprintf_res;
  snprintf_res =
    snprintf(buffer,
	     LEN(buffer),
	     "GET %s HTTP/1.1" CRLF
	     "Host: %s" CRLF
	     CRLF,
	     url, host);
  if(snprintf_res < 0 || snprintf_res > LEN(buffer)) return -1;
  return send(sockfd, buffer, snprintf_res, 0);
}

ssize_t make_http_post_request(int sockfd, const char* url, const char* host, const char* data){
  char buffer[1024];
  int snprintf_res;
  snprintf_res =
    snprintf(buffer,
	     LEN(buffer),
	     "POST %s HTTP/1.1" CRLF
	     "Host: %s" CRLF
	     "Content-Length: %zu" CRLF
	     CRLF
	     "%s",
	     url,host,strlen(data),data);
  if(snprintf_res < 0 || snprintf_res > LEN(buffer)) return -1;
  return send(sockfd, buffer, snprintf_res, 0);
}

unsigned int count_words_in_sentence(const char* sentence){
  int in_word = 0;
  unsigned int words = 0;
  while(*sentence != '\0'){
    if(isalnum(*sentence)){
      if(!in_word){
	in_word = 1;
	words++;
      }
    } else in_word = 0;
    sentence++;
  }
  return words;
}

int main(void){
  int sockfd;
  struct hostent *task_host;
  struct sockaddr_in addr;
  char uri_buff[1024];
  char recv_buff[1024];
  ssize_t recv_len;
  char *secret;
  char* sentence;
  unsigned int words_in_sentence;
  char answer_buff[20];
  char* server_justice;

  //Get host name
  task_host = gethostbyname(TASK_SERVER);
  if(task_host == NULL){
    perror("Can't resolve host name");
    exit(EXIT_FAILURE);
  }

  //Connect to socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(TASK_SERVER_PORT);
  memcpy(&addr.sin_addr, task_host->h_addr_list[0], task_host->h_length);
  if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) != 0){
    perror("Can't connect");
    exit(EXIT_FAILURE);
  }

  //Request secret
  if(make_http_get_request(sockfd, "/var/" TASK_VARIANT, TASK_SERVER) < 0){
    perror("Can't request secret");
    exit(EXIT_FAILURE);
  }
  //Receive secret
  recv_len = recv(sockfd, recv_buff, LEN(recv_buff)-1, 0);
  recv_buff[recv_len] = '\0';
  secret = strstr(recv_buff, CRLF CRLF "secret=");
  if(secret == NULL){
    perror("Can't find secret =( Maybe, buffer is not big enough");
    exit(EXIT_FAILURE);
  }
  secret+=strlen(CRLF CRLF "secret=");
  printf("Secret is \"%s\"\n", secret);

  //Request data
  sprintf(uri_buff,"/var/" TASK_VARIANT "?secret=%s", secret);
  if(make_http_get_request(sockfd, uri_buff, TASK_SERVER) < 0){
    perror("Can't request data");
    exit(EXIT_FAILURE);
  }
  //Receive data
  recv_len = recv(sockfd, recv_buff, LEN(recv_buff) -1, 0);
  recv_buff[recv_len] = '\0';
  sentence =  strstr(recv_buff, CRLF CRLF);
  if(sentence == NULL){
    perror("Can't find data =) Maybe, buffer is not big enough");
    exit(EXIT_FAILURE);
  }
  sentence+=strlen(CRLF CRLF);
  //Count words
  words_in_sentence = count_words_in_sentence(sentence);
  printf("Sentence is \"%s\" and it has %d words\n",sentence, words_in_sentence);

  //Send data processing result
  strcpy(uri_buff,"/var/" TASK_VARIANT);
  sprintf(answer_buff, "result=%d", words_in_sentence);
  make_http_post_request(sockfd, uri_buff, TASK_SERVER, answer_buff);
  //Receive "Failure!" or "Success!" from server
  recv_len = recv(sockfd,recv_buff, LEN(recv_buff) -1, 0);
  recv_buff[recv_len] = '\0';
  server_justice = strstr(recv_buff,CRLF CRLF "Failure!");
  if(server_justice!=NULL){
    puts("Failure, for some reason");
  } else {
    server_justice = strstr(recv_buff, CRLF CRLF "Success!");
    if(server_justice!=NULL){
      puts("Did that");
    } else {
      puts("Not \"Success!\" nor \"Failure!\" found. Shitty client"
           "deserved shitty result");
    }
  }
  
  close(sockfd);
  return EXIT_SUCCESS;
}
