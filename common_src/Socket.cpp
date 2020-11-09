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
#include <sstream>
#include <iostream>

#define ACTIVO 1
#define PASIVO 0
#define ACCEPT_QUEUE_LEN 10
#define CHUNK_SIZE 64

#define MSG_ERR_CONNECT "Error en la conexion del socket\n\n"
#define MSG_ERR_BL "Error el bind del socket\n\n"
#define MSG_ERR_ACCEPT "Error al aceptar una conexion\n\n"
#define MSG_ERR_SEND "Error al enviar por socket\n\n"
#define MSG_ERR_RECV "Error al recibir por socket\n\n"
#define MSG_ERR_BIND "Error en el bind del socket\n\n"
#define MSG_ERR_LISTEN "Error en el listen del socket\n\n"
#define MSG_ERR_SETSOCKOPT "Error en el setsockopt\n\n"

int Socket::send_all(std::string &msg, size_t size){
	size_t total_sent = 0;
	while (total_sent < size){
		int sent = send(this->fd, &msg[total_sent], size - total_sent, MSG_NOSIGNAL);
		if (sent < 0) throw NetworkError(MSG_ERR_SEND);
		total_sent += sent;
	}
	return total_sent;
}

std::string Socket::receive_all(){
	int received = 1;
	char buffer[CHUNK_SIZE];
	std::stringstream ss;
	while (received){
		received = recv(this->fd, buffer, CHUNK_SIZE, 0);
		if (received < 0) throw NetworkError(MSG_ERR_RECV);
		for (int i = 0; i < received; i++) ss << buffer[i];
	}
	return ss.str();
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

void Socket::bind_to_available_port(const char* host, const char* port,
											bool is_active) {
	struct addrinfo *server_info, *server;
	this->_getaddrinfo(host, port, &server_info, is_active);
	for (server = server_info; server != NULL; server = server->ai_next) {
		this->fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
		std::cout << this->fd << "\n";
		if (this->fd == -1) continue;
		if (bind(this->fd, server->ai_addr, server->ai_addrlen) == 0){
			freeaddrinfo(server_info);
			return;
		}
	}
	freeaddrinfo(server_info);
	throw NetworkError(MSG_ERR_BIND);	
}

void Socket::connect_to_available_server(const char* host, const char* port,
											bool is_active) {
	struct addrinfo *server_info, *server;
	this->_getaddrinfo(host, port, &server_info, is_active);
	for (server = server_info; server != NULL; server = server->ai_next) {
		this->fd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
		if (this->fd == -1) continue;
		if (connect(this->fd, server->ai_addr, server->ai_addrlen) == 0){
			freeaddrinfo(server_info);
			return;
		}
	}
	freeaddrinfo(server_info);
	throw NetworkError(MSG_ERR_CONNECT);
}

void Socket::_connect(const char* host, const char* port){
	this->connect_to_available_server(host, port, ACTIVO);
}

void Socket::_bind_and_listen(const char* port) {
	this->bind_to_available_port(NULL, port, PASIVO);
	int val = 1;
	if(setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
		throw NetworkError(MSG_ERR_SETSOCKOPT);
	if(listen(this->fd, ACCEPT_QUEUE_LEN)) throw NetworkError(MSG_ERR_LISTEN);
}

Socket::Socket(const char* host, const char* port){
	_connect(host, port);
}

Socket::Socket(const char* port){
		_bind_and_listen(port);
}

Socket::Socket(int fd):
	fd(fd){}


int Socket::send_message(std::string mensaje, size_t tamanio){
	return this->send_all(mensaje, tamanio);
}

Socket Socket::accept_connection(){
	int fd = accept(this->fd, NULL, NULL);
	if (fd == -1) throw NetworkError(MSG_ERR_ACCEPT);
	return Socket(fd);
}

std::string Socket::receive_message(){
	return this->receive_all();
}

Socket::Socket(Socket&& other) {
    this->fd = std::move(other.fd);
    other.fd = -1;
}

Socket& Socket::operator=(Socket&& other) {
    this->fd = std::move(other.fd);
    return *this;
}

void Socket::kill_channel(const std::string &t){
	if (t == "r") shutdown(this->fd, SHUT_RD);
	if (t == "w") shutdown(this->fd, SHUT_WR);
}

void Socket::force_shutdown(){
	shutdown(this->fd, SHUT_RDWR);
	close(this->fd);
	this->fd = -1;
}

Socket::~Socket(){
	if (this->fd != -1){
		shutdown(this->fd, SHUT_RDWR);
		close(this->fd);
	}
}
