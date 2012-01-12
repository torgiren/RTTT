#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "Message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<Message> Message_queue;

class Client{
public:
  Client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator)
    : _io_service(io_service), _socket(io_service){
    tcp::endpoint endpoint = *endpoint_iterator;
    _socket.async_connect(endpoint, boost::bind(&Client::handle_connect, this, boost::asio::placeholders::error, ++endpoint_iterator));
  }

  void write(const Message& msg){
    _io_service.post(boost::bind(&Client::do_write, this, msg));
  }

  void close(){
    _io_service.post(boost::bind(&Client::do_close, this));
  }

private:
  void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator){
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

  void handle_read_header(const boost::system::error_code& error){
    if (!error && _read_msg.decode_header()){
      boost::asio::async_read(_socket,
          boost::asio::buffer(_read_msg.body(), _read_msg.body_length()),
          boost::bind(&Client::handle_read_body, this, boost::asio::placeholders::error));
    }
    else
      do_close();
  }

  void handle_read_body(const boost::system::error_code& error){
    if (!error){
      std::cout.write(_read_msg.body(), _read_msg.body_length());
      std::cout << "\n";
      boost::asio::async_read(_socket, boost::asio::buffer(_read_msg.data(), Message::header_length), boost::bind(&Client::handle_read_header, this,
            boost::asio::placeholders::error));
    }
    else
      do_close();
  }

  void do_write(Message msg)
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

  void handle_write(const boost::system::error_code& error)
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

  void do_close()
  {
    _socket.close();
  }

private:
  boost::asio::io_service& _io_service;
  tcp::socket _socket;
  Message _read_msg;
  Message_queue _write_msgs;
};



#endif //CLIENT_HPP
