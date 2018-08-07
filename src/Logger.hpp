#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Package.hpp"

#include <fstream>

class Logger
{
public:
    static Logger& instance();
    void logPackage(const Package &package, bool sent);

private:
    Logger();
    Logger(const Logger &) = delete;
    Logger(Logger &&) = delete;

    std::ofstream file;

    static constexpr const char* FILE_NAME_ = "/tmp/spw_test.log";
};



#endif /* end of include guard: LOGGER_HPP */
