#ifndef utilities_h
#define utilities_h

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
    int id_;
    int value_;

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
    //sort in decreasing order
    static inline bool cmp_cap (const Server& a, const Server& b) {
        return a.cap_ > b.cap_;
    }
	void print(std::ostream &out) const;
};

std::ostream &operator<<(std::ostream &out, const Server &s);
std::ostream &operator<<(std::ostream &out, const Pair &s);

#endif
