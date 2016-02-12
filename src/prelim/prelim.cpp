#include <algorithm>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "prelim.h"
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

		pweights.resize(nprods_);
		for(int i = 0; i < nprods_; ++i){
			myfile >> pweights[i];
		}

		myfile >> nwarehouses_;
		warehouses.resize(nwarehouses_);

		for(int i = 0; i < nwarehouses_; ++i){
			myfile >> warehouses[i].pos_.x_;
			myfile >> warehouses[i].pos_.y_;
			for(int j = 0; j < nprods_; ++j){
				myfile >> warehouses[i].av_[j];
			}
		}

		//get number of orders
		myfile >> norders_;
		orders.resize(norders_);
		for(int i = 0; i < norders_; ++i){
			myfile >> orders[i].pos_.x_;
			myfile >> orders[i].pos_.y_;
			myfile >> orders[i].nitems_;
			for(int j = 0; j < nprods_; ++j){
				myfile >>orders[i].req_[j];
			}
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




