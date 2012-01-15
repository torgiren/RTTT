#include "Room.hpp"
#include <sstream>
 void Room::join(Participant_ptr participant){
   _participants.insert(participant);
   _idents.push_back(std::pair<Participant*, unsigned>(participant.get(), _current_id++));
    std::for_each(_recent_msgs.begin(), _recent_msgs.end(),
        boost::bind(&Participant::deliver, participant, _1));
  }

  void Room::leave(Participant_ptr participant){
        _participants.erase(participant);
  }

  void Room::deliver(const Message& msg){
    std::cout << "od" << msg.source() << std::endl;
    char tmp[512];
    std::memcpy(tmp,msg.body(),msg.body_length());
    tmp[msg.body_length()]='\0';
    std::string body(tmp);
    if(body=="NIEE") return;
   
    _recent_msgs.push_back(msg);
    while (_recent_msgs.size() > max_recent_msgs)
      _recent_msgs.pop_front();
    std::for_each(_participants.begin(), _participants.end(),
        boost::bind(&Participant::deliver, _1, boost::ref(msg)));
  }
