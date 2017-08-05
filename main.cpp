#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "find_macaddr.hpp"

int main(int argc, char *argv[], char *envp[])
{
	if(argc != 4) // Have to use four arguments
	{
		printf("\033[1;32mUsage: send_arp <interface> <sender(victim) ip> <target ip>\033[0m\n\033[1;31mEx)send_arp wlan0 192.168.10.2 192.168.10.1\033[0m\n");
		exit(0);
	}
	
	unsigned char mac[13];
	mac_eth0(mac);
	return 0;
}
