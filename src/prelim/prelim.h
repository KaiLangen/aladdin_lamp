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
#include <limits>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
#include <deque>

class prelim;
class command;

enum command_type {LOAD, UNLOAD, DELIVER, WAIT};

struct command{
	int did_;
	command_type type_;
	int wid_;
	int pid_;
	int nitems_;
	command(int did, command_type type, int wid, int pid, int num):
	did_(did), type_(type), wid_(wid), pid_(pid), nitems_(num){};
	void print(std::ostream &out) const;
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
	int cap_;
	int turns_left_;
	coord pos_;
	int id_;
	std::vector<command> commands_;

	drone(int cap, int time, coord pos, int id):
		cap_(cap),turns_left_(time),pos_(pos),id_(id){}

	void add_op(int did, command_type type, int wid, int pid, int num);
	void action(int order_num, prelim& p);
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
	std::vector<drone> drones;
	std::vector<drone> dead_drones;
	std::vector<order> orders;

	prelim(std::string filename);

	~prelim();

	void print(std::ostream &out) const;

	void output_prelim_data(std::string outfile);

	void master_command();
};

std::ostream &operator<<(std::ostream &out, const command& c);

#endif
