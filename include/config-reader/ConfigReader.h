#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <string>
#include <IpPortConfig.h>

using namespace std;

class ConfigReader
{
  public:
	ConfigReader(string path_file);
	ConfigReader(const ConfigReader &config_reader);
	ConfigReader & operator = (const ConfigReader &config_reader);
	~ConfigReader();

    IpPortConfig get_config_server() const;
    IpPortConfig get_config_upstream() const;

  private:
    ConfigReader();
    IpPortConfig *m_ip_port_config_server;
    IpPortConfig *m_ip_port_config_upstream;
};

#endif   /* CONFIG_READER_H */
