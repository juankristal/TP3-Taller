#include "Server.h"
#include <iostream>
#include <stdio.h>
#include "../common_src/NetworkError.h"

#define ARGV_LENGHT 3
#define PORT 1
#define ROOT_FILE 2

int main(int argc, char const *argv[]){

	if (argc != ARGV_LENGHT) return -1;
	int status = 0;
	try {
		Server server(argv[PORT], argv[ROOT_FILE]);
		server();
		while(getchar() != 'q'){}
		server.shutdown();
	} catch (NetworkError &e) {
		std::cerr << e.what();
		status = 1;
	}
	return status;
}
