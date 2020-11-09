#include "Worker.h"
#include "HTTPRequestParser.h"
#include <string>
#include <sstream>
#include <iostream>

#define CHUNK_SIZE 64
#define HTTP405 "HTTP 405 METHOD NOT ALLOWED\n\n"
#define HTTP403 "HTTP 403 FORBIDDEN\n\n"
#define HTTP404 "HTTP 404 NOT FOUND\n\n"
#define HTTP402 "HTTP 200 OK\n\n"

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

std::string Worker::procesar_request(std::string command, std::string resource, std::string body){
	if (command != "GET" && command != "POST")
		return std::string(HTTP405);
	if (command == "POST" && resource == "/")
		return std::string(HTTP403);
	if (command == "POST"){
		this->resources.write_resource(resource, body);
		return std::string(HTTP402) + body;
	}
	return std::string(HTTP402) + this->resources.read_resource(resource);
}

void Worker::run(){
	std::cout << "Empezando a recibir\n";
	std::string s = this->skt.receive_message();
	HTTPRequestParser parser(s);
	std::cout << parser.getFirstLine();
	std::cout.flush();
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