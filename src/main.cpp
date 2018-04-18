#include "Shell.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Hello world" << std::endl;

	Shell sh{argc, argv};
	sh.run();
}
