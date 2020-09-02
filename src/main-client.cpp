#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <TCPConnector.h>
#include <unistd.h>
#include <IpPortConfig.h>
#include <ConfigReader.h>


using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("usage: %s <path-to-config>\n", argv[0]);
        exit(1);
    }

    ConfigReader config_reader(argv[1]);
    IpPortConfig ip_port_config_server = config_reader.get_config_server();

    int len;
    int counter = 0;
    string message;
    char line[256];
    TCPConnector* connector = new TCPConnector();
    
    TCPStream* stream;
    
    while (1) {
      stream = connector->connect(ip_port_config_server.get_ip().c_str(), ip_port_config_server.get_port());
      if (stream) {
        message = "request ";
        message += to_string(counter);
        message += " ";
        counter++;
        message += argv[0];
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        len = stream->receive(line, sizeof(line));
        line[len] = 0;
        printf("received - %s\n", line);
        delete stream;
      }
      else {
        break;
      }
      unsigned int microseconds = 1000 * atoi(argv[1]);
      usleep(microseconds);
    }

    exit(0);
}
