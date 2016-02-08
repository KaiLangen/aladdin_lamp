#include "check.h"

int check::choose_op (std::string cmd) {
    if (cmd.find("PAINT_SQUARE") != std::string::npos) {
        return 3;
    }
    if (cmd.find("PAINT_LINE") != std::string::npos) {
        return 4;
    }
    if (cmd.find("ERASE_CELL") != std::string::npos) {
        return 2;
    }
    return 0;
}

void check::draw (int type_op, std::stringstream &ss) {
    if (type_op == 2) {
        int x, y;
        ss >> x;
        ss >> y;
        erase_cell(x, y);
        return;
    }

    if (type_op == 3) {
        int r, c, s;
        ss >> r;
        ss >> c;
        ss >> s;
        paint_square(r, c, s);
        return;
    }

    if (type_op == 4) {
        int x1, x2, y1, y2;
        ss >> x1;
        ss >> y1;
        ss >> x2;
        ss >> y2;
        paint_line(x1, y1, x2, y2);
    }
}

void check::paint_line (int x1, int y1, int x2, int y2) {
    if (x1 > x2 or y1 > y2) {
        std::cout << "Wrong line opeartion: first coord is greater than second" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (x1 != x2 and y1 != y2) {
        std::cout << "Wrong line opeartion: unequal coords" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (x1 == x2) {
        for (int i = y1; i <= y2; i++) {
            output_[x1][i] = true;
        }
    }
    if (y1 == y2) {
        for (int i = x1; i <= x2; i++) {
            output_[i][y1] = true;
        }
    }
}

void check::erase_cell (int x, int y) {
    output_[x][y] = false;
}

void check::paint_square (int r, int c, int s) {
   for (int i = s - r; i <= s + r; i++) {
           for (int j = s - c; j <= s + c; j++) {
                output_[i][j] = true;
           }
   }
}
check::check (std::string ofname) {
    R = 5, C = 7;
    output_.resize(R);
    for (int i =0; i < R; i++)
        output_[i].resize(C);
    std::ifstream ofile(ofname.c_str());    
    if (!ofile.is_open()) {
        std::cout<<"Unable to open input file"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    ofile >> ncommands_;
     
    std::string cmd_line;
    getline(ofile, cmd_line);
    for (int i = 0; i < ncommands_; i++) {
        getline(ofile, cmd_line);
        std::stringstream s(cmd_line);
        std::string cmd;
        s >> cmd;
        int op = choose_op(cmd);
        if (!op) {
            std::cout << "Wrong operation " << cmd << " in line " << i << std::endl;
            exit(EXIT_FAILURE);
        }
        draw(op, s);
    }

}

bool check::cmp (const std::vector < std::vector <bool> > &reference) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (output_[i][j] != reference[i][j]){
                std::cerr << "mismatch in " << i << " " << j<< std::endl;
                return false;
            }
        }
    }
    return true;
}
void check::print(std::ostream &out) const{
   for (int i = 0; i < R; i++) {
     for (int j = 0; j < C; j++) {
         out << output_[i][j] << ' ';   
     }
     out << std::endl;
   }
}

std::ostream &operator<<(std::ostream &out, const check &s){
    s.print(out);
    return out;
}

/*
 int main (int argc, char** argv) {
    check trial("output.txt");
    std::cout << trial;
    bool res = trial.cmp();
    std::cout << res << std::endl;
    return 0;
 }
 */
