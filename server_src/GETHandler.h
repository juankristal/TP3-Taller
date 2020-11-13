#include "Resources.h"
#include <string>

class GETHandler{
	Resources &resources;
	public:
		explicit GETHandler(Resources &resources);

		/* Devuelve un string representando a una respuesta de GET
		en base a un resource al cual acceder*/
		std::string operator()(const std::string &resource);

		~GETHandler();
};
