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

        avail_drones_ = ndrones_;

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


void prelim::deliver() {
    for (int t = 0; t < nturns_; t++) {
        update_drones();
        while (orders.size() and avail_drones_) {
            order cur_ord = choose_order();
            put_order(cur_ord);
        }
    }
}


order& prelim::choose_order() {
    int rn = rand() % orders.size();
    return orders[rn];

}

drone& prelim::choose_drone() {
    int rn = rand() % drones.size();
    while (!drones[rn].counter) {
        rn = rand() % drones.size();
    }
    return drones[rn];

}

void prelim::put_order (order & cur_order) {
    while (avail_drones_ and cur_order.nitems_) {
        drone& cur_drone  = choose_drone();
        
    load_drone(cur_drone, cur_order);
    avail_drones_ --;
//    update_order();
    }
}

void prelim::load_drone (drone& cur_drone, order& cur_order) {
    while (cur_drone.cap_ > 0 ) {
        // iterate over products in the order
        for (int it = 0; it < cur_order.req_.size(); it++) {
            int itnum = cur_order.req_[it];
            // reduce number of items of the product until it fits the drone 
            while (itnum * pweights[it] > max_payload_ - cur_drone. and itnum > 1) {
                itnum--;
            }
            // if at least 1 item left
            if (itnum) {
                 cur_drone.cup_ -= itnum * pweights[it];
            }
        }
       choose_item();
       choose_warehouse(); 
       load_commands();
    }

}
