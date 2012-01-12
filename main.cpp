#include "Participant.hpp"
#include "Room.hpp"
#include "Message.hpp"
#include "Session.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv){

int choose;

std::cout << "0 - client \n 1 - server \n wybor: \n";
std::cin >> choose;

if (choose){
try
  {
    if (argc < 2)
    {
      std::cerr << "Usage: Server <port> [<port> ...]\n";
      return 1;
    }
    boost::asio::io_service io_service;
    Server_list servers;
    for (int i = 1; i < argc; ++i)
    {
      using namespace std; // For atoi.
      tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
      Server_ptr server(new Server(io_service, endpoint));
      servers.push_back(server);
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}
else{
     try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: Client <host> <port>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    Client c(io_service, iterator);

    boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

    char line[Message::max_body_length + 1];
    while (std::cin.getline(line, Message::max_body_length + 1))
    {
      using namespace std; // For strlen and memcpy.
      Message msg;
      msg.body_length(strlen(line));
      memcpy(msg.body(), line, msg.body_length());
      msg.encode_header();
      c.write(msg);
    }

    c.close();
    t.join();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

}

return 0;
}
