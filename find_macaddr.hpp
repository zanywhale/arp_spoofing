#ifndef FIND_MACADDR_HPP
#define FIND_MACADDR_HPP

class information{
	public:
		information();
		~information();
		char My_MACaddr[13];
	protected:
	private:
		void mac_eth0(char MAC_str[13]);
};

#endif