#include "server_farm.h"

void Server::print(std::ostream &out) const{
	out<<id_<<" " << width_ << " " << cap_ << " " << dens_ << std::endl;
}

ServerFarm::ServerFarm(std::string filename){
	std::string line;
	std::ifstream myfile(filename.c_str());
	if(myfile.is_open()){
		myfile >> nrows_;
		myfile >> nslots_;
		matrix_.resize(nrows_);
		for(size_t i = 0; i < nrows_; ++i){
			matrix_[i].resize(nslots_);
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

        servers_v_.resize(nservers_);
		for(size_t i = 0; i < nservers_; ++i){
			Server newServer;
			myfile >> newServer.width_;
			myfile >> newServer.cap_;
            newServer.id_ = i;
            newServer.dens_ = newServer.cap_ * 1.0 / newServer.width_;
			std::cout<<newServer.width_<<" "<<newServer.cap_<< " " << newServer.dens_ << std::endl;
			servers_.push(newServer);
            servers_v_[i] = newServer;
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
		for(size_t j = 0; j < nslots_; ++j){
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
		for(size_t j = 0; j < nslots_; ++j){
			out<<matrix_[i][j]<<"\t";
		}
		out<<std::endl;
	}
}

void ServerFarm::print_servers(std::ostream &out) const{
	for(size_t i = 0; i < nservers_; ++i){
		out<<servers_v_[i];
		out<<std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, const ServerFarm &s){
	s.print(out);
	return out;
}

std::ostream &operator<<(std::ostream &out, const Server &s){
	s.print(out);
	return out;
}
