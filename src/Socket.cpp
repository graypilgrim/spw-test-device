#include "Socket.hpp"

#include <stdexcept>
#include <iostream>
#include <thread>

Socket::Socket(unsigned int port_no)
	: port_no_(port_no)
{}

void Socket::startServer(std::function<void(const Package &package)> on_package_received)
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

	on_package_received_ = std::move(on_package_received);
	reading_thread_ = std::thread(&Socket::receivePackage, this);
	reading_thread_.detach();
}

void Socket::receivePackage()
{
	std::vector<uint8_t> buffer(Package::MAX_PACKAGE_LEN);

	while (true) {
		auto read_chars = read(client_socket_descriptor_, buffer.data(), Package::MAX_PACKAGE_LEN);

		if (read_chars == -1)
			throw std::runtime_error("Reading data error");

		if (read_chars == 0) {
			on_package_received_({});
			break;
		}

		std::cout << "Received: " << read_chars << "B" << std::endl;
		on_package_received_({std::move(buffer)});
	}
}

void Socket::sendPackage(const Package &package)
{
	auto sent_chars = write(client_socket_descriptor_, package.getRawData(), package.getPackageLen());

	if (sent_chars < 0)
		throw std::runtime_error("Writing data error");

	if (static_cast<size_t>(sent_chars) < package.getPackageLen()) {
		std::cerr << "Sent less data than expected.";
		std::cerr << "Sent: " << sent_chars << ", expected: " << package.getPackageLen() << std::endl;	
	}
}

