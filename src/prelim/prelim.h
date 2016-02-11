#ifndef prelim_h
#define prelim_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <list>
#include <cstddef>
#include <cstdlib>

typedef enum {} e;

struct data {
    static const std::string hw_;
    void print(std::ostream &out) const;
};

class prelim {
private:
	std::vector<std::vector<data> > matrix_;
public:
	int nrows_;
	int ncols_;

	prelim(std::string filename);

	~prelim();

	void print(std::ostream &out) const;

        void output_prelim_data(std::string outfile);
};

std::ostream &operator<<(std::ostream &out, const prelim &p);

std::ostream &operator<<(std::ostream &out, const data &d);

#endif
