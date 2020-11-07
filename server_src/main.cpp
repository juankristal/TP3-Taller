#include "Server.h"
#include <iostream>
#include "../common_src/NetworkError.h"

#define ARGV_LENGHT 3
#define PORT 1
#define ROOT_FILE 2

int main(int argc, char const *argv[]){

	if (argc != ARGV_LENGHT) return -1;

	Server server(argv[PORT], argv[ROOT_FILE]);
	try {
		server();
	} catch (NetworkError &e){
		std::cerr << e.what();
		return 1;
	}
	while(std::cin.getline() != 'q'){}
	return 0;
}
