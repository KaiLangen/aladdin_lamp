#include <iostream>
#include "server_farm.h"

int main(int argc, char * const argv[]){
	ServerFarm sf("input_example.txt");
	std::cout<<sf<<std::endl;

	while(!sf.servers_.empty()){
		sf.add_server();
	}
	std::cout<<sf<<std::endl;
	return 0;
}
