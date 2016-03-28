#include "HTTPRequest.h"

namespace atommed {
namespace http {
  HTTPRequest::HTTPRequest(std::size_t data_length)
    : method(HTTPMethod::UNKNOWN_METHOD),
      status(HTTPStatus::UNKNOWN_STATUS)
  {
    if(data_length != 0)
      data = new char[data_length];
    else data = nullptr;
  };
  HTTPRequest::~HTTPRequest(){
    delete data;
  };

  void HTTPRequest::set_method(HTTPMethod method){
    this->method = method;
  }
  HTTPMethod HTTPRequest::get_method(){
    return method;
  }

  void HTTPRequest::set_status(HTTPStatus status){
    this->status = status;
  }
  HTTPStatus HTTPRequest::get_status(){
    return status;
  }

  void HTTPRequest::set_version(std::string version){
    this->version = version;
  }
  std::string HTTPRequest::get_version(){
    return version;
  }

  void HTTPRequest::add_header(std::string key, std::string value){
   //TODO
   //NOTE: separate by comas
  }
  void HTTPRequest::get_header(std::string key){
    return key + " not implemented"; //TODO
  }

} //namespace http
} //namespace atommed
