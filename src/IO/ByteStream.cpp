#include "../../include/IO/ByteStream.hpp"
#include <bit>
using namespace sneaky::IO;

template <typename T>
T readShortLE(uint8_t* a_buf, int& a_pos)
{
	uint16_t retval = a_buf[a_pos++];
	retval |= a_buf[a_pos++] << 8;
	return static_cast<T>(retval);
}
template <typename T>
T readShortBE(uint8_t* a_buf, int& a_pos)
{
	uint16_t retval = a_buf[a_pos++] << 8;
	retval |= a_buf[a_pos++];
	return static_cast<T>(retval);
}
template <typename T>
T readIntLE(uint8_t* a_buf, int& a_pos)
{
	uint32_t retval = a_buf[a_pos++];
	retval |= a_buf[a_pos++] << 8;
	retval |= a_buf[a_pos++] << 16;
	retval |= a_buf[a_pos++] << 24;
	return static_cast<T>(retval);
}
template <typename T>
T readIntBE(uint8_t* a_buf, int& a_pos)
{
	uint32_t retval = a_buf[a_pos++] << 24;
	retval |= a_buf[a_pos++] << 16;
	retval |= a_buf[a_pos++] << 8;
	retval |= a_buf[a_pos++];
	return static_cast<T>(retval);
}
ByteStream::ByteStream()
{
	if (std::endian::native == std::endian::little) {
		readSignedShort = [this](void) { return readShortLE<int16_t>(this->m_buf, this->m_pos); };
		readUnsignedShort = [this](void) { return readShortLE<uint16_t>(this->m_buf, this->m_pos); };
		readSignedInt = [this](void) { return readIntLE<int32_t>(this->m_buf, this->m_pos); };
		readUnsignedInt = [this](void) { return readIntLE<uint32_t>(this->m_buf, this->m_pos); };
	}
	else if (std::endian::native == std::endian::big) {
		readSignedShort = [this](void) { return readShortBE<int16_t>(this->m_buf, this->m_pos); };
		readUnsignedShort = [this](void) { return readShortBE<uint16_t>(this->m_buf, this->m_pos); };
		readSignedInt = [this](void) { return readIntBE<int32_t>(this->m_buf, this->m_pos); };
		readUnsignedInt = [this](void) { return readIntBE<uint32_t>(this->m_buf, this->m_pos); };
	}
	else {
		std::cerr << "[Error] Machine has unknown endianess";
	}
}

void ByteStream::wrap(uint8_t* a_buf, int a_size) {
	m_buf = a_buf;
	m_len = a_size;
	m_pos = 0;
}

int8_t ByteStream::readSignedByte() {
	return static_cast<int8_t>(m_buf[m_pos++]);
}
uint8_t ByteStream::readUnsignedByte() {
	return  static_cast<uint8_t>(m_buf[m_pos++]);
}

void ByteStream::skip(const int& a_amount) {
	m_pos += a_amount;
}

const int& ByteStream::getPos()
{
	return m_pos;
}

const int& ByteStream::getLen()
{
	return m_len;
}