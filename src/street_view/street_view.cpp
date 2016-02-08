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
                getline(myfile, line); // this corrects a bug: when you read the individual inputs first, it doesn't count as a line, so we have to throw away an additional one at the start
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
				graph_[new_edge.src_]->push_back(new_edge);
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
    while(my_car.time_left_ >= 0){

        bool all_edges_visited = true;

        for(std::vector<edge>::iterator it = graph_[my_pos]->begin(); it != graph_[my_pos]->end(); ++it){
            if(!(*it).visited_){
                my_pos = (*it).dst_;
                my_car.history_.push_back(my_pos);
                (*it).visited_ = true;
                my_car.time_left_ -= (*it).time_;
                all_edges_visited = false;
                break;
            }
        }
        //check if all edges are visited
        if ( all_edges_visited ) {
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
    // when we get here, the last visited edge was over the time limit, so we remove it
    my_car.history_.pop_back();
}

void street_view_graph::run () {
    for (int i = 0; i < ncars_; i++) {
        drive(garage_[i]);
    }
}

std::ostream& operator<<(std::ostream  & os, car& c) {
    os << c.history_size() << std::endl;
    for( car::car_history_iterator it= c.history_begin(); it != c.history_end(); it++){
        os << *it << std::endl;
    }
    return os;
}


void street_view_graph::output_to_file(std::string outfile) {
    std::ofstream ofile(outfile.c_str());
    if(ofile.is_open()){
        // write total number of cars
        ofile << garage_.size() << std::endl;

        for(std::vector<car>::iterator it = garage_.begin(); it != garage_.end(); it++){
            ofile << *it << std::endl;
        }
        ofile.close();
    }
    else{
        std::cout<<"Unable to open output file"<<std::endl;
        exit(EXIT_FAILURE);
    }
}


long long int street_view_graph::calculate_score(std::string filename) {

    std::ifstream myfile(filename.c_str());
    if( !myfile.is_open() ){
		std::cerr<<"Unable to open results file"<<std::endl;
		exit(EXIT_FAILURE);
    }

    // read in number of cars
    int num_cars;
    myfile >> num_cars;

    // initialize total score and set of visited edges
    long long int total_score = 0;
    std::set<std::pair<int,int> > visited_edges;

    // for each car
    for(int car = 0; car < num_cars; ++car){
        // initialize time to 0
        int elapsed_time = 0;

        // for each edge in the car's history
        int tot_visited_junctions;
        myfile >> tot_visited_junctions;

        // get initial junction
        int old_junction;
        myfile >> old_junction;

        for (int junctions_so_far = 1; junctions_so_far < tot_visited_junctions; ++junctions_so_far){
            int current_junction;
            myfile >> current_junction;

            // try to find this edge in the graph
            std::vector<edge>::iterator it;
            it = std::find_if( graph_[old_junction]->begin(), graph_[old_junction]->end(), [&] (edge e) { return e.dst_ == current_junction; }  );

            // check if it was a valid edge
            if ( it != graph_[old_junction]->end() ) {
                // if it was never visited
                if ( std::find( visited_edges.begin(), visited_edges.end(), std::make_pair(old_junction, current_junction) ) == visited_edges.end() &&
                     std::find( visited_edges.begin(), visited_edges.end(), std::make_pair(current_junction, old_junction) ) == visited_edges.end() ) {
                    // add to total score
                    total_score += it->length_;
                    // insert in list of visited edges
                    visited_edges.insert(std::make_pair(old_junction, current_junction));
                }
                // add to total time
                elapsed_time += it->time_;
            } else {
                std::cerr << "Invalid junction!" << std::endl;
                std::cerr << "junction " << current_junction << " does not follow junction " << old_junction <<  std::endl;
                std::cerr << "visited by car " << car << " at time " << elapsed_time << std::endl;
                exit(1);
            }

            old_junction = current_junction;
        }
        // check that total car time is valid
        if ( elapsed_time > total_time_ ) {
            std::cerr << "Invalid time!" << std::endl;
            std::cerr << "total time of car " << car << " was " << elapsed_time << " which is larger than the total allowed time of " << total_time_ << std::endl;
            exit(2);
        }
    }
    // close file
    myfile.close();

    return total_score;
}
