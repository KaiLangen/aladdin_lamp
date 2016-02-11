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


void prelim::deliver() {
    for (int t = 0; t < nturns_; t++) {
        for( std::vector<drone>::iterator it = drones.begin(), it != drones.end(), it++ ) {
           update_drone(*it);
        }

        while (orders_left and avail_drones) {
            order cur_ord = choose_order();
            put_order(cur_ord);
        }
    }
}


order& prelim::choose_order() {
    int rn = rand() % orders.size();
    return orders[rn];

}

void prelim::put_order (order & cur_order) {
    while (avail_drones)
    drone = choose_drone();

    load_commands(drone);
    update_order();
}

void prelim::update_drone(drone& d) {

    if ( d.turns_left_) {
        d.turns_left_--;
    } else if ( !d.immediate_pending_commands_.is_empty() ) {
        command todo = d.immediate_pending_commands_.pop();
        switch(todo.type_) {
            case LOAD:
                warehouses[todo.wid_] -= nitems_;
                d.load[todo.pid_] += nitems_;
                break;
            case UNLOAD:
                d.load[todo.pid_] -= nitems_;
                orders[todo.oid_].delv_[todo.pid_] += nitems_; 
                break;
            case MOVE:
                d.turns_left_ += pid_;
                break;
            default:
                std::cerr << "Unrecognized command" << std::endl; 
                exit(1);
        }
    }    
}



