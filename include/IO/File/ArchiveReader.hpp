#pragma once
#include "../../external/gzip/gzstream.hpp"
#include "../../external/tar/microtar.h"

#include <string>
#include <filesystem>
#include <memory>

namespace sneaky {
namespace IO {
namespace File {
	class Archive {
	public:
		Archive();
		~Archive();
		bool next();
		bool load(std::string a_filename);
		void close();
		mtar_header_t* getEntryHeader();
		std::byte* getEntryData();
	private:
		std::filesystem::path m_archive;
		gzip::igzstream m_stream;
		mtar_t m_tarball;
		mtar_header_t m_entry;
		std::byte* m_data{ nullptr };
	};
}
}
}