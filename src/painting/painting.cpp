#include "painting.h"
#include <algorithm>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

painting::painting(std::string infile){
	srand(time(NULL));
	std::string line;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
		myfile >> nrows_;
		myfile >> ncols_;

//                std::cout<<"rows "<<nrows_<<"cols "<<ncols_<<std::endl;

		input_matrix_.resize(nrows_);
                for(int i = 0; i < nrows_; ++i)
                    input_matrix_[i].resize(ncols_);
                
		getline(myfile, line); 
		for(int i = 0; i < nrows_; ++i){
		    getline(myfile, line); 
		    for(int j = 0; j < ncols_; ++j){
			if(line[j] == '#')
			   input_matrix_[i][j] = true;
                        else
			   input_matrix_[i][j] = false;

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

void painting::add_command(size_t sindex){
}

void painting::print(std::ostream &out) const{
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
	   out<<input_matrix_[i][j];
        }
        out<<std::endl;
    }

}

void painting::output_painting_data(std::string outfile){
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

std::ostream & operator<<(std::ostream& out, const operation & op) {
    switch(op.name_) {
        case LINE:
            out << "PAINT_LINE ";
            for(size_t i = 0; i < 4; ++i) {
                out << op.data_[i] << " ";
            }
            break;
        case SQUARE:
            out << "PAINT_SQUARE ";
            for(size_t i = 0; i < 3; ++i) {
                out << op.data_[i] << " ";
            }
            break;
        case ERASE:
            out << "ERASE_CELL ";
            for(size_t i = 0; i < 2; ++i) {
                out << op.data_[i] << " ";
            }
            break;
        default:
            std::cerr << "Unrecognized operation while performing output!" << std::endl;
            exit(1);
    }
    out << std::endl;
    return out;
}

void painting::output_painting_data (std::string outfile) {
    std::ofstream ofile(outfile.c_str());
    if(ofile.is_open()){
        ofile << op_list.size() << std::endl;

        std::list<operation>::iterator it;
        for(it = op_list.begin(); it != op_list.end(); it++){
            ofile << *(it);
        }
    }

}


