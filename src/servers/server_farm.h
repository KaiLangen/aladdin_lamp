#ifndef server_farm_h
#define server_farm_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstddef>
#include <cstdlib>

struct Server {
	size_t width_;
	size_t cap_;
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

public:
	std::priority_queue<Server, std::vector<Server>, cap_less> servers_;

	ServerFarm(std::string filename);

	void print(std::ostream &out) const;

	void add_server();
};

std::ostream &operator<<(std::ostream &out, const ServerFarm &s);

#endif
