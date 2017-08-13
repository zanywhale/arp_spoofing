#ifndef NET_HEADER_HPP
#define NET_HEADER_HPP
#include <stdint.h>
#include <arpa/inet.h>
#include <pcap.h>

#ifndef ETHERTYPE_PUP
#define ETHERTYPE_PUP           0x0200  /* PUP protocol */
#endif
#ifndef ETHERTYPE_IP
#define ETHERTYPE_IP            0x0800  /* IP protocol */
#endif
#ifndef ETHERTYPE_ARP
#define ETHERTYPE_ARP           0x0806  /* addr. resolution protocol */
#endif
#ifndef ETHERTYPE_REVARP
#define ETHERTYPE_REVARP        0x8035  /* reverse addr. resolution protocol */
#endif
#ifndef ETHERTYPE_VLAN
#define ETHERTYPE_VLAN          0x8100  /* IEEE 802.1Q VLAN tagging */
#endif
#ifndef ETHERTYPE_EAP
#define ETHERTYPE_EAP           0x888e  /* IEEE 802.1X EAP authentication */
#endif
#ifndef ETHERTYPE_MPLS
#define ETHERTYPE_MPLS          0x8847  /* MPLS */
#endif
#ifndef ETHERTYPE_LOOPBACK
#define ETHERTYPE_LOOPBACK      0x9000  /* used to test interfaces */
#endif
#define ETHERNET_ALEN 6

#ifndef ARP_REQUEST
#define ARP_REQUEST 1
#endif
#ifndef ARP_REPLY
#define ARP_REPLY 2
#endif

#if __UAPI_DEF_IN_IPPROTO
enum {
  IPPROTO_IP = 0,       /* Dummy protocol for TCP       */
#define IPPROTO_IP      IPPROTO_IP
  IPPROTO_ICMP = 1,     /* Internet Control Message Protocol    */
#define IPPROTO_ICMP        IPPROTO_ICMP
  IPPROTO_IGMP = 2,     /* Internet Group Management Protocol   */
#define IPPROTO_IGMP        IPPROTO_IGMP
  IPPROTO_IPIP = 4,     /* IPIP tunnels (older KA9Q tunnels use 94) */
#define IPPROTO_IPIP        IPPROTO_IPIP
  IPPROTO_TCP = 6,      /* Transmission Control Protocol    */
#define IPPROTO_TCP     IPPROTO_TCP
  IPPROTO_EGP = 8,      /* Exterior Gateway Protocol        */
#define IPPROTO_EGP     IPPROTO_EGP
  IPPROTO_PUP = 12,     /* PUP protocol             */
#define IPPROTO_PUP     IPPROTO_PUP
  IPPROTO_UDP = 17,     /* User Datagram Protocol       */
#define IPPROTO_UDP     IPPROTO_UDP
  IPPROTO_IDP = 22,     /* XNS IDP protocol         */
#define IPPROTO_IDP     IPPROTO_IDP
  IPPROTO_TP = 29,      /* SO Transport Protocol Class 4    */
#define IPPROTO_TP      IPPROTO_TP
  IPPROTO_DCCP = 33,        /* Datagram Congestion Control Protocol */
#define IPPROTO_DCCP        IPPROTO_DCCP
  IPPROTO_IPV6 = 41,        /* IPv6-in-IPv4 tunnelling      */
#define IPPROTO_IPV6        IPPROTO_IPV6
  IPPROTO_RSVP = 46,        /* RSVP Protocol            */
#define IPPROTO_RSVP        IPPROTO_RSVP
  IPPROTO_GRE = 47,     /* Cisco GRE tunnels (rfc 1701,1702)    */
#define IPPROTO_GRE     IPPROTO_GRE
  IPPROTO_ESP = 50,     /* Encapsulation Security Payload protocol */
#define IPPROTO_ESP     IPPROTO_ESP
  IPPROTO_AH = 51,      /* Authentication Header protocol   */
#define IPPROTO_AH      IPPROTO_AH
  IPPROTO_MTP = 92,     /* Multicast Transport Protocol     */
#define IPPROTO_MTP     IPPROTO_MTP
  IPPROTO_BEETPH = 94,      /* IP option pseudo header for BEET */
#define IPPROTO_BEETPH      IPPROTO_BEETPH
  IPPROTO_ENCAP = 98,       /* Encapsulation Header         */
#define IPPROTO_ENCAP       IPPROTO_ENCAP
  IPPROTO_PIM = 103,        /* Protocol Independent Multicast   */
#define IPPROTO_PIM     IPPROTO_PIM
  IPPROTO_COMP = 108,       /* Compression Header Protocol      */
#define IPPROTO_COMP        IPPROTO_COMP
  IPPROTO_SCTP = 132,       /* Stream Control Transport Protocol    */
#define IPPROTO_SCTP        IPPROTO_SCTP
  IPPROTO_UDPLITE = 136,    /* UDP-Lite (RFC 3828)          */
#define IPPROTO_UDPLITE     IPPROTO_UDPLITE
  IPPROTO_MPLS = 137,       /* MPLS in IP (RFC 4023)        */
#define IPPROTO_MPLS        IPPROTO_MPLS
  IPPROTO_RAW = 255,        /* Raw IP packets           */
#define IPPROTO_RAW     IPPROTO_RAW
  IPPROTO_MAX
};
#endif

typedef struct _ethernet{
    uint8_t dest[ETHERNET_ALEN];
    uint8_t src[ETHERNET_ALEN];
    uint16_t type;
}__attribute__((packed))Ethernet_H;

typedef struct _arp{
    uint16_t h_type;
    uint16_t p_type;
    uint8_t h_len;
    uint8_t p_len;
    uint16_t oper;
    uint8_t sender_MAC[6];
    uint8_t sender_IP[6];
    uint8_t target_MAC[6];
    uint8_t target_IP[6];
}__attribute__((packed))Arp_H;

typedef struct _ip{
    uint8_t chk;
    uint8_t tos;
    uint16_t len;
    uint16_t id;
    uint16_t off;
    uint8_t ttl;
    uint8_t p;
    uint16_t sum;
    uint32_t src;
    uint32_t dst;
}__attribute__((packed))Ip_H;

typedef struct _tcp{
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq;
    uint32_t ack;
    uint8_t data_offset;  // 4 bits
    uint8_t flags;
    uint16_t window_size;
    uint16_t checksum;
    uint16_t urgent_p;
}__attribute__((packed))Tcp_H;

#endif