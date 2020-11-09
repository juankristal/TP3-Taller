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

		void write_resource(std::string resourse, std::string &value);
		std::string read_resource(std::string resourse);

		~Resources();
};
#endif
