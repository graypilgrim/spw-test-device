#include "Logger.hpp"

#include <iostream>
#include <sstream>

#include <time.h>

Logger::Logger()
{
    file.open(FILE_NAME_, std::ofstream::out | std::ofstream::app);
}

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

	file << res.str() << std::endl;
}

Logger& Logger::instance()
{
    static Logger l;
    return l;
}
