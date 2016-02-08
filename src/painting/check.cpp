#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cstddef>
#include <cstdlib>
struct ops {
    static std::string psquare = "PAINT_SQUARE"; 
    static std::string pline = "PAINT_LINE"; 
    static std::string ecell = "ERASE_CELL";
};

 class check {
     private:
        //std::list<  >
        std::vector< vector<bool> > output_;
        int ncommands_;
        int choose_op (std::string cmd) {
            if (cmd.find(ops::psquare) != std::string::npos) {
                return 3;
            }
            if (cmd.find(ops::pline) != std::string::npos) {
                return 4;
            }
            if (cmd.find(ops::ecell) != std::string::npos) {
                return 2;
            }
            return 0;
        }
    public:
        void read_in (std::string ofname) {
            std::ifstream ofile(ofname.c_str());    
            if (!ofile.is_open()) {
                std::cout<<"Unable to open input file"<<std::endl;
                exit(EXIT_FAILURE);
            }
            
            ofile >> ncommands_; 
            for (int i = 0; i < ncommands_; i++) {
                ofile >> std::string cmd_line;
                int op = choose_op(cmd_line);
                if (!op) {
                    std::cout << "Wrong operation " << cmd_line << " in line " << i << std::endl;
                    exit(EXIT_FAILURE);
                }
                stringstream s(cmd_line);
                string cmd;
                s >> cmd;
                for (int i = 0; i < op; i++) {
                    s >>
                }

            }

        }

 };
