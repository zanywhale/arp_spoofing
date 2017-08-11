#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "info_network.hpp"
using namespace std;
int main(int argc, char *argv[], char *envp[])
{
    if(argc != 4) // Have to use four arguments
    {
        cout << "\033[1;32mUsage: send_arp <interface> <sender(victim) ip> <target ip>" <<\
                "\033[0m\n\033[1;31mEx)send_arp wlan0 192.168.10.2 192.168.10.1\033[0m\n";
        exit(0);
    }
    
    info_network info = info_network(argv[1], argv[2], argv[3]);
    info.print_status();
    return 0;
}
