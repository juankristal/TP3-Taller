#include "Server.h"
#include "Peer.h"

Server::Server(char* port, char* root_file):
	skt(port){
		std::stringstream ss;
		std::ifstream input(root_file);
		while(input >> ss.rdbuf()){}
		map[root_file] = str(ss);
}

void Server::run(){
	this();
}

void Server::operator()(){

	while(true){

		// realizar manejo de peer

		_reap();
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

Server::~Server(){
	this.join();
}