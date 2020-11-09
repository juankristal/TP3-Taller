#include "Resources.h"
#include <string>

class GETHandler{
	Resources &resources;
	public:
		explicit GETHandler(Resources &resources);

		std::string operator()(const std::string &resource);

		~GETHandler();
};
