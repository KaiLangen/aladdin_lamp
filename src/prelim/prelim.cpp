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
		//initialize all the drones at warehouse 0 location
		drones.resize(ndrones_, drone(max_payload_, warehouses[0].pos_));
		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}
}

prelim::~prelim(){
}

void command::print(std::ostream &out) const{
	out << did_;
	if(type_ == LOAD)
		out << "L";
	else if(type_ == UNLOAD)
		out << "U";
	else{
		std::cout<<"INVALID COMMAND TYPE"<<std::endl;
		exit(EXIT_FAILURE);
	}
	out << wid_;
	out << pid_;
	out << nitems_;
}

std::ostream &operator<<(std::ostream &out, const command &c){
	c.print(out);
	return out;
}

void drone::add_command(){

}


void prelim::output_prelim_data (std::string outfile) {
    std::ofstream ofile(outfile.c_str());
    if(ofile.is_open()){
        for(int i = 0; i < ndrones_; ++i){
			for(size_t j = 0; j < drones[i].commands_.size(); ++j){
				ofile << drones[i].commands_[j] << std::endl;
			}
        }
        ofile.close();
    }
    else{
        std::cout<<"Unable to open output file"<<std::endl;
        exit(EXIT_FAILURE);
    }
}




