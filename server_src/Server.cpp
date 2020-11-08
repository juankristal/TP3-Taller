#include "Server.h"
#include "Worker.h"
#include <sstream>
#include <fstream>

Server::Server(const char* port, const char* root_file):
	skt(port),
	accepting_connections(true){
		std::stringstream ss;
		std::ifstream input(root_file);
		while(input >> ss.rdbuf()){}
		this->resources.write_resource(std::string("/"), ss.str());
		this->start();
}

void Server::run(){
	std::vector<Worker*> workers;
	Resources resources;
	while(accepting_connections){

		workers.push_back(new Worker(this->skt.accept_connection(), resources));
		for (size_t i = 0; i < workers.size(); i++){
			if (workers[i]->isDead()){
				workers[i]->join();
				delete workers[i];
			}
		}
	}
	for (size_t i = 0; i < workers.size(); i++){
		workers[i]->join();
		delete workers[i];
	}
}

void Server::operator()(){
	this->run();
}

void Server::shutdown(){
	this->accepting_connections = false;
	this->join();
}

Server::~Server(){}
