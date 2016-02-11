#ifndef check_h
#define check_h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cstddef>
#include <cstdlib>
class check {
     private:
        std::vector< std::vector<bool> > output_;
        int ncommands_;
        int R, C;

        int choose_op (std::string cmd) ;

        void draw (int type_op, std::stringstream &ss) ;

        void paint_line (int x1, int y1, int x2, int y2) ;

        void erase_cell (int x, int y) ;

        void paint_square (int r, int c, int s) ;

    public:
       check (std::string ofname, int r, int c) ;

       bool cmp (const std::vector < std::vector <bool> > &reference) ;

       void print(std::ostream &out) const;
 };

std::ostream &operator<<(std::ostream &out, const check &s);

#endif
