#include "Client.h"
#include <iostream>

#define CHUNK_SIZE 64

Client::Client(const char* ip, const char* port):
	skt(ip, port){}

void Client::operator()(){
	std::stringstream ss;
	while (std::cin >> ss){}
	std::string buffer = str(ss);
	int i = 0;
	while(i < ss.size()){	
		this->skt.send_message(&buffer[i], ss.size() - i < CHUNK_SIZE ?
											ss.size() - i : CHUNK_SIZE);
		i += CHUNK_SIZE;
	}
	while (this->skt.receive_message(buffer, CHUNK_SIZE)){
		std::cout << buffer;
	}
}

Client::~Client(){}