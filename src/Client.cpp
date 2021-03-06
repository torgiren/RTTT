#include "Client.hpp"
  Client* Client::create(const std::string host, const std::string port){
     boost::asio::io_service* io=new boost::asio::io_service();
     return new Client(*io, host.c_str(), port.c_str());
    
  } 
  void Client::close(){
    _io_service.post(boost::bind(&Client::do_close, this));
  }
  void Client::send(const std::string& m){
      Message msg;
      msg.body_length(strlen(m.c_str()));
      memcpy(msg.body(), m.c_str(), msg.body_length());
      msg.encode_header();
      write(msg);
  }


  Client::Client(boost::asio::io_service& io_service, const char* host, const char* port):
   _io_service(io_service), _socket(io_service)
  {
    tcp::resolver resolver(_io_service);
    tcp::resolver::query query(host, port);
    tcp::resolver::iterator iterator = resolver.resolve(query);
    tcp::endpoint endpoint = *iterator;
    _socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++iterator));
    _t = new boost::thread(boost::bind(&boost::asio::io_service::run, &io_service));
  }
  Client::~Client(){
     _t->join();
     delete _t;
  }

  void Client::write(const Message& msg){
    _io_service.post(boost::bind(&Client::do_write, this, msg));
  }

  void Client::handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator){
    if (!error)
    {
      boost::asio::async_read(_socket,
          boost::asio::buffer(_read_msg.data(), Message::header_length),
          boost::bind(&Client::handle_read_header, this, boost::asio::placeholders::error));
    }
    else if (endpoint_iterator != tcp::resolver::iterator())
    {
      _socket.close();
      tcp::endpoint endpoint = *endpoint_iterator;
      _socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this,
            boost::asio::placeholders::error, ++endpoint_iterator));
    }
  }

  void Client::handle_read_header(const boost::system::error_code& error){
    if (!error && _read_msg.decode_header()){
      boost::asio::async_read(_socket,
          boost::asio::buffer(_read_msg.body(), _read_msg.body_length()),
          boost::bind(&Client::handle_read_body, this, boost::asio::placeholders::error));
    }
    else
      do_close();
  }

  void Client::handle_read_body(const boost::system::error_code& error){
      if (!error){
      std::string tmp(_read_msg.body(),_read_msg.body_length());
      _incoming.push_back(tmp);
      boost::asio::async_read(_socket, boost::asio::buffer(_read_msg.data(), Message::header_length), boost::bind(&Client::handle_read_header, this,
            boost::asio::placeholders::error));
    }
    else
      do_close();
  }

  void Client::do_write(Message msg)
  {
    bool write_in_progress = !_write_msgs.empty();
    _write_msgs.push_back(msg);
    if (!write_in_progress){
      boost::asio::async_write(_socket,
          boost::asio::buffer(_write_msgs.front().data(),
            _write_msgs.front().length()),
          boost::bind(&Client::handle_write, this,
            boost::asio::placeholders::error));
    }
  }

  void Client::handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      _write_msgs.pop_front();
      if (!_write_msgs.empty())
      {
        boost::asio::async_write(_socket,
            boost::asio::buffer(_write_msgs.front().data(),
              _write_msgs.front().length()),
            boost::bind(&Client::handle_write, this,
              boost::asio::placeholders::error));
      }
    }
    else
    {
      do_close();
    }
  }

  void Client::do_close()
  {
    _socket.close();
  }

  std::string Client::receive(){
     if(!_incoming.empty()){
     std::string tmp(_incoming.front());
     _incoming.pop_front();
     return tmp;
     }
     else return "empty";
  }

