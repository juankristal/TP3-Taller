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
		En caso de error levanta NetworkError. */

		int send_message(std::string mensaje, size_t tamanio);

		/*	Intenta aceptar una conexion. Se devuelve el socket generado en caso de aceptarse.
		En caso de error levanta NetworkError. */

		Socket accept_connection();

		/* Recibe un mensaje hasta que se corte la comunicacion y lo devuelve.
		En caso de error levanta NetworkError. */

		std::string receive_message();

		/*	Desconecta el socket de su direccion vinculada.
		En caso de error levanta NetworkError. */

		void kill_channel(const std::string &t);

	    /* Se hace shutdown a ambos canales de comunicacion y cierra el socket. */
		void force_shutdown();

		~Socket();

		Socket(const Socket& other) = delete;

		Socket(Socket&& other);
    	Socket& operator=(Socket&& other);
};
#endif
