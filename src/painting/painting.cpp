#include "server_farm.h"
#include <algorithm>
#include <numeric>

painting::painting(std::string infile){
/*	srand(time(NULL));
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
		myfile >> nrows_;
		myfile >> ncols_;
		size_t x,y;
		for(size_t i = 0; i < nunavaiable_; ++i){
			myfile >> x;
			myfile >> y;
			matrix_[x][y] = -1;
		}

		for(size_t i = 0; i < nservers_; ++i){
			Server *newServer = new Server();
			myfile >> newServer->width_;
			myfile >> newServer->cap_;
			std::cout<<newServer->width_<<" "<<newServer->cap_<<std::endl;
			servers_.push_back(newServer);
		}

		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}*/
}

painting::~painting(){
}

//naive algorithm to add new servers to the server farm
void painting::add_server(size_t sindex){
}

void painting::print(std::ostream &out) const{
}

void painting::output_server_data(std::string outfile){
/*	std::ofstream ofile(outfile.c_str());
	if(ofile.is_open()){
		for(size_t i = 0; i < nservers_; ++i){
			Server *s = servers_[i];
			if(s->was_placed_)
				ofile<<s->row_<<" "<<s->col_<<" "<<s->pool_<<std::endl;
			else
				ofile<<"x"<<std::endl;
		}
		ofile.close();
	}
	else{
		std::cout<<"Unable to open output file"<<std::endl;
		exit(EXIT_FAILURE);
	}*/
}

//referenced compute from count_score.cpp
size_t painting::calculate_score(std::string file){
}

std::ostream &operator<<(std::ostream &out, const painting &s){
	s.print(out);
	return out;
}

