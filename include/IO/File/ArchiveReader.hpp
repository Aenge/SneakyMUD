#pragma once
#include "../../external/gzip/gzstream.hpp"
#include "../../external/tar/microtar.h"
#include "../../IO/ByteStream.hpp"

#include <string>
#include <filesystem>
#include <memory>

namespace sneaky {
namespace IO {
namespace File {
	class ArchiveReader {
	public:
		ArchiveReader();
		~ArchiveReader();
		bool next();
		bool load(const std::filesystem::path& a_filename);
		void close();
		mtar_header_t* getEntryHeader();
		uint8_t* getEntryData();
		ByteStream& getDataStream();
	private:
		std::filesystem::path m_archive;
		gzip::igzstream m_stream;
		mtar_t m_tarball;
		mtar_header_t m_entry;
		uint8_t* m_data{ nullptr };
		ByteStream m_datastream;
	};
}
}
}