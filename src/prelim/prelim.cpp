#include <algorithm>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <stdio.h>
#include <math.h>

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
			warehouses[i].av_.resize(nprods_);
			for(int j = 0; j < nprods_; ++j){
				myfile >> warehouses[i].av_[j];
				//std::cout<<warehouses[i].av_[j]<<std::endl;
			}
		}

		//get number of orders
		myfile >> norders_;
		orders.resize(norders_);
		for(int i = 0; i < norders_; ++i){
			myfile >> orders[i].pos_.x_;
			myfile >> orders[i].pos_.y_;
			myfile >> orders[i].nitems_;
			orders[i].req_.resize(nprods_);
			for(int j = 0; j < nprods_; ++j){
				myfile >>orders[i].req_[j];
			}
		}
		//initialize all the drones at warehouse 0 location
		for (int i = 0; i < ndrones_; ++i){
			drones.push_back(drone(max_payload_, nturns_, warehouses[0].pos_,i));
		}
		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}
}

int distance(coord a, coord b){
	int result = sqrt(pow((a.x_ - b.x_),2) + pow((a.x_ - b.x_),2));
	result += 1;
	return result;
}

void prelim::master_command(){
	for(int i = 0; i < norders_; ++i){
		while(drones.size()){
			drones.back().action(i, *this);
			dead_drones.push_back(drones.back());
			drones.pop_back();
		}
	}
}

void drone::action(int order_num, prelim& p){
	order *o = &(p.orders[order_num]);
	//randomly select order
	//start by order of orders

	//execute order
	for(size_t i = 0; i < o->req_.size(); ++i){

	//search warehouse database for items you need
		int dist = std::numeric_limits<int>::max();
		wh* closest = NULL;
		int wid;
		for(int j = 0; j < p.nwarehouses_; ++j){
			wh* cur = &(p.warehouses[j]);
			//if warehouse contains product
			if(cur->av_[i] > 0){
				//if distance to cur is less than distance
				int d = distance(pos_, cur->pos_);
				if(d < dist){
					dist= d;
					closest = cur;
					wid = j;
				}
			}
		}
		//go to nearest warehouse
		//load
		turns_left_ -= 1;
		int can_carry = 0;
		turns_left_ -= dist;
		if(!(turns_left_ > 0 && closest)){
			break;
		}
		pos_ = closest->pos_;
		int required = o->req_[i];
		can_carry = cap_ / (p.pweights[i]);
		can_carry = std::min(required, can_carry);
		add_op(id_, LOAD, wid, i, can_carry);
		closest->av_[i] -= can_carry;
		o->req_[i] -= can_carry;
		//go to destination
		dist = distance(pos_, o->pos_);
		turns_left_ -= dist;

		//deliver
		add_op(id_, LOAD, order_num, i, can_carry);
	}
}

void drone::add_op(int did, command_type type,
int wid, int pid, int num){
	command c(did, type, wid, pid, num);
	std::cout<<c<<std::endl;
	commands_.push_back(c);
}

prelim::~prelim(){
}

void command::print(std::ostream &out) const{
	out << did_<<" ";
	if(type_ == LOAD)
		out << "L ";
	else if(type_ == UNLOAD)
		out << "U ";
	else if(type_ == DELIVER)
		out << "D ";
	else if(type_ == WAIT)
		out << "W ";
	else{
		std::cout<<"INVALID COMMAND TYPE: "<<type_<<std::endl;
		exit(EXIT_FAILURE);
	}
	out << wid_<<" ";
	out << pid_<<" ";
	out << nitems_<<" ";
}

std::ostream &operator<<(std::ostream &out, const command& c){
	c.print(out);
	return out;
}

void prelim::output_prelim_data (std::string outfile) {
    std::ofstream ofile(outfile.c_str());
    if(ofile.is_open()){
		assert(dead_drones.size() == static_cast<size_t>(ndrones_));
        for(int i = 0; i < ndrones_; ++i){
			for(size_t j = 0; j < dead_drones[i].commands_.size(); ++j){
				ofile << dead_drones[i].commands_[j] << std::endl;
			}
        }
        ofile.close();
    }
    else{
        std::cout<<"Unable to open output file"<<std::endl;
        exit(EXIT_FAILURE);
    }
}




