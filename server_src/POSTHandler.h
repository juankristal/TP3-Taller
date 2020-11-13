#include "Resources.h"
#include <string>

class POSTHandler{
	Resources &resources;
	public:
		explicit POSTHandler(Resources &resources);

		/* Devuelve un string representando a una respuesta de POST
		en base a un recurso a escribir y un cuerpo a asignar */
		std::string operator()(const std::string &resource,
								const std::string &body);

		~POSTHandler();
};
