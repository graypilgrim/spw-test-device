#include "Shell.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "Logger.hpp"

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
				log_file_.open(optarg, std::ios::out);
				verbosity = false;
				break;

			default:
				throw std::runtime_error("Commands parsing failed");

		}
	} while(res > 0);

	methods.emplace(help_command_, [this](const std::string&) { printHelpMessage(); });
	methods.emplace(send_command_, [this](const std::string &package_size) { sendPackage(package_size); });
	methods.emplace(verbose_command_, [this](const std::string&) { beVerbose(); });
	methods.emplace(quiet_command_, [this](const std::string&) { beQuiet(); });
}

void Shell::run()
{
	std::cout << "Starting server on port " << server_port_ << "..." << std::endl;
	socket = Socket{server_port_};
	socket.startServer([this](Package package){onPackageReceiving(std::move(package));});

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
	size_t size;
	try {
		size = std::stoull(package_size.c_str());
	} catch (std::exception &e) {
		std::cout << "Package size must be positive number";
		return;
	}

	auto p = Package{size};
	// for (uint8_t it : p.getData())
	// 	std::cout << std::hex << (uint32_t)it  << std::dec << " ";
	// std::cout << std::endl;

	std::cout << "sending package of data size: " << package_size << "B" << std::endl;
	socket.sendPackage(p);
}

void Shell::onPackageReceiving(Package package) {
	if (package.empty()) {
		std::cout << "Client disconnected" << std::endl;
		exit(0);
	}

	// for (uint8_t it : package.getData())
	// 	std::cout << std::hex << (uint32_t)it  << std::dec << " ";
	// std::cout << std::endl;

	Logger::logPackage(package, false);
}

std::string Shell::logHeader() {
	return "ID\tSent/Received\tData length\tCorrectness";
}

void Shell::beVerbose(const std::string&) {
	std::cout << "verbose" << std::endl;
	verbosity = true;
}

void Shell::beQuiet(const std::string&) {
	std::cout << "quiet" << std::endl;
	verbosity = false;
}
