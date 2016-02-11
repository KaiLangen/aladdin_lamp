#include "prelim.h"
#include <algorithm>
#include <numeric>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
const std::string data::hw_("HELLO WORLD");

prelim::prelim(std::string infile){
	srand(time(NULL));
	std::string line;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
                //get single items from input file
		myfile >> nrows_;
		myfile >> ncols_;

		matrix_.resize(nrows_);
                for(int i = 0; i < nrows_; ++i){
                    matrix_[i].resize(ncols_);
                }

                //discard the first line
		getline(myfile, line);
                //get entire lines at a time
		for(int i = 0; i < nrows_; ++i){
		    getline(myfile, line);
                    //do something with that line
                    std::cout<<line<<std::endl;
		}
		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}
}

prelim::~prelim(){
}

void prelim::print(std::ostream &out) const{
    for(int i = 0; i < nrows_; ++i){
        for(int j = 0; j < ncols_; ++j){
	   out<<matrix_[i][j]<<std::endl;
        }
        out<<std::endl;
    }

}

void data::print(std::ostream &out) const{
    out<<hw_;
}

std::ostream &operator<<(std::ostream &out, const prelim &s){
	s.print(out);
	return out;
}

std::ostream &operator<<(std::ostream &out, const data &d){
	d.print(out);
	return out;
}

void prelim::output_prelim_data (std::string outfile) {
    std::ofstream ofile(outfile.c_str());
    if(ofile.is_open()){
        //print something
        ofile << "something" << std::endl;
        //print other things
        char ot[] = {"other things"};
        for(int i = 0; i < 12; ++i){
            ofile << ot[i] << std::endl;
        }
        ofile.close();
    }
    else{
        std::cout<<"Unable to open output file"<<std::endl;
        exit(EXIT_FAILURE);
    }
}




