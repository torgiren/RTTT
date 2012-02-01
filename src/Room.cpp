#include "../include/Room.hpp"

 void Room::join(Participant_ptr participant){
   _participants.insert(participant);
   _idents.push_back(std::pair<Participant*, unsigned>(participant.get(), _current_id++));
//    std::for_each(_recent_msgs.begin(), _recent_msgs.end(),
//        boost::bind(&Participant::deliver, participant, _1));
  }

  void Room::leave(Participant_ptr participant){
        _participants.erase(participant);
  }
  
  void Room::todo(const Message msg){
      _todo.push_back(msg);
  }
  
  Message Room::todo(){
     while(true){
     if(!_todo.empty()){
       Message msg = _todo.front();
        _todo.pop_front();
        return msg;
        }
     boost::this_thread::sleep(boost::posix_time::milliseconds(500));
     }
  }
  
  void Room::deliver(const Message& msg){
/*    _recent_msgs.push_back(msg);
    while (_recent_msgs.size() > max_recent_msgs)
      _recent_msgs.pop_front();
*/
    std::for_each(_participants.begin(), _participants.end(),
        boost::bind(&Participant::deliver, _1, boost::ref(msg)));
  }
  
  void Room::deliver(unsigned who, const Message& msg){
      search(who)->deliver(msg);
  }
  
  Participant* Room::search (unsigned ident){
      for(int i=0; i< _idents.size(); ++i){
          if(_idents[i].second==ident)
              return _idents[i].first;
         }
         ///jak juz cos to zwrocmy pierwszego
          return _idents[0].first;
  }
  
  unsigned Room::search(Participant* participant){
      for(int i=0; i< _idents.size(); ++i)
           if(_idents[i].first==participant)
                return _idents[i].second;
      return 0;
  }

