#include "../common_src/Socket.h"

class Client{
	Socket skt;

	public:
		Client(const char* ip, const char* port);

		void operator()();

		~Client();
};
