#ifndef __WORKER_H
#define __WORKER_H

#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include "Resources.h"
#include <atomic>
#include <string>

class Worker: public Thread{
	Socket skt;
	std::atomic<bool> mIsDead;
	Resources &resources;

	/* Envia un mensaje por socket */
	void send_message(std::string msg);

	/* Devuelve la respuesta al cliente en base a los 
	parametros indicados */
	std::string procesar_request(const std::string &command,
								const std::string &resource,
								const std::string &body);

	public:
		Worker(Socket skt, Resources &resources);

		/* Atiende a un cliente y le envia su respuesta
		correspondiente */
		void run() override;

		/* Devuelve el estado del Worker. True si termino y
		False si aun sigue corriendo */
		bool isDead();

		~Worker();
};
#endif
