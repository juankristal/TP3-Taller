#include "GETHandler.h"

#define HTTP404 "HTTP/1.1 404 NOT FOUND\n\n"
#define HTTP402 "HTTP/1.1 200 OK\n\n"
#define ROOT402 "HTTP/1.1 200 OK\nContent-Type: text/html\n\n"

GETHandler::GETHandler(Resources &resources):
	resources(resources){}

std::string GETHandler::operator()(const std::string &resource){
	std::string read = this->resources.read_resource(resource);
	if (read == "") return std::string(HTTP404);
	if (resource == "/") return std::string(ROOT402) + read;
	return std::string(HTTP402) + read;
}

GETHandler::~GETHandler(){}
