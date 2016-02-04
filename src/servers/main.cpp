#include <iostream>
#include "server_farm.h"

int main(int argc, char * const argv[]){
	ServerFarm sf("input_example.txt");
	std::cout<<sf<<std::endl;

	for(size_t i = 0; i < sf.get_nservers(); ++i){
		sf.add_server(i);
	}
	std::cout<<sf<<std::endl;
	sf.output_server_data("random_output.txt");
	size_t gc = sf.calculate_score("random_output.txt");

	std::cout<<gc<<std::endl;
	return 0;
}
