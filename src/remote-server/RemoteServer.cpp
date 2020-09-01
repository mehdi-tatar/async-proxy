#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include "RemoteServer.h"

using boost::asio::ip::tcp;

RemoteServer::RemoteServer(boost::asio::io_context& io_context, short port)
  : io_context_(io_context),
    acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
  start_accept();
}

void RemoteServer::start_accept()
{
  SessionServer* new_SessionServer = new SessionServer(io_context_);
  acceptor_.async_accept(new_SessionServer->socket(),
                         boost::bind(&RemoteServer::handle_accept, this, new_SessionServer,
                         boost::asio::placeholders::error));
}

void RemoteServer::handle_accept(SessionServer* new_SessionServer,
    const boost::system::error_code& error)
{
  if (!error)
  {
    new_SessionServer->start();
  }
  else
  {
    delete new_SessionServer;
  }

  start_accept();
}
