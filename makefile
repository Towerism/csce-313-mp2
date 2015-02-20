# makefile
all: clean dataserver client

reqchannel.o: reqchannel.H reqchannel.C
	g++ -c -g reqchannel.c

dataserver: dataserver.c reqchannel.o 
	g++ -o dataserver dataserver.c reqchannel.o -lpthread

client: client.c
	g++ -o client client.c reqchannel.o

clean: 
	rm -f *.o *.gch Main

