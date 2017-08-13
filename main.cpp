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

    // get info
    arp_packet arp = arp_packet(argv[1], argv[2], argv[3]);
    // get victim's MAC Address
    // info.print_status();
    arp.arp_request();
    arp.arp_capture();
    arp.print_status();
    // infect victim ARP table
    return 0;
}
