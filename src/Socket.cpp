#include "Socket.hpp"

#include <stdexcept>
#include <iostream>
#include <thread>

#include "Logger.hpp"

namespace
{
	enum class ReadStatus
	{
		start,
		data,
		partial_header,
		partial_data,
		read_eop,
		completed
	};
}

Socket::Socket(unsigned int port_no)
	: port_no_(port_no)
{}

void Socket::startServer(std::function<void(Package package)> on_package_received)
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

	int read_chars = 1;
	bool append = true;
	ReadStatus read_status = ReadStatus::start;
	std::vector<uint8_t> res;
	std::vector<uint8_t> buffer;
	buffer.resize(Package::MAX_PACKAGE_LEN);

	while (read_chars > 0) {
		append = true;

		switch (read_status) {
		case ReadStatus::start:
		{
			read_chars = read(client_socket_descriptor_, buffer.data(), Package::HEADER_LEN);

			if (static_cast<size_t>(read_chars) < Package::HEADER_LEN) {
				read_status = ReadStatus::partial_header;
			} else {
				if (Package{buffer}.getDataLen() == 0)
					read_status = ReadStatus::read_eop;
				else
					read_status = ReadStatus::data;
			}
		}
		break;

		case ReadStatus::data:
		{
			int expected = Package{res}.getDataLen() + Package::DATA_CRC_LEN; //TODO: static method
			read_chars = read(client_socket_descriptor_, buffer.data(), expected);

			if (read_chars < expected)
				read_status = ReadStatus::partial_data;
			else
				read_status = ReadStatus::read_eop;
		}
		break;

		case ReadStatus::partial_header:
		{
			read_chars = read(client_socket_descriptor_, buffer.data(), Package::HEADER_LEN - res.size());

			if (read_chars + res.size() == Package::HEADER_LEN)
				read_status = ReadStatus::data;
		}
		break;

		case ReadStatus::partial_data:
		{
			int expected = Package::HEADER_LEN + Package{res}.getDataLen() + Package::DATA_CRC_LEN - res.size();
			read_chars = read(client_socket_descriptor_, buffer.data(), expected);

			std::cout << "~~ " << res.size() + read_chars << " " << Package::HEADER_LEN + Package{res}.getDataLen() + Package::DATA_CRC_LEN << std::endl;
			if (res.size() + read_chars == Package::HEADER_LEN + Package{res}.getDataLen() + Package::DATA_CRC_LEN) {
				read_status = ReadStatus::read_eop;
			}
		}
		break;

		case ReadStatus::read_eop:
		{
			read_chars = read(client_socket_descriptor_, buffer.data(), 1);
			read_status = ReadStatus::completed;
		}
		break;

		case ReadStatus::completed:
		{
			on_package_received_({std::move(res)});
			res.clear();
			read_status = ReadStatus::start;
			append = false;
		}

		}

		if (append)
			res.insert(res.end(), buffer.begin(), buffer.begin() + read_chars);
	}

	if (read_chars == -1)
		throw std::runtime_error("Reading data error");

	if (read_chars == 0)
		on_package_received_({});
}

void Socket::sendPackage(const Package &package)
{
	auto sent_chars = write(client_socket_descriptor_, package.getRawData(), package.getPackageLen());

	if (sent_chars < 0)
		throw std::runtime_error("Writing data error");

	if (static_cast<size_t>(sent_chars) < package.getPackageLen()) {
		std::cerr << "Sent less data than expected.";
		std::cerr << "Sent: " << sent_chars << ", expected: " << package.getPackageLen() << std::endl;
	} else {
		Logger::instance().logPackage(package, true);
	}
}
