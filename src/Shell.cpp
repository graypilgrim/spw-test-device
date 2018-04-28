#include "Shell.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

Shell::Shell(int argc, char* argv[])
{
	struct option long_options[] =
    	{
          {"port",		required_argument, 0, 'p'},
          {"log-file",	required_argument, 0, 'l'},
          {0, 0, 0, 0}
        };

	int option_index = 0;
	char res = 0;

	do {
		res = getopt_long(argc, argv, "p:l:", long_options, &option_index);
		if (res == -1) break;

		switch(res)
		{
			case 'p':
				std::cout << optarg << std::endl;
				try {
					server_port_ = std::stoul(optarg, NULL, 0);
				} catch (std::exception &e) {
					throw;
				}
				break;

			case 'l':
				std::cout << optarg << std::endl;
				log_file_name_ = optarg;
				verbosity = false;
				break;

			default:
				throw std::runtime_error("Commands parsing failed");

		}
	} while(res > 0);

	methods.emplace(help_command_, std::bind(&Shell::printHelpMessage, this, std::string{}));
	methods.emplace(send_command_, std::bind(&Shell::sendPackage, this, std::placeholders::_1));
	methods.emplace(verbose_command_, std::bind(&Shell::beVerbose, this, std::string{}));
	methods.emplace(quiet_command_, std::bind(&Shell::beQuiet, this, std::string{}));
	
}

void Shell::run()
{
	std::cout << "Starting server on port " << server_port_ << "..." << std::endl;
	socket = Socket{server_port_};
	socket.startServer([this](const Package &package){onPackageReceiving(package);});
	
	std::cout << "Client connected" << std::endl;
	
	std::string line;
	while(printPrompt(), std::getline(std::cin, line)) {
		std::istringstream iss{line};
		std::string command;
		std::string argument;

		iss >> command;
		iss >> argument;

		auto it = methods.find(command);
		if (it == methods.end()) {
			std::cout << "Invalid option. Use \"help\"." << std::endl;
			continue;
		}
		it->second(argument);
	}
}

void Shell::printPrompt() {
	std::cout <<"% " << std::flush;
}

void Shell::printHelpMessage(const std::string&) {
	//TODO
	std::cout << "helpMessage" << std::endl;
}

void Shell::sendPackage(const std::string &package_size) {
	std::cout << "sending package of size: " << package_size << "B" << std::endl;

	size_t size;
	try {
		size = std::strtoull(package_size.c_str(), NULL, 0);
	} catch (std::exception &e) {
		std::cout << "Package size must be positive number";
		return;
	}

	socket.sendPackage(Package{size});
}

void Shell::onPackageReceiving(const Package &package) {
	//TODO
	std::cout << "Shell command" <<  std::endl;
}

void Shell::onClientConnection() const{
	//TODO
}

void Shell::logPackage(const Package &package, bool sent) {
	//TODO
}

void Shell::beVerbose(const std::string&) {
	std::cout << "verbose" << std::endl;
	verbosity = true;
}

void Shell::beQuiet(const std::string&) {
	std::cout << "quiet" << std::endl;
	verbosity = false;
}

