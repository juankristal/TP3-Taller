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
	while (this->skt.receive_message(buffer, CHUNK_SIZE)){
		std::cout << buffer;
	}
}

Client::~Client(){}