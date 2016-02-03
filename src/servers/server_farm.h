#ifndef server_farm_h
#define server_farm_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <unistd.h>

struct Pair {
    unsigned int id_;
    unsigned int value_;

    Pair (int id = 0, int value = 0) {
        id_ = id;
        value_ = value;
    }
    static inline bool cmp (const Pair& a, const Pair& b) {
        return a.value_ < b.value_;
    }

	void print(std::ostream &out) const;
};

struct Server {
	size_t width_;
	size_t cap_;
    unsigned int id_;
    double dens_;
/*
    inline bool operator() (const Server& a, const Server& b) {
        return a.dens_ < b.dens_;
    }
*/    
    static inline bool cmp_dens (const Server& a, const Server& b) {
        return a.dens_ < b.dens_;
    }
    static inline bool cmp_width (const Server& a, const Server& b) {
        return a.width_ < b.width_;
    }
    static inline bool cmp_cap (const Server& a, const Server& b) {
        return a.cap_ < b.cap_;
    }
	void print(std::ostream &out) const;
};

class ServerFarm {
private:
	struct cap_less{
		bool operator() (const Server &x, const Server &y) const {
			return x.cap_ < y.cap_;
		}
	};

	std::vector<std::vector<int> > matrix_;

	size_t nrows_;
	size_t nslots_;
	size_t npools_;
	size_t nunavaiable_;
	size_t nservers_;

    // id_ = row number, value_ = number of n/a slots
    std::vector<Pair> na_slots_;
    // first free slot[row id]
    std::vector<int> first_slot_;
    // vector of (row, slot) placement for servers: output
    std::vector<Pair> placement_;
    void count_na_slots();
    double avg_cperpr_; // capacity/(pools*rows)
    double median_server_length_; 
public:
	std::priority_queue<Server, std::vector<Server>, cap_less> servers_;
    std::vector <Server> servers_v_;

	ServerFarm(std::string filename);

	void print(std::ostream &out) const;

    void print_servers(std::ostream &out) const;
    void print_placement(std::ostream &out) const;

	void add_server();
    int find_place_inrow(unsigned int row, unsigned int width);
    Pair find_place(unsigned int row, unsigned int width);
    void place_servers();
    
    void sort_dens() {
        std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_dens);
    }
 
    void sort_width() {
        std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_width);
    }
    
    void count_avg_cperpr();
    double get_avg_cperpr() {return avg_cperpr_;} 
};

std::ostream &operator<<(std::ostream &out, const ServerFarm &s);
std::ostream &operator<<(std::ostream &out, const Server &s);
std::ostream &operator<<(std::ostream &out, const Pair &s);

#endif
