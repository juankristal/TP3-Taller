#include "Client.h"
#include <iostream>
#include "../common_src/NetworkError.h"

#define ARGV_LENGHT 3
#define IP 1
#define PORT 2

int main(int argc, char const *argv[]){
	if (argc != ARGV_LENGHT) return -1;

	try {
		Client client(argv[IP], argv[PORT]);
		client();
	} catch (NetworkError &e){
		std::cerr << e.what();
		return 1;
	}
	return 0;
}
