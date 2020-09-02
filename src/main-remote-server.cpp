#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>

#include <RemoteServer.h>
#include <IpPortConfig.h>
#include <ConfigReader.h>


//using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("usage: %s <path-to-config>\n", argv[0]);
        exit(1);
    }

    try
    {
        ConfigReader config_reader(argv[1]);
        IpPortConfig ip_port_config_upstream = config_reader.get_config_upstream();

        boost::asio::io_context io_context;

        // ???
        ip_port_config_upstream.get_ip().c_str();
        
        RemoteServer remote_server(io_context, ip_port_config_upstream.get_port());
        
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
