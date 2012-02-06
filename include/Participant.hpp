#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP
#include "Message.hpp"
#include <boost/shared_ptr.hpp>
#include <deque>
/**
* @details Klasa abstrakcyjna reprezentująca połączenie socketów od klientów
* @author Paweł Ściegienny
* @brief Interfejs pokoju
*/
class Participant
{
public:
  ///@brief wirtualny destruktor
  virtual ~Participant() {}
  ///@brief metoda czysto wirtualna
  virtual void deliver(const Message& msg) = 0;
};

typedef boost::shared_ptr<Participant> Participant_ptr;
typedef std::deque<Message> Message_queue;

#endif //PARTICIPANT_HPP

