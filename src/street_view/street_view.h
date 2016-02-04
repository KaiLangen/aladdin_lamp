#ifndef street_view_h
#define street_view_h

#include <sstream>
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <vector>
#include <numeric>

struct edge {
	int src_;
	int dst_;
	int time_;
	int length_;
	bool visited_;
	bool dead_end_;

    edge(): src_(0), dst_(0), time_(0), length_(0), visited_(false), dead_end_(false) {}
};

struct car {
	std::vector<int> history_;
	int time_left_;

    car (int t = 0): time_left_(t) {}
};

struct is_less {
    bool operator() (const edge& x, const edge& y) const{
        return x.length_ < y.length_; 
    }
};

class street_view_graph {
private:
	int njunctions_;
	int nstreets_;
	int total_time_;
	int ncars_;
	int start_;

	std::vector<std::vector<edge>* >graph_;
    std::vector<car> garage_;
public:
	int total_distance_;

	street_view_graph(std::string infile);

	~street_view_graph();
	void create_car_path();
	void drive(car& mycar);
	void run();

	void output_to_file();

	void calculate_score();
};

#endif
