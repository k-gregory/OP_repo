#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CR '\r'
#define LF '\n'

#define CRLF "\r\n"

#define MAX_URI_LENGTH 100
#define MAX_HEADERS 100

#define PARSE_OK 0
#define PARSE_END 1
#define PARSE_ERROR 2

typedef enum ParseError{
  PARSE_NOTSTARTED,
  PARSED,
  BAD_SEPARATOR,
  BAD_CRLF,
} ParseError;

typedef enum ParseStatus{
  PARSE_START,
  
  PARSE_METHOD,
  
  PARSE_SPACE_BEFORE_URI,
  PARSE_URI,
  
  PARSE_SPACE_BEFORE_VERSION,  
  PARSE_VERSION,
  
  PARSE_CR_BEFORE_HEADER_NAME,
  PARSE_LF_BEFORE_HEADER_NAME,
  PARSE_HEADER_NAME = 42,
  PARSE_HEADER_VALUE_SEP,
  PARSE_SPACE_BEFORE_HEADER_VALUE,
  PARSE_HEADER_VALUE,
} ParseStatus;

typedef enum HTTPMethod {
  GET=-50,
  POST,
  DELETE,
  METHOD_UNKNOWN,
} HTTPMethod;

typedef enum HTTPVersion {
  HTTP11=-45,
  VERSION_UNKNOWN,
} HTTPVersion;

typedef struct HTTPHeader {
  char* name;
  char* value;
} HTTPHeader;

typedef struct HTTPRequest {
  HTTPMethod method;
  char URI[MAX_URI_LENGTH];

  HTTPVersion http_version;
  
  HTTPHeader headers[MAX_HEADERS];/*TODO: Use hashmap*/
  size_t headers_num;

  char* body;
  size_t content_length;

  char parse_buff[1024];
  size_t parse_buff_pos;
  ParseStatus parse_status;
  ParseError err;
} HTTPRequest;

HTTPRequest* http_request_new(){
  HTTPRequest* req;
  req = malloc(sizeof(HTTPRequest));
  
  req->method = METHOD_UNKNOWN;
  req->URI[0] = '\0';
  req->http_version = VERSION_UNKNOWN;
  req->headers_num = 0;
  req->body = NULL;
  req->content_length = 0;
  req->parse_buff_pos = 0;
  req->parse_status = PARSE_START;
  req->err = PARSE_NOTSTARTED;
  
  return req;
}

void http_request_free(HTTPRequest* req){
  size_t i;
  for(i = 0; i < req->headers_num; i++){
    free(req->headers[i].name);
    free(req->headers[i].value);
  }
  free(req->body);
  free(req);
}

