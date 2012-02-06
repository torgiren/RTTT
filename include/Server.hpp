#ifndef SERVER_HPP
#define SERVER_HPP
#include "Room.hpp"
#include "Session.hpp"
#include "Message.hpp"
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
class Server
{
public:
  ///@brief Nazwany konstruktor
  static Server* create(std::string port){
     tcp::endpoint endpoint(tcp::v4(), std::atoi(port.c_str()));
     _io = new boost::asio::io_service();
     Server* instance = new Server(*_io, endpoint);
     _t = new boost::thread(boost::bind(&boost::asio::io_service::run, _io));
     return instance;
  }
 ///@brief Destruktor
 ///@details Zamyka połączenie, sprząta
~Server(){
      _t->join();
      delete _t;
      delete _io;
      
  }
  ///@brief Metoda wysyłająca wiadomość do wszystkich
  ///@details metoda pozwalająca rozesłać do wszystkich użytkowników wiadomość
  ///@param[in] m string z treścią wiadomości
  void send(const std::string& m){
      Message msg;
      msg.body_length(strlen(m.c_str()));
      memcpy(msg.body(), m.c_str(), msg.body_length());
      msg.encode_header();
      _room.deliver(msg);      
  }
  ///@brief Metoda wysyłająca wiadomość do konkretnego użytkownika
  ///@details metoda pozwalająca na wysłanie wiadomości do konkretnego użytkownika
  ///@param[in] who id użytkownika
  ///@param[in] m string z treścią wiadomości
  void send(unsigned who, std::string m){
      Message msg;
      msg.body_length(strlen(m.c_str()));
      memcpy(msg.body(), m.c_str(), msg.body_length());
      msg.encode_header();
      _room.deliver(who,msg);

  }
  ///@brief Metoda odbierająca
  ///@details Metoda pozwalająca sprawdzić co serwer ma do roboty
  ///@returns Message wiadomość zawierającą id i treść
  Message receive(){
         return _room.todo();
     }
private:
  ///@brief prywatny konstruktor
  ///@details za dużo boosta do używania explicit
  Server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint): _io_service(io_service), _acceptor(io_service, endpoint){
    Session_ptr new_session(new Session(_io_service, _room));
    _acceptor.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
  }
  ///@brief handler rozpoczynający akceptację żądań
  void handle_accept(Session_ptr session, const boost::system::error_code& error);
  ///@brief miejsce na socket
  boost::asio::io_service& _io_service;
  ///@brief miejsce na socket (dość głupie)
  static boost::asio::io_service* _io;
  ///@brief miejsce na wątek (dość głupie)
  static boost::thread* _t;
  ///@brief nazwa mówi sowje
  tcp::acceptor _acceptor;
  ///@brief to tam są te wszystkie sesje
  Room _room;
};

typedef boost::shared_ptr<Server> Server_ptr;
typedef std::list<Server_ptr> Server_list;



#endif //SERVER_HPP
