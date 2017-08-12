#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "info_network.hpp"
#include "verification.hpp"
using namespace std;

int main(int argc, char *argv[], char *envp[])
{
    // start verification
    verification *verif = new verification(argv[1], argv[2], argv[3]);
    if(argc != 4) // Have to use four arguments
        verif->check_argc();
    else{ // check interface and ip addr
        verif->check_interface(argv[1]);
        verif->check_ipaddr(argv[2], argv[3]);
    }
    delete verif;
    // end verification

    info_network info = info_network(argv[1], argv[2], argv[3]);
    info.print_status();
    return 0;
}
