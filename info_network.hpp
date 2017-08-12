#ifndef INFO_NETWORK_HPP
#define INFO_NETWORK_HPP
#include <stdint.h>

class info_network{
    public:
        info_network(char INTERFACE[10], char SENDER_IP[16], char TARGET_IP[16]);
        virtual ~info_network();
        void find_mac_addr(char MAC_str[13], char user_interface[10]);
        void print_status();
    protected:
    private:
        char interface[10];
        char my_MACaddr[13];
        char my_IPaddr[13];
        char sender_IP[16];
        char sender_MACaddr[13];
        char target_IP[16];
        char target_MACaddr[13];
};

class arp_packet{
    public:
        arp_packet();
        virtual ~arp_packet();

        // ethernet header
        uint8_t eth_dst_addr[6];
        uint8_t eth_src_addr[6];
        uint16_t type;

        // arp header
        uint16_t h_type;
        uint16_t p_type;
        uint8_t h_len;
        uint8_t p_len;
        uint16_t oper;
        uint8_t sender_MAC[6];
        uint8_t sender_IP[6];
        uint8_t target_MAC[6];
        uint8_t target_IP[6];
};

#endif