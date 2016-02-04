#include "street_view.h"

street_view_graph::street_view_graph(std::string infile){
	srand(time(NULL));
	std::string line;
	std::ifstream myfile(infile.c_str());
	if(myfile.is_open()){
		myfile >> njunctions_;
		myfile >> nstreets_;
		myfile >> total_time_;
		myfile >> ncars_;
		myfile >> start_;

        garage_.resize(ncars_, car(total_time_));

		graph_.resize(njunctions_);

        for(int  i = 0; i < njunctions_; ++i){
            graph_[i] = new std::vector<edge>();
        }

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
			graph_[new_edge.src_]->push_back(new_edge);
			if(directions == 2){
				int temp_src = new_edge.src_;
				new_edge.src_  = new_edge.dst_;
				new_edge.dst_  = temp_src;
				graph_[new_edge.dst_]->push_back(new_edge);
			}
		}
        for(int i = 0; i < njunctions_; ++i){
            std::sort(graph_[i]->begin(), graph_[i]->end(), is_less());
        }
		myfile.close();
	}
	else{
		std::cout<<"Unable to open input file"<<std::endl;
		exit(EXIT_FAILURE);
	}

}

street_view_graph::~street_view_graph(){
for(int  i = 0; i < njunctions_; ++i){
    delete graph_[i];
}

}

void street_view_graph::drive (car &my_car) {
    my_car.history_.push_back(start_);
    int my_pos = start_;
    while(my_car.time_left_ > 0){
        for(std::vector<edge>::iterator it = graph_[my_pos]->begin(); it != graph_[my_pos]->end(); ++it){
            if(!(*it).visited_){
                my_pos = (*it).dst_;
                my_car.history_.push_back(my_pos);
                (*it).visited_ = true;
                my_car.time_left_ -= (*it).time_;
                break;
            }
        }
        //all edges are visited
        // generate a random number
        int index = rand() % graph_[my_pos]->size();
        std::vector<edge>::iterator it = graph_[my_pos]->begin();
        std::advance(it,index);
        // visit corresponding edge in the vector
        my_pos = (*it).dst_;
        my_car.history_.push_back(my_pos);
        //(*it).visited_ = true;
        my_car.time_left_ -= (*it).time_;

    }
}

void street_view_graph::run () {
    for (int i = 0; i < ncars_; i++) {
        drive(garage_[i]);
    }
}
