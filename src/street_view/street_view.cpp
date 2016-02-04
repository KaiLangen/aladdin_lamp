#include "server_farm.h"
#include <algorithm>
#include <numeric>

struct edge {
	int src_;
	int dest_;
	int time_;
	int length_;
	bool was_visited_;
	bool dead_end_;
};

struct car {
	std::vector<int> history_;
	int time_left_;
};

class street_view_graph {
private:
	int njunctions_;
	int nstreets_;
	int total_time_;
	int ncars_;
	int start_;

	std::vector<std::priority_queue<edge>* >graph_;

public:
	int total_distance_;

	street_view_graph(std::string infile);

	void create_car_path();

	void output_to_file();

	void calculate_score();
};


street_view_graph(std::string infile){
	srand(time(NULL));
	std::string line;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
		myfile >> njunctions_;
		myfile >> nstreets_;
		myfile >> total_time_;
		myfile >> ncars_;
		myfile >> start_;

		graph_.resize(njunctions_);

		//who cares about coordinates?
		for(int i = 0; i < njunctions_; ++i){
			getline(myfile, line);
		}

		int directions;
		edge new_edge;
		for(int i = 0; i < nstreets_; ++i){
			myfile >> new_edge.src_;
			myfile >> new_edge.dst_;
			myfile >> directions;
			myfile >> new_edge.time_;
			myfile >> new_edge.length_;

			//if directions 1 input once, if 2 input twice
			graph_[new_edge.src_].push_back(new_edge);
			if(directions == 2){
				int temp_src = new_edge.src_;
				new_edge.src_  = new_edge.dst_;
				new_edge.dst_  = temp_src;
				graph_[new_edge.dst_].push_back(new_edge);
			}
		}

		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}

}


