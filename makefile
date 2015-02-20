# makefile
all: dataserver simpleclient client

client: client.c
	g++ -o client client.c

reqchannel.o: reqchannel.H reqchannel.C
	g++ -c -g reqchannel.C

dataserver: dataserver.C reqchannel.o 
	g++ -o dataserver dataserver.C reqchannel.o -lpthread

simpleclient: simpleclient.C reqchannel.o
	g++ -o simpleclient simpleclient.C reqchannel.o
