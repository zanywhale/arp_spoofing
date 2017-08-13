#ifndef INFO_NETWORK_HPP
#define INFO_NETWORK_HPP
#include "net_header.hpp"
#include <pcap.h>

class info_network{
    public:
        info_network(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16]);
        virtual ~info_network();
        void find_mac_addr(unsigned char MAC_str[6], char user_interface[10]);
        void print_status();
    protected:
        char interface[10];
        unsigned char my_MACaddr[6];
        int my_IPaddr;
        char sender_IP[16];
        unsigned char sender_MACaddr[6];
        char target_IP[16];
        unsigned char target_MACaddr[6];
        char errbuf[PCAP_ERRBUF_SIZE];
    private:
};

class arp_packet : public info_network{
    public:
        arp_packet(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16]);
        virtual ~arp_packet();
        void arp_request();
        void arp_reply();
        void arp_capture();
    private:
        pcap_t *handle;
};

#endif