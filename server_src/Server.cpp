#include "Server.h"
#include "Peer.h"

Server::Server(char* port, char* root_file):
	skt(port),
	must_reap(false){
		std::stringstream ss;
		std::ifstream input(root_file);
		while(input >> ss.rdbuf()){}
		map[root_file] = ss.str();
}

void _reap(){
	std::unique_lock<std::mutex> lock(this->m);
	this->must_reap = false;
}

void Server::run(){
	this();
}

void Server::operator()(){

	while(accepting_connections){

		// realizar manejo de peer
		if (must_reap){
			_reap();
		}
	}

	for (int i = 0; i < peers.size(); i++){
		peers[i]->join();
		delete peers[i];
	}
}

void Server::write_resource(std::string resourse, std::string value){
	std::unique_lock<std::mutex> lock(this->m);
	map[resourse] = value;
}

std::string Server::read_resource(std::string resourse){
	std::unique_lock<std::mutex> lock(this->m);
	return map[resourse];
}

void Server::shutdown(){
	this->accepting_connections = false;
	this.join()
}

Server::~Server(){}
