#ifndef VERIFICATION_HPP
#define VERIFICATION_HPP

class verification{
	public:
		verification(char argv1[10], char argv2[16], char argv3[16]);
		virtual ~verification();
		void check_interface(char *interface);
		void check_argc();
	private:

};

#endif