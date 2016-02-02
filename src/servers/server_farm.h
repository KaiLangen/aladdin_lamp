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
	size_t ncols_;
	size_t npools_;
	size_t nunavaiable_;
	size_t nservers_;

public:
	std::priority_queue<Server, std::vector<Server>, cap_less> servers_;
    std::vector <Server> servers_v_;

	ServerFarm(std::string filename);

	void print(std::ostream &out) const;

	void add_server();

	void print_servers(std::ostream &out) const;
    
    void sort_dens() {
        std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_dens);
    }
 
    void sort_width() {
        std::sort(servers_v_.begin(), servers_v_.end(), Server::cmp_width);
    }
    
};

std::ostream &operator<<(std::ostream &out, const ServerFarm &s);
std::ostream &operator<<(std::ostream &out, const Server &s);

#endif
