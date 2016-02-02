#include "server_farm.h"

ServerFarm::ServerFarm(std::string filename){
	std::string line;
	std::ifstream myfile(filename.c_str());
	if(myfile.is_open()){
		myfile >> nrows_;
		myfile >> ncols_;
		matrix_.resize(nrows_);
		for(size_t i = 0; i < nrows_; ++i){
			matrix_[i].resize(ncols_);
		}
		myfile >> nunavaiable_;
		myfile >> npools_;
		myfile >> nservers_;
		size_t x,y;
		for(size_t i = 0; i < nunavaiable_; ++i){
			myfile >> x;
			myfile >> y;
			matrix_[x][y] = -1;
		}

		for(size_t i = 0; i < nservers_; ++i){
			Server newServer;
			myfile >> newServer.width_;
			myfile >> newServer.cap_;
			std::cout<<newServer.width_<<" "<<newServer.cap_<<std::endl;
			servers_.push(newServer);
		}

		myfile.close();
	}
	else{
		std::cout<<"Unable to open file"<<std::endl;
		exit(EXIT_FAILURE);
	}
}

//naive algorithm to add new servers to the server farm
void ServerFarm::add_server(){
	Server newServer = servers_.top();
	std::cout<<newServer.cap_<<std::endl;
	servers_.pop();
	size_t consecutive = 0;
	for(size_t i = 0; i < nrows_; ++i){
		for(size_t j = 0; j < ncols_; ++j){
			if(matrix_[i][j] == 0)
				++consecutive;

			if(consecutive == newServer.width_){
				size_t start = j + 1 - newServer.width_;
				matrix_[i][start] = newServer.cap_;
				//fill in all intermediate elements with -1
				for(size_t k = (start + 1); k <= j; ++k){
					matrix_[i][k] = -1;
				}
			}
		}
		consecutive = 0;
	}
}

void ServerFarm::print(std::ostream &out) const{
	for(size_t i = 0; i < nrows_; ++i){
		for(size_t j = 0; j < ncols_; ++j){
			out<<matrix_[i][j]<<"\t";
		}
		out<<std::endl;
	}
}


std::ostream &operator<<(std::ostream &out, const ServerFarm &s){
	s.print(out);
	return out;
}

