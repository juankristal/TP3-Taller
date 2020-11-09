#include "Resources.h"
#include <string>

class POSTHandler{
	Resources &resources;
	public:
		explicit POSTHandler(Resources &resources);

		std::string operator()(const std::string &resource,
								const std::string &body);

		~POSTHandler();
};
