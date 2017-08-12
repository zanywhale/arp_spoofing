#include "verification.hpp"
#include <pcap.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

verification::verification(char argv1[10], char argv2[16], char argv3[16]){}
verification::~verification(){}

void verification::check_interface(char *interface) 
{
    pcap_if_t *devs;
    char errbuf[40];
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
        check_argc();
        exit(1);
    }
}

void verification::check_argc()
{
    cout << "\033[1;32mUsage: send_arp <interface> <sender(victim) ip> <target ip> \033[0m" << endl <<\
            "\033[1;31mEx)send_arp wlan0 192.168.10.2 192.168.10.1\033[0m\n";
    exit(0);
}

