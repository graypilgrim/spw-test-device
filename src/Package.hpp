#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <memory>

class Package
{
public:
	virtual ~Package() = default;

	virtual size_t getHeaderLen() const = 0;
	virtual size_t getDataLen() const = 0;
	virtual uint8_t getHeaderCRC() const = 0;
	virtual uint8_t getDataCRC() const = 0;


	const uint8_t* getRawData() const;
	uint8_t* getRawData();

protected:
	static uint8_t calculateCRC(const uint8_t *data, size_t len);

	static constexpr uint32_t WORD_OFFSET_ = 4;
	static constexpr uint32_t HEADER_LEN_OFFSET_ = 3;
	
	std::unique_ptr<uint8_t> raw_package_;
};

class TransmitPackage : public Package
{
public:
	TransmitPackage(size_t header_len, size_t data_len);
	TransmitPackage(std::unique_ptr<uint8_t> raw_package);

	size_t getHeaderLen() const override;
	size_t getDataLen() const override;
	uint8_t getHeaderCRC() const override;
	uint8_t getDataCRC() const override;

private:
	static constexpr uint32_t MAX_HEADER_LEN_ = 255;
	static constexpr uint32_t MAX_DATA_LEN_ = 16777215;
	static constexpr uint32_t MIN_PACKAGE_LEN_ = 8;
};

class ReceivePackage : public Package
{
public:
	ReceivePackage();

	size_t getHeaderLen() const override;
	size_t getDataLen() const override;
	uint8_t getHeaderCRC() const override;
	uint8_t getDataCRC() const override;

private:
	static constexpr uint32_t MAX_PACKET_SIZE_ = 16777480;

};

#endif
