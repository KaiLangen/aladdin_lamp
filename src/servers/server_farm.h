#ifndef server_farm_h
#define server_farm_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <cstddef>
#include <cstdlib>

struct Server {
	Server() : width_(0), cap_(0), row_(0),
	col_(0), pool_(0), was_placed_(false) {}

	size_t width_;
	size_t cap_;
	size_t row_;
	size_t col_;
	size_t pool_;
	bool was_placed_;
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
	size_t ncols_;
	size_t npools_;
	size_t nunavaiable_;
	size_t nservers_;
	std::vector<Server*> servers_;

public:

	ServerFarm(std::string filename);

	~ServerFarm();

	void print(std::ostream &out) const;

	void add_server(size_t sindex);

	void output_server_data(std::string outfile);

	size_t calculate_score(std::string file);

	size_t get_nservers(){return nservers_;};
};

std::ostream &operator<<(std::ostream &out, const ServerFarm &s);

#endif
