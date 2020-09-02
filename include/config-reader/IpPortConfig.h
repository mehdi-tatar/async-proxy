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
    ~IpPortConfig();

    string get_ip();
    int    get_port();


  private:
    IpPortConfig();

    string  m_ip;
    int     m_port;
};

#endif   /* IP_PORT_CONFIG_H */
