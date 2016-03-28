#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>

namespace atommed {
namespace http {
class HttpRequest {
public:
  const std::string HTTP11 = "HTTP/1.1";
  enum class HttpMethod { GET, POST};

  void set_method(std::string method);
  void set_uri(std::string uri);
  void set_version(std::string);
  void set_header(std::string name, std::string value);
  void set_cookie

  std::string get_method();
  std::string get_uri();
  std::string get_version();
  std::string get_header(std::string name);

private:
  HttpMethod method;
  std::string uri;
  std::string version;
  std::unordered_map<std::string, std::string> headers;
  char* data;
  std::size_t data_length;
};// class HttpRequest
} // namespace http
} // namespace atommed
