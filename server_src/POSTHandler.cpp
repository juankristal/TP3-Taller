#include "POSTHandler.h"

#define HTTP403 "HTTP/1.1 403 FORBIDDEN\n\n"
#define HTTP402 "HTTP/1.1 200 OK\n\n"

POSTHandler::POSTHandler(Resources &resources):
	resources(resources){}

std::string POSTHandler::operator()(const std::string &resource,
									const std::string &body){
	if (resource == "/") return std::string(HTTP403);
	this->resources.write_resource(resource, body);
	return std::string(HTTP402) + body;
}

POSTHandler::~POSTHandler(){}
