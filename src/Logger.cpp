#include "Logger.hpp"

#include <iostream>
#include <sstream>

void Logger::logPackage(const Package &package, bool sent)
{
    std::stringstream res;

	res << package.getId() << "\t";
	res << (sent ? "S" : "R") << "\t";
	res << package.getDataLen() << "\t";
	res << (package.correct() ? "C\t" : "X\t");

	timespec time1;
    clock_gettime(CLOCK_MONOTONIC, &time1);
    res << time1.tv_sec << ":" << time1.tv_nsec;

	std::cout << res.str() << std::endl;
}
