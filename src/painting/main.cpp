#include <iostream>
#include "painting.h"
#include "check.h"

int main(int argc, char * const argv[]){
        operation op1(LINE, {1,1,43,5});
        std::cout << op1;
      
        painting p("logo.in");
        std::cout << p.elem_remaining_<<std::endl;
        std::cout<<p<<std::endl;
        p.paint_horz_lines();
        p.paint_elems();
        
        std::cout<<p.elem_remaining_<<std::endl;

        p.output_painting_data("output.txt");

        check trial("output.txt");	
        trial.cmp(p.starting_matrix_);
  
        return 0;
}
