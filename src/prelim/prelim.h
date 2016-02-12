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
enum command_type {LOAD UNLOAD};

struct command{
	int did_;
	command_type type_;
	int wid_;
	int pid_;
	int nitems_;
};

struct coord{
	int x_;
	int y_;
};

struct wh {
	coord pos_;
	std::vector<int> av_;
};

struct drone {
	coord pos_;
	int cap_;
	std::vector<int> load_;
	std::vector<command> commands_;
};

struct order {
	coord pos_;
	int nitems_;
	std::vector<int> req_;
};

class prelim {
public:
	int nrows_;
	int ncols_;
	int ndrones_;
	int nturns_;
	int max_payload_;
	int nprods_;
	int nwarehouses_;
	int norders_;
	std::vector<int> pweights;
	std::vector<wh> warehouses;
	std::vector<order> orders;

	prelim(std::string filename);

	~prelim();

	void print(std::ostream &out) const;

	void output_prelim_data(std::string outfile);
};

std::ostream &operator<<(std::ostream &out, const prelim &p);

#endif
