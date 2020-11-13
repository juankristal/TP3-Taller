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

		/* Acepta conexiones a clientes de forma concurrente
		y las ejecuta */
		void run() override;

		void operator()();

		/* Apaga al servidor. El servidor no se termina de apagar
		hasta que terminen de ejecutarse los clientes remanentes */
		void shutdown();

		~Server();
};
#endif
