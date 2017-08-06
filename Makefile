#Makefile
all: send_arp

send_arp: main.o find_macaddr.o
	g++ -o send_arp main.o find_macaddr.o 

main.o: find_macaddr.hpp main.cpp 

find_macaddr.o: find_macaddr.hpp find_macaddr.cpp

clean:
	rm -f *.o
