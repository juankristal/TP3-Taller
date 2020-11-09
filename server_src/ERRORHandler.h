#include <string>

class ERRORHandler{
	public:
		ERRORHandler();

		std::string operator()(const std::string &command);

		~ERRORHandler();
};