/*TODO: Parse buff size is limited*/
int http_request_parse_feed(HTTPRequest* req,const char data[], size_t len){
  size_t pos;
  pos = 0;
  
  while(pos < len){
    switch(req->parse_status){
      
    case PARSE_START:
      req->parse_status = PARSE_METHOD;/*TODO: skip trailing CRLF*/
      break;
      
    case PARSE_METHOD:
      /*TODO: isalpha depends on locale*/      
      while(isalpha(data[pos]) && pos < len){
	req->parse_buff[req->parse_buff_pos++] = data[pos];
	pos++;
      }
      if(data[pos] == ' '){
	req->parse_buff[req->parse_buff_pos] = '\0';
	if     (!strcmp("GET",    req->parse_buff))
	  req->method =  GET;
	else if(!strcmp("POST",   req->parse_buff))
	  req->method =  POST;
	else if(!strcmp("DELETE", req->parse_buff))
	  req->method =  DELETE;

	req->parse_buff_pos =  0;
	req->parse_status = PARSE_SPACE_BEFORE_URI;
      }
      break;

    case PARSE_SPACE_BEFORE_URI:
      if(data[pos] == ' '){
	req->parse_status = PARSE_URI;
	pos++;
      } else {
	req->err = BAD_SEPARATOR;
	return PARSE_ERROR;
      }
      break;

    case PARSE_URI:
      while(data[pos] != ' ' && pos < len){
	req->parse_buff[req->parse_buff_pos++] = data[pos];
	pos++;
      }

      if(data[pos] == ' ') {
	req->parse_buff[req->parse_buff_pos] = '\0';
	strncpy(req->URI, req->parse_buff, MAX_URI_LENGTH);

	req->parse_status = PARSE_SPACE_BEFORE_VERSION;
	req->parse_buff_pos = 0;
      }
      break;

    case PARSE_SPACE_BEFORE_VERSION:
      if(data[pos] == ' '){
	req->parse_status = PARSE_VERSION;
	pos++;
      } else {
	req->err = BAD_SEPARATOR;
	return PARSE_ERROR;
      }
      break;
      
    case PARSE_VERSION:
      while(data[pos] != '\r' && pos < len){
	req->parse_buff[req->parse_buff_pos++] = data[pos];
	pos++;
      }

      if(data[pos] == '\r') {
	req->parse_buff[req->parse_buff_pos] = '\0';
	if(!strcmp("HTTP/1.1", req->parse_buff))
	  req->http_version = HTTP11;

	req->parse_buff_pos = 0;
	req->parse_status = PARSE_LF_BEFORE_HEADER_NAME;

	pos++;
      }
      break;

    case PARSE_LF_BEFORE_HEADER_NAME:
      if(data[pos] == '\n'){
	req->parse_status = PARSE_CR_BEFORE_HEADER_NAME;
	pos++;
      } else  {
	req->err = BAD_CRLF;
	return PARSE_ERROR;
      }
      break;

    case PARSE_CR_BEFORE_HEADER_NAME:
      if(data[pos] == '\r'){
	req->parse_status = PARSE_LF_BEFORE_HEADER_NAME;
	pos++;
      } else req->parse_status = PARSE_HEADER_NAME;
      break;

    case PARSE_HEADER_NAME:
      while(data[pos] != ':' && pos < len){
	req->parse_buff[req->parse_buff_pos++] = data[pos];
	pos++;
      }
      if(data[pos] == ':'){
	size_t headername_len;
	req->parse_buff[req->parse_buff_pos] = '\0';
	req->parse_buff_pos = 0;
	
	headername_len = strlen(req->parse_buff);
	req->headers[req->headers_num].name = malloc(headername_len+1);
	req->headers[req->headers_num].value = NULL;
	strcpy(req->headers[req->headers_num].name,
	       req->parse_buff);
	++req->headers_num;
	
	req->parse_status = PARSE_HEADER_VALUE_SEP;
      }
      break;

    case PARSE_HEADER_VALUE_SEP:
      if(data[pos] == ':') pos++;
      else {
	req->err = BAD_SEPARATOR;
	return PARSE_ERROR;
      }
      req->parse_status = PARSE_SPACE_BEFORE_HEADER_VALUE;
      break;

    case PARSE_SPACE_BEFORE_HEADER_VALUE:
      while(data[pos] == ' ' && pos < len) ++pos;
      if(data[pos] != ' ') req->parse_status = PARSE_HEADER_VALUE;
      break;
      
    case PARSE_HEADER_VALUE:
      while(data[pos] != CR && pos < len){
	req->parse_buff[req->parse_buff_pos++] = data[pos];
	pos++;
      }
      if(data[pos] == CR){
	size_t headervalue_len;
	req->parse_buff[req->parse_buff_pos] = '\0';
	req->parse_buff_pos = 0;

	headervalue_len = strlen(req->parse_buff);
	req->headers[req->headers_num - 1].value =
	  malloc(headervalue_len + 1);
	strcpy(req->headers[req->headers_num -1].value,
	       req->parse_buff);

	req->parse_status = PARSE_CR_BEFORE_HEADER_NAME;
	//	++pos;
      }
      break;
    }
  }
  return PARSE_OK;
}

int main(int argc, char* argv[]){
  HTTPRequest* req;
  const char* test_req;
  
  req = http_request_new();
  test_req ="GET /index.html HTTP/1.1" CRLF\
            "Content-Length: 1" CRLF\
            "A:       B" CRLF\
            "C:          D" CRLF\
            CRLF\
            "x";

  //http_request_parse_feed(req, test_req, strlen(test_req));
  
  while(*test_req!='\0'){
    http_request_parse_feed(req,test_req,1);
    ++test_req;
    };

  printf("method: %d\n, URI:\"%s\"\n, version: %d\n"\
	 "header1: %s: %s\n"\
	 "header3: %s: %s\n"\
	 "err : %d\n",
	 req->method,
	 req->URI,
	 req->http_version,
	 req->headers[0].name, req->headers[0].value,
	 req->headers[2].name, req->headers[2].value,
	 req->err);
  
  http_request_free(req);
  exit(EXIT_SUCCESS);
}
