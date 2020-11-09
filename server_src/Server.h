#ifndef __SERVER_H
#define __SERVER_H

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include "Resources.h"

class Server: public Thread{
	Socket skt;
	bool accepting_connections;
	Resources resources;

	public:
		Server(const char* port, const char* root_file);

		void run() override;

		void write_resource(std::string resource, std::string value);

		std::string read_resource(std::string resource);

		void operator()();

		void shutdown();

		~Server();
};
#endif
