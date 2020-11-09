#include "Client.h"
#include <iostream>
#include <sstream>

#define CHUNK_SIZE 64

Client::Client(const char* ip, const char* port):
	skt(ip, port){}

void Client::operator()(){
	std::stringstream ss;
	while (std::cin >> ss.rdbuf()){}
	std::string buffer = ss.str();
	long unsigned int i = 0;
	while(i < buffer.size()){	
		this->skt.send_message(&buffer[i], buffer.size() - i < CHUNK_SIZE ?
											buffer.size() - i : CHUNK_SIZE);
		i += CHUNK_SIZE;
	}
	this->skt.kill_channel("w");
	std::cout << "Send done\n";
	std::cout << this->skt.receive_message();
}

Client::~Client(){}