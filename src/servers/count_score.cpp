#include <iostream>
#include <fstream> 
#include <string.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#define LS 3 //numbers in line
#define P 2
#define R 3
#define NA "x"
using namespace std;

class Pools {
    public:
    vector <int> rows;
    
    Pools () {
        rows.reserve(R);

    }

    int sum_capacity (int deleted_row) {
        vector<int>::iterator it = rows.begin();
        advance(it, deleted_row);
        int ret = 0;
        accumulate(rows.begin(), it, ret);
        advance(it, 1);
        accumulate(it, rows.end(), ret);
        return ret;
    }
}

vector<int> servers({1,2,3,4,5});

int compute (string fname) {
    ifstream output;
    output.open(fname.c_str());
    string s;
    char c; 
    int server_id = 0;
    vector <Pools> data;
    data.reserve(P);
    
    
    while (output.getline(s, LS) {
        if (!strcmp(s, NA)) 
            server_id++;
            continue;
        else {
           sstream str(s);
           int row << str;
           int slot << str;
           int pool << str;
           data[pool][row] += servers[server_id];
        }

        server_id++;
    }
    return 1;

}

int main () {
    compute("output.txt") ;   
    return 0;
}
