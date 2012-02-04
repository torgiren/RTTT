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

/**
* @details Klasa odpowiedzialna za obsługę połączenia z serwerem
* @author Paweł Ściegienny
* @brief Połączenie z serwerem.
*/

//class MainWindow;
class Client{
public:
  ///@brief metoda zamykająca połączenie
  ///@detail metoda binduje handler do_close z metodą post socketu
  void close();
  ///@brief metoda wysyłająca wiadomość do serwera
  ///@detail metoda konwertuje stringa do Message, a następnie wysyła do serwera
  ///@param[in] m referencja do strina który ma zostać wysłany
  void send(const std::string& m);

public:
  ///@brief Nazwany konstruktor
  ///@detail Jedyny legalny sposób tworzenia instancji klienckich 
  ///@param[in] host hostname
  ///@param[in] ip adres ip
  static Client* create(const std::string host, const std::string port);
  ///@brief destruktor
 ~Client();
  ///@brief metoda zwracająca wiadomosc od serwera
  std::string receive();
  ///@brief metoda wysyłająca wiadomość
  ///@details metoda bindująca handler do_writer z metodą post socketu
  void write(const Message& msg);
private:
  ///@brief Konstruktor połączenia
  ///@defails Konstruktor. Ustawia handler połączenia.
  ///@param[in] host hostname
  ///@param[in] ip adres ip
  Client(boost::asio::io_service& io_service, const char* host, const char* port);

  ///@brief handler łączący
  void handle_connect(const boost::system::error_code& error, tcp::resolver::iterator endpoint_iterator);
  ///@brief handler sczytujący header
  void handle_read_header(const boost::system::error_code& error);
  ///@brief handler sczytujący treść
  void handle_read_body(const boost::system::error_code& error);
  ///@brief handler wysyłający wiadomość
  void do_write(Message msg);
  ///@brief handler wysyłający wiadomość
  void handle_write(const boost::system::error_code& error);
  ///@brief handler zamykający połączenie
  void do_close();

  ///@brief przechowuje socket
  boost::asio::io_service& _io_service;
  ///@brief przechowuje socket
  tcp::socket _socket;
  ///@brief miejsce na odczytaną wiadomość
  Message _read_msg;
  ///@brief historia wysłanych wiadomości
  Message_queue _write_msgs;
  ///@brief miejsce gdzie trzymamy nasz wątek socketu
  boost::thread* _t;
  ///@brief bardzo nierozsądne miejsce na instancje
  static Client* _instance;
  ///@brief kolejka otrzymanych wiadomości
  std::deque<std::string> _incoming;
};

#endif //CLIENT_HPP
