#Makefile
all: send_arp

send_arp: main.o info_network.o verification.o
	g++ -o send_arp main.o info_network.o verification.o -Wall -lpcap
	rm -f *.o

main.o: info_network.hpp main.cpp 

info_network.o: info_network.hpp info_network.cpp

verification.o: verification.hpp verification.cpp

clean:
	rm -f *.o
	rm -f send_arp