#include "TestingModule.hpp"

void TestingModule::packageSent()
{
	sent_time_ = std::chrono::high_resolution_clock::now();
}

std::chrono::microseconds TestingModule::packageReceived()
{
	auto n = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(n - sent_time_);
}
