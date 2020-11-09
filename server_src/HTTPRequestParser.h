#include <string>

class HTTPRequestParser{
	std::string text;

	public:
		HTTPRequestParser(std::string &text);

		std::string getCommand();
		std::string getResource();
		std::string getBody();
		std::string getFirstLine();

		~HTTPRequestParser();
};
