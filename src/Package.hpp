#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <memory>

class Package
{
public:
	virtual size_t getDataLen() const = 0;
	virtual ~Package();

	const uint32_t* getRawData();

protected:
	std::unique_ptr<uint32_t> raw_package_;
};

class TransmitPackage : public Package
{
public:
	TransmitPackage(size_t header_len, size_t data_len);
	TransmitPackage(std::unique_ptr<uint32_t> raw_package);

	size_t getHeaderLen() const;
	size_t getDataLen() const override;
};

class ReceivePackage : public Package
{
public:
	ReceivePackage(size_t data_len);
	ReceivePackage(std::unique_ptr<uint32_t> raw_package);

	size_t getDataLen() const override;
};

#endif
