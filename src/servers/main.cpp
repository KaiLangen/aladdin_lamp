#include <iostream>
#include "server_farm.h"

int main(int argc, char * const argv[]){
	ServerFarm sf("input.txt");
//	ServerFarm sf(argv[1]);
/*
	std::cout<<sf<<std::endl;

    sf.sort_dens();
    sf.print_servers(std::cout);

	while(!sf.servers_.empty()){
		sf.add_server();
	}
*/
    std::cout << "Room: " << std::endl;    
	std::cout<<sf<<std::endl;
    sf.place_servers();
    sf.print_placement(std::cout);
    std::cout << "Room: " << std::endl;    
	std::cout<<sf<<std::endl;
	return 0;
}
