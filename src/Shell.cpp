#include "Shell.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <stdexcept>

Shell::Shell(int argc, char* argv[])
{
	struct option long_options[] =
    	{
          {"port",		required_argument, 0, 'p'},
          {"directory",	required_argument, 0, 'd'},
          {0, 0, 0, 0}
        };

	int option_index = 0;
	int res = 0;

	do {
		res = getopt_long(argc, argv, "p:d:", long_options, &option_index);
		if (res == -1) break;

		switch(res)
		{
			case 'p':
				server_port_ = strtol(optarg, NULL, 0);
				break;

			case 'd':
				directory_ = optarg;
				break;

			default:
				std::string name = long_options[option_index].name;
				throw std::runtime_error("Unexpected option: " + name);

		}
	} while(res > 0);
}

void Shell::run()
{

}

