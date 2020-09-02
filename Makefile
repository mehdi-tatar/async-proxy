# Makes the tcpsocket lib

all: client proxy-server remote-server

clean:
	make -f Makefile.client        clean
	make -f Makefile.proxy-server  clean	
	make -f Makefile.remote-server clean	

client:
	make -f Makefile.client

proxy-server:
	make -f Makefile.proxy-server

remote-server:
	make -f Makefile.remote-server
