#include "../common_src/Socket.h"
#include "../common_src/Thread.h"
#include <map>

class Server: public Thread{
	Socket skt;
	bool must_reap;
	std::map<std::string, std::string> recursos;
	std::mutex m;
	std::vector<*Peer> peers;

	void _reap();

	public:
		Server(const char* port, const char* root_file);

		void run();

		void write_resource(std::string resource, std::string value);

		std::string read_resourse(std::string resource);

		void operator()();

		void shutdown();

		~Server();
};
