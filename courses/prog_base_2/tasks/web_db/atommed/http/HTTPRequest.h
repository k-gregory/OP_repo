#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>

namespace atommed {
namespace http {

enum class HTTPMethod {GET, POST, UNKNOWN_METHOD};
enum class HTTPStatus {
  OK = 200,
  NOT_FOUND = 404,
  UNKNOWN_STATUS,
};

class HTTPRequest {
public:
  const std::string HTTP11 = "HTTP/1.1";

  HTTPRequest(std::size_t data_len = 0);
  ~HTTPRequest();

  void set_method(HTTPMethod method);
  void set_status(HTTPStatus status);
  void set_uri(std::string uri);
  void set_version(std::string);
  void add_header(std::string name, std::string value);

  HTTPMethod get_method();
  HTTPStatus get_status();
  std::string get_uri();
  std::string get_version();
  std::string get_header(std::string name);

  void remove_header(std::string name);

private:
  HTTPMethod method;
  std::string uri;
  std::string version;
  HTTPStatus status;
  std::unordered_map<std::string, std::string> headers;
  std::unordered_map<std::string, std::vector<std::string>
    multi_headers;
  char* data;
  std::size_t data_length;
};// class HttpRequest
} // namespace http
} // namespace atommed
