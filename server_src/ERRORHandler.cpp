#include "ERRORHandler.h"

#define HTTP405 "HTTP/1.1 405 METHOD NOT ALLOWED\n\n"
#define UNKNOWN " es un comando desconocido\n"

ERRORHandler::ERRORHandler(){}

std::string ERRORHandler::operator()(const std::string &command){
	return std::string(HTTP405) +
						command + std::string(UNKNOWN);
}

ERRORHandler::~ERRORHandler(){}
