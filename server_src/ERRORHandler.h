#include <string>

class ERRORHandler{
	public:
		ERRORHandler();

		/* Devuelve un string representando a una respuesta de error
		en base a un command */
		std::string operator()(const std::string &command);

		~ERRORHandler();
};
