/* client.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <TCPConnector.h>
#include <unistd.h>


using namespace std;

int main(int argc, char** argv)
{
    if (argc != 4) {
        printf("usage: %s <port> <ip> <request time>\n", argv[0]);
        exit(1);
    }

    int len;
    int counter = 0;
    string message;
    char line[256];
    TCPConnector* connector = new TCPConnector();
    
    TCPStream* stream;
    
    while (1) {
      stream = connector->connect(argv[2], atoi(argv[1]));
      if (stream) {
        message = "request site ";
        message += to_string(counter);
        counter++;
        message += argv[0];
        stream->send(message.c_str(), message.size());
        printf("sent - %s\n", message.c_str());
        len = stream->receive(line, sizeof(line));
        line[len] = 0;
        printf("received - %s\n", line);
        delete stream;
      }
      unsigned int microseconds = 1000 * atoi(argv[3]);
      usleep(microseconds);
    }

    exit(0);
}
