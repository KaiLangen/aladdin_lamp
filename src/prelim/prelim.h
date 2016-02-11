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
class prelim;

enum command_type {LOAD, UNLOAD, MOVE};

struct command{
	int did_;
	command_type type_;
	int wid_;
	int oid_;
	int pid_;
	int nitems_;
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
	coord pos_;
	int cap_;
    int turns_left_;
	std::vector<int> load_;
	std::vector<command> commands_history_;
        std::queue<command> immediate_pending_commands_;

	drone(int cap, coord pos){
		//start at the 0th warehouse
		pos_ = pos;
		cap_ = cap;
        turns_left_ = 0;
	}

	void add_command();

};

struct order {
	coord pos_;
	int nitems_;
	std::vector<int> req_;
        std::vector<int> delv_;

        bool is_fulfilled() {
            return
            std::accumulate(req_.begin() , req_end()) == 0 &&
            std::accumulate(delv_.begin(), delv_.end()) == nitems_;
        }
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
    
    int avail_drones_;

	std::vector<int> pweights;
	std::vector<wh> warehouses;
	std::vector<drone> drones;
	std::vector<order> orders;

	prelim(std::string filename);

	~prelim();

	void print(std::ostream &out) const;

	void output_prelim_data(std::string outfile);

    void deliver();
    order& choose_order();
    drone& choose_drone();
    void put_order (order & cur_order);
    void load_drone (drone& cur_drone, order& cur_order);
    void update_drone(drone & );
};

std::ostream &operator<<(std::ostream &out, const prelim &p);

#endif
