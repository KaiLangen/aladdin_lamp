
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>

//#include <boost/tokenizer.hpp>

struct Server {
	size_t width_;
	size_t cap_;
};

class ServerFarm {
private:
std::vector<std::vector<int> > matrix_;
std::vector<Server> servers_;
size_t nrows_;
size_t ncols_;
size_t npools_;
size_t nunavaiable_;
size_t nservers_;

public:
ServerFarm(){
	std::string line;
	std::ifstream myfile("input_example.txt");
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

		servers_.resize(nservers_);
		for(size_t i = 0; i < nservers_; ++i){
			myfile >> servers_[i].width_;
			myfile >> servers_[i].cap_;
		}

		myfile.close();
	}
	else std::cout<<"Unable to open file"<<std::endl;
}

void print(){
	for(size_t i = 0; i < nrows_; ++i){
		for(size_t j = 0; j < ncols_; ++j){
			std::cout<<matrix_[i][j]<<"\t";
		}
		std::cout<<std::endl;
	}
}

};

int main(int argc, char * const argv[]){
	ServerFarm sf;
	sf.print();
	return 0;
}
