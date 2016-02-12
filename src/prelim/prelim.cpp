#include "prelim.h"
#include <algorithm>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
const std::string data::hw_("HELLO WORLD");

prelim::prelim(std::string infile){
	srand(time(NULL));
	std::string line;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
                //get single items from input file
		myfile >> nrows_;
		myfile >> ncols_;
		myfile >> ndrones_;
		myfile >> nturns_;
		myfile >> max_payload_;
		myfile >> nprods_;

		int weight;
		for(int i = 0; i < nprods_; ++i){
			myfile >> weight;
			//do something with that weight
			std::cout<<weight<<std::endl;
		}
		myfile >> nwarehouses_;
		//discard the first 4 lines
		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line);
		getline(myfile, line);

		for(int i = 0; i < nwarehouses_; ++i){
			//get two lines per warehouse
			getline(myfile, line);
			getline(myfile, line);
		}

		//get number of orders
		getline(myfile, line);
		//norders_;

		for(int i = 0; i < norders_; ++i){
			//get 3 lines per order
			getline(myfile, line);
			getline(myfile, line);
			getline(myfile, line);
		}

		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}
}

prelim::~prelim(){
}

void prelim::print(std::ostream &out) const{
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
//	   out<<matrix_[i][j]<<std::endl;
        }
        out<<std::endl;
    }

}

std::ostream &operator<<(std::ostream &out, const prelim &s){
	s.print(out);
	return out;
}

void prelim::output_prelim_data (std::string outfile) {
    std::ofstream ofile(outfile.c_str());
    if(ofile.is_open()){
        //print something
        ofile << "something" << std::endl;
        //print other things
        char ot[] = {"other things"};
        for(int i = 0; i < 12; ++i){
            ofile << ot[i] << std::endl;
        }
        ofile.close();
    }
    else{
        std::cout<<"Unable to open output file"<<std::endl;
        exit(EXIT_FAILURE);
    }
}




