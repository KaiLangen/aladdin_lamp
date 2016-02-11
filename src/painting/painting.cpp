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
           else {
               consecutive = 0;
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
        consecutive = 0;
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


void painting::obvious_vertical_lines_optimization() {

    // go through the list of operations
    std::list<operation>::iterator it;
    for( it = op_list.begin(); it != op_list.end(); it++){

    // when you find a horizontal line
        if ( (it->name_ == LINE) && ( it->data_[0] == it->data_[2] ) ) {

            int length = it->data_[3] - it->data_[1] + 1;
            int last_row_position = it->data_[0]; // this will be useful later

            // populate a list of lines of same length that are exactly underneath this one
            std::list< std::list<operation>::iterator > to_delete;
            std::list<operation>::iterator it_under = it;
            std::advance(it_under,1);

            while ( ( it_under =
              std::find_if( it_under, op_list.end(),
                        [&] (operation op) {
                          if (
                          ( op.name_ == LINE ) &&
                          ( op.data_[0] == op.data_[2] ) &&
                          ( op.data_[0] == last_row_position + 1 ) &&
                          ( op.data_[1] == it->data_[1] ) &&
                          ( op.data_[3] == it->data_[3] ) ) {
                            return true;
                          } else { return false; }
                          } )
                     ) != op_list.end() ){

                to_delete.push_back(it_under);
                last_row_position = it_under->data_[0];
                std::advance(it_under,1);
            }

            // if the number of such lines is larger than the length of a single one, there is an optimization opportunity!
            if ( to_delete.size() > length) {
                std::cerr << "found an optimization opportunity at " << it->data_[0] << " " << it->data_[1] << std::endl;
                std::cerr << " of height " << to_delete.size() << " and length " << length << std::endl;
                // replace "many horizontal lines" with "few vertical lines"

                for( int i = 0; i < length; ++i) {
                    operation tmp(LINE, { it->data_[0],
                                          it->data_[1] + i,
                                          last_row_position,
                                          it->data_[1] + i } );
                    op_list.push_back( tmp );
                }

                std::for_each( to_delete.begin(), to_delete.end(),
                  [&] ( std::list<operation>::iterator it_to_delete ) {
                    op_list.erase( it_to_delete ); } );
            }

            to_delete.clear();

        }
    }
}




