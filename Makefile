#Makefile
all: arp_spoofing

arp_spoofing: main.o info_network.o verification.o
	g++ -o arp_spoofing main.o info_network.o verification.o -Wall -lpcap
	rm -f *.o
	rm -f *.gch

main.o: info_network.hpp main.cpp
	g++ -c info_network.hpp main.cpp -std=c++11

info_network.o: info_network.hpp info_network.cpp net_header.hpp
	g++ -c info_network.hpp info_network.cpp net_header.hpp -std=c++11

verification.o: info_network.hpp verification.cpp 
	g++ -c info_network.hpp verification.cpp -std=c++11

clean:
	rm -f *.o
	rm -f arp_spoofing
