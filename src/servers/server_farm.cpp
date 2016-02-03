#include "server_farm.h"
#include <algorithm>

void Pair::print(std::ostream &out) const{
	out<<id_<<" " << value_ << std::endl;
}
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
        na_slots_.resize(nrows_);
        first_slot_.resize(nrows_);
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
            // count unavailable slots per row
            na_slots_[x].value_ += 1; ;
		}


        servers_v_.resize(nservers_);
        placement_.resize(nservers_);
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

void ServerFarm::count_na_slots(){
        std::cout << "count_na_slots" << std::endl;
        for (unsigned int i = 0; i< nrows_; i++) {
            int num_slots = std::accumulate(matrix_[i].begin(), matrix_[i].end(), 0);
            // minus because in matrix there are 0 and -1
            na_slots_[i] = Pair(i, -num_slots);
            std::cout  << na_slots_[i];
        }
}

void ServerFarm::count_avg_cperpr() {
    double sum_capacity = 0.0;
    for (int i = 0; i < nservers_; i++){
        sum_capacity += servers_v_[i].cap_;   
    }
    avg_cperpr_ = sum_capacity * 1.0/(npools_ * nrows_); 
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

// for rows and available slots we can use sparse matrix format: (number of element, number of consecutive free slots)
int ServerFarm::find_place_inrow(unsigned int row, unsigned int width) {
    unsigned int consecutive = 0;
    for (unsigned int sl = first_slot_[row]; sl < nslots_; sl++) {
        if (matrix_[row][sl] == 0) {
           consecutive++;
        }
        if (consecutive == width) {
            unsigned int start = sl - consecutive + 1;
            for (unsigned int i = start; i < width; i++) {
                matrix_[row][i] = -1;
            }
            return start;
        }
        if (matrix_[row][sl] == -1 ) {
            consecutive = 0;
        }
    }
    return -1;
}

Pair ServerFarm::find_place(unsigned int row, unsigned int width) {
    bool found = false;
    for (unsigned int i = 0; i < nrows_; i++) {
        // example: nrows_ = 5 row = 3 r = {3 4 0 1 2}
        int r = (i+row) % nrows_;
        int slot = find_place_inrow(r, width);
        if (slot >= 0) {
            return Pair(r, slot);
        }
    }
    return Pair(-1, 0);
}

void ServerFarm::place_servers() {
    //std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_dens); 
    //if sort is preserving order 2 sorts will make servers be sorted by capacity
    // and for each capacity value - by size
    std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_width); 
    std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_cap); 
    count_na_slots();
    // sort rows by free slots
    std::sort(na_slots_.begin(), na_slots_.end(), Pair::cmp);
    //Server newServer = servers_.top();
    unsigned int current_row = 0;
    for (unsigned int s = 0; s < nservers_; s++) {
        Server server = servers_v_[s];
        bool not_placed = true;
        while (not_placed) {
            // for each r_th server we start placing with 0 (first) row
            // in case the server does not fit in current row R we move to next
            // until find place in the row F
            // and for next server has to start from row R until fitting except row F
            Pair place = find_place(current_row, server.width_);
            if (place.id_ >= 0) {
                not_placed = false;
                placement_[s] = place;
                if (place.id_ == current_row) {
                    current_row++;
                }
            } else {
                placement_[s] = Pair(-1, -1);
            }
        }
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

void ServerFarm::print_placement(std::ostream &out) const{
	for(size_t i = 0; i < nservers_; ++i){
		out << placement_[i] << std::endl;
	}
    out << std::endl;
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

std::ostream &operator<<(std::ostream &out, const Pair &s){
	s.print(out);
	return out;
}
