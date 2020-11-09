#include "Server.h"
#include <iostream>
#include <stdio.h>
#include "../common_src/NetworkError.h"
#include <string>

#define ARGV_LENGHT 3
#define PORT 1
#define ROOT_FILE 2
#define EXIT_CHAR "q"

int main(int argc, char const *argv[]){

	if (argc != ARGV_LENGHT) return -1;
	int status = 0;
	try {
		Server server(argv[PORT], argv[ROOT_FILE]);
		server();
		std::string c;
		while(c != EXIT_CHAR){
			std::getline(std::cin, c);
			std::cout << c;
		}
		server.shutdown();
		server.join();
	} catch (NetworkError &e) {
		std::cerr << e.what();
		status = 1;
	}
	return status;
}
