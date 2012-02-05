#ifndef SESSION_HPP
#define SESSION_HPP
#include "Participant.hpp"
#include "Room.hpp"
#include "Message.hpp"
#include <string>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;
/**
* @details klasa utrzymująca szerokorozumianą sesję
* @author Paweł Ściegienny
* @brief reprezentacja sesji
*/
class Session
  : public Participant,
    public boost::enable_shared_from_this<Session>
{
public:
  ///@brief konstruktor tworzący z listą inicjalizacyjną
  Session(boost::asio::io_service& io_service, Room& room) : _socket(io_service), _room(room){
  }
  ///@brief jaki to socket
  tcp::socket& socket(){
    return _socket;
  }
  ///@brief starter
  void start();
  ///@brief dostarczacz wiadomosci
  void deliver(const Message& msg);
  ///@brief odczyt nagłówka
  void handle_read_header(const boost::system::error_code& error);
  ///@brief odczyt ciała wiadomości
  void handle_read_body(const boost::system::error_code& error);
  ///@brief handler wysyłający
  void handle_write(const boost::system::error_code& error);

private:
  tcp::socket _socket;
  Room& _room;
  Message _read_msg;
  Message_queue _write_msgs;
};

typedef boost::shared_ptr<Session> Session_ptr;

#endif //SESSION_HPP
