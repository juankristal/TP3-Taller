#ifndef __WORKER_H
#define __WORKER_H

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include "Resources.h"
#include <atomic>

class Worker: public Thread{

	Socket skt;
	std::atomic<bool> mIsDead;
	Resources &resources;
	void send_message(std::string msg);
	std::string procesar_request(std::string command,
								std::string resource, std::string body);

	public:

		Worker(Socket skt, Resources &resources);

		void run();

		bool isDead();

		~Worker();
};
#endif
