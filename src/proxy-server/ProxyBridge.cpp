#include <iostream>
#include <cstdlib>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>

#include "ProxyBridge.h"


typedef boost::asio::ip::tcp::socket socket_type;

ProxyBridge::ProxyBridge(boost::asio::io_service& ios)
: downstream_socket_(ios),
  upstream_socket_(ios)
{}

socket_type& ProxyBridge::downstream_socket()
{
   return downstream_socket_;
}

socket_type& ProxyBridge::upstream_socket()
{
   return upstream_socket_;
}

void ProxyBridge::start(const std::string& upstream_host, unsigned short upstream_port)
{
   upstream_socket_.async_connect(
        boost::asio::ip::tcp::endpoint(
             boost::asio::ip::address::from_string(upstream_host),
             upstream_port),
         boost::bind(&ProxyBridge::handle_upstream_connect,
              shared_from_this(),
              boost::asio::placeholders::error));
}

void ProxyBridge::handle_upstream_connect(const boost::system::error_code& error)
{
   if (!error)
   {
      upstream_socket_.async_read_some(
           boost::asio::buffer(upstream_data_,max_data_length),
           boost::bind(&ProxyBridge::handle_upstream_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

      downstream_socket_.async_read_some(
           boost::asio::buffer(downstream_data_,max_data_length),
           boost::bind(&ProxyBridge::handle_downstream_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
   }
   else
      close();
}

void ProxyBridge::handle_downstream_write(const boost::system::error_code& error)
{
   if (!error)
   {
      upstream_socket_.async_read_some(
           boost::asio::buffer(upstream_data_,max_data_length),
           boost::bind(&ProxyBridge::handle_upstream_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
   }
   else
      close();
}

void ProxyBridge::handle_downstream_read(const boost::system::error_code& error,
                                         const size_t& bytes_transferred)
{
   if (!error)
   {
      async_write(upstream_socket_,
            boost::asio::buffer(downstream_data_,bytes_transferred),
            boost::bind(&ProxyBridge::handle_upstream_write,
                  shared_from_this(),
                  boost::asio::placeholders::error));
   }
   else
      close();
}

void ProxyBridge::handle_upstream_write(const boost::system::error_code& error)
{
   if (!error)
   {
      downstream_socket_.async_read_some(
           boost::asio::buffer(downstream_data_,max_data_length),
           boost::bind(&ProxyBridge::handle_downstream_read,
                shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
   }
   else
      close();
}

void ProxyBridge::handle_upstream_read(const boost::system::error_code& error,
                                       const size_t& bytes_transferred)
{
   if (!error)
   {
      async_write(downstream_socket_,
           boost::asio::buffer(upstream_data_,bytes_transferred),
           boost::bind(&ProxyBridge::handle_downstream_write,
                shared_from_this(),
                boost::asio::placeholders::error));
   }
   else
      close();
}

void ProxyBridge::close()
{
   boost::mutex::scoped_lock lock(mutex_);

   if (downstream_socket_.is_open())
   {
      downstream_socket_.close();
   }

   if (upstream_socket_.is_open())
   {
      upstream_socket_.close();
   }
}
