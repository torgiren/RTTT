#ifndef ROOM_HPP
#define ROOM_HPP

#include "Participant.hpp"
#include <typeinfo>
#include <algorithm>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
/**
* @details implementacja interfejsu Participant. Konkretne rozwiązania
* @author Paweł Ściegienny
* @brief miejsce gdzie zbiegają się sockety.
*/
class Room {
	
	public:
                ///@brief metoda dodająca uczestnika
		void join(Participant_ptr participant);
                ///@brief metoda usuwająca uczestnika
		void leave(Participant_ptr participant);
                ///@brief dostarczenie wiadomości do wszystkich klientów
		void deliver(const Message& msg);
                ///@brief metoda dostarczająca wiadomość do konkretnego klienta
		void deliver(unsigned who, const Message& msg);
                ///@brief metoda pozwalająca zidentyfikować uczesnika na podstawie socketu
		unsigned search(Participant* participant);
                ///@brief metoda pozwalająca znaleźć socket na podstawie ID klienta
		Participant* search (unsigned ident);
                ///@brief odczyt wiadomości
		Message todo();
                ///@brief dodanie wiadomości do bufora
		void todo(const Message msg);

	private:
		std::set<Participant_ptr> _participants;
		std::vector<std::pair<Participant*, unsigned> > _idents;
		unsigned _current_id;
		Message_queue _todo;
		
};

#endif //ROOM_HPP
