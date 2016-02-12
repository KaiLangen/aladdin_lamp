#include <iostream>
#include "prelim.h"

int main(int argc, char * const argv[]){
        prelim p("input.txt");

        p.output_prelim_data("output.txt");

//        check trial("output.txt", p.nrows_, p.ncols_);
//        trial.cmp(p.starting_matrix_);

        return 0;
}
