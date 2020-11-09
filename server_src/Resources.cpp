#include "Resources.h"

Resources::Resources(){}

void Resources::write_resource(std::string resource, std::string &value){
	std::unique_lock<std::mutex> lock(this->m);
	this->recursos[resource] = value;
}

std::string Resources::read_resource(std::string resource){
	std::unique_lock<std::mutex> lock(this->m);
	return this->recursos[resource];
}

Resources::~Resources(){}