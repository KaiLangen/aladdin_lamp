#include "painting.h"
#include <algorithm>
#include <numeric>
#include <string>

painting::painting(std::string infile){
	srand(time(NULL));
	std::string line;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
		myfile >> nrows_;
		myfile >> ncols_;
		size_t x,y;
                
		getline(myfile, line); 
		for(size_t i = 0; i < nrows_; ++i){
		    getline(myfile, line); 
		    for(int j = 0; j < ncols_; ++j){
			if(strcmp(line[j],"#") == 0){
			   input_matrix_[i].push_back(true);
                        else
			   input_matrix_[i].push_back(false);

		    }
		}

		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}
}

painting::~painting(){
}

//naive algorithm to add new servers to the server farm
void painting::add_command(size_t sindex){
}

void painting::print(std::ostream &out) const{
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < nrows_; ++j){
	   out<<input_matrix_[i][j];
        }
        out<<std::endl;
    }

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

std::ostream &operator<<(std::ostream &out, const painting &s){
	s.print(out);
	return out;
}

