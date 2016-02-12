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
#include <deque>

typedef enum {} e;

struct coord{
	int x_;
	int y_;
}

struct wh {
	coord pos_;
	std::vector<int> av_;
};

struct prod {
	int id_;
	int weight_;
};

struct drone {
	coord pos_;
	int cap_;
	std::vector<int> load_;

};

struct order {
	coord pos_;
	std::vector<int> req_;
};

class prelim {
private:
	std::vector<std::vector<data> > matrix_;
public:
	int nrows_;
	int ncols_;
	int ndrones_;
	int nturns_;
	int max_payload_;
	int nprods_;
	int nwarehouses_;
	int norders_;

	prelim(std::string filename);

	~prelim();

	void print(std::ostream &out) const;

	void output_prelim_data(std::string outfile);
};

std::ostream &operator<<(std::ostream &out, const prelim &p);

std::ostream &operator<<(std::ostream &out, const data &d);

#endif
