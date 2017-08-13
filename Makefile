#Makefile
all: send_arp

send_arp: main.o info_network.o verification.o
	g++ -o send_arp main.o info_network.o verification.o -Wall -lpcap
	rm -f *.o
	rm -f *.gch

main.o: info_network.hpp verification.hpp main.cpp
	g++ -c info_network.hpp verification.hpp main.cpp

info_network.o: info_network.hpp info_network.cpp net_header.hpp
	g++ -c info_network.hpp info_network.cpp net_header.hpp

verification.o: verification.hpp verification.cpp 
	g++ -c verification.hpp verification.cpp -std=c++11

clean:
	rm -f *.o
	rm -f send_arp