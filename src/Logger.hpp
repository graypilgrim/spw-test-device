#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Package.hpp"

class Logger
{
public:
    static void logPackage(const Package &package, bool sent);
};



#endif /* end of include guard: LOGGER_HPP */
