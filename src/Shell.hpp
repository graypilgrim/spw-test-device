#ifndef SHELL_HPP
#define SHELL_HPP

#include "Package.hpp"
#include "Socket.hpp"

#include <string>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <mutex>

class Shell
{
public:
	Shell(int argc, char* argv[]);

	void run();

private:
	void printPrompt();
	void printHelpMessage(const std::string& = {});
	void sendPackage(const std::string &package_size);
	void onPackageReceiving(Package package);
	std::string logHeader();
	void beVerbose(const std::string& = {});
	void beQuiet(const std::string& = {});

	unsigned int server_port_;
	bool verbosity = true;
	std::ofstream log_file_;
	std::unordered_map<std::string, std::function<void(const std::string&)>> methods;

	Socket socket;

	static constexpr const char* help_command_ = "help";
	static constexpr const char* send_command_ = "send";
	static constexpr const char* verbose_command_ = "verbose";
	static constexpr const char* quiet_command_ = "quiet";
	static constexpr const char* exit_command_ = "exit";
};

#endif
