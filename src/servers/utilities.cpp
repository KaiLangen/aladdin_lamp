#include "utilities.h"

void Pair::print(std::ostream &out) const{
	out<<id_<<" " << value_ << std::endl;
}
void Server::print(std::ostream &out) const{
	out<<id_<<" " << width_ << " " << cap_ << " " << dens_ << std::endl;
}

std::ostream &operator<<(std::ostream &out, const Server &s){
	s.print(out);
	return out;
}

std::ostream &operator<<(std::ostream &out, const Pair &s){
	s.print(out);
	return out;
}
