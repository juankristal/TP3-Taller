#ifndef __SOCKET_H
#define __SOCKET_H

#include <stddef.h>
#include <string>

class Socket{

	private:
		int fd;
		bool is_passive;
		int send_all(std::string &msg, size_t size);
		int receive_all(std::string &buffer, size_t size);
		void _getaddrinfo(const char* host, const char* port,
					struct addrinfo** server_info, int is_passive);
		void connect_to_available_server(const char* host, const char* port,
											bool is_active, bool is_binded);
		void _connect(const char* host, const char* port);
		void _bind_and_listen(const char* port);
		explicit Socket(int fd);

	public:
		Socket(const char* host, const char* port);

		explicit Socket(const char* port);

	    /*	Envia tamanio cantidad de bytes de un mensaje recibido por parametro.
		Devuelve -1 en caso de error. */

		int send_message(std::string mensaje, size_t tamanio);

		/*	Recibe un socket y acepta una conexion vinculando a other a dicha conexion.
		Devuelve -1 en caso de error. */

		Socket accept_connection();

		/*	Recibe un tamanio cantidad de bytes y los almacena en un buffer recibido por parametro.
		Devuelve la cantidad de bytes recibidos o bien -1 si hay un error. */

		int receive_message(std::string buffer, size_t tamanio);

		/*	Desconecta el socket de su direccion vinculada.
		Devuelve -1 en caso de error.  */

		~Socket();

		Socket(const Socket& other) = delete;

		Socket(Socket&& other);
    	Socket& operator=(Socket&& other);
};
#endif
