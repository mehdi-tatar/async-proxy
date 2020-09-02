/* IpPortConfig.cpp */

#include <string>
#include <IpPortConfig.h>

using namespace std;

IpPortConfig::IpPortConfig(string ip)
    : m_ip(ip), m_port(8080) {} 

IpPortConfig::IpPortConfig(string ip, int port)
    : m_ip(ip), m_port(port) {} 

IpPortConfig::~IpPortConfig()
{
}

string IpPortConfig::get_ip()
{
    return m_ip;
}

int IpPortConfig::get_port()
{
    return m_port;
}

