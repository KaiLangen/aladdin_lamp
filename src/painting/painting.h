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

class painting {
private:

public:

	painting(std::string filename);

	~painting();

	void print(std::ostream &out) const;

	void add_server(size_t sindex);
};

std::ostream &operator<<(std::ostream &out, const painting &s);

#endif
