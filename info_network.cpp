#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <pcap.h>
#include "info_network.hpp"
#define HWADDR_len 6
using namespace std;

// info_network
info_network::info_network(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16]){
    strncpy(this->interface, INTERFACE, 9);
    strncpy(this->sender_IP, SENDER_IP, 16);
    strncpy(this->target_IP, TARGET_IP, 16);
    find_mac_addr(this->my_MACaddr, interface);
}

info_network::~info_network(){
}

void info_network::find_mac_addr(char MAC_str[13], char user_interface[10])
{
    int s,i;
    struct ifreq ifr;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, user_interface);
    ioctl(s, SIOCGIFHWADDR, &ifr);
    for (i=0; i<HWADDR_len; i++)
        sprintf(&MAC_str[i*2],"%02X",((unsigned char*)ifr.ifr_hwaddr.sa_data)[i]);
    MAC_str[12]='\0';
}

void info_network::print_status()
{
    cout << "\033[1;32m================== Status =================\033[0m" << endl;
    cout << "Interface  : " << interface << endl;
    cout << "MAC Address     : " << my_MACaddr << endl;
    cout << "sender_ip       : " << sender_IP << endl;
    cout << "sender_mac      : " << sender_MACaddr << endl;
    cout << "target_ip       : " << target_IP << endl;
    cout << "target_mac      : " << target_MACaddr << endl; 
    cout << "\033[1;32m===========================================\033[0m\n";
}

// arp_packet
arp_packet::arp_packet(){}
arp_packet::~arp_packet(){}

