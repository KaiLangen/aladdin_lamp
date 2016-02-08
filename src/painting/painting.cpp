#include "painting.h"
#include <algorithm>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

painting::painting(std::string infile){
	srand(time(NULL));
	std::string line;
        elem_remaining_ = 0;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
		myfile >> nrows_;
		myfile >> ncols_;

		working_matrix_.resize(nrows_);
		starting_matrix_.resize(nrows_);
                for(int i = 0; i < nrows_; ++i){
                    working_matrix_[i].resize(ncols_);
		    starting_matrix_[i].resize(ncols_);
                }
                
		getline(myfile, line); 
		for(int i = 0; i < nrows_; ++i){
		    getline(myfile, line); 
		    for(int j = 0; j < ncols_; ++j){
			if(line[j] == '#'){
			   working_matrix_[i][j] = true;
			   starting_matrix_[i][j] = true;
                           ++elem_remaining_;
                        }
                        else{
			   working_matrix_[i][j] = false;
			   starting_matrix_[i][j] = false;
                        }

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

void painting::paint_elems(){
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
	   if(working_matrix_[i][j]){
               //push command to list
               operation new_op(SQUARE, { i, j, 0});
               op_list.push_back(new_op);
               working_matrix_[i][j] = false;
               --elem_remaining_;
           }
        }       
    }
}

void painting::paint_square(){
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
        //push command to list
	
        }       
    }
}

void painting::paint_vert_line(){
    for(int j = 0; j < ncols_; ++j){
        for(int i = 0; i < nrows_; ++i){
        //push command to list
	    
        }       
    }
}

void painting::paint_horz_lines(){
    int consecutive = 0;
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
	   if(working_matrix_[i][j]){
	      ++consecutive;
           }
           else if(consecutive > 1){
	      int start_col = (j - consecutive);
              operation new_op(LINE, {i, start_col, i, (j - 1)});
              op_list.push_back(new_op);
              consecutive = 0;
              for(int k = start_col; k < j; ++k){
                  working_matrix_[i][k] = false; 
                  --elem_remaining_;
              }
           }
           if((j == ncols_ - 1) && working_matrix_[i][j] && (consecutive > 1)){//end of row
	      int start_col = (j - consecutive + 1);
              operation new_op(LINE, {i, start_col, i, (j)});
              op_list.push_back(new_op);
              consecutive = 0;
              for(int k = start_col; k <= j; ++k){
                  working_matrix_[i][k] = false; 
                  --elem_remaining_;
              }
           }
        }       
    }
}

void painting::print(std::ostream &out) const{
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
	   out<<working_matrix_[i][j];
        }
        out<<std::endl;
    }

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
        ofile.close();
    }

}


