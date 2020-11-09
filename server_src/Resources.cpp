#include "Resources.h"
#include <iostream>

Resources::Resources(){}

void Resources::write_resource(std::string resource, std::string value){
	std::unique_lock<std::mutex> lock(this->m);
	this->recursos[std::move(resource)] = std::move(value);
}

std::string Resources::read_resource(std::string resource){
	std::unique_lock<std::mutex> lock(this->m);
	if (this->recursos.count(resource) != 1) return "";
	return this->recursos[resource];
}

Resources::~Resources(){}