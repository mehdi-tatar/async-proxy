#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include "SessionServer.h"

using boost::asio::ip::tcp;

SessionServer::SessionServer(boost::asio::io_context& io_context) : socket_(io_context)
{
}

tcp::socket& SessionServer::socket()
{
  return socket_;
}

void SessionServer::start()
{
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
      boost::bind(&SessionServer::handle_read, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void SessionServer::handle_read(const boost::system::error_code& error,
    size_t bytes_transferred)
{
  if (!error)
  {
    boost::asio::async_write(socket_,
        boost::asio::buffer(data_, bytes_transferred),
        boost::bind(&SessionServer::handle_write, this,
          boost::asio::placeholders::error));
  }
  else
  {
    delete this;
  }
}

void SessionServer::handle_write(const boost::system::error_code& error)
{
  if (!error)
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&SessionServer::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }
  else
  {
    delete this;
  }
}
