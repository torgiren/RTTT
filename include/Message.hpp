#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

class Message
{
public:
  enum { header_length = 4 };
  enum { max_body_length = 512 };

  Message(): _body_length(0){
  }

  const char* data() const {
    return _data;
  }

  char* data(){
    return _data;
  }

  size_t length() const{
    return header_length + _body_length;
  }

  const char* body() const{
    return _data + header_length;
  }

  char* body(){
    return _data + header_length;
  }

  size_t body_length() const{
    return _body_length;
  }

  void body_length(size_t length){
    _body_length = length;
    if (_body_length > max_body_length)
      _body_length = max_body_length;
  }

  bool decode_header(){
    using namespace std; // For strncat and atoi.
    char header[header_length + 1] = "";
    strncat(header, _data, header_length);
    _body_length = atoi(header);
    if (_body_length > max_body_length){
      _body_length = 0;
      return false;
    }
    return true;
  }

  void encode_header(){
    using namespace std; // For sprintf and memcpy.
    char header[header_length + 1] = "";
    sprintf(header, "%4d", _body_length);
    memcpy(_data, header, header_length);
  }

private:
  char _data[header_length + max_body_length];
  size_t _body_length;
};

#endif // CHAT_MESSAGE_HPP
