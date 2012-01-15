#ifndef ROOM_HPP
#define ROOM_HPP
#include "Participant.hpp"
#include <algorithm>
#include <set>
#include <string>
#include <iostream>
#include <boost/bind.hpp>

class Room
{
public:
  void join(Participant_ptr participant);
  void leave(Participant_ptr participant);
  void deliver(const Message& msg);
  unsigned search(Participant* participant){
      for(int i=0; i< _idents.size(); ++i)
           if(_idents[i].first==participant)
                return _idents[i].second;
  }
private:
  std::set<Participant_ptr> _participants;
  std::vector<std::pair<Participant*, unsigned> > _idents;
  unsigned _current_id;
  enum { max_recent_msgs = 100 };
  Message_queue _recent_msgs;
};

#endif //ROOM_HPP
