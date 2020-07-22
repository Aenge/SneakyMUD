#include "../../../include/IO/File/ArchiveReader.hpp"
#include <iostream>

using namespace sneaky::IO::File;

static unsigned round_up(unsigned& n, const unsigned& incr) {
	return n + (incr - n % incr) % incr;
}

int callback_read(mtar_t* tar, void* data, unsigned int size) {
	static_cast<gzip::igzstream*>(tar->stream)->read((char*)data, size);
	if (static_cast<gzip::igzstream*>(tar->stream))
		return MTAR_ESUCCESS;

	return MTAR_EREADFAIL;
	
}

int callback_close(mtar_t* tar) {
	return MTAR_ESUCCESS;
}

void callback_ignore(mtar_t* tar, unsigned size) {
	static_cast<gzip::igzstream*>(tar->stream)->ignore(size);
}

//Used for iterating through .tar.gz archives
ArchiveReader::ArchiveReader() : m_tarball(), m_entry() {
}

ArchiveReader::~ArchiveReader() {
	close();
}

bool ArchiveReader::next() {	
	int err = mtar_read_header(&m_tarball, &m_entry);
	
	if (err == MTAR_ESUCCESS) {
		if (m_data != nullptr)
			delete m_data;

		int amount = round_up(m_entry.size, TAR_BLOCK_SIZE);
		m_data = new std::byte[amount]();
		mtar_read_data(&m_tarball, m_data, amount);

		m_datastream.wrap(m_data, m_entry.size);
		return true;
	}
	else if (err != MTAR_ENULLRECORD) {
		std::cerr << "[Error] Archive parse error in " << m_archive.filename() << std::endl;
	}
	
	close();
	return false;
}

void ArchiveReader::close() {
	m_stream.close();
	m_archive.clear();
	if (m_tarball.close != nullptr) {
		mtar_close(&m_tarball);
	}
	if (m_data != nullptr) {
		delete m_data;
		m_data = nullptr;
	}
}

mtar_header_t* ArchiveReader::getEntryHeader()
{
	return &m_entry;
}

std::byte* ArchiveReader::getEntryData()
{
	return m_data;
}

sneaky::IO::ByteStream* ArchiveReader::getDataStream()
{
	return &m_datastream;
}

bool ArchiveReader::load(const std::string& a_filename) {
	if (std::filesystem::exists(a_filename)) {
		m_archive = std::filesystem::path(a_filename);
		m_stream.open(a_filename.data());
		
		if (!m_stream.good()) {
			m_stream.close();
			m_archive.clear();
			return false;
		}

		memset(&m_tarball, 0, sizeof(m_tarball));
		m_tarball.stream = &m_stream;
		m_tarball.noseek = 1;
		m_tarball.read = &callback_read;
		m_tarball.close = &callback_close;
		m_tarball.ignore = &callback_ignore;

		return true;
	}

	return false;
}