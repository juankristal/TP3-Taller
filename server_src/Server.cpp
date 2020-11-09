#include "Server.h"
#include "Worker.h"
#include "../common_src/NetworkError.h"
#include <sstream>
#include <fstream>
#include <iostream>

Server::Server(const char* port, const char* root_file):
	skt(port),
	accepting_connections(true){
		std::stringstream ss;
		std::ifstream input(root_file);
		while(input >> ss.rdbuf()){}
		this->resources.write_resource("/", ss.str());
}

void _reap(std::vector<Worker*> &workers){
    std::vector<Worker*>::iterator it = workers.begin();
    while (it != workers.end()) {
        if ((*it)->isDead()) {
            (*it)->join();
            delete (*it);
            it = workers.erase(it);
        } else {
            ++it;
        }
    }
}

void Server::run(){
	std::vector<Worker*> workers;
	while(accepting_connections){

		try {
			Socket peer = std::move(this->skt.accept_connection());
			workers.push_back(new Worker(std::move(peer), resources));
		} catch (const NetworkError &e) {	
			continue;
		}
		_reap(workers);
	}
	for (size_t i = 0; i < workers.size(); i++){
		workers[i]->join();
		delete workers[i];
	}
}

void Server::operator()(){
	this->start();
}

void Server::shutdown(){
	this->accepting_connections = false;
	this->skt.force_shutdown();
}

Server::~Server(){}
