/* IpPortConfig.h */

#ifndef IP_PORT_CONFIG_H
#define IP_PORT_CONFIG_H

#include <string>

using namespace std;

class IpPortConfig
{
  public:
    IpPortConfig(string ip);
    IpPortConfig(string ip, int port);
    IpPortConfig(const IpPortConfig &ip_port_config);
    ~IpPortConfig();

    string get_ip() const;
    int    get_port() const;


  private:
    IpPortConfig();

    string  m_ip;
    int     m_port;
};

#endif   /* IP_PORT_CONFIG_H */
