#include "Worker.h"
#include "HTTPRequestParser.h"
#include "GETHandler.h"
#include "POSTHandler.h"
#include "ERRORHandler.h"
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

#define CHUNK_SIZE 64

Worker::Worker(Socket skt, Resources &resources):
	skt(std::move(skt)),
	mIsDead(false),
	resources(resources){
		this->start();
	}

void Worker::send_message(std::string msg){
	size_t i = 0;
	while(i < msg.size()){	
		this->skt.send_message(&msg[i], msg.size() - i < CHUNK_SIZE ?
											msg.size() - i : CHUNK_SIZE);
		i += CHUNK_SIZE;
	}
}

std::string Worker::procesar_request(const std::string &command,
									const std::string &resource,
									const std::string &body){
	if (command == "GET") return GETHandler(this->resources)(resource);
	if (command == "POST") return POSTHandler(this->resources)(resource, body);
	return ERRORHandler()(command);
}

void Worker::run(){
	std::string s = this->skt.receive_message();
	HTTPRequestParser parser(s);
	std::cout << parser.getFirstLine(); // Thread safe por
										// operacion atomica
	send_message(procesar_request(parser.getCommand(),
									parser.getResource(),
									parser.getBody()));
	this->skt.kill_channel("w");
	this->mIsDead = true;
}

bool Worker::isDead(){
	return this->mIsDead;
}

Worker::~Worker(){}
