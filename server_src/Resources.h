#ifndef __RESOURCES_H
#define __RESOURCES_H

#include <map>
#include <string>
#include <mutex>

class Resources{
	std::mutex m;
	std::map<std::string, std::string> recursos;

	public:
		Resources();

		/* Escribe value en el resource correspondiente */
		void write_resource(std::string resource, std::string value);

		/* Devuelve el valor asignado al recurso recibido */
		std::string read_resource(std::string resource);

		~Resources();
};
#endif
