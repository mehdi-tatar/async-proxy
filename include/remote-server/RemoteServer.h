
#ifndef REMOTE_SERVER_H
#define REMOTE_SERVER_H

// #include <cstdlib>
// #include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include "SessionServer.h"

using boost::asio::ip::tcp;

class RemoteServer
{
public:
  RemoteServer(boost::asio::io_context& io_context, short port);

private:
  void start_accept();
  void handle_accept(SessionServer* new_session, const boost::system::error_code& error);

  boost::asio::io_context& io_context_;
  tcp::acceptor acceptor_;
};

#endif /* REMOTE_SERVER_H */
