#include <utility>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "Socket.h"
#include "NetworkError.h"
#include <errno.h>
#include <stdio.h>
#include <cstring>
#include <iostream>

#define ACTIVO 0
#define PASIVO 1
#define ACCEPT_QUEUE_LEN 10

#define MSG_ERR_CONNECT "Error en la conexion del socket\n\n"
#define MSG_ERR_BL "Error el bind del socket\n\n"
#define MSG_ERR_ACCEPT "Error al aceptar una conexion\n\n"
#define MSG_ERR_SEND "Error al enviar por socket\n\n"
#define MSG_ERR_RECV "Error al recibir por socket\n\n"

int Socket::send_all(std::string &msg, size_t size){
	size_t total_sent = 0;
	while (total_sent < size){
		int sent = send(this->fd, &msg[total_sent], size - total_sent, MSG_NOSIGNAL);
		if (sent < 0) throw NetworkError(MSG_ERR_SEND);
		total_sent += sent;
	}
	return total_sent;
}

int Socket::receive_all(std::string &buffer, size_t size){
	size_t total_received = 0;
	while (total_received < size){
		int received = recv(this->fd, &buffer[total_received],
							size - total_received, 0);
		if (received < 0) throw NetworkError(MSG_ERR_RECV);
		if (received == 0) break;
		total_received += received;
	}
	return total_received;
}

void Socket::_getaddrinfo(const char* host, const char* port,
					struct addrinfo** server_info, int is_passive) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = is_passive ? AI_PASSIVE : 0;
	if (getaddrinfo(host, port, &hints, server_info)){
		throw NetworkError(MSG_ERR_CONNECT);
	}
}

void Socket::connect_to_available_server(const char* host, const char* port,
											bool is_active, bool is_binded) {
	struct addrinfo* server_info;
	this->_getaddrinfo(host, port, &server_info, is_active);
	struct addrinfo* server = server_info->ai_next;
	for (; server != NULL; server = server_info->ai_next) {
		this->fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
		if (this->fd == -1) continue;
		if (connect(this->fd, server->ai_addr, server->ai_addrlen) == 0) {
			if (is_binded) bind(this->fd, server->ai_addr, server->ai_addrlen);
			freeaddrinfo(server_info);
			return;
		}
	}
	freeaddrinfo(server_info);
	throw NetworkError(MSG_ERR_CONNECT);
}

void Socket::_connect(const char* host, const char* port){
	this->connect_to_available_server(host, port, ACTIVO, false);
}

void Socket::_bind_and_listen(const char* port) {
	this->connect_to_available_server(NULL, port, PASIVO, true);
	int val = 1;
	if(setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw NetworkError(MSG_ERR_BL);
	listen(this->fd, ACCEPT_QUEUE_LEN);
}

Socket::Socket(const char* host, const char* port):
	is_passive(false){
	_connect(host, port);
}

Socket::Socket(const char* port):
	is_passive(true){
	_bind_and_listen(port);
}

Socket::Socket(int fd):
	fd(fd),
	is_passive(false){}


int Socket::send_message(std::string mensaje, size_t tamanio){
	return this->send_all(mensaje, tamanio);
}

Socket Socket::accept_connection(){
	int fd = accept(this->fd, NULL, NULL);
	if (fd) throw NetworkError(MSG_ERR_ACCEPT);
	return Socket(fd);
}

int Socket::receive_message(std::string buffer, size_t tamanio){
	return this->receive_all(buffer, tamanio);
}

Socket::Socket(Socket&& other) {
    this->fd = std::move(other.fd);
    this->is_passive = std::move(other.is_passive);
}

Socket& Socket::operator=(Socket&& other) {
    this->fd = std::move(other.fd);
    this->is_passive = std::move(other.is_passive);
    return *this;
}

Socket::~Socket(){
	if (this->fd != -1){
		shutdown(this->fd, SHUT_RDWR);
		close(this->fd);
	}
}
