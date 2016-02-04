#include "server_farm.h"

ServerFarm::ServerFarm(std::string infile){
	srand(time(NULL));
	std::ifstream myfile(infile.c_str());
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
	}
}

ServerFarm::~ServerFarm(){
	for(size_t i = 0; i < servers_.size(); ++i){
		delete servers_[i];
	}
	servers_.clear();
}

//naive algorithm to add new servers to the server farm
void ServerFarm::add_server(size_t sindex){
	Server *newServer = servers_[sindex];
	std::cout<<newServer->cap_<<std::endl;
	size_t consecutive = 0;
	//start at a random row/column combination and iterate through matrix
	size_t rand_row = static_cast<size_t>(rand() % nrows_);
	size_t rand_col = static_cast<size_t>(rand() % ncols_);
	for(size_t i = 0; i < nrows_; ++i){
		for(size_t j = 0; j < ncols_; ++j){
			size_t wrapped_row = (i + rand_row) % nrows_;
			size_t wrapped_col = (j + rand_col) % ncols_;

			//if reach 0th index, reset consecutive
			if(wrapped_col == 0)
				consecutive = 0;

			//if empty, increment consecutive
			if(matrix_[wrapped_row][wrapped_col] == 0)
				++consecutive;

			//find a contiguous space the size of the server
			if(consecutive == newServer->width_){
				size_t start = wrapped_col + 1 - newServer->width_;
				matrix_[wrapped_row][start] = newServer->cap_;
				//fill in all intermediate elements with -1
				for(size_t k = (start + 1); k <= wrapped_col; ++k){
					matrix_[wrapped_row][k] = -1;
				}
				//update the server with it's new location, etc
				servers_[sindex]->col_ = start;
				servers_[sindex]->row_ = wrapped_row;
				servers_[sindex]->pool_ = rand() % npools_;
				servers_[sindex]->was_placed_ = true;
				return;
			}
		}
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

void ServerFarm::output_server_data(std::string outfile){
	std::ofstream ofile(outfile.c_str());
	if(ofile.is_open()){
		for(size_t i = 0; i < servers_.size(); ++i){
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
	}
}

std::ostream &operator<<(std::ostream &out, const ServerFarm &s){
	s.print(out);
	return out;
}

