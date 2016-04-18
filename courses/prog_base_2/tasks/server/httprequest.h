#pragma once

#include <stdlib.h>

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
  BAD_BODYLENGTH_UNDEFINED,
  BAD_UNIMPLEMENTED,
} ParseError;


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

typedef struct HTTPRequest HTTPRequest;

HTTPRequest* http_request_new();
void http_request_free(HTTPRequest* req);
ParseError http_request_get_error(HTTPRequest* req);

int http_request_parse_feed(HTTPRequest* req,
			    const char data[],
			    size_t len);

HTTPMethod http_request_get_method(HTTPRequest* req);
char* http_request_get_uri(HTTPRequest* req);
HTTPVersion http_request_get_http_version(HTTPRequest* req);
char* http_request_get_header(HTTPRequest* req, char* name);
char* http_request_get_body(HTTPRequest* req);
