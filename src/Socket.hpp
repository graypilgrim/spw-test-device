#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "Package.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <functional>
#include <thread>

class Socket
{
public:
	Socket() = default;
	Socket(unsigned int port_no);

	void startServer(std::function<void(Package package)> on_package_received);
	void sendPackage(const Package &package);

private:
	void receivePackage();

	unsigned int port_no_ = 0;
	int socket_descriptor_ = 0;
	int client_socket_descriptor_ = 0;
	sockaddr_in socket_data_;
	sockaddr_in client_socket_data_;
	std::function<void(const Package &package)> on_package_received_;
	std::thread reading_thread_;
};

#endif
