#include "httprequest.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CR '\r'
#define LF '\n'

typedef enum ParseStatus{
  PARSE_START = 0,
  
  PARSE_METHOD = 1,
  
  PARSE_SPACE_BEFORE_URI = 2,
  PARSE_URI = 3,
  
  PARSE_SPACE_BEFORE_VERSION = 4,  
  PARSE_VERSION = 5,
  
  PARSE_CR_BEFORE_HEADER_NAME = 6,
  PARSE_LF_BEFORE_HEADER_NAME = 7,
  PARSE_HEADER_NAME = 8,
  PARSE_HEADER_VALUE_SEP = 9,
  PARSE_SPACE_BEFORE_HEADER_VALUE = 10,
  PARSE_HEADER_VALUE = 11,
  PARSE_PRE_BODY = 12,
  PARSE_BODY=13,
  PARSE_FOOTERS,
} ParseStatus;

typedef struct HTTPHeader {
  char* name;
  char* value;
} HTTPHeader;

struct HTTPRequest {
  HTTPMethod method;
  char URI[MAX_URI_LENGTH];

  HTTPVersion http_version;
  
  HTTPHeader headers[MAX_HEADERS];/*TODO: Use hashmap*/
  size_t headers_num;

  char* body;
  size_t content_length;

  unsigned int crlf_count; /*TODO: Use parse_buff*/
  char parse_buff[1024];
  size_t parse_buff_pos;
  ParseStatus parse_status;
  ParseError err;
};

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
  req->crlf_count = 0;
  
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
  size_t pos,i,bytes_to_copy;
  pos = 0;
  
  while(pos < len){
    //    printf("a\"%c\"b: %d\n",data[pos],req->parse_status);
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
	req->parse_status = PARSE_CR_BEFORE_HEADER_NAME;

	//	pos++;
      }
      break;

    case PARSE_LF_BEFORE_HEADER_NAME:
      if(data[pos] == '\n'){
	++req->crlf_count;
	//	printf("CCC: %d\n",req->crlf_count);
	if(req->crlf_count < 2)
	req->parse_status = PARSE_CR_BEFORE_HEADER_NAME;
	else req->parse_status = PARSE_PRE_BODY;
	       
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

	req->crlf_count = 0;
	req->parse_status = PARSE_CR_BEFORE_HEADER_NAME;
	//	++pos;
      }
      break;

    case PARSE_PRE_BODY:
      //      puts("Pre body");
      for(i = 0; i < req->headers_num;i++){
	if(!strcmp(req->headers[i].name,"Content-Length")){
	  /*TODO: replace %zu*/
	  /*TODO: check maximum content-length*/
	  sscanf(req->headers[i].value,"%zu",&req->content_length);
	  req->body = realloc(req->body,req->content_length+1);
	  req->body[req->content_length] = '\0';
	}
      }
      if(req->body == NULL){
	req->err = BAD_BODYLENGTH_UNDEFINED;
	return PARSE_ERROR;
      }
      req->parse_buff_pos = 0;
      req->parse_status = PARSE_BODY;
      break;

    case PARSE_BODY:
      if(len - pos > req->content_length - req->parse_buff_pos){
	req->err = PARSED;
	bytes_to_copy = req->content_length - req->parse_buff_pos;
	req->parse_status = PARSE_FOOTERS;
      }
      else {
	bytes_to_copy = len - pos;
      }
      memcpy(req->body+req->parse_buff_pos,
	     data+pos,
	     bytes_to_copy);
      req->parse_buff_pos += bytes_to_copy;
      pos += bytes_to_copy;
      if(req->parse_buff_pos == req->content_length)
	return PARSED_BODY;
      break;

    case PARSE_FOOTERS:
      req->err = BAD_UNIMPLEMENTED;
      return PARSE_END; /*Footers not implemented yet*/
      return PARSE_ERROR;
      pos++;
      break;
    }
  }
  return PARSE_OK;
}


ParseError http_request_get_error(HTTPRequest* req){
  return req->err;
}

HTTPMethod http_request_get_method(HTTPRequest* req){
  return req->method;
}

HTTPVersion http_request_get_http_version(HTTPRequest* req){
  return req->http_version;
}

char* http_request_get_uri(HTTPRequest* req){
  return req->URI;
}

char* http_request_get_header(HTTPRequest* req, char* name){
  size_t i;
  for(i = 0; i < req->headers_num; i++)
    if(!strcmp(req->headers[i].name, name))
      return req->headers[i].value;
  
  return NULL;
}

char* http_request_get_body(HTTPRequest* req){
  return req->body;
}

#ifdef __KILL_THIS_CODE__
int main(int argc, char* argv[]){
  size_t reqlen;
  HTTPRequest* req;
  const char* test_req;
  
  req = http_request_new();
  test_req ="GET /index.html HTTP/1.1" CRLF\
            "Content-Length: 1" CRLF\
            "A:       B" CRLF\
            "C:          D" CRLF\
            CRLF\
            "x";

  reqlen =  strlen(test_req) - 1;

  //http_request_parse_feed(req, test_req, strlen(test_req));

  
  for(size_t i = 0;  i < reqlen / 9; i+=9){
    http_request_parse_feed(req,test_req,9);
    test_req+=9;
  }
  http_request_parse_feed(req,test_req,reqlen - reqlen / 9);
  
  /*while(*test_req!='\0'){
    http_request_parse_feed(req,test_req,1);
    ++test_req;
    };*/

  printf("method: %d\n, URI:\"%s\"\n, version: %d\n"\
	 "header1: \"%s\": \"%s\"\n"\
	 "header3: \"%s\": %s\n"\
	 "err : %d\n"\
	 "body: %s\n",
	 req->method,
	 req->URI,
	 req->http_version,
	 req->headers[0].name, req->headers[0].value,
	 req->headers[2].name, req->headers[2].value,
	 req->err,
	 req->body);
  
  http_request_free(req);
  exit(EXIT_SUCCESS);
}
#endif
