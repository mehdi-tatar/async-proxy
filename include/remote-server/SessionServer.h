
#ifndef SESSION_SERVER_H
#define SESSION_SERVER_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class SessionServer
{
public:
  SessionServer(boost::asio::io_context& io_context);
  tcp::socket& socket();

  void start();

private:
  void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
  void handle_write(const boost::system::error_code& error);

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
};

#endif /* SESSION_SERVER_H */
