#Makefile
all: send_arp

send_arp: main.o info_network.o
	g++ -o send_arp main.o info_network.o -Wall
	rm -f *.o

main.o: info_network.hpp main.cpp 

info_network.o: info_network.hpp info_network.cpp

clean:
	rm -f *.o
	rm -f send_arp