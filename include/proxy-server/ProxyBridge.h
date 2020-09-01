
#ifndef PROXY_BRIDGE_H
#define PROXY_BRIDGE_H

#include <iostream>
#include <cstdlib>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/asio.hpp>


typedef boost::asio::ip::tcp::socket socket_type;

class ProxyBridge : public boost::enable_shared_from_this<ProxyBridge>
{
public:
  ProxyBridge(boost::asio::io_service& ios);
  socket_type& downstream_socket();
  socket_type& upstream_socket();
  void start(const std::string& upstream_host, unsigned short upstream_port);
  void handle_upstream_connect(const boost::system::error_code& error);

private:
  void handle_downstream_write(const boost::system::error_code& error);
  void handle_downstream_read(const boost::system::error_code& error,
                              const size_t& bytes_transferred);
  void handle_upstream_write(const boost::system::error_code& error);
  void handle_upstream_read(const boost::system::error_code& error,
                            const size_t& bytes_transferred);
  void close();

  socket_type downstream_socket_;
  socket_type upstream_socket_;

  enum { max_data_length = 8192 }; //8KB
  unsigned char downstream_data_[max_data_length];
  unsigned char upstream_data_[max_data_length];

  boost::mutex mutex_;
};

#endif /* PROXY_BRIDGE_H */
