#ifndef SHELL_HPP
#define SHELL_HPP

#include <string>

class Shell
{
public:
	Shell(int argc, char* argv[]);

	void run();

private:
	int server_port_;
	std::string directory_;
};

#endif
