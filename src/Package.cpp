#include "Package.hpp"

#include "RMAPConstants.hpp"

const uint32_t* Package::getRawData()
{
	return raw_package_.get();
}

Package::~Package()
{
	raw_package_.reset();
}

TransmitPackage::TransmitPackage(size_t header_len, size_t data_len)
{
	//TODO
}

TransmitPackage::TransmitPackage(std::unique_ptr<uint32_t> raw_package)
{
	raw_package_ = std::move(raw_package);
}

size_t TransmitPackage::getHeaderLen() const
{
	//TODO
}

size_t TransmitPackage::getDataLen() const
{
	//TODO
}

ReceivePackage::ReceivePackage(size_t data_len)
{
	//TODO
}

ReceivePackage::ReceivePackage(std::unique_ptr<uint32_t> raw_package)
{
	raw_package_ = std::move(raw_package);
}

size_t ReceivePackage::getDataLen() const
{
	//TODO
}
