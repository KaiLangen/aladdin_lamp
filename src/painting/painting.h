#ifndef server_farm_h
#define server_farm_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cstddef>
#include <cstdlib>

typedef enum { LINE, SQUARE, ERASE } op_name;

struct operation {
    operation(op_name n, std::vector<int> d) : name_(n), data_(d) {};
    op_name name_;
    std::vector<int> data_;
    friend std::ostream &operator<<(std::ostream& out, const operation & op);
};

class painting {
private:
	int nrows_;
	int ncols_;
	std::vector<std::vector<bool> > input_matrix_;
        std::list<operation> op_list;
public:

	painting(std::string filename);

	~painting();

	void print(std::ostream &out) const;

	void add_command(size_t sindex);

        void output_painting_data(std::string outfile);
};

std::ostream &operator<<(std::ostream &out, const painting &s);

#endif
