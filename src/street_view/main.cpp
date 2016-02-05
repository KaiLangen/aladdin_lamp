#include <iostream>
#include "street_view.h"

int main(int argc, char * const argv[]){
//    std::cout<<"HELLO WORLD"<<std::endl;
//	return 0;

    std::cout<<"Initializing graph"<<std::endl;
    street_view_graph g("paris_54000.txt");

    std::cout<<"running simulation"<<std::endl;
    g.run();

    std::cout<<"outputting file"<<std::endl;
    g.output_to_file("computed_output_paris_54000.txt");

    return 0;
}
