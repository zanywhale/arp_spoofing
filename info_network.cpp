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
    cout << "sender_mac      : ";
    for(int i = 0; i < 6 ; i++)
        printf("%02X",(sender_MACaddr[i]));
    cout << endl;
    cout << "target_ip       : " << target_IP << endl;
    cout << "\033[1;32m===========================================\033[0m\n";
}

// arp_packet
arp_packet::arp_packet(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16]):info_network(INTERFACE, SENDER_IP, TARGET_IP){};
arp_packet::~arp_packet(){};

void arp_packet::arp_request()
{
    // Ethernet_H *eth_h = (Ethernet_H *)malloc(sizeof(Ethernet_H));
    // Arp_H *arp_h = (Arp_H *)malloc(sizeof(Arp_H));
    unsigned char packet[1514];
    pcap_t *handle;

    handle = pcap_open_live(this->interface, BUFSIZ, 1, 1000, this->errbuf);
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
    memcpy(arp_h->target_MAC, "\x00\x00\x00\x00\x00\x00", 6) ;
    *(uint16_t *)arp_h->sender_IP = my_IPaddr;
    *(uint16_t *)arp_h->target_IP = inet_addr(sender_IP);

    cout << "[+] ARP_Request(BroadCast)... then get victim's MAC address!" << endl;
    pcap_sendpacket(handle, packet, sizeof(Ethernet_H)+sizeof(Arp_H));
    cout << "[+] ARP_Request is done." << endl;
}

void arp_packet::arp_capture()
{
    pcap_t *handle;         /* Session handle */
    struct bpf_program fp;      /* The compiled filter */
    char filter_exp[] = "port 80";  /* The filter expression */
    bpf_u_int32 mask;       /* Our netmask */
    bpf_u_int32 net;        /* Our IP */
    struct pcap_pkthdr *header; /* The header that pcap gives us */
    const u_char *packet;       /* The actual packet */
    int res;

    /* Open the session in promiscuous mode */
    handle = pcap_open_live(this->interface, BUFSIZ, 1, 1000, this->errbuf);
    cout << "[+] Capture ARP_REPLY..." << endl;
    /* Grab a packet */
    while(1){
        res = pcap_next_ex(handle, &header, &packet);
        if(res == 1){
            Ethernet_H* eth_h = (Ethernet_H *)packet;
            if(ntohs(eth_h->type) == ETHERTYPE_ARP){
                Arp_H* arp_h = (Arp_H *)(packet+sizeof(Ethernet_H));
                if ((ntohs(arp_h->oper) == ARP_REPLY)){// && (arp_h->sender_IP == (uint8_t *)this->target_IP)){
                    cout << "[+] Find sender_IP's MAC addr : ";
                    for(int i = 0; i < 6; i++)
                        printf("%02X",(arp_h->sender_MAC[i]));
                    cout << endl;
                    memcpy(this->sender_MACaddr, arp_h->sender_MAC, 6);
                    break;
                }
            }
            else{
                continue;
            }
        }
    }
    /* And close the session */
    pcap_close(handle);
}


