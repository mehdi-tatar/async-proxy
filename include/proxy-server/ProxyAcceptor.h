
#ifndef PROXY_ACCEPTOR_H
#define PROXY_ACCEPTOR_H

#include <cstdlib>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>

#include "ProxyBridge.h"
#include <boost/asio.hpp>


typedef boost::shared_ptr<ProxyBridge> ptr_type;


class ProxyAcceptor
{
public:
   ProxyAcceptor(boost::asio::io_service& io_service,
            const std::string& local_host, unsigned short local_port,
            const std::string& upstream_host, unsigned short upstream_port);
   bool accept_connections();

private:
   void handle_accept(const boost::system::error_code& error);

   boost::asio::io_service& io_service_;
   boost::asio::ip::address_v4 localhost_address;
   boost::asio::ip::tcp::acceptor acceptor_;
   ptr_type session_;
   unsigned short upstream_port_;
   std::string upstream_host_;
};

#endif /* PROXY_ACCEPTOR_H */

