#ifndef __SOCKET_H
#define __SOCKET_H

#include <stddef.h>
#include <string>

class Socket{
	private:
		int fd;
		int send_all(std::string &msg, size_t size);
		std::string receive_all();
		void _getaddrinfo(const char* host, const char* port,
					struct addrinfo** server_info, int is_passive);
		void connect_to_available_server(const char* host, const char* port,
											bool is_active);
		void _connect(const char* host, const char* port);
		void _bind_and_listen(const char* port);
		void bind_to_available_port(const char* host, const char* port,
											bool is_active);
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

		std::string receive_message();

		/*	Desconecta el socket de su direccion vinculada.
		Devuelve -1 en caso de error.  */

		void kill_channel(const std::string &t);

		void force_shutdown();

		~Socket();

		Socket(const Socket& other) = delete;

		Socket(Socket&& other);
    	Socket& operator=(Socket&& other);
};
#endif
