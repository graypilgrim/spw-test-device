#include "Socket.hpp"

#include <stdexcept>

Socket::Socket(unsigned int port_no)
	: port_no_(port_no)
{}

void Socket::startServer(std::function<void(void)> on_client_connection)
{
	socket_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor_ < 0)
		throw std::runtime_error("Cannot open socket");

	socket_data_.sin_family = AF_INET;
	socket_data_.sin_addr.s_addr = INADDR_ANY;
	socket_data_.sin_port = htons(port_no_);

	auto ret = bind(socket_descriptor_, reinterpret_cast<sockaddr*>(&socket_data_), sizeof socket_data_);
	if (ret == -1)
		throw std::runtime_error("Cannot bind socket");

	listen(socket_descriptor_, 1);

	unsigned int client_socket_data_len = sizeof(sockaddr_in);
	client_socket_descriptor_ = accept(socket_descriptor_, reinterpret_cast<sockaddr*>(&client_socket_data_), &client_socket_data_len);

		if (client_socket_descriptor_ == -1 )
			throw std::runtime_error("Cannot open client socket");
}

void Socket::receivePackage(std::function<void(Package package)> on_package_received)
{
	unsigned char buffer[256] = {0};
	auto read_chars = read(client_socket_descriptor_, &buffer, 256);

	if (read_chars == -1)
		throw std::runtime_error("Reading data error");
}

void Socket::sendPackage(const Package &package)
{

}

