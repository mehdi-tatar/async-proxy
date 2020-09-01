#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

#include "RemoteServer.h"

//using namespace std;

int main(int argc, char* argv[])
{
  try
  {
#ifdef READ_FROM_TERMINAL
    if (argc != 2)
  {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }
    if (argc < 2 || argc > 4) {
        printf("usage: remote-server <port>\n");
        exit(1);
    }

  int port_number = std::atoi(argv[1]);
#else
  int port_number = 3001;
#endif

    boost::asio::io_context io_context;

    RemoteServer remote_server(io_context, port_number);
    
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
