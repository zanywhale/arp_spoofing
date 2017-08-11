#ifndef INFO_NETWORK_HPP
#define INFO_NETWORK_HPP

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
		char sender_ip[16];
		char target_ip[16];
};

#endif