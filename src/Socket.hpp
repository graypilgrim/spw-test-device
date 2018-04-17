#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Package.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <functional>

class Socket
{
public:
	Socket(unsigned int port_no);

	void startServer(std::function<void(void)> on_client_connection);
	void receivePackage(std::function<void(Package package)> on_package_received);
	void sendPackage(const Package &package);

private:
	unsigned int port_no_ = 0;
	int socket_descriptor_;
	int client_socket_descriptor_;
	sockaddr_in socket_data_;
	sockaddr_in client_socket_data_;
};

#endif
