#ifndef ROOM_HPP
#define ROOM_HPP
#include "Participant.hpp"
#include <algorithm>
#include <set>
#include <boost/bind.hpp>

class Room
{
public:
  void join(Participant_ptr participant);
  void leave(Participant_ptr participant);
  void deliver(const Message& msg);

private:
  std::set<Participant_ptr> _participants;
  enum { max_recent_msgs = 100 };
  Message_queue _recent_msgs;
};

#endif //ROOM_HPP
