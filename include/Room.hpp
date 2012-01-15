#ifndef ROOM_HPP
#define ROOM_HPP
#include "Participant.hpp"
#include <algorithm>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <boost/bind.hpp>

class Room
{
public:
  void join(Participant_ptr participant);
  void leave(Participant_ptr participant);
  void deliver(const Message& msg);

private:
  std::set<Participant_ptr> _participants;
  unsigned _current_id;
  enum { max_recent_msgs = 100 };
  Message_queue _recent_msgs;
};

#endif //ROOM_HPP
