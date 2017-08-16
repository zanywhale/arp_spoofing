#include <pcap.h>
#include <iostream>
#include "info_network.hpp"
#include <regex>
#include <stdlib.h>
#include <string.h>
using namespace std;

void info_network::check_interface(char *interface) 
{
    pcap_if_t *devs;
    char errbuf[PCAP_ERRBUF_SIZE];
    int check = 0;
    if (-1 == pcap_findalldevs(&devs, errbuf))
    {
        cout << "Couldn't open device list: " << errbuf << endl;
        exit(1);
    }
    if (!devs) {
        cout << "No devices found." << endl;
        exit(1);
    }
    for (pcap_if_t *d = devs; d; d = d->next) {
        if(!strcmp(d->name, interface))
            check++;
    }
    pcap_freealldevs(devs);

    if(!check){
        cout << "\033[1;34mError : interface is not exist... Check it plz.\033[0m" << endl;
        cout << "\033[1;32mUsage: send_arp <interface> <sender(victim) ip> <target ip> \033[0m" << endl <<\
                "\033[1;31mEx)send_arp wlan0 192.168.10.2 192.168.10.1\033[0m\n";
        exit(1);
    }
}

void info_network::check_ipaddr(char ip1[16], char ip2[16])
{
    regex reg("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    smatch m1;
    smatch m2;
    std::string str1(ip1);
    std::string str2(ip2);
    if( !regex_match(str1, m1, reg)){
        cout << "\033[1;34mError : ip address is strange... Check it plz.\033[0m" << endl;
        cout << "\033[1;32mUsage: send_arp <interface> <sender(victim) ip> <target ip> \033[0m" << endl <<\
                "\033[1;31mEx)send_arp wlan0 192.168.10.2 192.168.10.1\033[0m\n";
        exit(1);
    }
    if( !regex_match(str2, m2, reg)){
        cout << "\033[1;34mError : ip address is strange... Check it plz.\033[0m" << endl;
        cout << "\033[1;32mUsage: send_arp <interface> <sender(victim) ip> <target ip> \033[0m" << endl <<\
                "\033[1;31mEx)send_arp wlan0 192.168.10.2 192.168.10.1\033[0m\n";
        exit(1);
    }
}
