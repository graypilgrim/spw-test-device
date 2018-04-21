#ifndef TESTING_MODULE_HPP
#define TESTING_MODULE_HPP

#include <chrono>

class TestingModule
{
public:
	void packageSent();
	std::chrono::microseconds packageReceived();

private:
	std::chrono::high_resolution_clock::time_point sent_time_;
};

#endif
