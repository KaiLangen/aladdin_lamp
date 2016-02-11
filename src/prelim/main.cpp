#include <iostream>
#include "prelim.h"

int main(int argc, char * const argv[]){
        prelim p("input.txt");
        std::cout<<p<<std::endl;

        p.output_prelim_data("output.txt");

//        check trial("output.txt", p.nrows_, p.ncols_);
//        trial.cmp(p.starting_matrix_);

        return 0;
}
