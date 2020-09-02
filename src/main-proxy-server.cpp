#include <config.h>

#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include <ProxyAcceptor.h>
#include <IpPortConfig.h>
#include <ConfigReader.h>


int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: %s <path-to-config>\n", argv[0]);
        exit(1);
    }

    ConfigReader config_reader("config.toml");
    IpPortConfig ip_port_config_server   = config_reader.get_config_server();
    IpPortConfig ip_port_config_upstream = config_reader.get_config_upstream();

    const std::string local_host      = ip_port_config_server.get_ip();
    const unsigned short local_port   = static_cast<unsigned short>(ip_port_config_server.get_port());

    const std::string forward_host    = ip_port_config_upstream.get_ip();
    const unsigned short forward_port = static_cast<unsigned short>(ip_port_config_upstream.get_port());

#if DEBUG_MOD_PRINT==1
    cout << "DEBUG:" << endl;
    cout << local_host << endl;
    cout << local_port << endl;
    cout << forward_host << endl;
    cout << forward_port << endl;
#endif

    boost::asio::io_service ios;

    try
    {
        ProxyAcceptor acceptor(ios,
                               local_host, local_port,
                               forward_host, forward_port);

        acceptor.accept_connections();

        ios.run();
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
