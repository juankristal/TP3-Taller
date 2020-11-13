#include "../common_src/Socket.h"

class Client{
	Socket skt;

	public:
		Client(const char* ip, const char* port);

	    /* Envia un mensaje desde stdin por Socket al servidor e
		imprime la respuesta del mismo por stdout.*/
		void operator()();

		~Client();
};
