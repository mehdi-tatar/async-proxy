/* ConfigReader.cpp */

#include <config.h>

#include <string>
#include <ConfigReader.h>
#include <IpPortConfig.h>
#include <iostream>
#include <fstream>
#include <toml.hpp>

using namespace std;

ConfigReader::ConfigReader(string path_file)
{
	string server_ip;
	string server_port;
	string upstream_ip;
	string upstream_port;

    toml::table tbl;
    try
    {
        size_t pos = 0;
		string delimiter = ":";
        tbl = toml::parse_file(path_file);
  
        /* server */
        string ip_port_server(tbl["server"]["address"].value_or(""sv));

		pos = ip_port_server.find(delimiter);
	    server_ip = ip_port_server.substr(0, pos);
	    ip_port_server.erase(0, pos + delimiter.length());
	    pos = ip_port_server.find(delimiter);
	    server_port = ip_port_server.substr(0, pos);

#if DEBUG_MOD_PRINT==1
	    cout << server_ip << endl;
	    cout << server_port << endl;
#endif

        /* upstream */
        string ip_port_upstream(tbl["upstream"]["address"].value_or(""sv));
		pos = ip_port_upstream.find(delimiter);
	    upstream_ip = ip_port_upstream.substr(0, pos);
	    ip_port_upstream.erase(0, pos + delimiter.length());
	    pos = ip_port_upstream.find(delimiter);
	    upstream_port = ip_port_upstream.substr(0, pos);

#if DEBUG_MOD_PRINT==1
	    cout << upstream_ip << endl;
	    cout << upstream_port << endl;
#endif
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "Parsing failed:\n" << err << "\n";
    }

	m_ip_port_config_server   = new IpPortConfig(server_ip, stoi(server_port));
	m_ip_port_config_upstream = new IpPortConfig(upstream_ip, stoi(upstream_port));
} 

ConfigReader::~ConfigReader()
{
	delete m_ip_port_config_server;
	delete m_ip_port_config_upstream;
}

IpPortConfig ConfigReader::get_config_server()
{
    return (*m_ip_port_config_server);
}

IpPortConfig ConfigReader::get_config_upstream()
{
    return (*m_ip_port_config_upstream);
}

