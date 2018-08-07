#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <vector>

#include <cstdint>

class Package
{
public:
	static constexpr size_t MAX_PACKAGE_LEN = 16777215;
	static constexpr size_t HEADER_LEN = 16;
	static constexpr size_t DATA_CRC_LEN = 1;
	static constexpr size_t EOP_LEN = 1;

	Package() = default;
	Package(size_t data_len);
	Package(std::vector<uint8_t> data);

	const uint8_t* getRawData() const;
	std::vector<uint8_t>& getData();

	bool correct() const;
	size_t getDataLen() const;
	uint8_t getHeaderCRC() const;
	uint8_t getDataCRC() const;
	size_t getId() const;
	bool empty() const;
	size_t getPackageLen() const;

	static uint8_t calculateCRC(const uint8_t *data, size_t len);

private:
	uint8_t calculateHeaderCRC() const;
	uint8_t calculateDataCRC() const;
	void setDataLen(size_t len);
	size_t getDataCRCIndex() const;
	void setId();

	std::vector<uint8_t> raw_package_;

	static size_t counter;

	static constexpr size_t MIN_PACKAGE_LEN_= 16;
	static constexpr size_t DATA_OFFSET_ = 16;
	static constexpr size_t TRANSACTION_ID_MS_ = 5;
	static constexpr size_t TRANSACTION_ID_LS_ = 6;
	static constexpr size_t DATA_LEN_MS_ = 12;
	static constexpr size_t DATA_LEN_ = 13;
	static constexpr size_t DATA_LEN_LS_ = 14;
	static constexpr size_t HEADER_CRC_ = 15;
	static constexpr uint8_t EOP_SIGN_ = 0xf0;
};

#endif
