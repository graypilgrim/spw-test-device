#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <memory>

static constexpr int CLIENT_PORT = 1984;

int main() {
	auto socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_descriptor < 0) {
		std::cout << "Cannot open socket" << std::endl;
		return 1;
	}

	sockaddr_in socket_data;
	socket_data.sin_family = AF_INET;
	socket_data.sin_addr.s_addr = INADDR_ANY;
	socket_data.sin_port = htons(CLIENT_PORT);

	auto ret = bind(socket_descriptor, (sockaddr *) &socket_data, sizeof socket_data);
	if (ret == -1) {
		std::cout << "Cannot bind socket" << std::endl;
		return 1;
	}

	listen(socket_descriptor, 5);

	do {
		auto client_socket_data = std::make_unique<sockaddr_in>();
		unsigned int client_socket_data_len = sizeof(sockaddr_in);
		auto client_descriptor = accept(socket_descriptor, (sockaddr *) client_socket_data.get(), &client_socket_data_len);

		if (client_descriptor == -1 ) {
			std::cout << "Cannot open client socket" << std::endl;
			return 1;
		}

		unsigned char buffer[256] = {0};
		auto read_chars = read(client_descriptor, &buffer, 256);

		if (read_chars == -1) {
			std::cout << "Reading data error" << std::endl;
			return 1;
		}

		std::cout << "Received message: " << buffer << std::endl;

	} while(true);

	return 0;
}
