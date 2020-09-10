/* IpPortConfig.cpp */

#include <string>
#include <IpPortConfig.h>

using namespace std;

IpPortConfig::IpPortConfig(string ip)
    : m_ip(ip), m_port(8080)
{
} 

IpPortConfig::IpPortConfig(string ip, int port)
    : m_ip(ip), m_port(port)
{
} 

IpPortConfig::IpPortConfig(const IpPortConfig &ip_port_config)
    : m_ip(ip_port_config.m_ip), m_port(ip_port_config.m_port)
{
}

IpPortConfig::~IpPortConfig()
{
}

string IpPortConfig::get_ip() const
{
    return m_ip;
}

int IpPortConfig::get_port() const
{
    return m_port;
}
